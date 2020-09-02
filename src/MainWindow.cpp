#include "MainWindow.h"

MainWindow::MainWindow(ros::NodeHandle *node, QWidget *parent) : BaseWindow(node, parent) {
    //系统变量初始化
    SysVarInit();
    //初始化rostopic
    initRosToptic();
    //信号与槽绑定
    signalAndSlot();
}

MainWindow::~MainWindow() {

}

void MainWindow::initRosToptic() {

    fsmCmd_client = Node->serviceClient<hirop_msgs::taskInputCmd>("/VoiceCtlRob_TaskServerCmd");
    RobReset_client = Node->serviceClient<hsr_rosi_device::ClearFaultSrv>("/clear_robot_fault");
    RobEnable_client = Node->serviceClient<hsr_rosi_device::SetEnableSrv>("/set_robot_enable");
    RobSetMode_client = Node->serviceClient<hsr_rosi_device::setModeSrv>("/set_mode_srv");

    robStatus_subscriber=Node->subscribe<industrial_msgs::RobotStatus>("robot_status",1,boost::bind(&MainWindow::callback_robStatus_subscriber,this,_1));
    fsmState_subscriber=Node->subscribe<hirop_msgs::taskCmdRet>("/VoiceCtlRob_state",1,boost::bind(&MainWindow::callback_fsmState_subscriber,this,_1));
    personImg_subcriber=Node->subscribe<sensor_msgs::Image>("videphoto_feedback",1,boost::bind(&MainWindow::callback_peopleDetectImg_subscriber, this, _1));

}

void MainWindow::SysVarInit() {
    //监视对象
    devDetectorList.push_back(&RobConn_Detector);
    devDetectorList.push_back(&forceConn_Detector);
    devDetectorList.push_back(&kinectConn_Detector);
    devDetectorList.push_back(&d435iConn_Detector);
    devDetectorList.push_back(&handGrawConn_Detector);

    devDetectorList.push_back(&robNormal_Detector);
    devDetectorList.push_back(&robServo_Detector);
    devDetectorList.push_back(&fsmbridge_Detector);
    devDetectorList.push_back(&voiceNode_Detector);
    devDetectorList.push_back(&dmbridge_Detector);
    devDetectorList.push_back(&planbridge_Detector);
    devDetectorList.push_back(&motionbridge_Detector);
    devDetectorList.push_back(&forceNode_Detector);
    devDetectorList.push_back(&forcebridge_Detector);
    devDetectorList.push_back(&shakeHandJudge_Detector);

    in_nodeNameList.push_back("/dm_bridge");
    in_nodeNameList.push_back("/force_bridge");
    in_nodeNameList.push_back("/hscfsm_bridge");
    in_nodeNameList.push_back("/motion_bridge");
    in_nodeNameList.push_back("/trajectory_planner");
    in_nodeNameList.push_back("/shakeHandJudge");

    fsmStateList.push_back(init_fsmstate);
    fsmStateList.push_back(prepare_fsmstate);
    fsmStateList.push_back(detect_fsmstate);
    fsmStateList.push_back(shakehand_fsmstate);
    fsmStateList.push_back(wave_fsmstate);
    fsmStateList.push_back(homepoint_fsmstate);
    fsmStateList.push_back(dealErr_fsmstate);
    fsmStateList.push_back(exit_fsmstate);

    Timer_listenStatus = new QTimer(this);
    Timer_listenStatus->setInterval(1000);
    Timer_listenNodeStatus = new QTimer(this);
    Timer_listenNodeStatus->setInterval(1000);


}

