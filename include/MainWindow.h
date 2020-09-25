
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
#include "hirop_msgs/shakeHandStatus.h"
#include "std_msgs/Int16.h"
//标准库
#include "ros/ros.h"
#include <iostream>
#include <fstream>
#include <thread>
using namespace std;

//Q_DECLARE_METATYPE(vector<QLabel*>) ;

enum  infoLevel{information,warning};

struct  devDetector{
    string name; //设备名
    int lifeNum; //生命值
    bool real_time;//实时监控与否
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
    QMutex locker;
    vector<devDetector*> devDetectorList;//设备监控器列表
    QPalette palette;
    map<string, devDetector*> map_devDetector;//运行准备状态监控器
    map<string, fsmState*> map_fsmState;      //状态机状态监控
    vector<string> in_nodeNameList;           //ros节点名称列表

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
    ros::Subscriber d435iImagRes_subcriber;
    ros::Subscriber kinect2_subcriber;

    ros::Publisher shakeEnd_pub;
    ros::Publisher voiceOrder_pub;
    ros::Publisher listenToExit_pub;

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

    void lableShowImag(QLabel *lable, Qt::GlobalColor color);

        //按钮槽函数
    void slot_btn_tabmain_devConn();
    void slot_btn_tabmain_beginRun();
    void slot_btn_tabmain_sysStop();
    void slot_btn_tabmain_sysReset();

    void slot_btn_tabvoiceSH_run();
    void slot_btn_tabvoiceSH_normalstop();
    void slot_btn_tabvoiceSH_grabToy();
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
    void callback_d435iImagRes_subcriber(const sensor_msgs::Image::ConstPtr& msg);
    void callback_kinect2_subscriber(const sensor_msgs::Image::ConstPtr& msg);
    void callback_forceSensor_subscriber(const geometry_msgs::Wrench::ConstPtr msg);
    void callback_fsmState_subscriber(const hirop_msgs::taskCmdRet::ConstPtr msg);

signals:
    void emitLightColor(vector<QLabel*> label_list,string color);
    void emitQmessageBox(infoLevel level,QString info);

private slots:
    void showLightColor(vector<QLabel*>  label_list,string color);
    void showQmessageBox(infoLevel level,QString info);

};



#endif //RB_UI_MAINWINDOW_H
