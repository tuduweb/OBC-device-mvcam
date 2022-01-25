#include "MVCAMStream.hpp"

#include <QThread>
#include <QImage>

unsigned char* g_pRgbBuffer = NULL;     //处理后数据缓存区
BYTE* g_readBuf = NULL;    //画板显示数据区
Width_Height            g_W_H_INFO;         //显示画板到大小和图像大小
int                     g_hCamera = -1;     //设备句柄


MVCAMStream::MVCAMStream() : thread(new QThread) {
    qDebug() << QThread::currentThread();
    //moveToThread(thread);
    //qDebug() << QThread::currentThread();
}

#include <QTimer>

int MVCAMStream::StreamInit() {
    

	int                     iCameraCounts = 4;
	int                     iStatus = -1;
	tSdkCameraDevInfo       tCameraEnumList[4];

    tSdkCameraCapbility     g_tCapability;      //设备描述信息



    iStatus = CameraSdkInit(1);

    //枚举设备，并建立设备列表
	CameraEnumerateDevice(tCameraEnumList, &iCameraCounts);

    //没有连接设备
	if (iCameraCounts == 0) {
		return -1;
	}

    //choose which one to init
	//相机初始化。初始化成功后，才能调用任何其他相机相关的操作接口
	iStatus = CameraInit(&tCameraEnumList[0], -1, -1, &g_hCamera);
	//初始化失败
	if (iStatus != CAMERA_STATUS_SUCCESS) {
		return -1;
	}
    //获得相机的特性描述结构体。该结构体中包含了相机可设置的各种参数的范围信息。决定了相关函数的参数
	CameraGetCapability(g_hCamera, &g_tCapability);

    //alloc memorys : maybe can use other methods
    g_pRgbBuffer = (unsigned char*)malloc(g_tCapability.sResolutionRange.iHeightMax * g_tCapability.sResolutionRange.iWidthMax * 3);
	g_readBuf = (unsigned char*)malloc(g_tCapability.sResolutionRange.iHeightMax * g_tCapability.sResolutionRange.iWidthMax * 3);

	/*让SDK进入工作模式，开始接收来自相机发送的图像
		数据。如果当前相机是触发模式，则需要接收到
		触发帧以后才会更新图像。    */
	CameraPlay(g_hCamera);

    /*
		设置图像处理的输出格式，彩色黑白都支持RGB24位
	*/
	if (g_tCapability.sIspCapacity.bMonoSensor) {
		CameraSetIspOutFormat(g_hCamera, CAMERA_MEDIA_TYPE_MONO8);
	}
	else {
		CameraSetIspOutFormat(g_hCamera, CAMERA_MEDIA_TYPE_RGB8);
	}

	camera_init_Resolution(g_hCamera, &g_tCapability);

    //GUI_set_Resolution(hCamera, pCameraInfo);
	tSdkImageResolution* pImageSizeDesc = g_tCapability.pImageSizeDesc;// 预设分辨率选择
	tSdkImageResolution     sResolution;  //获取当前设置到分辨率

	//获得当前预览的分辨率。
	CameraGetImageResolution(g_hCamera, &sResolution);

	g_W_H_INFO.sensor_width = pImageSizeDesc[sResolution.iIndex].iWidth;
	g_W_H_INFO.sensor_height = pImageSizeDesc[sResolution.iIndex].iHeight;
	g_W_H_INFO.buffer_size = g_W_H_INFO.sensor_width * g_W_H_INFO.sensor_height;

	camera_init_WB(g_hCamera, &g_tCapability);

    return 0;
}

void MVCAMStream::StartLoop() {
    qDebug() << "startLoop";
    loop(g_hCamera);
}

