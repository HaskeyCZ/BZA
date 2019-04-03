/**
 * @file qbitbutton.h
 *
 * @brief Push button to represent one register bit.
 *        Handling right and left click events, animating
 *         shift movement and value update by color change
 * @ingroup LFSRBZA
 *
 * @author Jan Suchánek
 * Contact: xsucha09@stud.fit.vutbr.cz
 *
 */
#ifndef QBITBUTTON_H
#define QBITBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QPropertyAnimation>

class QBitButton : public QPushButton
{
    Q_OBJECT
public:
    QBitButton(size_t index, QWidget * parent, QString label);
    bool isFeedback;
private:
    size_t index;
    QPropertyAnimation *anim4;
signals:
    void clicked(size_t index);
    void rightClicked(size_t index);

private slots:
    void emitId();
    void updateLabel(size_t index, QString newLabel);
    void mousePressEvent(QMouseEvent *e);
    void changeColor();
    void movementEnd();

};

#endif // QBITBUTTON_H
