#pragma once

#include <QWidget>

class SettingsBaseWidget : public QWidget{
    Q_OBJECT

public:
    SettingsBaseWidget(QWidget* parent) : QWidget(parent) {};

signals:
	void SendEvent(const QJsonObject& event);

public:
	virtual void HandleEvent(const QJsonObject& event) {};

};