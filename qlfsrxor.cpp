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
    setMinimumSize(150,150);
    QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    setSizePolicy(policy);

    update();
}

void QLFSRXor::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(QPen(Qt::black, 5));
    painter.drawRect(0, 0, this->width()-1, this->height()-1);
    QFont font=painter.font() ;
     font.setPointSize ( 25 );
     font.setWeight(QFont::DemiBold);
     painter.setFont(font);
    painter.drawText(this->width()/2-50, this->height()/2, "XOR");
    // QWidget::paintEvent(event);
    painter.end();
}