//分辨率的添加, 遍历
int MVCAMStream::camera_init_Resolution(int hCamera, tSdkCameraCapbility* pCameraInfo) {
	int                     i = 0;
	tSdkImageResolution* pImageSizeDesc = pCameraInfo->pImageSizeDesc;// 预设分辨率选择
	int                     iImageSizeDesc = pCameraInfo->iImageSizeDesc; // 预设分辨率的个数，即pImageSizeDesc数组的大小

	_resolutionLists.clear();

	for (i = 0; i < iImageSizeDesc; i++) {
		//ui->res_combobox->addItem(QString::fromLocal8Bit(pImageSizeDesc[i].acDescription));
		_resolutionLists.append(QString::fromLocal8Bit(pImageSizeDesc[i].acDescription));
	}

	QJsonObject obj;
	obj.insert("type", "view");
	obj.insert("id", "resolution");
	obj.insert("data", QJsonArray::fromStringList(_resolutionLists));

	emit SendEvent(obj);

	return 0;
}

int MVCAMStream::camera_init_exposure(int hCamera, tSdkCameraCapbility* pCameraInfo) {

	BOOL            AEstate = FALSE;
	int             pbyAeTarget;
	double          pfExposureTime;
	int             pusAnalogGain;
	BOOL            FlickEnable = FALSE;
	int             piFrequencySel;
	double	        m_fExpLineTime = 0;//当前的行曝光时间，单位为us
	tSdkExpose* SdkExpose = &pCameraInfo->sExposeDesc;

	//获得相机当前的曝光模式。
	CameraGetAeState(hCamera, &AEstate);

	//获得自动曝光的亮度目标值。
	CameraGetAeTarget(hCamera, &pbyAeTarget);

	//获得自动曝光时抗频闪功能的使能状态。
	CameraGetAntiFlick(hCamera, &FlickEnable);

	//获得相机的曝光时间。
	CameraGetExposureTime(hCamera, &pfExposureTime);

	//获得图像信号的模拟增益值。
	CameraGetAnalogGain(hCamera, &pusAnalogGain);

	//获得自动曝光时，消频闪的频率选择。
	CameraGetLightFrequency(hCamera, &piFrequencySel);

	/*
		获得一行的曝光时间。对于CMOS传感器，其曝光
		的单位是按照行来计算的，因此，曝光时间并不能在微秒
		级别连续可调。而是会按照整行来取舍。这个函数的
		作用就是返回CMOS相机曝光一行对应的时间。
	*/
	CameraGetExposureLineTime(hCamera, &m_fExpLineTime);

    //整理参数为结果
    //some codes
    
    
    return 0;

}

int MVCAMStream::camera_init_WB(int hCamera, tSdkCameraCapbility* pCameraInfo) {
    
    int RPos, GPos, BPos, Saturation;

    CameraGetGain(hCamera, &RPos, &GPos, &BPos);
	CameraGetSaturation(hCamera, &Saturation);
    
    //manage all param from above
	QJsonObject obj;
	obj.insert("type", "view");
	obj.insert("id", "rgbs");
	obj.insert("data", QJsonArray{ RPos, GPos, BPos, Saturation});
	emit SendEvent(obj);

    return 0;

}

int MVCAMStream::StreamStart() {
    start();
    return 0;
}

void MVCAMStream::run() {
    loop(g_hCamera);
    exec();
}

const QStringList MVCAMStream::GetStreamLists() {
    QStringList lists;
    int                     iCameraCounts = 4;
	int                     iStatus = -1;
	tSdkCameraDevInfo       tCameraEnumList[4];

	//sdk初始化  0 English 1中文 // move to initalize
	CameraSdkInit(1);

	//枚举设备，并建立设备列表
	CameraEnumerateDevice(tCameraEnumList, &iCameraCounts);

	if (iCameraCounts <= 0)
		return {};

	for (int i = 0; i < iCameraCounts; ++i) {
		lists.append(
			QString("%1@@%2@@%3").arg(tCameraEnumList[i].acProductName)
			.arg(tCameraEnumList[i].acDriverVersion)
			.arg(tCameraEnumList[i].acSn)
		);
	}

	return lists;
}

