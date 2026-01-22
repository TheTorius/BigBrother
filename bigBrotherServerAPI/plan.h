#ifndef PLAN_H
#define PLAN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include <QGridLayout>
#include <QProcess>
#include <QCoreApplication>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QIcon>
#include <QStyleOption>
#include <QPainter>
#include <QtXml/QDomDocument>
#include <QComboBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QVariant>
#include <QTcpServer>
#include <QTcpSocket>

#pragma pack(push, 1)
struct Packet {
    char hostname[16];
    int type;
    long long timestamp;
    char message[64];
};
#pragma pack(pop)

class Plan : public QWidget
{
    Q_OBJECT
    QPushButton* array[16];
    QTcpServer *server;

private slots:
    void onNewConnection(); // Někdo se připojil
    void onReadyRead();
public:
    explicit Plan(int port, int numOfPlan = 0, QWidget *parent = nullptr);
    void updateButtonStatus(QString name, int type, QString msg);

signals:
};

#endif // PLAN_H
