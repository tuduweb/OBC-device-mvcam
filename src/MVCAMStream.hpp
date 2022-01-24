#pragma once
#include "StreamInterface.hpp"

#include "CameraApi.h"

#include <QStringList>
#include <QJsonObject>

#include <QThread>

typedef struct _WIDTH_HEIGHT {
	int     display_width;
	int     display_height;
	int     xOffsetFOV;
	int     yOffsetFOV;
	int     sensor_width;
	int     sensor_height;
	int     buffer_size;
}Width_Height;

class MVCAMStream : public StreamInterface{

    //stream type : data | video

public:
    MVCAMStream();

    int StreamInit() override;
    int StreamStart() override;

    int loop(int hCamera);

protected:
    void run() override;

public slots:
    void StartLoop();

public:
    int GUI_init_Resolution(int hCamera, tSdkCameraCapbility* pCameraInfo);
    QStringList _resolutionLists;

    //Constraints relationship
    static const QStringList GetStreamLists();
    static const QJsonObject GetStreamTypes(){ return {}; };

    QThread* thread;
};