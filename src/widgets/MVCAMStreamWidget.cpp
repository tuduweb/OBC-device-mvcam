#include "MVCAMStreamWidget.hpp"


MVCAMStreamWidget::MVCAMStreamWidget(QWidget* parent)
	: QWidget(parent)
{
	setupUi(this);
	ReloadUI();
}

MVCAMStreamWidget::~MVCAMStreamWidget()
{
	//
}

void MVCAMStreamWidget::ReloadUI()
{
	QStringList deviceLists;
	int count = 0;//MVCAMRemoteStream::GetDeviceLists(deviceLists);

	deviceComboBox->clear();

	if (count == 0) {
		deviceComboBox->addItem("None", "");
	}
	else {
		//MV-SUA231GC
		for (int i = 0; i < deviceLists.count(); ++i) {
			QStringList param = deviceLists[i].split("@@");
			if (param.count() < 3)
				continue;
			deviceComboBox->addItem(param[0], deviceLists[i]);
			if (!_config_selected_deviceName.isEmpty() && param[0] == _config_selected_deviceName) {
				deviceComboBox->setCurrentIndex(deviceComboBox->count() - 1);
			}
		}
	}


	on_deviceComboBox_currentIndexChanged(0);
}

void MVCAMStreamWidget::SetContent(const QJsonObject& _content)
{
	content = _content;

	if (content.contains("deviceName")) {
		_config_selected_deviceName = content["deviceName"].toString();
	}

	ReloadUI();

	// PLUGIN_EDITOR_LOADING_SCOPE({
	// 	//if (content.contains("url"))
	// 	//	ui->url_le->setText(content["url"].toString());

	// 	//if (content.contains("timeout"))
	// 	//	ui->timeout_le->setText(QString::number(content["timeout"].toInt()));

	// if (content.contains("deviceName")) {
	// 	_config_selected_deviceName = content["deviceName"].toString();
	// }

	// ReloadUI();

	// 	});
}

void MVCAMStreamWidget::on_deviceComboBox_currentIndexChanged(int)
{
	//PLUGIN_EDITOR_LOADING_GUARD;

	QString data = deviceComboBox->currentData().toString();

	plainTextEdit->clear();

	if (data.isEmpty()) {
		_info_deviceName.clear();
		_info_version.clear();
		_info_sn.clear();
		return;
	}

	QStringList param = data.split("@@");
	if (param.count() < 3) {
		_info_deviceName.clear();
		_info_version.clear();
		_info_sn.clear();

		return;
	}

	_info_deviceName = param[0];
	_info_version = param[1];
	_info_sn = param[2];

	plainTextEdit->setPlainText(QString("%1\n%2\n%3\n").arg(_info_deviceName).arg(_info_version).arg(_info_sn));
}