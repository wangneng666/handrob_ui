
#include "BaseWindow.h"

BaseWindow::BaseWindow(ros::NodeHandle *node, QWidget *parent):QMainWindow(parent),Node(node) {
    initQtVal();
    //初始化UI
    initUi(this);
}

BaseWindow::~BaseWindow() {

}

void BaseWindow::initQtVal() {
    tab_qss=
            "QTabBar::tab{width:100}\n"
            "QTabBar::tab{height:40}";
    groupBox_qss=
            "QGroupBox{\n""\n"
            "border-width:2px;\n""\n"
            "border-style:solid;\n""\n"
            "border-radius: 10px;\n""\n"
            "border-color:gray;\n""\n"
            "margin-top:0.5ex;\n""\n""}\n""\n"
            "QGroupBox::title{\n""\n"
            "subcontrol-origin:margin;\n""\n"
            "subcontrol-position:top left;\n""\n"
            "left:10px;\n""\n"
            "margin-left:0px;\n""\n"
            "padding:0 1px;\n""\n""}"
            ;
    //获取工程文件路径
    photoPath= QDir::currentPath() +QString("/src/handrb_ui/photo");
    logPath= QDir::currentPath()+QString("/src/handrb_ui/photo/logo.png");

    //图片内容初始化
//    QPixmap tmp_pixmap_red=QPixmap(photoPath+"/icon/notok.png");
//    QPixmap tmp_pixmap_green=QPixmap(photoPath+"/icon/ok.png");
//    fitpixmap_redLight = tmp_pixmap_red.scaled(LABLE_STATUS_W,LABLE_STATUS_H, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
//    fitpixmap_greenLight = tmp_pixmap_green.scaled(LABLE_STATUS_W,LABLE_STATUS_H, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
}


void BaseWindow::initUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));

