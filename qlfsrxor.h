/**
 * @file qlfsrqor.h
 *
 * @brief Simple XOR representing widget
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */
#ifndef QLFSRXOR_H
#define QLFSRXOR_H

#include <QObject>
#include <QWidget>

class QLFSRXor : public QWidget
{
    Q_OBJECT
public:
    explicit QLFSRXor(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
signals:

public slots:
};

#endif // QLFSRXOR_H
