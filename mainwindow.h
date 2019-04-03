/**
 * @file MainWindow.h
 *
 * @brief MainAppWindow
 *          Handling animation, all connection lines drawn here.
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QParallelAnimationGroup>
#include <QTimer>


#include "lfsr.h"
#include "qlfsrcontroller.h"
#include "qlfsroutputtable.h"
#include "qlfsrxor.h"
#include "qsequenceoutput.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    int nOfBits;
private:
    QTimer * playTimer;
    bool isRunning;
    Ui::MainWindow *ui;
    QWidget *centralWidget;
    LFSR * test;
    QLFSRController * controller;
    QLFSRXor * lfsrXor;
    void drawFeedBackLine(QBitButton * const btn, QLFSRXor * xorWidget, QPainter & p);

    QParallelAnimationGroup *group;
    QSequentialAnimationGroup *seqGroup;
    QList<QLabel*> labels;
    QLabel * xorOutputLabel;
    QLabel * mainOutputLabel;

    QLFSROutputTable * outputTable;
    QSequenceOutput * outputStream;
    QGridLayout *mainLayout;
signals:
    void resetWidgets();
    void enableController();

public slots:
    void redrawFeedbackLines();
    void animateFeedbackFunction();
    void feedbackAnimationFinished();
    void animateXorOutputToNewValue(int newValue);
    void animationXorOutputFinished();
    void addBit();
    void removeBit();
    void reset();
};

#endif // MAINWINDOW_H
