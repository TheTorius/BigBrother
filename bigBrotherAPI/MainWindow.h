#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QPixmap* logoPixmap;

    QGridLayout* baseLayout;

    QLabel* fileName;
    QLabel* IPaddress;
    QLabel* logo;

    QLineEdit* fileNameEdit;
    QLineEdit* IPaddressEdit;

    QPushButton* accept;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void readXmlConfig(QString filePath);

public slots:
    void startBigBrother();
};
#endif // MAINWINDOW_H
