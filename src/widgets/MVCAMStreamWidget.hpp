#pragma once

#include <QWidget>
#include "ui_MVCAMStreamWidget.h"

#include <QJsonObject>

class MVCAMStreamWidget : public QWidget, public Ui::MVCAMStreamWidget
{
	Q_OBJECT

public:
	MVCAMStreamWidget(QWidget* parent = Q_NULLPTR);
	~MVCAMStreamWidget();

	void ReloadUI();

	void SetContent(const QJsonObject& _content);

	void SetCommObject(const QJsonObject& o) {};
	const QJsonObject GetCommObject() const { return {}; };
	bool Init() { return false; };
	void OnConnectClicked() {};
	void OnDisconnectClicked() {};
	void OnResetClicked() {};
	void UpdateConfig() {};

protected slots:
	void on_deviceComboBox_currentIndexChanged(int);

private:
	QString _info_sn;
	QString _info_deviceName;
	QString _info_version;

	QString _config_selected_deviceName;

	QJsonObject content;
};
