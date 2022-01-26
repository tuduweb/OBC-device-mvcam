#include "MVCAMDevice.hpp"

#include "MVCAMStream.hpp"

#include "widgets/MVCAMFullSettingsWidget.hpp"

MVCAMDevice::MVCAMDevice() : _settingsWidget(nullptr), _controlWidget(nullptr) {
    
    _controlWidget = new MVCAMFullSettingsWidget();

    stream = new MVCAMStream();
    streamInstances.push_back(stream);

    connect(_controlWidget, &SettingsBaseWidget::SendEvent, stream, &StreamInterface::HandleEvent);
    connect(stream, &StreamInterface::SendEvent, _controlWidget, &SettingsBaseWidget::HandleEvent);

    _settingsWidget = new MVCAMStreamWidget();
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