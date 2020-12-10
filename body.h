#ifndef BODY_H
#define BODY_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <math.h>
#include <QtDebug>

class Body : public QObject, public QGraphicsItem {
    Q_OBJECT

public: // Variables

private: // Variables
    double x, y;
    double m;
    int r;
    double V0x, V0y;
    double Ax, Ay;
    QString name;

    double T;
    double G;

    float scale;

public: // Methods
    explicit Body(QObject *parent = nullptr, QString name_ = "", double x_ = 0, double y_= 0, double m_= 0, int r_= 0, double V0x_= 0, double V0y_= 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    bool is_empty();

    void acelerate(Body *bod);
    void update();

    double getX() const;
    double getY() const;

    double getM() const;

    QString getName() const;
    float getScale() const;

private: // Methods

};

#endif // BODY_H
