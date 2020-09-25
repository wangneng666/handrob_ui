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
    fsmState_subscriber=Node->subscribe<hirop_msgs::taskCmdRet>("/VoiceCtlRob_state",1000,boost::bind(&MainWindow::callback_fsmState_subscriber,this,_1));
    personImg_subcriber=Node->subscribe<sensor_msgs::Image>("videphoto_feedback",1,boost::bind(&MainWindow::callback_peopleDetectImg_subscriber, this, _1));
    personImg_subcriber=Node->subscribe<sensor_msgs::Image>("/usb_cam/image_raw",1,boost::bind(&MainWindow::callback_peopleDetectImg_subscriber, this, _1));
    kinect2_subcriber=Node->subscribe<sensor_msgs::Image>("TOTOTOOTOTTO",1,boost::bind(&MainWindow::callback_kinect2_subscriber, this, _1));
    forceSensor_subscriber=Node->subscribe<geometry_msgs::Wrench>("/daq_data",1,boost::bind(&MainWindow::callback_forceSensor_subscriber, this, _1));
    d435iImagRes_subcriber=Node->subscribe<sensor_msgs::Image>("/camera_base/color/image_raw",1,boost::bind(&MainWindow::callback_d435iImagRes_subcriber, this, _1));

    shakeEnd_pub=Node->advertise<hirop_msgs::shakeHandStatus>("/shakeHandJudge/Status",1000);
    voiceOrder_pub=Node->advertise<std_msgs::Int16>("/voice_order",1);
    listenToExit_pub=Node->advertise<std_msgs::Int16>("/listen_toexit",1);
}

void MainWindow::SysVarInit() {
    //连接状态监控
    vector<string> devDetectorName\
    {"rbConn_Detector","rbIsWell_Detector","rbEnable_Detector","versionBridge_Detector","forceSensor_Detector",
     "d435iConn_Detector","kinect2Conn_Detector","forceBridge_Detector","pickPlaceBridge_Detector","fsmNode_Detector",
     "shakeJudge_Detector","dmBridge_Detector","plannerBridge_Detector","motionBridge_Detector","perceptionBridge_Detector"
    };
    vector<vector<QLabel*>> devDetectorShowLable\
    {{label_tabmain_rbConn},{label_tabmain_rbIsWell},{label_tabmain_rbEnable},{label_tabmain_versionBridge},{label_tabmain_forceSensor},
     {label_tabmain_d435iConn},{label_tabmain_kinect2Conn},{label_tabmain_forcebridge},{label_tabmain_pickPlaceBridge},{label_tabmain_fsmBridge},
     {label_tabmain_shakehandJudge},{label_tabmain_dmBridge},{label_tabmain_plannerBridge},{label_tabmain_motionBridge},{label_tabmain_perceptionBridge}
    };
    for (size_t i = 0; i <devDetectorName.size(); ++i) {
        map_devDetector.insert(pair<string ,devDetector*>(devDetectorName[i],new devDetector{devDetectorName[i],0,true,false,devDetectorShowLable[i]}));
    }
    //状态机状态监控
    vector<string> fsmStateName\
    {
            "init","prepare","detection","shakehand",
            "wave","detectToy","error","exit",
    };
    vector<QLabel*> fsmStateShowLable\
    {
            label_tabvoiceSH_initstate,label_tabvoiceSH_preparestate,label_tabvoiceSH_detectstate,label_tabvoiceSH_shakehandstate,
            label_tabvoiceSH_wavestate,label_tabvoiceSH_detectToystate,label_tabvoiceSH_errstate,label_tabvoiceSH_exitstate
    };
    for (size_t i = 0; i <fsmStateName.size(); ++i) {
        map_fsmState.insert(pair<string ,fsmState*>(fsmStateName[i],new fsmState{fsmStateName[i],false,fsmStateShowLable[i]}));
    }
    //节点名字监控
    vector<string > nodeName\
    {
        "/vision_bridge","force_bridge","/pickplace_bridge",
        "/hscfsm_bridge","/shakeHandJudge","/dm_bridge",
        "/trajectory_planner","/motion_bridge","/perception_bridge"
    };
    for (const auto & j : nodeName) {
        in_nodeNameList.push_back(j);
    }
    //初始化状态机颜色标签
    for (auto &fsmstate : map_fsmState) {
        lableShowImag(fsmstate.second->lableList_showStatus,Qt::lightGray);
    }
    Timer_listenStatus = new QTimer(this);
    Timer_listenStatus->setInterval(1000);
    Timer_listenNodeStatus = new QTimer(this);
    Timer_listenNodeStatus->setInterval(1000);

}

