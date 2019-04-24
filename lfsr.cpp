/**
 * @file lfsr.cpp
 *
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */
#include "lfsr.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>

LFSR::LFSR(QWidget *parent) : QWidget(parent)
{

}

LFSR::LFSR(QWidget *parent, size_t arraySize) : QWidget(parent)
{
    animationRunning = false;
    QHBoxLayout *layout = new QHBoxLayout;
    data = new int[arraySize];
    this->arraySize = arraySize;
    for (size_t x = 0; x < arraySize; x++) {
        data[x] = 0;
        QBitButton *button = new QBitButton(x,this,QString::number(data[x]));
        button->setStyleSheet("QBitButton {background-color: gray;font: bold \"Times New Roman\";min-width:100px;min-height:100px;font-size: 50px}");
        layout->addWidget(button);
        connect(button, SIGNAL(clicked(size_t)), this, SLOT(buttonClicked(size_t)));
        connect(button, SIGNAL(rightClicked(size_t)), this, SLOT(buttonRightClicked(size_t)));
        connect(this, SIGNAL(updateLabel(size_t, QString)), button, SLOT(updateLabel(size_t, QString)));
        LFSRButtons.append(button);
    }

    feedback = new int[arraySize];

    for (size_t x = 0; x < arraySize; x++) {
        feedback[x] = -1;
    }

    setLayout(layout);
    feedBackSet = false;

}

int LFSR::ShiftRight()
{
    int last = data[arraySize - 1];
    for(size_t x = arraySize-1; x>0; x--) {
        data[x] = data[x-1];
    }
    LFSRButtons.at(0)->setText("N/A");
    return last;
}

void LFSR::DebugPrint()
{
    qDebug() << "[";
    for (size_t x = 0; x < arraySize; x++) {
        qDebug() << x << ":" << data[x] << ", ";
    }
    qDebug() << "]\n";

    qDebug() << "[";
    for (size_t x = 0; x < arraySize; x++) {
        qDebug() << x << ":" << feedback[x] << ", ";
    }
    qDebug() << "]\n";
}

void LFSR::setBit(size_t n)
{
    assert(n < arraySize);
    data[n] = 1;

}

void LFSR::setFeedback(size_t n)
{
    assert(n < arraySize);
    feedback[n] = 1;
}

void LFSR::toogleBit(size_t n)
{
    assert(n < arraySize);
    if (data[n]) {
        emit updateLabel(n,"0");
        clearBit(n);
    } else {
        emit updateLabel(n,"1");
        setBit(n);
    }
}

void LFSR::toogleFeedback(size_t n)
{
    assert(n < arraySize);
    if (feedback[n] == -1) {
        setFeedback(n);
        auto button = LFSRButtons.at(static_cast<int>(n));
        button->setStyleSheet("QBitButton {background-color: cyan;font: bold \"Times New Roman\";min-width:100px;min-height:100px;font-size: 50px;}");
        button->isFeedback = true;
        button->update();

    } else {
        clearFeedback(n);
        auto button = LFSRButtons.at(static_cast<int>(n));
        button->setStyleSheet("QBitButton {background-color: gray;font: bold \"Times New Roman\";min-width:100px;min-height:100px;font-size: 50px;}");
        button->isFeedback = false;
        button->update();

    }
    feedBackSet = false;
    for (size_t x = 0; x < arraySize;x++) {
        if(feedback[x] == 1) {
            feedBackSet = true;
        }
    }
    if(!feedBackSet) {
        emit feedbackNotSet();
    } else {
        emit feedbackSet();
    }
}

void LFSR::clearBit(size_t n)
{
    assert(n < arraySize);
    data[n] = 0;
}

void LFSR::clearFeedback(size_t n)
{
    assert(n < arraySize);
    feedback[n] = -1;
}

void LFSR::buttonClicked(size_t n)
{
    if (animationRunning) return;
    toogleBit(n);
   // DebugPrint();
}

void LFSR::updateBits()
{
    for (size_t x = 1; x < arraySize; x++) {
        emit updateLabel(x,QString::number(data[x]));
        QTimer::singleShot(250,LFSRButtons.at(static_cast<int>(x)),SLOT(changeColor()));
        QTimer::singleShot(500,LFSRButtons.at(static_cast<int>(x)),SLOT(changeColor()));
    }
}

void LFSR::updateFirstBit()
{
    emit updateLabel(0,QString::number(newValue));
    QTimer::singleShot(250,LFSRButtons.at(0),SLOT(changeColor()));
    QTimer::singleShot(500,LFSRButtons.at(0),SLOT(changeColor()));
}

void LFSR::buttonRightClicked(size_t n)
{
    if (animationRunning) return;
    toogleFeedback(n);
    emit feedbackChanged();
}

void LFSR::feedbackAnimationFinished()
{
    bool first = true;

    newValue = 42;

    for (size_t x = 0; x < arraySize; x++) {
        if (feedback[x] == 1) {
            if(first){
                newValue = data[x];
                first = false;
            } else {
               // DebugPrint();
                newValue = newValue ^ data[x];
            }
        }
    }
    prevData = new int[arraySize];
    for (size_t x = 0; x < arraySize;x++) {
        prevData[x] = data[x];
    }
    lastOutput = ShiftRight();
    data[0] = newValue;
    updateBits();
    emit animateXorOutputToNewValue(newValue);

}

void LFSR::animationXorOutputFinished()
{
    updateFirstBit();
}

void LFSR::animationStarted()
{
    animationRunning = true;
}

void LFSR::animationStop()
{
    animationRunning = false;
}

