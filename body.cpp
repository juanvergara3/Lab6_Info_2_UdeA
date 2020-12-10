#include "body.h"

Body::Body(QObject *parent, QString name_, double x_, double y_, double m_, int r_, double V0x_, double V0y_) : QObject(parent) {
    name = name_;
    x = x_;
    y = y_;
    m = m_;
    r = r_;
    V0x = V0x_;
    V0y = V0y_;
    Ax = 0;
    Ay = 0;

    scale = 0.05;

    T = 0.1;
    //G = 6.67384e-11;
    G = 6.67384*pow(10,-11);
}

QRectF Body::boundingRect() const {
        //return QRectF(-r, -r, 2*r, 2*r);
        return QRectF(-1*scale*r, -1*scale*r, 2*scale*r, 2*scale*r);
}
void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::black);
    painter->drawEllipse(boundingRect());
}

bool Body::is_empty() {
    if(r == 0 || m == 0.0)
        return true;
    else
        return false;
}

void Body::acelerate(Body *bod){

    double dis;
    dis = pow((pow((bod->getX() - x), 2)+pow((bod->getY() - y),2)), 1/2);

    Ax = G*bod->getM()*(bod->getX()-x)/pow(dis, 2);
    Ay = G*bod->getM()*(bod->getY()-y)/pow(dis, 2);
}

void Body::update(){
    V0x = V0x + (Ax*T);
    V0y = V0y + (Ay*T);
    x = x + (V0x*T);
    y = y + (V0y*T);

    setPos(x*scale, y*scale);
}

double Body::getX() const{
    return x;
}
double Body::getY() const{
    return y;
}

double Body::getM() const{
    return m;
}

QString Body::getName() const {
    return name;
}
float Body::getScale() const {
    return scale;
}
