#pragma once

#include <QObject>
#include <QThread>


class StreamInterface : public QThread
{
    Q_OBJECT

public:
    enum StreamType
    {
        CameraStream = 1,
        DataStream = 2
    };
    Q_ENUM(StreamType);

public:

public:
    virtual int StreamInit() = 0;
    virtual int StreamStart() = 0;
    // int StreamPause();
    // int StreamStop();
    // int StreamDeinit();
    // int StreamDestory();

    /* configuration methods */
    //获取所有的流源: (可能需要换一饿地方存放)
    virtual QStringList getStreamLists() { return {}; };


public:
    virtual void HandleEvent(const QJsonObject& event) {};

signals:
    void FrameReceived(const QImage& frameImage);
    void DataReceived(const QByteArray& byteArray);
    void SendEvent(const QJsonObject& event);

protected:
    QString _streamId;//唯一id
    
};