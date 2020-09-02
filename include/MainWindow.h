
#ifndef RB_UI_MAINWINDOW_H
#define RB_UI_MAINWINDOW_H

#include "BaseWindow.h"

//opencv库
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//qt
#include <QMetaType>
#include <QVariant>
//消息类型头文件
#include "std_msgs/String.h"
#include "std_srvs/Empty.h"

#include "std_msgs/Bool.h"
#include "sensor_msgs/Image.h"
#include <cv_bridge/cv_bridge.h>
#include "hsr_rosi_device/ClearFaultSrv.h"
#include "hsr_rosi_device/SetEnableSrv.h"
#include "industrial_msgs/RobotStatus.h"
#include "geometry_msgs/Wrench.h"
#include "hsr_rosi_device/setModeSrv.h"
#include "std_srvs/SetBool.h"
#include "hirop_msgs/taskInputCmd.h"
#include "hirop_msgs/taskCmdRet.h"

//标准库
#include "ros/ros.h"
#include <iostream>
#include <fstream>
using namespace std;

//Q_DECLARE_METATYPE(vector<QLabel*>) ;

enum  infoLevel{information,warning};

struct  devDetector{
    string name; //设备名
    int lifeNum; //生命值
    int showType;//
    bool status; //状态
    vector<QLabel*> lableList_showStatus;//状态显示lable
};

struct  fsmState{
    string stateName;
    bool status;
    QLabel* lableList_showStatus;//状态显示lable
};

class MainWindow: public BaseWindow {
Q_OBJECT
public:
    MainWindow(ros::NodeHandle* node,QWidget* parent = Q_NULLPTR);
    ~MainWindow();
private:
    bool startUpFlag_devconn= false;

    vector<string> in_nodeNameList;
    vector<devDetector*> devDetectorList;//设备监控器列表
    devDetector RobConn_Detector={"RobConn",0, 0, false,{label_tabmain_rb_pic}}; //机器人连接状态
    devDetector forceConn_Detector={"forceConn",0, 0,false,{label_tabmain_force_pic}}; //机器人连接状态
    devDetector kinectConn_Detector={"kinectConn",0, 0,false,{label_tabmain_kinect_pic}}; //机器人连接状态
    devDetector d435iConn_Detector={"d435iConn",0, 0,false,{label_tabmain_d435i_pic}}; //机器人连接状态
    devDetector handGrawConn_Detector={"handGrawConn",0, 0,false,{lable_tabmain_handGraw_pic}}; //机器人连接状态

    devDetector robNormal_Detector={"robNormal_Detector",0, 1,false,{label_tabvoiceSH_rbok,label_tabstepSH_rbNormal}}; //机器人连接状态
    devDetector robServo_Detector={"robServo_Detector",0, 1,false,{label_rbservook,label_tabstepSH_rbservoOk}}; //机器人连接状态
    devDetector fsmbridge_Detector={"fsmbridge_Detector",0, 1,false,{label_fsmbridge,label_fsmbridgeok}}; //机器人连接状态
    devDetector voiceNode_Detector={"voiceNode_Detector",0, 1,false,{label_voiceok}}; //机器人连接状态
    devDetector dmbridge_Detector={"dmbridge_Detector",0, 1,false,{label_dmbridgeok,label_tabstepSH_dmbridgeOk}}; //机器人连接状态
    devDetector planbridge_Detector={"planbridge_Detector",0, 1,false,{label_tabstepSH_plannerOk,label_plannerok}}; //机器人连接状态
    devDetector motionbridge_Detector={"motionbridge_Detector",0, 1,false,{label_motionbridgeok,label_tabstepSH_motionbridgeOk}}; //机器人连接状态
    devDetector forceNode_Detector={"forceNode_Detector",0, 1,false,{label_forceok,label_tabstepSH_forceOk}}; //机器人连接状态
    devDetector forcebridge_Detector={"forcebridge_Detector",0, 1,false,{label_forcebridge,label_tabstepSH_forcebridgeok}}; //机器人连接状态
    devDetector shakeHandJudge_Detector={"shakeHandJudge_Detector",0, 1,false,{label_shakehandJudge}}; //机器人连接状态