//    //设置背景和背景颜色
//    QImage _image;
//    _image.load(photoPath+"/icon/backGround.jpg");
//    setAutoFillBackground(true);   // 这个属性一定要设置
//    QPalette pal(palette());
////    pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(), Qt::IgnoreAspectRatio)));
//    pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(), Qt::IgnoreAspectRatio,
//                                                        Qt::SmoothTransformation)));
//    setPalette(pal);

    MainWindow->resize(847, 616);
    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    horizontalLayout_8 = new QHBoxLayout(centralWidget);
    horizontalLayout_8->setSpacing(6);
    horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
    vLayout_main = new QVBoxLayout();
    vLayout_main->setSpacing(6);
    vLayout_main->setObjectName(QString::fromUtf8("vLayout_main"));
    hLayout_main_11 = new QHBoxLayout();
    hLayout_main_11->setSpacing(6);
    hLayout_main_11->setObjectName(QString::fromUtf8("hLayout_main_11"));
    label_main_logo = new QLabel(centralWidget);
    label_main_logo->setObjectName(QString::fromUtf8("label_main_logo"));
    label_main_logo->setPixmap(QPixmap(logPath));

    hLayout_main_11->addWidget(label_main_logo);

    label_main_title = new QLabel(centralWidget);
    label_main_title->setObjectName(QString::fromUtf8("label_main_title"));
    QFont font;
    font.setPointSize(40);
    font.setBold(true);
    font.setItalic(false);
    font.setWeight(75);
    label_main_title->setFont(font);
    label_main_title->setAlignment(Qt::AlignCenter);

    hLayout_main_11->addWidget(label_main_title);

    hLayout_main_11->setStretch(1, 6);

    vLayout_main->addLayout(hLayout_main_11);

    hLayout_main_12 = new QHBoxLayout();
    hLayout_main_12->setSpacing(6);
    hLayout_main_12->setObjectName(QString::fromUtf8("hLayout_main_12"));
    tabWidget = new QTabWidget(centralWidget);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setStyleSheet(tab_qss);

    tab_main = new QWidget();
    tab_main->setObjectName(QString::fromUtf8("tab_main"));
    verticalLayout_2 = new QVBoxLayout(tab_main);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setContentsMargins(11, 11, 11, 11);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    vLayout_tabmain_1 = new QVBoxLayout();
    vLayout_tabmain_1->setSpacing(6);
    vLayout_tabmain_1->setObjectName(QString::fromUtf8("vLayout_tabmain_1"));
    hLayout_tabmain_11 = new QHBoxLayout();
    hLayout_tabmain_11->setSpacing(6);
    hLayout_tabmain_11->setObjectName(QString::fromUtf8("hLayout_tabmain_11"));
    gBox_tabmain_status = new QGroupBox(tab_main);
    gBox_tabmain_status->setObjectName(QString::fromUtf8("gBox_tabmain_status"));
    gBox_tabmain_status->setStyleSheet(groupBox_qss);
    horizontalLayout_5 = new QHBoxLayout(gBox_tabmain_status);
    horizontalLayout_5->setSpacing(6);
    horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    gLayout_tabmain_status = new QGridLayout();
    gLayout_tabmain_status->setSpacing(6);
    gLayout_tabmain_status->setObjectName(QString::fromUtf8("gLayout_tabmain_status"));
    label_tabmain_motionBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_motionBridge->setObjectName(QString::fromUtf8("label_tabmain_motionBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_motionBridge, 3, 3, 1, 1);

    label_tabmain_perceptionBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_perceptionBridge->setObjectName(QString::fromUtf8("label_tabmain_perceptionBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_perceptionBridge, 3, 4, 1, 1);

    label_tabmain_rbConn = new QLabel(gBox_tabmain_status);
    label_tabmain_rbConn->setObjectName(QString::fromUtf8("label_tabmain_rbConn"));

    gLayout_tabmain_status->addWidget(label_tabmain_rbConn, 0, 0, 1, 1);

    label_tabmain_rbIsWell = new QLabel(gBox_tabmain_status);
    label_tabmain_rbIsWell->setObjectName(QString::fromUtf8("label_tabmain_rbIsWell"));

    gLayout_tabmain_status->addWidget(label_tabmain_rbIsWell, 0, 1, 1, 1);

    label_tabmain_rbEnable = new QLabel(gBox_tabmain_status);
    label_tabmain_rbEnable->setObjectName(QString::fromUtf8("label_tabmain_rbEnable"));

    gLayout_tabmain_status->addWidget(label_tabmain_rbEnable, 0, 2, 1, 1);

    label_tabmain_plannerBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_plannerBridge->setObjectName(QString::fromUtf8("label_tabmain_plannerBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_plannerBridge, 3, 2, 1, 1);

    label_tabmain_dmBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_dmBridge->setObjectName(QString::fromUtf8("label_tabmain_dmBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_dmBridge, 3, 1, 1, 1);

    label_tabmain_versionBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_versionBridge->setObjectName(QString::fromUtf8("label_tabmain_versionBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_versionBridge, 0, 3, 1, 1);

    label_tabmain_forceSensor = new QLabel(gBox_tabmain_status);
    label_tabmain_forceSensor->setObjectName(QString::fromUtf8("label_tabmain_forceSensor"));

    gLayout_tabmain_status->addWidget(label_tabmain_forceSensor, 0, 4, 1, 1);

    label_tabmain_d435iConn = new QLabel(gBox_tabmain_status);
    label_tabmain_d435iConn->setObjectName(QString::fromUtf8("label_tabmain_d435iConn"));

    gLayout_tabmain_status->addWidget(label_tabmain_d435iConn, 1, 0, 1, 1);

    label_tabmain_kinect2Conn = new QLabel(gBox_tabmain_status);
    label_tabmain_kinect2Conn->setObjectName(QString::fromUtf8("label_tabmain_kinect2Conn"));

    gLayout_tabmain_status->addWidget(label_tabmain_kinect2Conn, 1, 1, 1, 1);

    label_tabmain_shakehandJudge = new QLabel(gBox_tabmain_status);
    label_tabmain_shakehandJudge->setObjectName(QString::fromUtf8("label_tabmain_shakehandJudge"));

    gLayout_tabmain_status->addWidget(label_tabmain_shakehandJudge, 3, 0, 1, 1);

    label_tabmain_forcebridge = new QLabel(gBox_tabmain_status);
    label_tabmain_forcebridge->setObjectName(QString::fromUtf8("label_tabmain_forcebridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_forcebridge, 1, 2, 1, 1);

    label_tabmain_pickPlaceBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_pickPlaceBridge->setObjectName(QString::fromUtf8("label_tabmain_pickPlaceBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_pickPlaceBridge, 1, 3, 1, 1);

    label_tabmain_fsmBridge = new QLabel(gBox_tabmain_status);
    label_tabmain_fsmBridge->setObjectName(QString::fromUtf8("label_tabmain_fsmBridge"));

    gLayout_tabmain_status->addWidget(label_tabmain_fsmBridge, 1, 4, 1, 1);


    horizontalLayout_5->addLayout(gLayout_tabmain_status);


    hLayout_tabmain_11->addWidget(gBox_tabmain_status);


    vLayout_tabmain_1->addLayout(hLayout_tabmain_11);

    hLayout_tabmain_21 = new QHBoxLayout();
    hLayout_tabmain_21->setSpacing(6);
    hLayout_tabmain_21->setObjectName(QString::fromUtf8("hLayout_tabmain_21"));
    gBox_tabmain_mode = new QGroupBox(tab_main);
    gBox_tabmain_mode->setObjectName(QString::fromUtf8("gBox_tabmain_mode"));
    gBox_tabmain_mode->setStyleSheet(groupBox_qss);
    horizontalLayout_6 = new QHBoxLayout(gBox_tabmain_mode);
    horizontalLayout_6->setSpacing(6);
    horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
    cbox_tabmain_chooseMode = new QComboBox(gBox_tabmain_mode);
    cbox_tabmain_chooseMode->addItem(QString());
    cbox_tabmain_chooseMode->addItem(QString());
    cbox_tabmain_chooseMode->addItem(QString());
    cbox_tabmain_chooseMode->setObjectName(QString::fromUtf8("cbox_tabmain_chooseMode"));
    cbox_tabmain_chooseMode->setMaximumSize(QSize(200, 50));
    cbox_tabmain_chooseMode->setLayoutDirection(Qt::LeftToRight);

    horizontalLayout_6->addWidget(cbox_tabmain_chooseMode);


    hLayout_tabmain_21->addWidget(gBox_tabmain_mode);


    vLayout_tabmain_1->addLayout(hLayout_tabmain_21);

    hLayout_tabmain_31 = new QHBoxLayout();
    hLayout_tabmain_31->setSpacing(6);
    hLayout_tabmain_31->setObjectName(QString::fromUtf8("hLayout_tabmain_31"));
    gBox_tabmain_func = new QGroupBox(tab_main);
    gBox_tabmain_func->setObjectName(QString::fromUtf8("gBox_tabmain_func"));
    gBox_tabmain_func->setStyleSheet(groupBox_qss);
    horizontalLayout_7 = new QHBoxLayout(gBox_tabmain_func);
    horizontalLayout_7->setSpacing(6);
    horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
    btn_tabmain_devConn = new QPushButton(gBox_tabmain_func);
    btn_tabmain_devConn->setObjectName(QString::fromUtf8("btn_tabmain_devConn"));

    horizontalLayout_7->addWidget(btn_tabmain_devConn);

    btn_tabmain_devConn->setMaximumSize(QSize(150, 50));

    btn_tabmain_beginRun = new QPushButton(gBox_tabmain_func);
    btn_tabmain_beginRun->setObjectName(QString::fromUtf8("btn_tabmain_beginRun"));
    btn_tabmain_beginRun->setMaximumSize(QSize(150, 50));
    btn_tabmain_beginRun->setText("启动运行");
    horizontalLayout_7->addWidget(btn_tabmain_beginRun);

    btn_tabmain_sysStop = new QPushButton(gBox_tabmain_func);
    btn_tabmain_sysStop->setObjectName(QString::fromUtf8("btn_tabmain_sysStop"));
    btn_tabmain_sysStop->setMaximumSize(QSize(150, 50));

    horizontalLayout_7->addWidget(btn_tabmain_sysStop);

    btn_tabmain_sysReset = new QPushButton(gBox_tabmain_func);
    btn_tabmain_sysReset->setObjectName(QString::fromUtf8("btn_tabmain_sysReset"));
    btn_tabmain_sysReset->setMaximumSize(QSize(150, 50));

    horizontalLayout_7->addWidget(btn_tabmain_sysReset);


    hLayout_tabmain_31->addWidget(gBox_tabmain_func);


    vLayout_tabmain_1->addLayout(hLayout_tabmain_31);

    vLayout_tabmain_1->setStretch(0, 2);
    vLayout_tabmain_1->setStretch(1, 1);
    vLayout_tabmain_1->setStretch(2, 2);

    verticalLayout_2->addLayout(vLayout_tabmain_1);

    tabWidget->addTab(tab_main, QString());
    tab_voiceshakehand = new QWidget();
    tab_voiceshakehand->setObjectName(QString::fromUtf8("tab_voiceshakehand"));
    horizontalLayout = new QHBoxLayout(tab_voiceshakehand);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    hLayout_tabvoiceSH_1 = new QHBoxLayout();
    hLayout_tabvoiceSH_1->setSpacing(6);
    hLayout_tabvoiceSH_1->setObjectName(QString::fromUtf8("hLayout_tabvoiceSH_1"));
    vLayout_tabvoiceSH_11 = new QVBoxLayout();
    vLayout_tabvoiceSH_11->setSpacing(6);
    vLayout_tabvoiceSH_11->setObjectName(QString::fromUtf8("vLayout_tabvoiceSH_11"));
    gBox_tabvoiceSH_img = new QGroupBox(tab_voiceshakehand);
    gBox_tabvoiceSH_img->setObjectName(QString::fromUtf8("gBox_tabvoiceSH_img"));
    gBox_tabvoiceSH_img->setStyleSheet(groupBox_qss);
    horizontalLayout_15 = new QHBoxLayout(gBox_tabvoiceSH_img);
    horizontalLayout_15->setSpacing(6);
    horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
    label_tabvoiceSH_image = new QLabel(gBox_tabvoiceSH_img);
    label_tabvoiceSH_image->setObjectName(QString::fromUtf8("label_tabvoiceSH_image"));
//    label_tabvoiceSH_image->setMaximumSize(QSize(300, 300));

    horizontalLayout_15->addWidget(label_tabvoiceSH_image);


    vLayout_tabvoiceSH_11->addWidget(gBox_tabvoiceSH_img);


    hLayout_tabvoiceSH_1->addLayout(vLayout_tabvoiceSH_11);

    vLayout_tabvoiceSH_12 = new QVBoxLayout();
    vLayout_tabvoiceSH_12->setSpacing(6);
    vLayout_tabvoiceSH_12->setObjectName(QString::fromUtf8("vLayout_tabvoiceSH_12"));

    gBox_tabvoiceSH_fsm = new QGroupBox(tab_voiceshakehand);
    gBox_tabvoiceSH_fsm->setObjectName(QString::fromUtf8("gBox_tabvoiceSH_fsm"));
    gBox_tabvoiceSH_fsm->setStyleSheet(groupBox_qss);
    horizontalLayout_17 = new QHBoxLayout(gBox_tabvoiceSH_fsm);
    horizontalLayout_17->setSpacing(6);
    horizontalLayout_17->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
    gridLayout_tabvoiceSH_fsm = new QGridLayout();
    gridLayout_tabvoiceSH_fsm->setSpacing(6);
    gridLayout_tabvoiceSH_fsm->setObjectName(QString::fromUtf8("gridLayout_tabvoiceSH_fsm"));
    label_tabvoiceSH_wavestate = new QLabel(gBox_tabvoiceSH_fsm);
    label_tabvoiceSH_wavestate->setObjectName(QString::fromUtf8("label_tabvoiceSH_wavestate"));
    label_tabvoiceSH_wavestate->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabvoiceSH_fsm->addWidget(label_tabvoiceSH_wavestate, 1, 0, 1, 1);

    label_tabvoiceSH_detectstate = new QLabel(gBox_tabvoiceSH_fsm);
    label_tabvoiceSH_detectstate->setObjectName(QString::fromUtf8("label_tabvoiceSH_detectstate"));
    label_tabvoiceSH_detectstate->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabvoiceSH_fsm->addWidget(label_tabvoiceSH_detectstate, 0, 2, 1, 1);

    label_tabvoiceSH_shakehandstate = new QLabel(gBox_tabvoiceSH_fsm);
    label_tabvoiceSH_shakehandstate->setObjectName(QString::fromUtf8("label_tabvoiceSH_shakehandstate"));
    label_tabvoiceSH_shakehandstate->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabvoiceSH_fsm->addWidget(label_tabvoiceSH_shakehandstate, 0, 3, 1, 1);

    label_tabvoiceSH_preparestate = new QLabel(gBox_tabvoiceSH_fsm);
    label_tabvoiceSH_preparestate->setObjectName(QString::fromUtf8("label_tabvoiceSH_preparestate"));
    label_tabvoiceSH_preparestate->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabvoiceSH_fsm->addWidget(label_tabvoiceSH_preparestate, 0, 1, 1, 1);

    label_tabvoiceSH_initstate = new QLabel(gBox_tabvoiceSH_fsm);
    label_tabvoiceSH_initstate->setObjectName(QString::fromUtf8("label_tabvoiceSH_initstate"));
    label_tabvoiceSH_initstate->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabvoiceSH_fsm->addWidget(label_tabvoiceSH_initstate, 0, 0, 1, 1);

    label_tabvoiceSH_exitstate = new QLabel(gBox_tabvoiceSH_fsm);
    label_tabvoiceSH_exitstate->setObjectName(QString::fromUtf8("label_tabvoiceSH_exitstate"));
    label_tabvoiceSH_exitstate->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabvoiceSH_fsm->addWidget(label_tabvoiceSH_exitstate, 1, 3, 1, 1);

    label_tabvoiceSH_errstate = new QLabel(gBox_tabvoiceSH_fsm);
    label_tabvoiceSH_errstate->setObjectName(QString::fromUtf8("label_tabvoiceSH_errstate"));
    label_tabvoiceSH_errstate->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabvoiceSH_fsm->addWidget(label_tabvoiceSH_errstate, 1, 2, 1, 1);

    label_tabvoiceSH_detectToystate = new QLabel(gBox_tabvoiceSH_fsm);
    label_tabvoiceSH_detectToystate->setObjectName(QString::fromUtf8("label_tabvoiceSH_detectToystate"));
    label_tabvoiceSH_detectToystate->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabvoiceSH_fsm->addWidget(label_tabvoiceSH_detectToystate, 1, 1, 1, 1);

    horizontalLayout_17->addLayout(gridLayout_tabvoiceSH_fsm);


    vLayout_tabvoiceSH_12->addWidget(gBox_tabvoiceSH_fsm);

    gBox_tabvoiceSH_operate = new QGroupBox(tab_voiceshakehand);
    gBox_tabvoiceSH_operate->setObjectName(QString::fromUtf8("gBox_tabvoiceSH_operate"));
    gBox_tabvoiceSH_operate->setStyleSheet(groupBox_qss);
    verticalLayout_10 = new QVBoxLayout(gBox_tabvoiceSH_operate);
    verticalLayout_10->setSpacing(6);
    verticalLayout_10->setContentsMargins(11, 11, 11, 11);
    verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
    hLayout_tabvoiceSH_123 = new QHBoxLayout();
    hLayout_tabvoiceSH_123->setSpacing(6);
    hLayout_tabvoiceSH_123->setObjectName(QString::fromUtf8("hLayout_tabvoiceSH_123"));
    btn_tabvoiceSH_run = new QPushButton(gBox_tabvoiceSH_operate);
    btn_tabvoiceSH_run->setObjectName(QString::fromUtf8("btn_tabvoiceSH_run"));
    btn_tabvoiceSH_run->setMaximumSize(QSize(150, 50));

    hLayout_tabvoiceSH_123->addWidget(btn_tabvoiceSH_run);

    btn_tabvoiceSH_normalstop = new QPushButton(gBox_tabvoiceSH_operate);
    btn_tabvoiceSH_normalstop->setObjectName(QString::fromUtf8("btn_tabvoiceSH_normalstop"));
    btn_tabvoiceSH_normalstop->setMaximumSize(QSize(150, 50));

    hLayout_tabvoiceSH_123->addWidget(btn_tabvoiceSH_normalstop);

    btn_tabvoiceSH_grabToy = new QPushButton(gBox_tabvoiceSH_operate);
    btn_tabvoiceSH_grabToy->setObjectName(QString::fromUtf8("btn_tabvoiceSH_grabToy"));
    btn_tabvoiceSH_grabToy->setMaximumSize(QSize(150, 50));
    btn_tabvoiceSH_grabToy->setText("抓娃娃");
    hLayout_tabvoiceSH_123->addWidget(btn_tabvoiceSH_grabToy);

    btn_tabvoiceSH_quickstop = new QPushButton(gBox_tabvoiceSH_operate);
    btn_tabvoiceSH_quickstop->setObjectName(QString::fromUtf8("btn_tabvoiceSH_quickstop"));
    btn_tabvoiceSH_quickstop->setMaximumSize(QSize(150, 50));

    hLayout_tabvoiceSH_123->addWidget(btn_tabvoiceSH_quickstop);


    verticalLayout_10->addLayout(hLayout_tabvoiceSH_123);


    vLayout_tabvoiceSH_12->addWidget(gBox_tabvoiceSH_operate);


    hLayout_tabvoiceSH_1->addLayout(vLayout_tabvoiceSH_12);


    horizontalLayout->addLayout(hLayout_tabvoiceSH_1);

    tabWidget->addTab(tab_voiceshakehand, QString());
    tabWidget->setTabText(tabWidget->indexOf(tab_voiceshakehand), QString::fromUtf8("\345\243\260\346\216\247\346\217\241\346\211\213\347\225\214\351\235\242"));
    tab_stepshankehand = new QWidget();
    tab_stepshankehand->setObjectName(QString::fromUtf8("tab_stepshankehand"));
    verticalLayout_3 = new QVBoxLayout(tab_stepshankehand);
    verticalLayout_3->setSpacing(6);
    verticalLayout_3->setContentsMargins(11, 11, 11, 11);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    gBox_tabstepSH_status = new QGroupBox(tab_stepshankehand);
    gBox_tabstepSH_status->setObjectName(QString::fromUtf8("gBox_tabstepSH_status"));
    gBox_tabstepSH_status->setStyleSheet(groupBox_qss);
    horizontalLayout_18 = new QHBoxLayout(gBox_tabstepSH_status);
    horizontalLayout_18->setSpacing(6);
    horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
    gridLayout_tabstepSH_status = new QGridLayout();
    gridLayout_tabstepSH_status->setSpacing(6);
    gridLayout_tabstepSH_status->setObjectName(QString::fromUtf8("gridLayout_tabstepSH_status"));
    label_tabstepSH_rbNormal = new QLabel(gBox_tabstepSH_status);
    label_tabstepSH_rbNormal->setObjectName(QString::fromUtf8("label_tabstepSH_rbNormal"));
    label_tabstepSH_rbNormal->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabstepSH_status->addWidget(label_tabstepSH_rbNormal, 0, 0, 1, 1);

    label_tabstepSH_rbservoOk = new QLabel(gBox_tabstepSH_status);
    label_tabstepSH_rbservoOk->setObjectName(QString::fromUtf8("label_tabstepSH_rbservoOk"));
    label_tabstepSH_rbservoOk->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabstepSH_status->addWidget(label_tabstepSH_rbservoOk, 0, 1, 1, 1);

    label_fsmbridgeok = new QLabel(gBox_tabstepSH_status);
    label_fsmbridgeok->setObjectName(QString::fromUtf8("label_fsmbridgeok"));
    label_fsmbridgeok->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabstepSH_status->addWidget(label_fsmbridgeok, 0, 2, 1, 1);

    label_tabstepSH_forcebridgeok = new QLabel(gBox_tabstepSH_status);
    label_tabstepSH_forcebridgeok->setObjectName(QString::fromUtf8("label_tabstepSH_forcebridgeok"));
    label_tabstepSH_forcebridgeok->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabstepSH_status->addWidget(label_tabstepSH_forcebridgeok, 0, 3, 1, 1);

    label_tabstepSH_dmbridgeOk = new QLabel(gBox_tabstepSH_status);
    label_tabstepSH_dmbridgeOk->setObjectName(QString::fromUtf8("label_tabstepSH_dmbridgeOk"));
    label_tabstepSH_dmbridgeOk->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabstepSH_status->addWidget(label_tabstepSH_dmbridgeOk, 1, 0, 1, 1);

    label_tabstepSH_plannerOk = new QLabel(gBox_tabstepSH_status);
    label_tabstepSH_plannerOk->setObjectName(QString::fromUtf8("label_tabstepSH_plannerOk"));
    label_tabstepSH_plannerOk->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabstepSH_status->addWidget(label_tabstepSH_plannerOk, 1, 1, 1, 1);

    label_tabstepSH_motionbridgeOk = new QLabel(gBox_tabstepSH_status);
    label_tabstepSH_motionbridgeOk->setObjectName(QString::fromUtf8("label_tabstepSH_motionbridgeOk"));
    label_tabstepSH_motionbridgeOk->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabstepSH_status->addWidget(label_tabstepSH_motionbridgeOk, 1, 2, 1, 1);

    label_tabstepSH_forceOk = new QLabel(gBox_tabstepSH_status);
    label_tabstepSH_forceOk->setObjectName(QString::fromUtf8("label_tabstepSH_forceOk"));
    label_tabstepSH_forceOk->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    gridLayout_tabstepSH_status->addWidget(label_tabstepSH_forceOk, 1, 3, 1, 1);


    horizontalLayout_18->addLayout(gridLayout_tabstepSH_status);


    verticalLayout_3->addWidget(gBox_tabstepSH_status);

    gBox_tabstepSH_operate = new QGroupBox(tab_stepshankehand);
    gBox_tabstepSH_operate->setObjectName(QString::fromUtf8("gBox_tabstepSH_operate"));
    gBox_tabstepSH_operate->setStyleSheet(groupBox_qss);
    horizontalLayout_21 = new QHBoxLayout(gBox_tabstepSH_operate);
    horizontalLayout_21->setSpacing(6);
    horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
    btn_tabstepSH_beginshakehand = new QPushButton(gBox_tabstepSH_operate);
    btn_tabstepSH_beginshakehand->setObjectName(QString::fromUtf8("btn_tabstepSH_beginshakehand"));
    btn_tabstepSH_beginshakehand->setMaximumSize(QSize(150, 50));

    horizontalLayout_21->addWidget(btn_tabstepSH_beginshakehand);

    btn_tabstepSH_endshakehand = new QPushButton(gBox_tabstepSH_operate);
    btn_tabstepSH_endshakehand->setObjectName(QString::fromUtf8("btn_tabstepSH_endshakehand"));
    btn_tabstepSH_endshakehand->setMaximumSize(QSize(150, 50));

    horizontalLayout_21->addWidget(btn_tabstepSH_endshakehand);

    btn_tabstepSH_stop = new QPushButton(gBox_tabstepSH_operate);
    btn_tabstepSH_stop->setObjectName(QString::fromUtf8("btn_tabstepSH_stop"));
    btn_tabstepSH_stop->setMaximumSize(QSize(150, 50));

    horizontalLayout_21->addWidget(btn_tabstepSH_stop);


    verticalLayout_3->addWidget(gBox_tabstepSH_operate);

    tabWidget->addTab(tab_stepshankehand, QString());
    tab_debug = new QWidget();
    tab_debug->setObjectName(QString::fromUtf8("tab_debug"));
    verticalLayout_5 = new QVBoxLayout(tab_debug);
    verticalLayout_5->setSpacing(6);
    verticalLayout_5->setContentsMargins(11, 11, 11, 11);
    verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
    groupBox_tabdebug_1 = new QGroupBox(tab_debug);
    groupBox_tabdebug_1->setObjectName(QString::fromUtf8("groupBox_tabdebug_1"));
    groupBox_tabdebug_1->setStyleSheet(groupBox_qss);
    horizontalLayout_14 = new QHBoxLayout(groupBox_tabdebug_1);
    horizontalLayout_14->setSpacing(6);
    horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
    btn_rbSetEnable = new QPushButton(groupBox_tabdebug_1);
    btn_rbSetEnable->setObjectName(QString::fromUtf8("btn_rbSetEnable"));
    btn_rbSetEnable->setMaximumSize(QSize(150, 50));

    horizontalLayout_14->addWidget(btn_rbSetEnable);

    btn_rbReset = new QPushButton(groupBox_tabdebug_1);
    btn_rbReset->setObjectName(QString::fromUtf8("btn_rbReset"));
    btn_rbReset->setMaximumSize(QSize(150, 50));

    horizontalLayout_14->addWidget(btn_rbReset);


    verticalLayout_5->addWidget(groupBox_tabdebug_1);

    groupBox_tabdebug_2 = new QGroupBox(tab_debug);
    groupBox_tabdebug_2->setObjectName(QString::fromUtf8("groupBox_tabdebug_2"));
    groupBox_tabdebug_2->setStyleSheet(groupBox_qss);
    horizontalLayout_19 = new QHBoxLayout(groupBox_tabdebug_2);
    horizontalLayout_19->setSpacing(6);
    horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
    btn_gripper_open = new QPushButton(groupBox_tabdebug_2);
    btn_gripper_open->setObjectName(QString::fromUtf8("btn_gripper_open"));
    btn_gripper_open->setMaximumSize(QSize(150, 50));

    horizontalLayout_19->addWidget(btn_gripper_open);

    btn_gripper_close = new QPushButton(groupBox_tabdebug_2);
    btn_gripper_close->setObjectName(QString::fromUtf8("btn_gripper_close"));
    btn_gripper_close->setMaximumSize(QSize(150, 50));

    horizontalLayout_19->addWidget(btn_gripper_close);


    verticalLayout_5->addWidget(groupBox_tabdebug_2);

    groupBox_tabdebug_3 = new QGroupBox(tab_debug);
    groupBox_tabdebug_3->setObjectName(QString::fromUtf8("groupBox_tabdebug_3"));
    groupBox_tabdebug_3->setStyleSheet(groupBox_qss);
    horizontalLayout_20 = new QHBoxLayout(groupBox_tabdebug_3);
    horizontalLayout_20->setSpacing(6);
    horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
    btn_rbGoHomePose = new QPushButton(groupBox_tabdebug_3);
    btn_rbGoHomePose->setObjectName(QString::fromUtf8("btn_rbGoHomePose"));
    btn_rbGoHomePose->setMaximumSize(QSize(150, 50));

    horizontalLayout_20->addWidget(btn_rbGoHomePose);


    verticalLayout_5->addWidget(groupBox_tabdebug_3);

    tabWidget->addTab(tab_debug, QString());
    tab_recorder = new QWidget();
    tab_recorder->setObjectName(QString::fromUtf8("tab_recorder"));
    horizontalLayout_3 = new QHBoxLayout(tab_recorder);
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    vLayout_tab_recorder_1 = new QVBoxLayout();
    vLayout_tab_recorder_1->setSpacing(6);
    vLayout_tab_recorder_1->setObjectName(QString::fromUtf8("vLayout_tab_recorder_1"));
    vLayout_tab_recorder_11 = new QVBoxLayout();
    vLayout_tab_recorder_11->setSpacing(6);
    vLayout_tab_recorder_11->setObjectName(QString::fromUtf8("vLayout_tab_recorder_11"));
    plainText_tabrecorder = new QPlainTextEdit(tab_recorder);
    plainText_tabrecorder->setObjectName(QString::fromUtf8("plainText_tabrecorder"));

    vLayout_tab_recorder_11->addWidget(plainText_tabrecorder);


    vLayout_tab_recorder_1->addLayout(vLayout_tab_recorder_11);


    horizontalLayout_3->addLayout(vLayout_tab_recorder_1);

    vLayout_tab_recorder_2 = new QVBoxLayout();
    vLayout_tab_recorder_2->setSpacing(6);
    vLayout_tab_recorder_2->setObjectName(QString::fromUtf8("vLayout_tab_recorder_2"));
    btn_tab_recoder_ouputRecorder = new QPushButton(tab_recorder);
    btn_tab_recoder_ouputRecorder->setObjectName(QString::fromUtf8("btn_tab_recoder_ouputRecorder"));
    btn_tab_recoder_ouputRecorder->setMaximumSize(QSize(150, 50));

    vLayout_tab_recorder_2->addWidget(btn_tab_recoder_ouputRecorder);

    btn_tab_recoder_clearRecorder = new QPushButton(tab_recorder);
    btn_tab_recoder_clearRecorder->setObjectName(QString::fromUtf8("btn_tab_recoder_clearRecorder"));
    btn_tab_recoder_clearRecorder->setMaximumSize(QSize(150, 50));

    vLayout_tab_recorder_2->addWidget(btn_tab_recoder_clearRecorder);


    horizontalLayout_3->addLayout(vLayout_tab_recorder_2);

    tabWidget->addTab(tab_recorder, QString());

    hLayout_main_12->addWidget(tabWidget);


    vLayout_main->addLayout(hLayout_main_12);

    vLayout_main->setStretch(0, 1);
    vLayout_main->setStretch(1, 9);

    horizontalLayout_8->addLayout(vLayout_main);

    MainWindow->setCentralWidget(centralWidget);
    statusBar = new QStatusBar(MainWindow);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    MainWindow->setStatusBar(statusBar);

    label_tabmain_motionBridge->setFixedHeight(50);
    label_tabmain_perceptionBridge->setFixedHeight(50);
    label_tabmain_rbConn->setFixedHeight(50);
    label_tabmain_rbIsWell->setFixedHeight(50);
    label_tabmain_rbEnable->setFixedHeight(50);
    label_tabmain_plannerBridge->setFixedHeight(50);
    label_tabmain_dmBridge->setFixedHeight(50);
    label_tabmain_versionBridge->setFixedHeight(50);
    label_tabmain_forceSensor->setFixedHeight(50);
    label_tabmain_d435iConn->setFixedHeight(50);
    label_tabmain_kinect2Conn->setFixedHeight(50);
    label_tabmain_shakehandJudge->setFixedHeight(50);
    label_tabmain_forcebridge->setFixedHeight(50);
    label_tabmain_pickPlaceBridge->setFixedHeight(50);
    label_tabmain_fsmBridge->setFixedHeight(50);

    label_tabmain_motionBridge->setAlignment(Qt::AlignCenter);
    label_tabmain_perceptionBridge->setAlignment(Qt::AlignCenter);
    label_tabmain_rbConn->setAlignment(Qt::AlignCenter);
    label_tabmain_rbIsWell->setAlignment(Qt::AlignCenter);
    label_tabmain_rbEnable->setAlignment(Qt::AlignCenter);
    label_tabmain_plannerBridge->setAlignment(Qt::AlignCenter);
    label_tabmain_dmBridge->setAlignment(Qt::AlignCenter);
    label_tabmain_versionBridge->setAlignment(Qt::AlignCenter);
    label_tabmain_forceSensor->setAlignment(Qt::AlignCenter);
    label_tabmain_d435iConn->setAlignment(Qt::AlignCenter);
    label_tabmain_kinect2Conn->setAlignment(Qt::AlignCenter);
    label_tabmain_shakehandJudge->setAlignment(Qt::AlignCenter);
    label_tabmain_forcebridge->setAlignment(Qt::AlignCenter);
    label_tabmain_pickPlaceBridge->setAlignment(Qt::AlignCenter);
    label_tabmain_fsmBridge->setAlignment(Qt::AlignCenter);


    retranslateUi(MainWindow);

    tabWidget->setCurrentIndex(1);
    retranslateUi(MainWindow);
//    QMetaObject::connectSlotsByName(MainWindow);
}

void BaseWindow::retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
    label_main_logo->setText(QString());
    label_main_title->setText(QApplication::translate("MainWindow",
                                                      "协作机器人智能交互平台",
                                                      nullptr));
    gBox_tabmain_status->setTitle(QApplication::translate("MainWindow",
                                                          "\350\256\276\345\244\207\350\277\236\346\216\245\347\212\266\346\200\201",
                                                          nullptr));
    label_tabmain_motionBridge->setText(QApplication::translate("MainWindow", "\350\277\220\345\212\250\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_perceptionBridge->setText(QApplication::translate("MainWindow", "\346\204\237\347\237\245\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_rbConn->setText(QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\350\277\236\346\216\245", nullptr));
    label_tabmain_rbIsWell->setText(QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\346\255\243\345\270\270", nullptr));
    label_tabmain_rbEnable->setText(QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\344\274\272\346\234\215", nullptr));
    label_tabmain_plannerBridge->setText(QApplication::translate("MainWindow", "\350\247\204\345\210\222\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_dmBridge->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_versionBridge->setText(QApplication::translate("MainWindow", "\350\247\206\350\247\211\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_forceSensor->setText(QApplication::translate("MainWindow", "\345\212\233\346\204\237\345\272\224", nullptr));
    label_tabmain_d435iConn->setText(QApplication::translate("MainWindow", "d435i\347\233\270\346\234\272\350\277\236\346\216\245", nullptr));
    label_tabmain_kinect2Conn->setText(QApplication::translate("MainWindow", "kinect2\347\233\270\346\234\272\350\277\236\346\216\245", nullptr));
    label_tabmain_shakehandJudge->setText(QApplication::translate("MainWindow", "\346\217\241\346\211\213\350\256\241\347\256\227\350\212\202\347\202\271", nullptr));
    label_tabmain_forcebridge->setText(QApplication::translate("MainWindow", "\345\212\233\346\216\247\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_pickPlaceBridge->setText(QApplication::translate("MainWindow", "\346\212\223\345\217\226\346\241\245\350\212\202\347\202\271", nullptr));
    label_tabmain_fsmBridge->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\234\272\350\212\202\347\202\271", nullptr));
    gBox_tabmain_mode->setTitle(
            QApplication::translate("MainWindow", "\346\250\241\345\274\217\351\200\211\346\213\251", nullptr));
    cbox_tabmain_chooseMode->setItemText(0, QApplication::translate("MainWindow",
                                                                    "\350\257\267\351\200\211\346\213\251\350\277\220\350\241\214\346\250\241\345\274\217",
                                                                    nullptr));
    cbox_tabmain_chooseMode->setItemText(1, QApplication::translate("MainWindow",
                                                                    "\350\207\252\345\212\250\346\250\241\345\274\217",
                                                                    nullptr));
    cbox_tabmain_chooseMode->setItemText(2, QApplication::translate("MainWindow",
                                                                    "\346\211\213\345\212\250\346\250\241\345\274\217",
                                                                    nullptr));

    gBox_tabmain_func->setTitle(
            QApplication::translate("MainWindow", "\347\263\273\347\273\237\345\212\237\350\203\275", nullptr));
    btn_tabmain_devConn->setText(
            QApplication::translate("MainWindow", "\350\256\276\345\244\207\350\277\236\346\216\245", nullptr));
    btn_tabmain_sysStop->setText(
            QApplication::translate("MainWindow", "\347\264\247\346\200\245\345\201\234\346\255\242", nullptr));
    btn_tabmain_sysReset->setText(
            QApplication::translate("MainWindow", "\347\263\273\347\273\237\345\244\215\344\275\215", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_main),
                          QApplication::translate("MainWindow", "\344\270\273\347\225\214\351\235\242", nullptr));
    gBox_tabvoiceSH_img->setTitle(
            QApplication::translate("MainWindow", "\345\233\276\345\203\217\346\230\276\347\244\272", nullptr));
    label_tabvoiceSH_image->setText(QString());

    gBox_tabvoiceSH_fsm->setTitle(
            QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\234\272\347\233\221\346\216\247",
                                    nullptr));
    label_tabvoiceSH_wavestate->setText(
            QApplication::translate("MainWindow", "\346\214\245\346\211\213\347\212\266\346\200\201", nullptr));
    label_tabvoiceSH_detectstate->setText(
            QApplication::translate("MainWindow", "\346\243\200\346\265\213\347\212\266\346\200\201", nullptr));
    label_tabvoiceSH_shakehandstate->setText(
            QApplication::translate("MainWindow", "\346\217\241\346\211\213\347\212\266\346\200\201", nullptr));
    label_tabvoiceSH_preparestate->setText(
            QApplication::translate("MainWindow", "\345\207\206\345\244\207\347\212\266\346\200\201", nullptr));
    label_tabvoiceSH_initstate->setText(
            QApplication::translate("MainWindow", "\345\210\235\345\247\213\347\212\266\346\200\201", nullptr));
    label_tabvoiceSH_exitstate->setText(
            QApplication::translate("MainWindow", "\351\200\200\345\207\272\347\212\266\346\200\201", nullptr));
    label_tabvoiceSH_errstate->setText(
            QApplication::translate("MainWindow", "\346\225\205\351\232\234\347\212\266\346\200\201", nullptr));
    label_tabvoiceSH_detectToystate->setText(
            QApplication::translate("MainWindow", "抓取状态", nullptr));
    gBox_tabvoiceSH_operate->setTitle(
            QApplication::translate("MainWindow", "\346\223\215\344\275\234\346\240\217", nullptr));
    btn_tabvoiceSH_run->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
    btn_tabvoiceSH_normalstop->setText(
            QApplication::translate("MainWindow", "\345\276\252\347\216\257\345\201\234\346\255\242", nullptr));
    btn_tabvoiceSH_quickstop->setText(QApplication::translate("MainWindow", "\346\200\245\345\201\234", nullptr));
    gBox_tabstepSH_status->setTitle(
            QApplication::translate("MainWindow", "\345\207\206\345\244\207\347\212\266\346\200\201", nullptr));
    label_tabstepSH_rbNormal->setText(
            QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\346\255\243\345\270\270",
                                    nullptr));
    label_tabstepSH_rbservoOk->setText(
            QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\344\274\272\346\234\215",
                                    nullptr));
    label_fsmbridgeok->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\234\272", nullptr));
    label_tabstepSH_forcebridgeok->setText(QApplication::translate("MainWindow", "力控桥", nullptr));
    label_tabstepSH_dmbridgeOk->setText(
            QApplication::translate("MainWindow", "\346\225\260\346\215\256\346\241\245", nullptr));
    label_tabstepSH_plannerOk->setText(
            QApplication::translate("MainWindow", "\350\247\204\345\210\222\346\241\245", nullptr));
    label_tabstepSH_motionbridgeOk->setText(
            QApplication::translate("MainWindow", "\350\277\220\345\212\250\346\241\245", nullptr));
    label_tabstepSH_forceOk->setText(
            QApplication::translate("MainWindow", "\345\212\233\346\204\237\345\272\224", nullptr));
    gBox_tabstepSH_operate->setTitle(
            QApplication::translate("MainWindow", "\346\223\215\344\275\234\346\240\217", nullptr));
    btn_tabstepSH_beginshakehand->setText(
            QApplication::translate("MainWindow", "\346\217\241\346\211\213\345\274\200\345\247\213", nullptr));
    btn_tabstepSH_endshakehand->setText(
            QApplication::translate("MainWindow", "\346\217\241\346\211\213\347\273\223\346\235\237", nullptr));
    btn_tabstepSH_stop->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_stepshankehand), QApplication::translate("MainWindow",
                                                                                          "\346\211\213\345\212\250\346\217\241\346\211\213\347\225\214\351\235\242",
                                                                                          nullptr));
    groupBox_tabdebug_1->setTitle(
            QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\350\260\203\350\257\225",
                                    nullptr));
    btn_rbSetEnable->setText(QApplication::translate("MainWindow",
                                                     "\346\234\272\345\231\250\344\272\272\344\270\212\344\275\277\350\203\275",
                                                     nullptr));
    btn_rbReset->setText(
            QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\345\244\215\344\275\215",
                                    nullptr));
    groupBox_tabdebug_2->setTitle(QApplication::translate("MainWindow",
                                                          "\344\272\224\346\214\207\345\244\271\347\210\252\346\211\213\345\236\213\350\260\203\350\257\225",
                                                          nullptr));
    btn_gripper_open->setText(QApplication::translate("MainWindow", "\345\274\240\345\274\200", nullptr));
    btn_gripper_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
    groupBox_tabdebug_3->setTitle(
            QApplication::translate("MainWindow", "\345\205\266\344\273\226\350\260\203\350\257\225", nullptr));
    btn_rbGoHomePose->setText(QApplication::translate("MainWindow",
                                                      "\346\234\272\345\231\250\344\272\272\345\233\236\345\216\237\347\202\271",
                                                      nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_debug),
                          QApplication::translate("MainWindow", "\350\260\203\350\257\225\347\225\214\351\235\242",
                                                  nullptr));
    btn_tab_recoder_ouputRecorder->setText(
            QApplication::translate("MainWindow", "\346\227\245\345\277\227\345\257\274\345\207\272", nullptr));
    btn_tab_recoder_clearRecorder->setText(
            QApplication::translate("MainWindow", "\346\227\245\345\277\227\346\270\205\351\231\244", nullptr));
    tabWidget->setTabText(tabWidget->indexOf(tab_recorder),
                          QApplication::translate("MainWindow", "\346\227\245\345\277\227\347\225\214\351\235\242",
                                                  nullptr));
}