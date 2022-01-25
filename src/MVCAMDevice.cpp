#include "MVCAMDevice.hpp"

#include "MVCAMStream.hpp"

#include "widgets/MVCAMFullSettingsWidget.hpp"

MVCAMDevice::MVCAMDevice() : _settingsWidget(nullptr){
    
    _settingsWidget = new MVCAMFullSettingsWidget();

    stream = new MVCAMStream();
    streamInstances.push_back(stream);

    connect(_settingsWidget, &SettingsBaseWidget::SendEvent, stream, &StreamInterface::HandleEvent);
    connect(stream, &StreamInterface::SendEvent, _settingsWidget, &SettingsBaseWidget::HandleEvent);

}

int MVCAMDevice::DeviceInit() {
    for(int i = 0; i < streamInstances.size(); ++i) {
        streamInstances[i]->StreamInit();
    }
}

int MVCAMDevice::DeviceStart() {
    for(int i = 0; i < streamInstances.size(); ++i) {
        streamInstances[i]->StreamStart();
    }
}