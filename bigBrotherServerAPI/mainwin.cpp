#include "mainwin.h"

MainWin::MainWin(QWidget *parent)
    : QWidget(parent)
{
    QSize* windowSize = new QSize(325,275);
    this->resize(*windowSize);
    this->setWindowIcon(QIcon(":/icons/images/unnamed.jpg"));
    this->setWindowTitle("BigBrother - Server");
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setObjectName("MainWin");
    this->setAttribute(Qt::WA_StyledBackground, true);

    /////////////////////////////////////////////////////

    this->baseLayout = new QGridLayout();
    this->setLayout(this->baseLayout);

    this->logoPixmap = new QPixmap(":/icons/images/unnamed.jpg");
    this->logo = new QLabel();
    this->logo->setPixmap(this->logoPixmap->scaledToWidth(160));

    this->portId = new QLabel("Port: ");
    this->portIdEdit = new QLineEdit();

    this->classroom = new QLabel("Učebna: ");
    this->classroomBox = new QComboBox();

    this->classroomBox->addItem("MIT",1);
    this->classroomBox->addItem("FCM",0);
    this->classroomBox->addItem("SITE",2);
    this->classroomBox->addItem("VYT1",3);
    this->classroomBox->addItem("VYT2",4);

    QVariant v(0);

    this->classroomBox->model()->setData(this->classroomBox->model()->index(1,0),v,Qt::UserRole - 1);
    this->classroomBox->model()->setData(this->classroomBox->model()->index(2,0),v,Qt::UserRole - 1);
    this->classroomBox->model()->setData(this->classroomBox->model()->index(3,0),v,Qt::UserRole - 1);
    this->classroomBox->model()->setData(this->classroomBox->model()->index(4,0),v,Qt::UserRole - 1);

    this->accept = new QPushButton("Spustit Server BigBrothera");

    /////////////////////////////////////////////////////

    this->setStyleSheet("* {font-size: 13px; }"
                        "QWidget#MainWin {"
                        "   border-image: url(:/icons/images/hypno.jpg) 0 0 0 0 stretch stretch;"
                        "}");
    this->portId->setStyleSheet("margin-top: 30px; font-weight: bold; ");
    this->classroom->setStyleSheet("font-weight: bold; ");
    this->portIdEdit->setStyleSheet("margin-top: 30px; width: 100px;");
    this->accept->setStyleSheet("QPushButton { margin-top:10px; padding: 10px; color:black; background-color: rgb(230,230,230); width: 190px; font-size: 16px; }"
                                "QPushButton:hover { color:black; background-color: rgb(200,200,200); }");

    this->portIdEdit->setFixedWidth(50);
    this->classroomBox->setFixedWidth(50);

    /////////////////////////////////////////////////////

    this->baseLayout->addWidget(this->logo,0,0,1,2,Qt::AlignCenter);
    this->baseLayout->addWidget(this->portId,1,0,1,1,Qt::AlignRight);
    this->baseLayout->addWidget(this->portIdEdit,1,1,1,1,Qt::AlignLeft);
    this->baseLayout->addWidget(this->classroom,2,0,1,1,Qt::AlignRight);
    this->baseLayout->addWidget(this->classroomBox,2,1,1,1,Qt::AlignLeft);
    this->baseLayout->addWidget(this->accept,3,0,1,2,Qt::AlignCenter);

    /////////////////////////////////////////////////////

    connect(this->accept,&QPushButton::clicked,this,[this](){
        QString appPath = QCoreApplication::applicationDirPath();
        QString programPath = QDir::toNativeSeparators(appPath + "/bigBrotherServer.exe");

        QString program = "cmd.exe";
        QStringList arguments;

        arguments << "/C"     // Řekne CMD: "Proveď následující příkaz a skonči (ale nové okno zůstane)"
                  << "start"  // Příkaz Windows pro otevření nového okna
                  << "Big Brother Monitor"; // PRVNÍ argument startu je vždy TITULEK okna (důležité!)

        arguments << programPath;

        QProcess::startDetached(program, arguments);

        Plan* plan = new Plan(this->portIdEdit->text().toInt()+1);

        plan->show();

        this->close();
    });
}

MainWin::~MainWin() {
}
