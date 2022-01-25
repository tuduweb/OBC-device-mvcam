#include "MVCAMFullSettingsWidget.hpp"
#include "ui_MVCAMFullSettingsWidget.h"

#include <QStyledItemDelegate>

MVCAMFullSettingsWidget::MVCAMFullSettingsWidget(QWidget* parent)
	: QWidget(parent)
{
    ui = new Ui::MVCAMFullSettingsWidget();
	ui->setupUi(this);

    ui->groupBox_speed->setVisible(false);

	connect(ui->horizontalSlider_gain_r, SIGNAL(valueChanged(int)), ui->spinBox_gain_r, SLOT(setValue(int)));
	connect(ui->spinBox_gain_r, SIGNAL(valueChanged(int)), ui->horizontalSlider_gain_r, SLOT(setValue(int)));

	connect(ui->horizontalSlider_gain_g, SIGNAL(valueChanged(int)), ui->spinBox_gain_g, SLOT(setValue(int)));
	connect(ui->spinBox_gain_g, SIGNAL(valueChanged(int)), ui->horizontalSlider_gain_g, SLOT(setValue(int)));

	connect(ui->horizontalSlider_gain_b, SIGNAL(valueChanged(int)), ui->spinBox_gain_b, SLOT(setValue(int)));
	connect(ui->spinBox_gain_b, SIGNAL(valueChanged(int)), ui->horizontalSlider_gain_b, SLOT(setValue(int)));

	connect(ui->horizontalSlider_saturation, SIGNAL(valueChanged(int)), ui->spinBox_saturation, SLOT(setValue(int)));
	connect(ui->spinBox_saturation, SIGNAL(valueChanged(int)), ui->horizontalSlider_saturation, SLOT(setValue(int)));

    for(const auto& obj : this->children()) {
        qDebug() << obj->objectName() << obj->metaObject()->className();
    }


}

MVCAMFullSettingsWidget::~MVCAMFullSettingsWidget() {
    //
}

void MVCAMFullSettingsWidget::HandleEvent(const QJsonObject& event) {
    


    if(event.contains("type") && event["type"] == "view") {
        
        if(event.contains("id")) {
            
            if(event["id"] == "resolution") {
                
                QJsonArray items = event["data"].toArray();

                for (int i = 0; i < items.size(); i++) {
		            ui->res_combobox->addItem( items[i].toString() );
	            }

            }else if(event["id"] == "rgbs") {
                
                QJsonArray items = event["data"].toArray();

                ui->horizontalSlider_gain_r->setValue(items[0].toInt());
	            ui->horizontalSlider_gain_g->setValue(items[1].toInt());
	            ui->horizontalSlider_gain_b->setValue(items[2].toInt());

	            ui->horizontalSlider_saturation->setValue(items[3].toInt());
            }else if(event["id"] == "WB") {
                QJsonArray items = event["data"].toArray();

                ui->horizontalSlider_gain_r->setValue(items[0].toInt());
	            ui->horizontalSlider_gain_g->setValue(items[1].toInt());
	            ui->horizontalSlider_gain_b->setValue(items[2].toInt());
            }


        }

    }

}


void MVCAMFullSettingsWidget::on_horizontalSlider_gain_r_valueChanged(int value)
{
	//int RPos, GPos, BPos;
	// CameraGetGain(g_hCamera, &RPos, &GPos, &BPos);
	// CameraSetGain(g_hCamera, value, GPos, BPos);

    QJsonObject obj;
    obj.insert("id", sender()->objectName());
    obj.insert("data", value);
    emit SendEvent(obj);

	qDebug() << QString("R gain Value : %1").arg(value);
}

void MVCAMFullSettingsWidget::on_horizontalSlider_gain_g_valueChanged(int value)
{
	// int RPos, GPos, BPos;
	// CameraGetGain(g_hCamera, &RPos, &GPos, &BPos);
	// CameraSetGain(g_hCamera, RPos, value, BPos);

    QJsonObject obj;
    obj.insert("id", sender()->objectName());
    obj.insert("data", value);
    emit SendEvent(obj);
}

void MVCAMFullSettingsWidget::on_horizontalSlider_gain_b_valueChanged(int value)
{
	// int RPos, GPos, BPos;
	// CameraGetGain(gg_hCamera, &RPos, &GPos, &BPos);
	// CameraSetGain(gg_hCamera, RPos, GPos, value);
    QJsonObject obj;
    obj.insert("id", sender()->objectName());
    obj.insert("data", value);
    emit SendEvent(obj);
}

void MVCAMFullSettingsWidget::on_horizontalSlider_saturation_valueChanged(int value)
{
	// CameraSetSaturation(gg_hCamera, value);
    QJsonObject obj;
    obj.insert("id", sender()->objectName());
    obj.insert("data", value);
    emit SendEvent(obj);
}

void MVCAMFullSettingsWidget::on_AWB_once_button_released() {
    QJsonObject obj;
    //sender()->objectName()
    obj.insert("id", "WB");
    emit SendEvent(obj);
}



void MVCAMFullSettingsWidget::on_checkBox_isp_v_clicked(bool checked) {
    QJsonObject obj;
    //sender()->objectName()
    obj.insert("id", "flipv");
    obj.insert("data", checked);
    emit SendEvent(obj);
}
void MVCAMFullSettingsWidget::on_checkBox_isp_h_clicked(bool checked) {
    QJsonObject obj;
    //sender()->objectName()
    obj.insert("id", "fliph");
    obj.insert("data", checked);
    emit SendEvent(obj);
}