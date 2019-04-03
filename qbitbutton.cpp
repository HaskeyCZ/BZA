/**
 * @file qbitbutton.cpp
 *
 *
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */

#include "qbitbutton.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPalette>
#include <QTimer>

QBitButton::QBitButton(size_t index, QWidget * parent, QString label) : QPushButton (parent)
{
    this->index = index;
    setText(label);
    isFeedback = false;
}

void QBitButton::emitId()
{
    emit clicked(index);
}

void QBitButton::updateLabel(size_t n,QString newLabel)
{

    if (n == index) setText(newLabel);

   // qDebug() << "newLabel:" << newLabel;
}

void QBitButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
           emit rightClicked(index);
    else emit clicked(index);
}

void QBitButton::changeColor()
{

    QColor currentColor = this->palette().color(QPalette::Button);
     if (currentColor == Qt::yellow) {
         if (index != 0) {
         QPropertyAnimation *anim4 = new QPropertyAnimation(this,"geometry");
         anim4->setDuration(100);
         anim4->setStartValue(QRect(pos().x(), pos().y(),width(), height()));
         anim4->setEndValue(QRect(pos().x()+width(), pos().y(),width(), height()));
         connect(anim4, SIGNAL(finished()), this, SLOT(movementEnd()));
         anim4->start(QAbstractAnimation::DeleteWhenStopped);
         }
        if(isFeedback)
            setStyleSheet("QBitButton {background-color: cyan;}");
        else
            setStyleSheet("QBitButton {background-color: gray;}");
     }
     else
         setStyleSheet("QBitButton {background-color: yellow;}");

}

void QBitButton::movementEnd()
{
    setGeometry(QRect(pos().x()-width(), pos().y(),width(), height()));
    update();
}
