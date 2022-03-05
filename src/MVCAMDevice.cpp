#include "MVCAMDevice.hpp"

#include "MVCAMStream.hpp"

#include "widgets/MVCAMFullSettingsWidget.hpp"

MVCAMDevice::MVCAMDevice() : _settingsWidget(nullptr), _controlWidget(nullptr) {

    //load device config from device name


    //    

    stream = new MVCAMStream();
    streamInstances.push_back(stream);


    _controlWidget = new MVCAMFullSettingsWidget();
    _settingsWidget = new MVCAMStreamWidget();//TODO: maybe need add property deviceName -> load settings for .. so, we need static function for generate device interface

    connect(_controlWidget, &SettingsBaseWidget::SendEvent, stream, &StreamInterface::HandleEvent);
    connect(stream, &StreamInterface::SendEvent, _controlWidget, &SettingsBaseWidget::HandleEvent);

}

int MVCAMDevice::DeviceInit() {
    for(int i = 0; i < streamInstances.size(); ++i) {
        streamInstances[i]->StreamInit();
    }
    return 0;
}

int MVCAMDevice::DeviceStart() {
    for(int i = 0; i < streamInstances.size(); ++i) {
        streamInstances[i]->StreamStart();
    }
    return 0;
}

int MVCAMDevice::DeviceDeinit() {
    
    return 0;

}


QWidget* MVCAMDevice::MakeSettingsWidget()
{
    QWidget* widget = new MVCAMStreamWidget();
    return widget;
}



 QStringList MVCAMDevice::GetDeviceLists() {
    return MVCAMStream::GetStreamLists();
 }