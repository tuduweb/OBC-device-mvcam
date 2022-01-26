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


    QWidget* controlWidget() const { return _controlWidget; };
    QWidget* settingsWidget() const { return _settingsWidget; }

signals:
    void FrameArrived(const QImage& frame);
    void DataArrived(const QByteArray& data);

public:
    QVector<StreamInterface*> streamInstances;
    
protected:
    SettingsBaseWidget* _controlWidget;
    MVCAMStreamWidget* _settingsWidget;

public:
    StreamInterface* stream;//temp
};