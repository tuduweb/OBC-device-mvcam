#pragma once

#include <QDialog>
#include "ui_w_RemoteEditor.h"


#include <QJsonObject>

class RemoteEditor : public QDialog, public Ui::w_RemoteEditor
{
    Q_OBJECT

public:
    explicit RemoteEditor(int remoteId, QWidget *parent = Q_NULLPTR);
    ~RemoteEditor();

    QJsonObject OpenEditor();
};