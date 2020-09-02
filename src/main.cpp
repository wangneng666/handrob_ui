#include "MainWindow.h"
//#include "logmanager.h"
//#include "globalvar.h"
//#include "messagehandler.h"
#include <QApplication>

using namespace std;

int main(int argc,char** argv){
    //ros节点
    string nodeName = "handrb_ui";
    ros::init(argc, argv, nodeName);
    //创建节点
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::NodeHandle node;
    //应用程序
    QApplication app(argc, argv);
    MainWindow mainwindow(&node);
    mainwindow.show();
//    //日志初始化
//    log4cplus::Initializer initializer;
//    gloalMain = &mainwindow;
//    qInstallMessageHandler(customMessageHandler);
    return app.exec();
}