void MainWindow::signalAndSlot()
{
    //主界面
    connect(btn_tabmain_devConn,&QPushButton::clicked,this,&MainWindow::slot_btn_tabmain_devConn);
    connect(btn_tabmain_beginRun,&QPushButton::clicked,this,&MainWindow::slot_btn_tabmain_beginRun);
    connect(btn_tabmain_sysStop,&QPushButton::clicked,this,&MainWindow::slot_btn_tabmain_sysStop);
    connect(btn_tabmain_sysReset,&QPushButton::clicked,this,&MainWindow::slot_btn_tabmain_sysReset);
    //声控握手页面
    connect(btn_tabvoiceSH_run,&QPushButton::clicked,this,&MainWindow::slot_btn_tabvoiceSH_run);
    connect(btn_tabvoiceSH_normalstop,&QPushButton::clicked,this,&MainWindow::slot_btn_tabvoiceSH_normalstop);
    connect(btn_tabvoiceSH_grabToy,&QPushButton::clicked,this,&MainWindow::slot_btn_tabvoiceSH_grabToy);
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

//    qRegisterMetaType<vector<QLabel*>>("VQLABLE");
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
    map_devDetector["rbConn_Detector"]->lifeNum=100;
    map_devDetector["rbConn_Detector"]->status= true;
    if(robot_status->in_error.val==0){
        map_devDetector["rbIsWell_Detector"]->lifeNum=100;
        map_devDetector["rbIsWell_Detector"]->status= true;
    } else{
        map_devDetector["rbIsWell_Detector"]->status= false;
    }
    if(robot_status->drives_powered.val==1){
        map_devDetector["rbEnable_Detector"]->lifeNum=100;
        map_devDetector["rbEnable_Detector"]->status= true;
    } else{
        map_devDetector["rbEnable_Detector"]->status= false;
    }
}

