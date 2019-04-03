/**
 * @file qlfsrxor.cpp
 *
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */

#include "qlfsrxor.h"

#include <QLabel>
#include <QPainter>
#include <QSizePolicy>
#include <QBoxLayout>
QLFSRXor::QLFSRXor(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    setLayout(layout);
    setMinimumSize(100,100);
    QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    setSizePolicy(policy);

    update();
}

void QLFSRXor::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawRect(0, 0, this->width()-1, this->height()-1);
    painter.drawText(this->width()/2-20, this->height()/2, "XOR");
    // QWidget::paintEvent(event);
    painter.end();
}
