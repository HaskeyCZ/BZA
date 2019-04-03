/**
 * @file lfsr.h
 *
 * @brief Simple LFSR model
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */

#ifndef LFSR_H
#define LFSR_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include "qbitbutton.h"

class LFSR : public QWidget
{
    Q_OBJECT

public:
    explicit LFSR(QWidget *parent = nullptr);
    LFSR(QWidget *parent = nullptr, size_t arraySize = 8);

    int ShiftRight();
    void DebugPrint();
    void setBit(size_t n);
    void setFeedback(size_t n);
    void toogleBit(size_t n);

    void clearBit(size_t n);
    void clearFeedback(size_t n);

    void toogleFeedback(size_t n);

    QList<QBitButton*> LFSRButtons;

    int * data;
    int * prevData;
    int * feedback;
    size_t arraySize;
    int lastOutput;
    int newValue;

private:
    bool feedBackSet;
    bool animationRunning;



signals:
    void updateLabel(size_t index, QString newLabel);
    void feedbackChanged();
    void animateXorOutputToNewValue(int newValue);
    void feedbackSet();
    void feedbackNotSet();

public slots:
    void buttonClicked(size_t n);
    void updateBits();
    void updateFirstBit();
    void buttonRightClicked(size_t n);
    void feedbackAnimationFinished();
    void animationXorOutputFinished();
    void animationStarted();
    void animationStop();
};

#endif // LFSR_H