void MainWindow::signalAndSlot()
{
    //主界面
    connect(btn_tabmain_devConn,&QPushButton::clicked,this,&MainWindow::slot_btn_tabmain_devConn);
    connect(btn_tabmain_sysStop,&QPushButton::clicked,this,&MainWindow::slot_btn_tabmain_sysStop);
    connect(btn_tabmain_sysReset,&QPushButton::clicked,this,&MainWindow::slot_btn_tabmain_sysReset);
    //声控握手页面
    connect(btn_tabvoiceSH_run,&QPushButton::clicked,this,&MainWindow::slot_btn_tabvoiceSH_run);
    connect(btn_tabvoiceSH_normalstop,&QPushButton::clicked,this,&MainWindow::slot_btn_tabvoiceSH_normalstop);
    connect(btn_tabvoiceSH_quickstop,&QPushButton::clicked,this,&MainWindow::slot_btn_tabvoiceSH_quickstop);
    //手动握手页面
    connect(btn_tabstepSH_beginshakehand,&QPushButton::clicked,this,&MainWindow::slot_btn_tabstepSH_beginshakehand);
    connect(btn_tabstepSH_endshakehand,&QPushButton::clicked,this,&MainWindow::slot_btn_tabstepSH_endshakehand);
    connect(btn_tabstepSH_stop,&QPushButton::clicked,this,&MainWindow::slot_btn_tabstepSH_stop);
    //调试页面
    connect(btn_rbSetEnable,&QPushButton::clicked,this,&MainWindow::slot_btn_rbSetEnable);
    connect(btn_rbReset,&QPushButton::clicked,this,&MainWindow::slot_btn_rbReset);
    connect(btn_gripper_open,&QPushButton::clicked,this,&MainWindow::slot_btn_gripper_open);
    connect(btn_gripper_close,&QPushButton::clicked,this,&MainWindow::slot_btn_gripper_close);
    connect(btn_rbGoHomePose,&QPushButton::clicked,this,&MainWindow::slot_btn_rbGoHomePose);
    //日志页面
    connect(btn_tab_recoder_ouputRecorder,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_recoder_ouputRecorder);
    connect(btn_tab_recoder_clearRecorder,&QPushButton::clicked,this,&MainWindow::slot_btn_tab_recoder_clearRecorder);

    qRegisterMetaType<vector<QLabel*>>("VQLABLE");
    qRegisterMetaType<infoLevel>("infoLevel");
//    connect(this, SIGNAL(emitLightColor(vector<QLabel*> ,int,String)), this,SLOT(showLightColor(vector<QLabel*> ,int,String)));  //将自定义槽连接到自定义信号
    connect(this, &MainWindow::emitLightColor,this, &MainWindow::showLightColor);
    connect(this, SIGNAL(emitQmessageBox(infoLevel ,QString)), this,SLOT(showQmessageBox(infoLevel,QString)),Qt::QueuedConnection);  //将自定义槽连接到自定义信号
    connect(Timer_listenStatus, &QTimer::timeout, this, &MainWindow::slot_timer_updateStatus);
    connect(Timer_listenNodeStatus, &QTimer::timeout, this, &MainWindow::slot_timer_listenNodeStatus);

    Timer_listenStatus->start();
    Timer_listenNodeStatus->start();
}

void MainWindow::callback_robStatus_subscriber(const industrial_msgs::RobotStatus::ConstPtr robot_status) {
    RobConn_Detector.lifeNum=100;
    RobConn_Detector.status= true;
    if(robot_status->in_error.val==0){
        robNormal_Detector.lifeNum=100;
        robNormal_Detector.status= true;
    } else{
        robNormal_Detector.status= false;
    }
    if(robot_status->drives_powered.val==1){
        robServo_Detector.lifeNum=100;
        robServo_Detector.status= true;
    } else{
        robServo_Detector.status= false;
    }
}

void MainWindow::callback_peopleDetectImg_subscriber(const sensor_msgs::Image_<allocator<void>>::ConstPtr &msg) {
    //如果标志为关闭行人检测
    // if(!flag_switchPersonDecBtnText){
    //     return;
    // }
    const cv_bridge::CvImageConstPtr &ptr = cv_bridge::toCvShare(msg, "bgr8");
    cv::Mat mat = ptr->image;
    QImage qimage = cvMat2QImage(mat);
    QPixmap tmp_pixmap = QPixmap::fromImage(qimage);
    QPixmap new_pixmap = tmp_pixmap.scaled(label_tabvoiceSH_image->width(), label_tabvoiceSH_image->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
//    QPixmap tmp_pixmap = pixmap1.scaled(label_picture1->width(), label_picture1->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    label_tabvoiceSH_image->setPixmap(new_pixmap);
}
void MainWindow::callback_forceSensor_subscriber(geometry_msgs::Wrench msg){
    forceNode_Detector.lifeNum=100;
    forceNode_Detector.status= true;
}


//监听系统各设备状态
void MainWindow::slot_timer_updateStatus() {
    for (auto detector : devDetectorList)
    {
        if (detector->lifeNum > 0)
        {
            detector->lifeNum -= 50;
        } else
        {
            detector->lifeNum = 0;
            detector->status = false;
        }
        //刷新检测器标签状态
        if (detector->status)
        {
            emit emitLightColor(detector->lableList_showStatus, detector->showType,"green");
        } else
        {
            emit emitLightColor(detector->lableList_showStatus, detector->showType,"red");
        }
    }
}

void MainWindow::slot_timer_listenNodeStatus(){
     std::vector<bool > out_nodeIsAlive;
    checkNodeAlive(in_nodeNameList,out_nodeIsAlive);
    if(out_nodeIsAlive[0]){
        dmbridge_Detector.lifeNum=100;
        dmbridge_Detector.status=true;
    }
    if(out_nodeIsAlive[1]){
        forcebridge_Detector.lifeNum=100;
        forcebridge_Detector.status=true;
    }
    if(out_nodeIsAlive[2]){
        fsmbridge_Detector.lifeNum=100;
        fsmbridge_Detector.status=true;
    }
    if(out_nodeIsAlive[3]){
        motionbridge_Detector.lifeNum=100;
        motionbridge_Detector.status=true;
    }
    if(out_nodeIsAlive[4]){
        planbridge_Detector.lifeNum=100;
        planbridge_Detector.status=true;
    }
    if(out_nodeIsAlive[5]){
        shakeHandJudge_Detector.lifeNum=100;
        shakeHandJudge_Detector.status=true;
    }
}


void MainWindow::showLightColor(vector<QLabel*> label_list,int showType, string color) {

    switch (showType){
        case 0:
            if(color=="red")
            {
                for(auto label:label_list){
                    label->setPixmap(fitpixmap_redLight);
                }
            } else if(color=="green")
            {
                for(auto label:label_list) {
                    label->setPixmap(fitpixmap_greenLight);
                }
                            }
            break;
        case 1:
            if(color=="red")
            {
                for(auto label:label_list)
                {
                    label->setStyleSheet("background: rgb(255,0,0)");
                }
            } else if(color=="green")
            {
                for(auto label:label_list)
                {
                    label->setStyleSheet("background: rgb(0,255,0)");
                }
            }
            break;
    }


}

void MainWindow::checkNodeAlive(const std::vector<std::string>& in_nodeNameList, std::vector<bool >& out_nodeIsAlive){
    if(in_nodeNameList.size()==0)
    {
        return;
    }
    std::vector<bool > tmp_nodeIsAlive(in_nodeNameList.size());
    fill(tmp_nodeIsAlive.begin(),tmp_nodeIsAlive.end(), false);
    ros::V_string curAliveNodes;
    ros::master::getNodes(curAliveNodes);
    for (auto curNodeName :curAliveNodes)
    {
        for (int i = 0; i <in_nodeNameList.size(); ++i)
        {
            if(curNodeName==in_nodeNameList[i])
            {
                tmp_nodeIsAlive[i]= true;
            }
        }
    }
    out_nodeIsAlive=tmp_nodeIsAlive;
}

void MainWindow::slot_btn_tabmain_devConn() {
    if(!startUpFlag_devconn){
        startUpFlag_devconn= true;
        system("rosrun handrb_ui devConn.sh &");
    } else{
        emit emitQmessageBox(infoLevel::warning,QString("请不要重复连接设备!"));
    }

}

void MainWindow::slot_btn_tabmain_sysStop() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= false;
    RobEnable_client.call(srv);
}

