#ifndef MAINWIN_H
#define MAINWIN_H

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

class MainWin : public QWidget
{
    Q_OBJECT
private:
    QLabel* portId;
    QLabel* logo;
    QLabel* classroom;

    QPixmap* logoPixmap;

    QLineEdit* portIdEdit;

    QComboBox* classroomBox;

    QPushButton* accept;

    QGridLayout* baseLayout;

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();
};
#endif // MAINWIN_H
