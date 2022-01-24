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

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    std::cout << "hello world" << std::endl;

    std::cout << "res: " << CameraSdkInit(0) << std::endl;
    
    std::cout << "hello world" << std::endl;

    int                     iCameraCounts = 4;
	int                     iStatus = -1;
	tSdkCameraDevInfo       tCameraEnumList[4];

    QStringList lists;

	//枚举设备，并建立设备列表
	CameraEnumerateDevice(tCameraEnumList, &iCameraCounts);

	if (iCameraCounts <= 0)
		return 0;

	for (int i = 0; i < iCameraCounts; ++i) {
		lists.append(
			QString("%1@@%2@@%3").arg(tCameraEnumList[i].acProductName)
			.arg(tCameraEnumList[i].acDriverVersion)
			.arg(tCameraEnumList[i].acSn)
		);
	}

    qDebug() << lists;


    MVCAMStream* stream = new MVCAMStream();
    stream->StreamInit();

    stream->StreamStart();

    QTimer::singleShot(1000, stream, [=](){
        qDebug() << "one shot";
    });

    QWidget w;
    w.resize(500,400);
    QVBoxLayout* layout = new QVBoxLayout;
    w.setLayout(layout);
    w.show();

    QLabel* label = new QLabel("image");
    layout->addWidget(label);

    QObject::connect(stream, &MVCAMStream::FrameReceived, &w, [=](const QImage& image){
        label->setPixmap(QPixmap::fromImage(image));
    });

    return app.exec();
}
