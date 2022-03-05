#include "w_RemoteEditor.hpp"

#include "MVCAMDevice.hpp"

RemoteEditor::RemoteEditor(int remoteId, QWidget* parent) : QDialog(parent)
{
    setupUi(this);

    rightLayout->addWidget(MVCAMDevice::MakeSettingsWidget());
    
}

RemoteEditor::~RemoteEditor()
{
    //
}

QJsonObject RemoteEditor::OpenEditor()
{
    auto resultCode = this->exec();

    return {};
	//return resultCode == QDialog::Accepted ? {} : {};
}