void MainWindow::slot_btn_tabmain_sysReset() {
    system("rosrun openni2_tracker voice_shutdown.sh &");
    system("rosrun openni2_tracker vision_shutdown.sh &");
    system("rosnode kill $(rosnode list |grep -v handrb_ui)");
    startUpFlag_devconn= false;
}

void MainWindow::slot_btn_tabvoiceSH_run() {
    hirop_msgs::taskInputCmd srv;
    srv.request.taskName="VoiceCtlRob";
    srv.request.behavior="start";
    if(!fsmCmd_client.call(srv))
    {
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void MainWindow::slot_btn_tabvoiceSH_normalstop() {
    hirop_msgs::taskInputCmd srv;
    srv.request.taskName="VoiceCtlRob";
    srv.request.behavior="toExit";
    if(!fsmCmd_client.call(srv))
    {
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void MainWindow::slot_btn_tabvoiceSH_quickstop() {
    //1.首先下使能
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= false;
    RobEnable_client.call(srv);
    //2.再进行状态退出
    hirop_msgs::taskInputCmd srv_Cmd;
    srv_Cmd.request.taskName="VoiceCtlRob";
    srv_Cmd.request.behavior="toExit";
    if(!fsmCmd_client.call(srv_Cmd))
    {
        emit emitQmessageBox(infoLevel::warning,QString("状态机服务连接失败!"));
    }
}

void MainWindow::slot_btn_tabstepSH_beginshakehand() {

}

void MainWindow::slot_btn_tabstepSH_endshakehand() {

}

void MainWindow::slot_btn_tabstepSH_stop() {

}

void MainWindow::slot_btn_rbSetEnable() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= true;
    RobEnable_client.call(srv);
}

void MainWindow::slot_btn_rbReset() {
    hsr_rosi_device::ClearFaultSrv srv;
    RobReset_client.call(srv);
}

void MainWindow::slot_btn_gripper_open() {

}

void MainWindow::slot_btn_gripper_close() {

}

void MainWindow::slot_btn_rbGoHomePose() {

}

void MainWindow::slot_btn_tab_recoder_ouputRecorder() {

}

void MainWindow::slot_btn_tab_recoder_clearRecorder() {

}

void MainWindow::showQmessageBox(infoLevel level, QString info) {
    switch (level){
        case infoLevel ::information:
            QMessageBox::information(this,"提示",info,QMessageBox::Ok);break;
        case infoLevel ::warning:
            QMessageBox::warning(this,"警告",info,QMessageBox::Ok);break;
    }
}

void MainWindow::callback_fsmState_subscriber(const hirop_msgs::taskCmdRet::ConstPtr msg) {
    cout<<msg->behevior<<endl;
    if(msg->behevior=="initing"){
        for (auto fsmstate : fsmStateList) {
            if(fsmstate.stateName==msg->state){
                fsmstate.lableList_showStatus->setStyleSheet("background: rgb(0,255,0)");
            }
        }
    }
    if(msg->behevior=="quiting"){
        for (auto fsmstate : fsmStateList) {
            if(fsmstate.stateName==msg->state){
                fsmstate.lableList_showStatus->setStyleSheet("background: rgb(255,0,0)");
            }
        }
    }

}

QImage MainWindow::cvMat2QImage(const cv::Mat &mat) {
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
//        image.setNumColors(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
        // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        return QImage();
    }
}