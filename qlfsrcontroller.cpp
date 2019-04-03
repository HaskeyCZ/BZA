/**
 * @file qlfsrcontroller.cpp
 *
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */

#include "qlfsrcontroller.h"

#include <qboxlayout.h>
#include <QStyle>
#include <QTimer>
#include <QDebug>

QLFSRController::QLFSRController(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;

    startBtn = new QPushButton(this);
    startBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    startBtn->setDisabled(true);

    pauseBtn = new QPushButton(this);
    pauseBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    pauseBtn->setDisabled(true);

    stepBtn = new QPushButton("Step", this);
    stepBtn->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    stepBtn->setDisabled(true);
    connect(stepBtn, SIGNAL(clicked()), this, SLOT(stepSlot()));
    connect(startBtn, SIGNAL(clicked()), this, SLOT(startSlot()));
    connect(pauseBtn, SIGNAL(clicked()), this, SLOT(pauseSlot()));

    addBtn = new QPushButton("+", this);
    subBtn = new QPushButton("-", this);
    connect(addBtn, SIGNAL(clicked()), this, SLOT(addBitSlot()));
    connect(subBtn, SIGNAL(clicked()), this, SLOT(removeBitSlot()));
    layout->addWidget(startBtn);
    layout->addWidget(pauseBtn);
    layout->addWidget(stepBtn);
    layout->addWidget(addBtn);
    layout->addWidget(subBtn);
    setLayout(layout);

    QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    setSizePolicy(policy);
}


void QLFSRController::startSlot() {
    stepBtn->setDisabled(true);
    pauseBtn->setEnabled(true);
    startBtn->setDisabled(true);

    addBtn->setDisabled(true);
    subBtn->setDisabled(true);
    emit start();
}
void QLFSRController::pauseSlot() {
    stepBtn->setDisabled(true);
    pauseBtn->setDisabled(true);
    startBtn->setDisabled(true);

    addBtn->setDisabled(true);
    subBtn->setDisabled(true);
    emit pause();

}
void QLFSRController::stepSlot() {
    stepBtn->setDisabled(true);
    pauseBtn->setDisabled(true);
    startBtn->setDisabled(true);
    addBtn->setDisabled(true);
    subBtn->setDisabled(true);

    emit step();
}

void QLFSRController::stepFinished()
{
    stepBtn->setEnabled(true);
    pauseBtn->setDisabled(true);
    startBtn->setEnabled(true);
    addBtn->setEnabled(true);
    subBtn->setEnabled(true);
}

void QLFSRController::controllerDisabled()
{
    stepBtn->setDisabled(true);
    pauseBtn->setDisabled(true);
    startBtn->setDisabled(true);

}

void QLFSRController::controllerEnabled()
{
    stepBtn->setEnabled(true);
    pauseBtn->setDisabled(true);
    startBtn->setEnabled(true);

    addBtn->setEnabled(true);
    subBtn->setEnabled(true);

}

void QLFSRController::addBitSlot()
{
    emit addBit();
}

void QLFSRController::removeBitSlot()
{
    emit removeBit();
}

