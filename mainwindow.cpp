/**
 * @file mainwindow.cpp
 *
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <qpainter.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    playTimer = new QTimer(this);
    playTimer->setInterval(10000);
    connect(playTimer,SIGNAL(timeout()), this, SLOT(animateFeedbackFunction()));
    isRunning = false;
    nOfBits = 4;
    centralWidget = new QWidget (this);
    setCentralWidget(centralWidget);

   mainLayout = new QGridLayout(centralWidget);
    test = new LFSR(centralWidget, static_cast<size_t>(nOfBits));

    controller = new QLFSRController();
    lfsrXor = new QLFSRXor;

    outputTable = new QLFSROutputTable(this);
    outputTable->setLFSRModel(test);

    outputStream = new QSequenceOutput(this);
    outputStream->setLFSRModel(test);
    connect(test, SIGNAL(feedbackChanged()), this, SLOT(redrawFeedbackLines()));
    connect(test,SIGNAL(feedbackSet()), controller, SLOT(controllerEnabled()));
    connect(test,SIGNAL(feedbackNotSet()), controller, SLOT(controllerDisabled()));
    connect(test,SIGNAL(animateXorOutputToNewValue(int)), this, SLOT(animateXorOutputToNewValue(int)));
    connect(test, SIGNAL(feedbackChanged()), outputTable, SLOT(clearSlot()));
    connect(test, SIGNAL(feedbackChanged()), outputStream, SLOT(clearSlot()));

    connect(controller, SIGNAL(addBit()), this, SLOT(addBit()));
    connect(controller, SIGNAL(removeBit()), this, SLOT(removeBit()));

    connect(this, SIGNAL(resetWidgets()), outputTable,SLOT(clearSlot()));
    connect(this, SIGNAL(resetWidgets()), outputStream,SLOT(clearSlot()));
    connect(this, SIGNAL(resetWidgets()), controller,SLOT(controllerDisabled()));
    connect(this, SIGNAL(resetWidgets()), this,SLOT(reset()));



    connect(controller, SIGNAL(step()), this, SLOT(animateFeedbackFunction()));
    connect(controller, SIGNAL(start()), playTimer, SLOT(start()));
    connect(controller, SIGNAL(start()), playTimer, SIGNAL(timeout()));
    connect(controller, SIGNAL(pause()), playTimer, SLOT(stop()));

    connect(controller, SIGNAL(start()), test,SLOT(animationStarted()));
    connect(controller, SIGNAL(pause()), test,SLOT(animationStop()));



    mainLayout->addWidget(test,1,1);
    mainLayout->addWidget(controller,10,1);
    mainLayout->addWidget(lfsrXor,5,2,2,2);
    mainLayout->addWidget(outputTable,1,3,10,4);
    mainLayout->addWidget(outputStream,11,4,1,3);
    mainLayout->addWidget(new QLabel("Output sequence: ", this), 11,3);
    setMinimumSize(1200,300);
    QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    setSizePolicy(policy);

    //connect(this, SIGNAL(resetWidgets()), ,SLOT());
    //connect(this, SIGNAL(resetWidgets()), ,SLOT());
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    for (size_t x = 0; x < test->arraySize; x++) {
        if (test->feedback[x] == 1) {
            drawFeedBackLine(test->LFSRButtons.at(static_cast<int>(x)), lfsrXor, p);
        }
    }
    p.drawLine( QPoint(lfsrXor->pos().x(), lfsrXor->pos().y()+lfsrXor->height()/2), QPoint(10,lfsrXor->pos().y()+lfsrXor->height()/2));
    p.drawLine( QPoint(10,lfsrXor->pos().y()+lfsrXor->height()/2),QPoint(10,test->LFSRButtons.at(0)->pos().y()+test->LFSRButtons.at(0)->height()));
    p.drawLine( QPoint(10,test->LFSRButtons.at(0)->pos().y()+test->LFSRButtons.at(0)->height()), QPoint(test->LFSRButtons.at(0)->pos().x()+test->LFSRButtons.at(0)->width()/2,test->LFSRButtons.at(0)->pos().y()+test->LFSRButtons.at(0)->height()));
    p.drawLine( QPoint(
                    test->LFSRButtons.at(test->arraySize-1)->pos().x()+test->LFSRButtons.at(test->arraySize-1)->width(),
                    test->LFSRButtons.at(test->arraySize-1)->pos().y()+test->LFSRButtons.at(test->arraySize-1)->height()),
                 QPoint(
                     test->LFSRButtons.at(test->arraySize-1)->pos().x()+test->LFSRButtons.at(test->arraySize-1)->width()+260,
                    test->LFSRButtons.at(test->arraySize-1)->pos().y()+test->LFSRButtons.at(test->arraySize-1)->height())
                );
}

void MainWindow::drawFeedBackLine(QBitButton * const btn, QLFSRXor *xorWidget, QPainter& p)
{
    p.drawLine(QPoint(btn->pos().x()+btn->width()/2, btn->pos().y()+btn->height()/2), QPoint(xorWidget->pos().x()+xorWidget->width()/2, xorWidget->pos().y()+xorWidget->height()/2));
}

void MainWindow::redrawFeedbackLines()
{
    update();
}

void MainWindow::animateFeedbackFunction()
{
    group = new QParallelAnimationGroup;

    QList<QPropertyAnimation *> animations;
    for (size_t x = 0; x < test->arraySize; x++) {
        if (test->feedback[x] == 1) {
            auto btn = test->LFSRButtons.at(x);
            QLabel * lbl = new QLabel(QString::number(test->data[x]),this);
            labels.append(lbl);
            lbl->setStyleSheet("QLabel { background-color : red; color : blue; }");
            lbl->setAlignment(Qt::AlignCenter);
            lbl->show();
            QPropertyAnimation * animation;
            animation = new QPropertyAnimation(lbl, "geometry");
            animation->setDuration(3000);
            animation->setStartValue(QRect(btn->pos().x()+btn->width()/2, btn->pos().y()+btn->height()/2,30, 30));
            animation->setEndValue(QRect(lfsrXor->pos().x()+lfsrXor->width()/2,lfsrXor->pos().y()+lfsrXor->height()/2,30, 30));
            animations.append(animation);
         //   qDebug() << animations.size();
        }
    }

    mainOutputLabel = new QLabel(QString("output: ")+QString::number(test->data[test->arraySize-1]),this);
    mainOutputLabel->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    mainOutputLabel->setAlignment(Qt::AlignCenter);
    mainOutputLabel->show();

    QPropertyAnimation *anim4 = new QPropertyAnimation(mainOutputLabel,"geometry");
    anim4->setDuration(3000);
    anim4->setStartValue(QRect(test->LFSRButtons.at(test->arraySize-1)->pos().x(), test->LFSRButtons.at(test->arraySize-1)->pos().y(),130, 30));
    anim4->setEndValue(QRect(test->LFSRButtons.at(test->arraySize-1)->pos().x()+130, test->LFSRButtons.at(test->arraySize-1)->pos().y(), 130, 30));


 //   qDebug() << group->state();
    for (int x = 0;x<animations.size();x++) {
        group->addAnimation(animations.at(x));
    }
    group->addAnimation(anim4);
    group->start(QAbstractAnimation::DeleteWhenStopped);
    connect(group, SIGNAL(finished()), this, SLOT(feedbackAnimationFinished()));
    connect(group, SIGNAL(finished()), test, SLOT(feedbackAnimationFinished()));

}

void MainWindow::feedbackAnimationFinished()
{
    for(auto label : labels) {
        label->hide();
        delete label;
    }
    labels.clear();
    delete mainOutputLabel;
}

void MainWindow::animateXorOutputToNewValue(int newValue)
{
    seqGroup = new QSequentialAnimationGroup();
    xorOutputLabel = new QLabel(QString::number(newValue),this);
    xorOutputLabel->setStyleSheet("QLabel { background-color : green; color : black; }");
    xorOutputLabel->setAlignment(Qt::AlignCenter);
    xorOutputLabel->show();



    QPropertyAnimation * anim1 = new QPropertyAnimation(xorOutputLabel,"geometry");
    QPropertyAnimation *anim2 = new QPropertyAnimation(xorOutputLabel,"geometry");
    QPropertyAnimation *anim3 = new QPropertyAnimation(xorOutputLabel,"geometry");
    anim1->setDuration(3000);
    anim1->setStartValue(QRect(lfsrXor->pos().x(), lfsrXor->pos().y()+lfsrXor->height()/2,30, 30));
    anim1->setEndValue(QRect(10,lfsrXor->pos().y()+lfsrXor->height()/2, 30, 30));

    anim2->setDuration(2000);
    anim2->setStartValue(QRect(10,lfsrXor->pos().y()+lfsrXor->height()/2, 30, 30));
    anim2->setEndValue(QRect(10,test->LFSRButtons.at(0)->pos().y()+test->LFSRButtons.at(0)->height(), 30, 30));

    anim3->setDuration(1000);
    anim3->setStartValue(QRect(10,test->LFSRButtons.at(0)->pos().y()+test->LFSRButtons.at(0)->height(), 30, 30));
    anim3->setEndValue(QRect(test->LFSRButtons.at(0)->pos().x()+test->LFSRButtons.at(0)->width()/2,test->LFSRButtons.at(0)->pos().y()+test->LFSRButtons.at(0)->height(),30,30));


    seqGroup->addAnimation(anim1);
    seqGroup->addAnimation(anim2);
    seqGroup->addAnimation(anim3);

    seqGroup->start(QAbstractAnimation::DeleteWhenStopped);
    connect(seqGroup, SIGNAL(finished()), this, SLOT(animationXorOutputFinished()));
    connect(seqGroup, SIGNAL(finished()), test, SLOT(animationXorOutputFinished()));
    connect(seqGroup, SIGNAL(finished()), outputTable, SLOT(stepFinished()));
    connect(seqGroup, SIGNAL(finished()), outputStream, SLOT(stepFinished()));

    if(!playTimer->isActive()) {
        connect(seqGroup, SIGNAL(finished()), controller, SLOT(stepFinished()));

    }

}

void MainWindow::animationXorOutputFinished()
{
    delete xorOutputLabel;
    if (!playTimer->isActive())
    {
    connect(this, SIGNAL(enableController()), controller, SLOT(controllerEnabled()));
    emit enableController();
    }
}

void MainWindow::addBit()
{
    nOfBits++;
    emit resetWidgets();
}

void MainWindow::removeBit()
{
    nOfBits--;
    if (nOfBits < 1) {
        nOfBits = 1;
    }
    emit resetWidgets();
}

void MainWindow::reset()
{
    disconnect(this, 0, 0, 0);
    disconnect(test, 0, 0, 0);
    test->hide();
    mainLayout->removeWidget(test);
    delete test;

    isRunning = false;
    if (playTimer->isActive()) {
        playTimer->stop();
    }
    test = new LFSR(centralWidget, nOfBits);
    mainLayout->addWidget(test,1,1);


    outputTable->setLFSRModel(test);
    outputStream->setLFSRModel(test);
    connect(test, SIGNAL(feedbackChanged()), this, SLOT(redrawFeedbackLines()));
    connect(test,SIGNAL(feedbackSet()), controller, SLOT(controllerEnabled()));
    connect(test,SIGNAL(feedbackNotSet()), controller, SLOT(controllerDisabled()));
    connect(test,SIGNAL(animateXorOutputToNewValue(int)), this, SLOT(animateXorOutputToNewValue(int)));
        connect(test, SIGNAL(feedbackChanged()), outputTable, SLOT(clearSlot()));
        connect(test, SIGNAL(feedbackChanged()), outputStream, SLOT(clearSlot()));


        connect(controller, SIGNAL(start()), test,SLOT(animationStarted()));
        connect(controller, SIGNAL(pause()), test,SLOT(animationStop()));

    connect(this, SIGNAL(resetWidgets()), outputTable,SLOT(clearSlot()));
    connect(this, SIGNAL(resetWidgets()), outputStream,SLOT(clearSlot()));
    connect(this, SIGNAL(resetWidgets()), controller,SLOT(controllerDisabled()));
    connect(this, SIGNAL(resetWidgets()), this,SLOT(reset()));

    update();
}
