#include <iostream>
#include "ros/ros.h"
#include "hirop_msgs/taskInputCmd.h"
#include "hirop_msgs/taskCmdRet.h"
using namespace std;

struct fsmstate{
    string state;
    string behevior;
};

int main(int argc,char** argv){
    string nodeName = "fsm_pub";
    ros::init(argc, argv, nodeName);
    //创建节点
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::NodeHandle node;
    ros::Publisher fsm_pub=node.advertise<hirop_msgs::taskCmdRet>("/VoiceCtlRob_state",1);
//    ros::Publisher fsm_pub=node.advertise<hirop_msgs::taskCmdRet>("/VisualCapture_state",1);
    hirop_msgs::taskCmdRet fsm_msg;
    vector<fsmstate* > fsmstateList;

    fsmstateList.push_back((new fsmstate{"init","quiting"}));
    fsmstateList.push_back(new fsmstate{"prepare","quiting"});
    fsmstateList.push_back(new fsmstate{"detection","quiting"});
    fsmstateList.push_back(new fsmstate{"shakehand","quiting"});
    fsmstateList.push_back(new fsmstate{"wave","quiting"});
    fsmstateList.push_back(new fsmstate{"detectToy","quiting"});
    fsmstateList.push_back(new fsmstate{"error","quiting"});
    fsmstateList.push_back(new fsmstate{"exit","quiting"});
//    int a;
//    cout<<"请输入数字"<<endl;
//    cin>>a;
    for (int i = 0; i < 3600*5; ++i)
    {
        for (auto fsm:fsmstateList) {
            usleep(10*10000);
    //        sleep(1);
            fsm_msg.state=fsm->state;
            fsm_msg.behevior=fsm->behevior;
            fsm_pub.publish(fsm_msg);
            fsm->behevior="initing";
        }
        for (auto fsm:fsmstateList) {
            usleep(10*10000);
            fsm_msg.state=fsm->state;
            fsm_msg.behevior=fsm->behevior;
            fsm_pub.publish(fsm_msg);
            fsm->behevior="quiting";

        }
    }
    cout<<"执行完毕"<<endl;
    return 0;
}

