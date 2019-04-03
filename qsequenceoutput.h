/**
 * @file qsequenceoutput.h
 *
 * @brief Represents text field for showing output bit stream.
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */
#ifndef QSEQUENCEOUTPUT_H
#define QSEQUENCEOUTPUT_H

#include "lfsr.h"

#include <QLineEdit>
#include <QWidget>
#include <QObject>

class QSequenceOutput : public QLineEdit
{
    Q_OBJECT
public:
    explicit QSequenceOutput(QWidget *parent = nullptr);

    void setLFSRModel(LFSR * model) {
        lfsrModel = model;
    }
signals:

public slots:
    void stepFinished();
    void clearSlot();

private:
    QString output;
    LFSR * lfsrModel;
};

#endif // QSEQUENCEOUTPUT_H
