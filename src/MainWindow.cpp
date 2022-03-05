#include "MainWindow.hpp"


#include <QDebug>
#include <QVBoxLayout>

#include "MVCAMDevice.hpp"
#include "MVCAMStream.hpp"

#include "w_RemoteEditor.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), mvcam(nullptr), label(nullptr)
{
    setupUi(this);

    device_cb->addItem("MVCAM Test #1");
    device_cb->addItem("MVCAM Test #1");


    QVBoxLayout* layout = new QVBoxLayout;
    
    qDebug() << frame->layout();

    frame->setLayout(layout);

    mvcam = new MVCAMDevice();

    label = new QLabel("image");

    layout->addWidget(label);
}

MainWindow::~MainWindow()
{
    //
}

void MainWindow::on_btn_1_clicked()
{
    RemoteEditor editor(123, this);
    editor.OpenEditor();
}

void MainWindow::on_btn_2_clicked()
{
    centralwidget->layout()->addWidget(mvcam->controlWidget());

    QObject::connect(mvcam->stream, &MVCAMStream::FrameReceived, this, [=](const QImage& image){
        label->setPixmap(QPixmap::fromImage(image.scaled(192, 108)));
    });

    mvcam->DeviceInit();
    mvcam->DeviceStart();
}