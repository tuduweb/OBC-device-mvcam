#pragma once
#include <QObject>
#include <QWidget>

#include "StreamInterface.hpp"
#include "SettingsBaseWidget.hpp"

class MVCAMDevice : public QObject{
    Q_OBJECT
    //std::unique_ptr
public:
    MVCAMDevice();
    
    int DeviceInit();
    int DeviceStart();


    QWidget* settingsWidget() const { return _settingsWidget; };


signals:
    void FrameArrived(const QImage& frame);
    void DataArrived(const QByteArray& data);

public:
    QVector<StreamInterface*> streamInstances;
    SettingsBaseWidget* _settingsWidget;

    StreamInterface* stream;//temp
};