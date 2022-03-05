#pragma once
#include <QObject>
#include <QWidget>

#include "StreamInterface.hpp"
#include "SettingsBaseWidget.hpp"

#include "widgets/MVCAMStreamWidget.hpp"

class MVCAMDevice : public QObject{
    Q_OBJECT
    //std::unique_ptr
public:
    MVCAMDevice();
    
    int DeviceInit();
    int DeviceStart();

    int DeviceDeinit();


    QWidget* controlWidget() const { return _controlWidget; };
    QWidget* settingsWidget() const { return _settingsWidget; }


    static QStringList GetDeviceLists();

signals:
    void FrameArrived(const QImage& frame);
    void DataArrived(const QByteArray& data);

public:
    QVector<StreamInterface*> streamInstances;
    
protected:
    SettingsBaseWidget* _controlWidget;//控制面板 是在打开摄像头后的面板
    MVCAMStreamWidget* _settingsWidget;//设置面板 是在打开摄像头前的设置面板 //TODO: 类型名字更改

public:
    StreamInterface* stream;//temp
};