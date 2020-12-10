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
    double Ax, Ay;

private: // Variables
    double x, y;
    double m;
    int r;
    double V0x, V0y;
    //double Ax, Ay;
    QString name;

    double T;
    double G;

public: // Methods
    explicit Body(QObject *parent = nullptr, QString name_ = "", double x_ = 0, double y_= 0, double m_= 0, int r_= 0, double V0x_= 0, double V0y_= 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    bool is_empty();

    void calculate_Ax(QList<Body *> bods);
    void calculate_Ay(QList<Body *> bods);

    void calculate_Vx();
    void calculate_Vy();

    void calculate_x();
    void calculate_y();

    double calculate_distance(Body *bod);

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getM() const;

    double getV0x() const;
    double getV0y() const;

    QString getName() const;

private: // Methods

};

#endif // BODY_H
