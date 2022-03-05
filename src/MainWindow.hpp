#pragma once
#include "ui_MainWindow.h"

#include <QMainWindow>

#include "MVCAMDevice.hpp"

class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected slots:
    void on_btn_1_clicked();
    void on_btn_2_clicked();

public:
    MVCAMDevice* mvcam;
    QLabel* label;
};