void MainWindow::callback_peopleDetectImg_subscriber(const sensor_msgs::Image_<allocator<void>>::ConstPtr &msg) {
    const cv_bridge::CvImageConstPtr &ptr = cv_bridge::toCvShare(msg, "bgr8");
    cv::Mat mat = ptr->image;
    QImage qimage = cvMat2QImage(mat);
    QPixmap tmp_pixmap = QPixmap::fromImage(qimage);
    QPixmap new_pixmap = tmp_pixmap.scaled(msg->width, msg->height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
//    QPixmap tmp_pixmap = pixmap1.scaled(label_picture1->width(), label_picture1->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    label_tabvoiceSH_image->setPixmap(new_pixmap);
}

void MainWindow::callback_forceSensor_subscriber(const geometry_msgs::Wrench::ConstPtr msg){
    map_devDetector["forceSensor_Detector"]->lifeNum=100;
    map_devDetector["forceSensor_Detector"]->status= true;
}

//监听系统各设备状态
void MainWindow::slot_timer_updateStatus() {
    for (auto &detector : map_devDetector)
    {
        if(detector.second->real_time)
        {
            if (detector.second->lifeNum > 0) {
                detector.second->lifeNum -= 50;
            } else {
                detector.second->lifeNum = 0;
                detector.second->status = false;
            }
            //刷新检测器标签状态
            if (detector.second->status) {
                emit emitLightColor(detector.second->lableList_showStatus, "green");
            } else {
                emit emitLightColor(detector.second->lableList_showStatus, "red");
            }
        }
    }
}

void MainWindow::slot_timer_listenNodeStatus(){
    std::vector<bool > out_nodeIsAlive;
    checkNodeAlive(in_nodeNameList,out_nodeIsAlive);
    if(out_nodeIsAlive[0]){
        map_devDetector["versionBridge_Detector"]->lifeNum=100;
        map_devDetector["versionBridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[1]){
        map_devDetector["forceBridge_Detector"]->lifeNum=100;
        map_devDetector["forceBridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[2]){
        map_devDetector["pickPlaceBridge_Detector"]->lifeNum=100;
        map_devDetector["pickPlaceBridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[3]){
        map_devDetector["fsmNode_Detector"]->lifeNum=100;
        map_devDetector["fsmNode_Detector"]->status=true;
    }
    if(out_nodeIsAlive[4]){
        map_devDetector["shakeJudge_Detector"]->lifeNum=100;
        map_devDetector["shakeJudge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[5]){
        map_devDetector["dmBridge_Detector"]->lifeNum=100;
        map_devDetector["dmBridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[6]){
        map_devDetector["plannerBridge_Detector"]->lifeNum=100;
        map_devDetector["plannerBridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[7]){
        map_devDetector["motionBridge_Detector"]->lifeNum=100;
        map_devDetector["motionBridge_Detector"]->status=true;
    }
    if(out_nodeIsAlive[8]){
        map_devDetector["perceptionBridge_Detector"]->lifeNum=100;
        map_devDetector["perceptionBridge_Detector"]->status=true;
    }

}

void MainWindow::showLightColor(vector<QLabel*> label_list, string color) {
    if(color=="red")
    {
        for(auto label:label_list)
        {
            lableShowImag(label,Qt::red);
        }
    } else if(color=="green")
    {
        for(auto label:label_list)
        {
            lableShowImag(label,Qt::green);
        }
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
        for (size_t i = 0; i <in_nodeNameList.size(); ++i)
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

void MainWindow::slot_btn_tabmain_beginRun(){
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= true;
    RobEnable_client.call(srv);
    if(!map_devDetector["shakeJudge_Detector"]->status){
        cout<<"打开握手计算节点"<<endl;
        system("rosrun force_bridge shakeHandJudge &");
    }
    sleep(1);
    if(!map_devDetector["forceBridge_Detector"]->status){
        cout<<"打开握手节点"<<endl;
        system("roslaunch force_bridge bring_up_realRobot.launch &");
    }
}


void MainWindow::slot_btn_tabmain_sysStop() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= false;
    RobEnable_client.call(srv);
}

void MainWindow::slot_btn_tabmain_sysReset() {
//    system("rosrun openni2_tracker voice_shutdown.sh &");
//    system("rosrun openni2_tracker vision_shutdown.sh &");
    std::thread t([&]{
        btn_tabmain_sysReset->setEnabled(false);
        system("rosnode kill $(rosnode list |grep -v handrb_ui ) &");
        sleep(5);
        cout<<"5s休眠完"<<endl;
        system("kill -9 $(ps -ef | grep kinect2* | awk '{print $2}')");
        system("echo y| rosrun grabrb_ui clearNode.sh &");

        startUpFlag_devconn= false;
        btn_tabmain_sysReset->setEnabled(true);
    });
    t.detach();
    //初始化状态机颜色标签
    for (auto &fsmstate : map_fsmState) {
        lableShowImag(fsmstate.second->lableList_showStatus,Qt::lightGray);
    }
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

void MainWindow::slot_btn_tabvoiceSH_grabToy(){
    std_msgs::Int16 msg;
    msg.data=1;
    listenToExit_pub.publish(msg);

    hirop_msgs::taskInputCmd srv;
    srv.request.taskName="VoiceCtlRob";
    srv.request.behavior="todetectToy";
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
    hirop_msgs::shakeHandStatus msg;
    msg.shakeHand_count=1;
    msg.shakeHand_over=true;
    shakeEnd_pub.publish(msg);
    sleep(1);
}

void MainWindow::slot_btn_tabstepSH_endshakehand() {

}

void MainWindow::slot_btn_tabstepSH_stop() {

}

void MainWindow::slot_btn_rbSetEnable() {
    hsr_rosi_device::SetEnableSrv srv;
    srv.request.enable= true;
    RobEnable_client.call(srv);
//    sleep(2);
//    system("  roslaunch force_bridge bring_up_realRobot.launch &");
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
    if(msg->behevior=="initing"){
        for (auto &fsmstate : map_fsmState) {
            if(fsmstate.second->stateName==msg->state){
                lableShowImag(fsmstate.second->lableList_showStatus,Qt::green);
            }
        }
    }
    if(msg->behevior=="quiting"){
        for (auto &fsmstate : map_fsmState) {
            if(fsmstate.second->stateName==msg->state){
                lableShowImag(fsmstate.second->lableList_showStatus,Qt::red);
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

void MainWindow::lableShowImag(QLabel *lable, Qt::GlobalColor color) {
//    lock_showImg.lock();
    palette.setBrush(lable->backgroundRole(),QBrush(color));
    lable->setPalette(palette);
    lable->setAutoFillBackground(true);
//    lock_showImg.unlock();
}

void MainWindow::callback_d435iImagRes_subcriber(const sensor_msgs::Image::ConstPtr &msg) {
    map_devDetector["d435iConn_Detector"]->lifeNum=100;
    map_devDetector["d435iConn_Detector"]->status= true;
}

void MainWindow::callback_kinect2_subscriber(const sensor_msgs::Image_<allocator<void>>::ConstPtr &msg) {
    map_devDetector["kinect2Conn_Detector"]->lifeNum=100;
    map_devDetector["kinect2Conn_Detector"]->status= true;
}