    vector<fsmState> fsmStateList;
    fsmState init_fsmstate{"init",true,label_tabvoiceSH_initstate};
    fsmState prepare_fsmstate{"prepare",true,label_tabvoiceSH_preparestate};
    fsmState detect_fsmstate{"detection",true,label_tabvoiceSH_detectstate};
    fsmState shakehand_fsmstate{"shakehand",true,label_tabvoiceSH_shakehandstate};
    fsmState wave_fsmstate{"wave",true,label_tabvoiceSH_wavestate};
    fsmState homepoint_fsmstate{"homepoint",true,label_tabvoiceSH_homepointstate};
    fsmState dealErr_fsmstate{"dealErr",true,label_tabvoiceSH_errstate};
    fsmState exit_fsmstate{"exit",true,label_tabvoiceSH_exitstate};

    QTimer* Timer_listenStatus;
    QTimer* Timer_listenNodeStatus;
    //ros消息对象
    ros::ServiceClient RobReset_client;
    ros::ServiceClient RobEnable_client;
    ros::ServiceClient RobSetMode_client;
    ros::ServiceClient fsmCmd_client;///VoiceCtlRob_TaskServerCmd

    ros::Subscriber fsmState_subscriber;
    ros::Subscriber robStatus_subscriber;
    ros::Subscriber peopleDetectImg_subscriber;
    ros::Subscriber forceSensor_subscriber;
    ros::Subscriber personImg_subcriber;

public:
    //初始化Ros话题与服务
    void initRosToptic();
    //输入想要监控的节点名称列表 输出监控状态列表
    void checkNodeAlive(const std::vector<std::string>& in_nodeNameList, std::vector<bool >& out_nodeIsAlive);

    QImage cvMat2QImage(const cv::Mat &mat) ;
private:
    //系统变量初始化
    void SysVarInit();
    //处理所有信号和槽函数
    void signalAndSlot();
    //按钮槽函数
    void slot_btn_tabmain_devConn();
    void slot_btn_tabmain_sysStop();
    void slot_btn_tabmain_sysReset();
    void slot_btn_tabvoiceSH_run();
    void slot_btn_tabvoiceSH_normalstop();
    void slot_btn_tabvoiceSH_quickstop();
    void slot_btn_tabstepSH_beginshakehand();
    void slot_btn_tabstepSH_endshakehand();
    void slot_btn_tabstepSH_stop();
    void slot_btn_rbSetEnable();
    void slot_btn_rbReset();
    void slot_btn_gripper_open();
    void slot_btn_gripper_close();
    void slot_btn_rbGoHomePose();
    void slot_btn_tab_recoder_ouputRecorder();
    void slot_btn_tab_recoder_clearRecorder();
    //主界面槽函数
    void slot_timer_updateStatus();
    void slot_timer_listenNodeStatus();
//*********************************************************************************
    //ros节点回调函数
    void callback_robStatus_subscriber(const industrial_msgs::RobotStatus::ConstPtr robot_status);
    void callback_peopleDetectImg_subscriber(const sensor_msgs::Image::ConstPtr& msg);
    void callback_forceSensor_subscriber(geometry_msgs::Wrench msg);
    void callback_fsmState_subscriber(const hirop_msgs::taskCmdRet::ConstPtr msg);
signals:
    void emitLightColor(vector<QLabel*> label_list,int showType,string color);
    void emitQmessageBox(infoLevel level,QString info);

private slots:
    void showLightColor(vector<QLabel*>  label_list,int showType,string color);
    void showQmessageBox(infoLevel level,QString info);

};



#endif //RB_UI_MAINWINDOW_H
