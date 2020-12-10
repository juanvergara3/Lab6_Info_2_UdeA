#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0, ui->graphicsView->width(), ui->graphicsView->height());
    //scene->setSceneRect(ui->graphicsView->width()/2,  ui->graphicsView->height()/2, ui->graphicsView->width(), ui->graphicsView->height());

    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();

    T = 0.1;
    //G = 6.673e-11;
    G = 6.67384*pow(10,-11);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(simulation()));
}
MainWindow::~MainWindow() {
    delete timer;
    delete scene;
    delete ui;
}

void MainWindow::simulation(){

    for(int i=0; i<bodies.size(); i++ ) {
        for(int j=0; j<bodies.size(); j++ ) {
            if(i!=j){
                bodies.at(i)->acelerate(bodies.at(j));
                bodies.at(i)->update();
            }
        }
    }
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
        bodies.at(k)->setPos(bodies.at(k)->getX()*bodies.at(k)->getScale(), bodies.at(k)->getY()*bodies.at(k)->getScale());
        scene->addItem(bodies.at(k));
    }

    timer->start(T);
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
        timer->start(T);
        ui->resume_button->setEnabled(false);
        if(!ui->pause_button->isEnabled())
            ui->pause_button->setEnabled(true);
    }

}
