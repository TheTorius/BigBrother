#ifndef MAINWIN_H
#define MAINWIN_H

#include "plan.h"

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
