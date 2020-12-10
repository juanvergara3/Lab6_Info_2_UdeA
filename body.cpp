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

    T = 0.01;
    //G = 6.67384e-11;
    G = 6.67384*pow(10,-11);
}

QRectF Body::boundingRect() const {
        return QRectF(-r, -r, 2*r, 2*r);
}
void Body::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::magenta);
    painter->drawEllipse(boundingRect());
}

bool Body::is_empty() {
    if(r == 0 || m == 0.0)
        return true;
    else
        return false;
}

void Body::calculate_Ax(QList<Body *> bods) {
    //double aux = Ax;
    double aux = 0;

    Ax= 0;

    for(int k = 0; k<bods.size(); k++){

        if(bods.at(k)->getName() != name){

            //aux = (G*(bods.at(k)->getM()*(bods.at(k)->getX() - x))/(pow(calculate_distance(bods.at(k)), 3)));
            aux = (G*(bods.at(k)->getM()*(bods.at(k)->getX() - x))/(pow(calculate_distance(bods.at(k)), 2)));

            Ax = aux;
        }

    }
    //Ax *= G;

    //aux *= G;
    //Ax = aux;
}
void Body::calculate_Ay(QList<Body *> bods) {
    //double aux = Ay;
    double aux = 0;

    Ay = 0;

    for(int k = 0; k<bods.size(); k++){

        if(bods.at(k)->getName() != name){

            //aux = (G*(bods.at(k)->getM()*(bods.at(k)->getY() - y)) / (pow(calculate_distance(bods.at(k)), 3)));
            aux = (G*(bods.at(k)->getM()*(bods.at(k)->getY() - y)) / (pow(calculate_distance(bods.at(k)), 2)));

            Ay = aux;
        }

    }
    //Ay *= G;

    //aux *= G;
    //Ay = aux;
}

void Body::calculate_Vx() {
    V0x = V0x + Ax*T;
}
void Body::calculate_Vy() {
    V0y = V0y + Ay*T;
}

void Body::calculate_x() {
    x = x + V0x*T;
}
void Body::calculate_y() {
    y = y + V0y*T;
}

double Body::calculate_distance(Body *bod) {
    return pow((pow((bod->getX())-x,2)+pow((bod->getY() - y),2)), 1/2);
    //return sqrt( pow((bod->getX() - x), 2) + pow((bod->getY() - y), 2) );
}

double Body::getX() const{
    return x;
}
void Body::setX(double value){
    x = value;
}
double Body::getY() const{
    return y;
}
void Body::setY(double value){
    y = value;
}

double Body::getM() const{
    return m;
}

double Body::getV0x() const{
    return V0x;
}
double Body::getV0y() const{
    return V0y;
}

QString Body::getName() const {
    return name;
}
