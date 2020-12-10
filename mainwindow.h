#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>

#include "body.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public: // Variables

private: // Variables
    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    QTimer *timer;

    QList <Body *> bodies;

    double T;
    double G;

public: // Methods
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int new_y(int y_max, int y_);
    int new_x(int x_max, int x_);

    double get_Ax(Body * self, Body *comp);
    double get_Ay(Body * self, Body *comp);

    double calculate_distance(Body * self, Body *comp);

    void remove_empty_bodies();

private: // Methods

private slots: //slots
    void on_start_button_clicked();
    void simulation();

    void on_pause_button_clicked();
    void on_resume_button_clicked();
};
#endif // MAINWINDOW_H
