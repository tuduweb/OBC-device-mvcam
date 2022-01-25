#pragma once
#include "StreamInterface.hpp"

#include "CameraApi.h"

#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>

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
    Q_OBJECT
public:
    MVCAMStream();

    int StreamInit() override;
    int StreamStart() override;

    int loop(int hCamera);

    int setPause() { pause_status = true; return 0; };
    int setStart() { pause_status = false; return 0; };
    int setStop() { quit_status = true; return 0; };



protected:
    void run() override;

public slots:
    void StartLoop();

protected:
    int camera_init_Resolution(int hCamera, tSdkCameraCapbility* pCameraInfo);
    int camera_init_exposure(int hCamera, tSdkCameraCapbility* pCameraInfo);
    int camera_init_WB(int hCamera, tSdkCameraCapbility* pCameraInfo);

    QStringList _resolutionLists;

public:
    //Constraints relationship
    static const QStringList GetStreamLists();
    static const QJsonObject GetStreamTypes(){ return {}; };

public slots:
    void HandleEvent(const QJsonObject& event);

signals:
    void SendEvent(const QJsonObject& event);

protected:
    QThread* thread;// need a better way to manage stream threads
    bool pause_status = false;
    bool quit_status = false;
};