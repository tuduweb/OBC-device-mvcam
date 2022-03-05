#include <iostream>

#include "CameraApi.h"

#include <QStringList>
#include "qdebug.h"

#include "MVCAMStream.hpp"
#include <QApplication>

#include <QTimer>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "widgets/MVCAMFullSettingsWidget.hpp"

#include "MVCAMDevice.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    // std::cout << "hello world" << std::endl;

    // std::cout << "res: " << CameraSdkInit(0) << std::endl;
    
    // std::cout << "hello world" << std::endl;

    // int                     iCameraCounts = 4;
	// int                     iStatus = -1;
	// tSdkCameraDevInfo       tCameraEnumList[4];

    // QStringList lists;

	// //枚举设备，并建立设备列表
	// CameraEnumerateDevice(tCameraEnumList, &iCameraCounts);

	// if (iCameraCounts <= 0)
	// 	return 0;

	// for (int i = 0; i < iCameraCounts; ++i) {
	// 	lists.append(
	// 		QString("%1@@%2@@%3").arg(tCameraEnumList[i].acProductName)
	// 		.arg(tCameraEnumList[i].acDriverVersion)
	// 		.arg(tCameraEnumList[i].acSn)
	// 	);
	// }

    // qDebug() << lists;

    QWidget w;
    w.resize(500,400);
    QVBoxLayout* layout = new QVBoxLayout;
    w.setLayout(layout);
    w.show();

    QLabel* label = new QLabel("image");
    layout->addWidget(label);

    QWidget* testWidget = new QWidget(&w);
    testWidget->resize(200, 300);
    QVBoxLayout* layout2 = new QVBoxLayout;
    testWidget->setLayout(layout2);

    layout->addWidget(testWidget);

#if 0
    StreamInterface* stream = new MVCAMStream();


    // QTimer::singleShot(1000, stream, [=](){
    //     qDebug() << "one shot";
    // });

    QObject::connect(stream, &StreamInterface::FrameReceived, &w, [=](const QImage& image){
        label->setPixmap(QPixmap::fromImage(image.scaled(192, 108)));
    });

    SettingsBaseWidget* settingsWidget = new MVCAMFullSettingsWidget();
    layout->addWidget(settingsWidget);

    QObject::connect(settingsWidget, &SettingsBaseWidget::SendEvent, stream, &StreamInterface::HandleEvent);
    QObject::connect(qobject_cast<MVCAMStream*>(stream), &MVCAMStream::SendEvent, settingsWidget, &SettingsBaseWidget::HandleEvent);

    stream->StreamInit();
    stream->StreamStart();
#endif

#if 1
    MVCAMDevice* mvcam = new MVCAMDevice();

    layout2->addWidget(mvcam->controlWidget());

    layout2->addWidget(mvcam->settingsWidget());


    QObject::connect(mvcam->stream, &MVCAMStream::FrameReceived, &w, [=](const QImage& image){
        label->setPixmap(QPixmap::fromImage(image.scaled(192, 108)));
    });

    mvcam->DeviceInit();
    mvcam->DeviceStart();

    QTimer::singleShot(10000, &w, [=](){
        qDebug() << "one shot";
        // delete testWidget;
        // //one shot
        // //~~~~~~~MVCAMFullSettingsWidget
    });
#endif
    return app.exec();
}
