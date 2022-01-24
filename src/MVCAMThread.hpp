#pragma once
#include <QThread>

class MVCAMThread : public QThread
{
public:
    MVCAMThread(int hCamera) : g_hCamera(hCamera){};

protected:
    void run() override;

private:
    int g_hCamera = -1;
};