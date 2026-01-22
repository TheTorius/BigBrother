#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QSize* windowSize = new QSize(325,275);
    this->resize(*windowSize);
    this->setWindowIcon(QIcon(":/icons/images/unnamed.jpg"));
    this->setWindowTitle("BigBrother");
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setObjectName("MainWin");
    this->setAttribute(Qt::WA_StyledBackground, true);

    /////////////////////////////////////////////////////

    this->baseLayout = new QGridLayout();
    this->setLayout(this->baseLayout);

    this->logoPixmap = new QPixmap(":/icons/images/unnamed.jpg");

    this->fileName = new QLabel("Název souboru: ");
    this->IPaddress = new QLabel("IP adresa serveru: ");
    this->logo = new QLabel();
    this->logo->setPixmap(this->logoPixmap->scaledToWidth(160));
    this->port = new QLabel("Číslo portu: ");
    this->maxWindowCount = new QLabel("Max oken: ");

    this->fileNameEdit = new QLineEdit();
    this->IPaddressEdit = new QLineEdit();
    this->portEdit = new QLineEdit();
    this->maxWindowCountEdit = new QLineEdit();

    this->accept = new QPushButton("Spustit Big Brothera");

    /////////////////////////////////////////////////////

    this->setStyleSheet("* {font-size: 13px; }"
                        "QWidget#MainWin {"
                        "   border-image: url(:/icons/images/hypno.jpg) 0 0 0 0 stretch stretch;"
                        "}");
    this->fileName->setStyleSheet("margin-top: 30px; font-weight: bold; ");
    this->fileNameEdit->setStyleSheet("margin-top: 30px; width: 100px;");
    this->IPaddress->setStyleSheet("font-weight: bold; ");
    this->port->setStyleSheet("font-weight: bold; ");
    this->maxWindowCount->setStyleSheet("font-weight: bold; ");
    this->IPaddressEdit->setStyleSheet("width: 100px;");
    this->accept->setStyleSheet("QPushButton { margin-top:10px; padding: 10px; color:black; background-color: rgb(230,230,230); width: 180px; font-size: 16px; }"
                                "QPushButton:hover { color:black; background-color: rgb(200,200,200); }");

    this->fileNameEdit->setFixedWidth(140);
    this->IPaddressEdit->setFixedWidth(140);
    this->portEdit->setFixedWidth(50);
    this->maxWindowCountEdit->setFixedWidth(50);

    /////////////////////////////////////////////////////

    this->baseLayout->addWidget(this->logo,0,0,1,2,Qt::AlignCenter);
    this->baseLayout->addWidget(this->fileName,1,0,1,1,Qt::AlignRight);
    this->baseLayout->addWidget(this->IPaddress,2,0,1,1,Qt::AlignRight);
    this->baseLayout->addWidget(this->fileNameEdit,1,1,1,1,Qt::AlignLeft);
    this->baseLayout->addWidget(this->IPaddressEdit,2,1,1,1,Qt::AlignLeft);
    this->baseLayout->addWidget(this->port,3,0,1,1,Qt::AlignRight);
    this->baseLayout->addWidget(this->portEdit,3,1,1,1,Qt::AlignLeft);
    this->baseLayout->addWidget(this->maxWindowCount,4,0,1,1,Qt::AlignRight);
    this->baseLayout->addWidget(this->maxWindowCountEdit,4,1,1,1,Qt::AlignLeft);
    this->baseLayout->addWidget(this->accept,5,0,1,2,Qt::AlignCenter);

    readXmlConfig("config.xml");

    connect(this->accept,SIGNAL(clicked(bool)),this,SLOT(startBigBrother()));
}

MainWindow::~MainWindow() {}

void MainWindow::startBigBrother()
{
    QString appPath = QCoreApplication::applicationDirPath();
    QString programPath = QDir::toNativeSeparators(appPath + "/bigBrother.exe");

    QString program = "cmd.exe";
    QStringList arguments;

    arguments << "/C"     // Řekne CMD: "Proveď následující příkaz a skonči (ale nové okno zůstane)"
              << "start"  // Příkaz Windows pro otevření nového okna
              << "Big Brother Monitor"; // PRVNÍ argument startu je vždy TITULEK okna (důležité!)

   arguments << programPath
              << this->fileNameEdit->text()
              << this->IPaddressEdit->text()
              << this->portEdit->text()
              << this->maxWindowCountEdit->text();

    if(this->fileNameEdit->text() == "" || this->IPaddressEdit->text() == "" || this->portEdit->text() == "" || this->maxWindowCountEdit->text() == ""){
       QMessageBox* confirmSettings = new QMessageBox();
       confirmSettings->setWindowIcon(QIcon(":/icons/images/unnamed.jpg"));
       confirmSettings->setWindowTitle("Upozornění");
       confirmSettings->setText("Některé z políček, které se v programu nacházejí, jsou nevyplněná. Dokud nebudou obsahovat řetězec, pak nemůžete pokračovat!");
       confirmSettings->setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
       confirmSettings->setDefaultButton(QMessageBox::Close);
       confirmSettings->setIcon(QMessageBox::Question);

       confirmSettings->exec();
       return;
    }

    QProcess::startDetached(program, arguments);

    QCoreApplication::quit();
}

void MainWindow::readXmlConfig(QString filePath)
{
    QDomDocument doc;
    QString appPath = QCoreApplication::applicationDirPath();
    QString path = QDir::toNativeSeparators(appPath + "/" + filePath);

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Chyba: Nelze otevřít soubor" << path;
        return;
    }

    if (!doc.setContent(&file)) {
        qDebug() << "Chyba: XML soubor je poškozený nebo prázdný.";
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();

    QDomNode node = root.firstChild();

    while (!node.isNull()) {
        QDomElement e = node.toElement(); // Převedeme node na element

        if (!e.isNull()) {
            if (e.tagName() == "server") {
                QString ip = e.attribute("ip","");
                QString port = e.attribute("port","");

                this->IPaddressEdit->setText(ip);
                this->portEdit->setText(port);
            }
            else if (e.tagName() == "file") {
                QString fileName = e.attribute("fileName", "");

                this->fileNameEdit->setText(fileName);
            } else if(e.tagName() == "windows") {
                QString maxWinCount = e.attribute("max","");

                this->maxWindowCountEdit->setText(maxWinCount);
            }
        }

        node = node.nextSibling();
    }
}
