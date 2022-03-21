#ifndef MAPLABEL_H
#define MAPLABEL_H

#include <QLabel>

class maplabel : public QLabel
{
public:
    explicit maplabel(QWidget *parent = 0);

    virtual void mousePressEvent(QMouseEvent *ev);
};

#endif // MAPLABEL_H
