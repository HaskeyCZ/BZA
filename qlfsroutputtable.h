/**
 * @file qlfsroutputtable.h
 *
 * @brief Output table for representing step history
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */
#ifndef QLFSROUTPUTTABLE_H
#define QLFSROUTPUTTABLE_H

#include "lfsr.h"

#include <QTableWidget>



class QLFSROutputTable : public QTableWidget
{
    Q_OBJECT
public:
    QLFSROutputTable(QWidget *parent);
    void setLFSRModel(LFSR * model) {
        lfsrModel = model;
    }
    int step;
    QString state;
public slots:
    void stepFinished();
    void clearSlot();

signals:

private:
    LFSR * lfsrModel;
};

#endif // QLFSROUTPUTTABLE_H
