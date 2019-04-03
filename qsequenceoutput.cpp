/**
 * @file qsequenceoutput.cpp
 *
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */

#include "qsequenceoutput.h"

QSequenceOutput::QSequenceOutput(QWidget *parent) : QLineEdit(parent)
{
    output = QString("");
}

void QSequenceOutput::stepFinished()
{
    output.append(QString::number(lfsrModel->lastOutput));
    setText(output);
}

void QSequenceOutput::clearSlot()
{
  //  qDebug() << "sequence output reset";
    output.clear();
    setText(output);
}