int MVCAMStream::loop(int g_hCamera) {

    //int                     g_hCamera = -1;     //设备句柄
	tSdkFrameHead           g_tFrameHead;       //图像帧头信息
	unsigned char*          g_pRawBuffer = NULL;     //raw数据

	int cnt = 0;

    while(1) {
		cnt++;
        if(cnt % 50 == 0) qDebug() << "mvcam thread : " << QThread::currentThread();
        if(!pause_status) {

            if(quit_status) break;

			if (CameraGetImageBuffer(g_hCamera, &g_tFrameHead, &g_pRawBuffer, 2000) == CAMERA_STATUS_SUCCESS)
			{

                CameraImageProcess(g_hCamera, g_pRawBuffer, g_pRgbBuffer, &g_tFrameHead);
				CameraReleaseImageBuffer(g_hCamera, g_pRawBuffer);

                if (g_tFrameHead.uiMediaType == CAMERA_MEDIA_TYPE_MONO8) {
                    //
                } else {
                    memcpy(g_readBuf, g_pRgbBuffer, g_W_H_INFO.buffer_size * 3);
                    if (quit_status) break;

                    QImage img = QImage((const uchar*)g_readBuf, g_W_H_INFO.sensor_width, g_W_H_INFO.sensor_height, QImage::Format_RGB888);
                    emit FrameReceived(img);
                }

            } else {
                
                printf("timeout \n");
				QThread::usleep(1000);
            
            }

        } else {
            QThread::usleep(1000);
        }
        if(quit_status) break;
    }

    return 0;

}


void MVCAMStream::HandleEvent(const QJsonObject& event) {

	if(!event.contains("data")) {
		qDebug() << "none data";
	}
	
	qDebug() << sender() << event;

	if(event.contains("id")) {

		if(event["id"] == "WB") {
					
			int RPos, GPos, BPos;
			CameraSetOnceWB(g_hCamera);
			CameraGetGain(g_hCamera, &RPos, &GPos, &BPos);

			QJsonObject obj;
			obj.insert("type", "view");
			obj.insert("id", "WB");
			obj.insert("data", QJsonArray{ RPos, GPos, BPos});

			emit SendEvent(obj);

		}else if(event["id"] == "flipv") {
			
			if (event["data"].toBool()) {
				CameraSetMirror(g_hCamera, MIRROR_DIRECTION_VERTICAL, true);
			}else{
				CameraSetMirror(g_hCamera, MIRROR_DIRECTION_VERTICAL, false);
			}

		}else if(event["id"] == "fliph") {

			if (event["data"].toBool()) {
				CameraSetMirror(g_hCamera, MIRROR_DIRECTION_HORIZONTAL, true);
			}else{
				CameraSetMirror(g_hCamera, MIRROR_DIRECTION_HORIZONTAL, false);
			}

		}else if(event["id"] == "horizontalSlider_gain_r") {

			int RPos, GPos, BPos;
			CameraGetGain(g_hCamera, &RPos, &GPos, &BPos);
			CameraSetGain(g_hCamera, event["data"].toInt(), GPos, BPos);

		}else if(event["id"] == "horizontalSlider_gain_g") {

			int RPos, GPos, BPos;
			CameraGetGain(g_hCamera, &RPos, &GPos, &BPos);
			CameraSetGain(g_hCamera, RPos, event["data"].toInt(), BPos);

		}else if(event["id"] == "horizontalSlider_gain_b") {

			int RPos, GPos, BPos;
			CameraGetGain(g_hCamera, &RPos, &GPos, &BPos);
			CameraSetGain(g_hCamera, RPos, GPos, event["data"].toInt());

		}else if(event["id"] == "horizontalSlider_saturation") {

			int RPos, GPos, BPos;
			CameraSetSaturation(g_hCamera, event["data"].toInt());

		}

	}

}