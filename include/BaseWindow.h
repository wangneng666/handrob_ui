

#ifndef RB_UI_BASEWINDOW_H
#define RB_UI_BASEWINDOW_H
//qt库
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QDateTime>
#include <QDialog>
#include <QDir>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>
#include <QThread>
#include <QImage>
#include <QPixmap>
#include <QMutex>
#include "QDebug"
#include "qdebug.h"

#include <iostream>
#include <ros/node_handle.h>

using namespace std;

#define  BTN_W 150
#define  BTN_H 50
#define  COMBOX_W 200
#define  COMBOX_H 50
#define  LABLE_STATUS_W 50
#define  LABLE_STATUS_H 50


class BaseWindow: public QMainWindow {
public:
    BaseWindow(ros::NodeHandle* node,QWidget* parent = Q_NULLPTR);
    ~BaseWindow();

public:
    //UI流程
    void initQtVal();
    void initUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);

public:
    //ros节点
    ros::NodeHandle* Node;
    //全局变量
    QString tab_qss;
    QString groupBox_qss;
    QString photoPath;
    QString logPath;
    QPixmap fitpixmap_redLight ;
    QPixmap fitpixmap_greenLight;
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *vLayout_main;
    QHBoxLayout *hLayout_main_11;
    QLabel *label_main_logo;
    QLabel *label_main_title;
    QHBoxLayout *hLayout_main_12;
    QTabWidget *tabWidget;

    QWidget *tab_main;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *vLayout_tabmain_1;
    QHBoxLayout *hLayout_tabmain_11;
    QGroupBox *gBox_tabmain_status;
    QHBoxLayout *horizontalLayout_5;
    QGridLayout *gLayout_tabmain_status;
    QLabel *label_tabmain_motionBridge;
    QLabel *label_tabmain_perceptionBridge;
    QLabel *label_tabmain_rbConn;
    QLabel *label_tabmain_rbIsWell;
    QLabel *label_tabmain_rbEnable;
    QLabel *label_tabmain_plannerBridge;
    QLabel *label_tabmain_dmBridge;
    QLabel *label_tabmain_versionBridge;
    QLabel *label_tabmain_forceSensor;
    QLabel *label_tabmain_d435iConn;
    QLabel *label_tabmain_kinect2Conn;
    QLabel *label_tabmain_shakehandJudge;
    QLabel *label_tabmain_forcebridge;
    QLabel *label_tabmain_pickPlaceBridge;
    QLabel *label_tabmain_fsmBridge;

    QHBoxLayout *hLayout_tabmain_21;
    QGroupBox *gBox_tabmain_mode;
    QHBoxLayout *horizontalLayout_6;
    QComboBox *cbox_tabmain_chooseMode;
    QHBoxLayout *hLayout_tabmain_31;
    QGroupBox *gBox_tabmain_func;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btn_tabmain_devConn;
    QPushButton *btn_tabmain_beginRun;
    QPushButton *btn_tabmain_sysStop;
    QPushButton *btn_tabmain_sysReset;

    QWidget *tab_voiceshakehand;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *hLayout_tabvoiceSH_1;
    QVBoxLayout *vLayout_tabvoiceSH_11;
    QGroupBox *gBox_tabvoiceSH_img;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_tabvoiceSH_image;
    QVBoxLayout *vLayout_tabvoiceSH_12;
    QGroupBox *gBox_tabvoiceSH_fsm;
    QHBoxLayout *horizontalLayout_17;
    QGridLayout *gridLayout_tabvoiceSH_fsm;
    QLabel *label_tabvoiceSH_wavestate;
    QLabel *label_tabvoiceSH_detectstate;
    QLabel *label_tabvoiceSH_shakehandstate;
    QLabel *label_tabvoiceSH_preparestate;
    QLabel *label_tabvoiceSH_initstate;
    QLabel *label_tabvoiceSH_exitstate;
    QLabel *label_tabvoiceSH_errstate;
    QLabel *label_tabvoiceSH_detectToystate;
    QGroupBox *gBox_tabvoiceSH_operate;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *hLayout_tabvoiceSH_123;
    QPushButton *btn_tabvoiceSH_run;
    QPushButton *btn_tabvoiceSH_normalstop;
    QPushButton *btn_tabvoiceSH_grabToy;
    QPushButton *btn_tabvoiceSH_quickstop;

    QWidget *tab_stepshankehand;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *gBox_tabstepSH_status;
    QHBoxLayout *horizontalLayout_18;
    QGridLayout *gridLayout_tabstepSH_status;
    QLabel *label_tabstepSH_rbNormal;
    QLabel *label_tabstepSH_rbservoOk;
    QLabel *label_fsmbridgeok;
    QLabel *label_tabstepSH_forcebridgeok;
    QLabel *label_tabstepSH_dmbridgeOk;
    QLabel *label_tabstepSH_plannerOk;
    QLabel *label_tabstepSH_motionbridgeOk;
    QLabel *label_tabstepSH_forceOk;
    QGroupBox *gBox_tabstepSH_operate;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *btn_tabstepSH_beginshakehand;
    QPushButton *btn_tabstepSH_endshakehand;
    QPushButton *btn_tabstepSH_stop;

    QWidget *tab_debug;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_tabdebug_1;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *btn_rbSetEnable;
    QPushButton *btn_rbReset;
    QGroupBox *groupBox_tabdebug_2;
    QHBoxLayout *horizontalLayout_19;
    QPushButton *btn_gripper_open;
    QPushButton *btn_gripper_close;
    QGroupBox *groupBox_tabdebug_3;
    QHBoxLayout *horizontalLayout_20;
    QPushButton *btn_rbGoHomePose;

    QWidget *tab_recorder;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *vLayout_tab_recorder_1;
    QVBoxLayout *vLayout_tab_recorder_11;
    QPlainTextEdit *plainText_tabrecorder;
    QVBoxLayout *vLayout_tab_recorder_2;
    QPushButton *btn_tab_recoder_ouputRecorder;
    QPushButton *btn_tab_recoder_clearRecorder;
    QStatusBar *statusBar;
};


#endif //RB_UI_BASEWINDOW_H
