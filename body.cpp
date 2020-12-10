#include "body.h"

Body::Body(QObject *parent, QString name_, QString color_, double x_, double y_, double m_, int r_, double V0x_, double V0y_) : QObject(parent) {
    name = name_;
    color = color_;
    x = x_;
    y = y_;
    m = m_;
    r = r_;
    V0x = V0x_;
    V0y = V0y_;
    Ax = 0;
    Ay = 0;

    scale = 0.05;

    label = new QLabel;
    label->setText(name);

    T = 0.1;
    //G = 6.67384e-11;
    G = 6.67384*pow(10,-11);
}
Body::~Body() {
    delete label;
}

QRectF Body::boundingRect() const {
        //return QRectF(-r, -r, 2*r, 2*r);
        return QRectF(-1*scale*r, -1*scale*r, 2*scale*r, 2*scale*r);
}
void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    if(color == "Yellow")
        painter->setBrush(Qt::yellow);
    else if(color == "Blue")
        painter->setBrush(Qt::blue);
    else if(color == "Red")
        painter->setBrush(Qt::red);
    else if(color == "Magenta")
        painter->setBrush(Qt::magenta);
    else if(color == "Green")
        painter->setBrush(Qt::green);
    else if(color == "Black")
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

    setPos(-1*x*scale, -1*y*scale);
}

double Body::getX() const{
    return x;
}
double Body::getY() const{
    return y;
}

float Body::getLabelX() const
{
    return (x*scale) + 2.5;
}
float Body::getLabelY() const
{
    return ((y-r)*scale) - 5;
}

double Body::getM() const{
    return m;
}
int Body::getR() const {
    return r;
}

QString Body::getName() const {
    return name;
}
float Body::getScale() const {
    return scale;
}
