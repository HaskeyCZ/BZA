/**
 * @file qlfsroutputtable.cpp
 *
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */

#include "qlfsroutputtable.h"

#include <QLabel>
#include <QHeaderView>

QLFSROutputTable::QLFSROutputTable(QWidget *parent) : QTableWidget (1, 3, parent)
{
    step = 0;
    QLabel * noStepLbl = new QLabel("Step #",this);
    noStepLbl->setStyleSheet("QLabel { background-color: green; color:white; }");
                noStepLbl->setAlignment(Qt::AlignCenter);

    QLabel * stateLbl = new QLabel("LFSR State",this);
    stateLbl->setStyleSheet("QLabel { background-color: green; color:white; }");
                stateLbl->setAlignment(Qt::AlignCenter);

    QLabel * outputLbl = new QLabel("Output",this);
    outputLbl->setStyleSheet("QLabel { background-color: green; color:white; }");
                outputLbl->setAlignment(Qt::AlignCenter);

    setCellWidget(0,0,noStepLbl);
    setCellWidget(0,1,stateLbl);
    setCellWidget(0,2,outputLbl);
    this->horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    adjustSize();
    setAlternatingRowColors(true);

}

void QLFSROutputTable::stepFinished()
{
    int newRowIndex = rowCount();
    insertRow(newRowIndex);
    auto noStepLbl = new QLabel(QString::number(step), this);
    noStepLbl->setAlignment(Qt::AlignCenter);
    setCellWidget(newRowIndex, 0, noStepLbl);
    step++;
    state = QString();
    state.append("[ ");
    state.append(QString::number(lfsrModel->prevData[0]));
    for (size_t x = 1; x < lfsrModel->arraySize; x++) {
        state.append(", ");
        state.append(QString::number(lfsrModel->prevData[x]));
    }
    state.append(" ]");
    auto stateLbl = new QLabel(state, this);
    stateLbl->setAlignment(Qt::AlignCenter);
    setCellWidget(newRowIndex, 1, stateLbl);
    auto outputLbl = new QLabel(QString::number(lfsrModel->lastOutput),this);
    outputLbl->setAlignment(Qt::AlignCenter);
    setCellWidget(newRowIndex, 2, outputLbl);
}

void QLFSROutputTable::clearSlot()
{
    step = 0;
 //   qDebug() << "table clear";
    setRowCount(1);
}
