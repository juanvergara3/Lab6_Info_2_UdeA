#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new QGraphicsScene;
    //scene->setSceneRect(0,0, ui->graphicsView->width(), ui->graphicsView->height());
    scene->setSceneRect(ui->graphicsView->width()/2,  ui->graphicsView->height()/2, ui->graphicsView->width(), ui->graphicsView->height());

    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();

    T = 0.01;
    //G = 6.673e-11;
    G = 6.67384*pow(10,-11);

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(simulation()));
}
MainWindow::~MainWindow() {

    delete timer;
    delete ui;
}

int MainWindow::new_y(int y_max, int y_){
    //return y_max-y_;
    return y_/1000;
}
int MainWindow::new_x(int x_max, int x_) {
    //return x_max-x_;
    return x_/1000;
}

double MainWindow::get_Ax(Body * self, Body * comp) {
//    double aux = 0;

//    for(int w = 0; w<bodies.size(); w++){

//        if(bodies.at(w)->getName() != self->getName()){

//            aux += ((bodies.at(w)->getM())/(pow(self->calculate_distance(bodies.at(w)), 3))) * (bodies.at(w)->getX() - self->getX());
//        }

//    }
//    aux *= G;

//    return aux;
    return (G*(comp->getM()*(comp->getX() - self->getX()))/(pow(calculate_distance(self, comp), 3)));
}
double MainWindow::get_Ay(Body * self, Body * comp) {
//    double aux = 0;

//    for(int w = 0; w<bodies.size(); w++){

//        if(bodies.at(w)->getName() != self->getName()){

//            aux += ((bodies.at(w)->getM())/(pow(self->calculate_distance(bodies.at(w)), 3))) * (bodies.at(w)->getY() - self->getY());
//        }

//    }
//    aux *= G;

//    return aux;
    return (G*(comp->getM()*(comp->getY() - self->getY()))/(pow(calculate_distance(self, comp), 3)));
}

double MainWindow::calculate_distance(Body *self, Body *comp) {
    return pow((pow((comp->getX())-self->getX(),2)+pow((comp->getY() - self->getY()),2)), 1/2);
}

void MainWindow::simulation(){

    for(int i = 0; i<bodies.size(); i++){

        for(int j = 0; j<bodies.size(); j++){

            if(i != j){
                //bodies.at(k)->calculate_Ax(bodies);
                //bodies.at(k)->calculate_Ay(bodies);

                bodies.at(i)->Ax = get_Ax(bodies.at(i), bodies.at(j));
                bodies.at(i)->Ay = get_Ay(bodies.at(i), bodies.at(j));

                bodies.at(i)->calculate_Vx();
                bodies.at(i)->calculate_Vy();

                bodies.at(i)->calculate_x();
                bodies.at(i)->calculate_y();

                bodies.at(i)->setPos(int(bodies.at(i)->getX()), int(bodies.at(i)->getY()));

                //bodies.at(k)->calculate_x();
                //bodies.at(k)->calculate_y();

                //bodies.at(k)->setPos(int(bodies.at(k)->getX()), int(bodies.at(k)->getY()));
                //bodies.at(k)->setPos(new_x(ui->graphicsView->width(), bodies.at(k)->getX()), new_y(ui->graphicsView->height(), bodies.at(k)->getY()));
            }
        }
    }

    //for(int k = 0; k<bodies.size(); k++)
       // bodies.at(k)->setPos(int(bodies.at(k)->getX()), int(bodies.at(k)->getY()));
}

void MainWindow::remove_empty_bodies() {
    QList <Body *> aux;

    for(int k = 0; k<bodies.size(); k++)
        if(!bodies.at(k)->is_empty())
            aux.push_back(bodies.at(k));

    bodies = aux;
}

void MainWindow::on_start_button_clicked() {

    if(!ui->resume_button->isEnabled())
        ui->resume_button->setEnabled(true);
    if(!ui->pause_button->isEnabled())
        ui->pause_button->setEnabled(true);

    for(int k = 0; k<bodies.size(); k++)
        scene->removeItem(bodies.at(k));

    bodies.clear();

    bodies.push_back(new Body(nullptr, ui->name_box_1->text(), ui->x_box_1->value(), ui->y_box_1->value(), ui->m_box_1->value(), ui->r_box_1->value(), ui->vx_box_1->value(), ui->vy_box_1->value()));
    bodies.push_back(new Body(nullptr, ui->name_box_2->text(), ui->x_box_2->value(), ui->y_box_2->value(), ui->m_box_2->value(), ui->r_box_2->value(), ui->vx_box_2->value(), ui->vy_box_2->value()));
    bodies.push_back(new Body(nullptr, ui->name_box_3->text(), ui->x_box_3->value(), ui->y_box_3->value(), ui->m_box_3->value(), ui->r_box_3->value(), ui->vx_box_3->value(), ui->vy_box_3->value()));
    bodies.push_back(new Body(nullptr, ui->name_box_4->text(), ui->x_box_4->value(), ui->y_box_4->value(), ui->m_box_4->value(), ui->r_box_4->value(), ui->vx_box_4->value(), ui->vy_box_4->value()));
    bodies.push_back(new Body(nullptr, ui->name_box_5->text(), ui->x_box_5->value(), ui->y_box_5->value(), ui->m_box_5->value(), ui->r_box_5->value(), ui->vx_box_5->value(), ui->vy_box_5->value()));
    bodies.push_back(new Body(nullptr, ui->name_box_6->text(), ui->x_box_6->value(), ui->y_box_6->value(), ui->m_box_6->value(), ui->r_box_6->value(), ui->vx_box_6->value(), ui->vy_box_6->value()));

    remove_empty_bodies();

    for(int k = 0; k<bodies.size(); k++){
        scene->addItem(bodies.at(k));
        bodies.at(k)->setPos(int(bodies.at(k)->getX()), int(bodies.at(k)->getY()));
    }

    timer->start(int(T*100));
}
void MainWindow::on_pause_button_clicked()
{
    timer->stop();
    ui->pause_button->setEnabled(false);
    if(!ui->resume_button->isEnabled())
        ui->resume_button->setEnabled(true);
}
void MainWindow::on_resume_button_clicked()
{
    if(!ui->pause_button->isEnabled()){
        timer->start(int(T*100));
        ui->resume_button->setEnabled(false);
        if(!ui->pause_button->isEnabled())
            ui->pause_button->setEnabled(true);
    }

}
