#include "plan.h"

Plan::Plan(int port, int numOfPlan, QWidget *parent)
    : QWidget{parent}
{
    QSize* windowSize = new QSize(900,600);
    this->resize(*windowSize);
    this->setWindowIcon(QIcon(":/icons/images/unnamed.jpg"));
    this->setWindowTitle("BigBrother - Server");
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setObjectName("MainWin");
    this->setAttribute(Qt::WA_StyledBackground, true);


    this->setStyleSheet("* {font-size: 13px; }"
                        "QWidget#MainWin {"
                        "   border-image: url(:/icons/images/MIT.png) 0 0 0 0 stretch stretch;"
                        "}");

    ///////////////////////////////////////////////

    for(int i = 0; i < 16; i++) {
        this->array[i] = new QPushButton("MIT" + QString::number(i+1) + "HP",this);
    }
    for(int i = 0; i < 4; i++){
        this->array[i]->move(QPoint(750,490-(89*i)));
    }
    for(int i = 4; i < 8; i++){
        this->array[i]->move(QPoint(610,223+(89*(i-4))));
    }
    for(int i = 8; i < 12; i++){
        this->array[i]->move(QPoint(220,223+(89*(i-8))));
    }
    for(int i = 12; i < 16; i++){
        this->array[i]->move(QPoint(90,223+(89*(i-12))));
    }

    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &Plan::onNewConnection);

    if(!server->listen(QHostAddress::Any, port)) {
        qDebug() << "Server se nepodarilo spustit!";
    } else {
        qDebug() << "Server bezi a ceka na bonzaky...";
    }

}

void Plan::onNewConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Plan::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

void Plan::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(!socket) return;

    while(socket->bytesAvailable() >= (qint64)sizeof(Packet)) {
        QByteArray data = socket->read(sizeof(Packet));

        const Packet *pkt = reinterpret_cast<const Packet*>(data.constData());

        QString pcName = QString::fromLatin1(pkt->hostname); // Název PC (např. MIT1HP)
        QString message = QString::fromLatin1(pkt->message); // Zpráva (např. "chrome")
        int type = pkt->type;

        qDebug() << "Prichozi alert od:" << pcName << "Zprava:" << message;

        updateButtonStatus(pcName, type, message);
    }
}

void Plan::updateButtonStatus(QString name, int type, QString msg)
{
    for(int i = 0; i < 16; i++) {
        if(QString::compare(this->array[i]->text(), msg, Qt::CaseInsensitive) == 0) {

            QPushButton *btn = this->array[i];
            btn->setStyleSheet("background-color: rgb(153,255,0)");
        }
    }
}
