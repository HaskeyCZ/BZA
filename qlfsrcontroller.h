/**
 * @file qlfsrcontroller.h
 *
 * @brief Animation controll bar implementation
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */
#ifndef QLFSRCONTROLLER_H
#define QLFSRCONTROLLER_H

#include <QObject>
#include <QWidget>
#include <qpushbutton.h>

class QLFSRController : public QWidget
{
    Q_OBJECT
public:
    explicit QLFSRController(QWidget *parent = nullptr);
signals:
    void shift();
    void start();
    void pause();
    void step();
    void addBit();
    void removeBit();

public slots:
    void startSlot();
    void pauseSlot();
    void stepSlot();
    void stepFinished();
    void controllerDisabled();
    void controllerEnabled();
    void addBitSlot();
    void removeBitSlot();

private:
    QPushButton * startBtn;
    QPushButton * pauseBtn;
    QPushButton * stepBtn;
    QPushButton * addBtn;
    QPushButton * subBtn;

};

#endif // QLFSRCONTROLLER_H
