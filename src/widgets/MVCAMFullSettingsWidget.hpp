#pragma once

#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>
namespace Ui { class MVCAMFullSettingsWidget; };

class MVCAMFullSettingsWidget : public QWidget
{
	Q_OBJECT

public:
	MVCAMFullSettingsWidget(QWidget* parent);
	~MVCAMFullSettingsWidget();

signals:
	void SendEvent(const QJsonObject& event);

public slots:
	void HandleEvent(const QJsonObject& event);

	void on_horizontalSlider_gain_r_valueChanged(int value);
	void on_horizontalSlider_gain_g_valueChanged(int value);
	void on_horizontalSlider_gain_b_valueChanged(int value);
	void on_horizontalSlider_saturation_valueChanged(int value);

	void on_AWB_once_button_released();

	void on_checkBox_isp_v_clicked(bool checked);
	void on_checkBox_isp_h_clicked(bool checked);

private:
	Ui::MVCAMFullSettingsWidget* ui;
};
