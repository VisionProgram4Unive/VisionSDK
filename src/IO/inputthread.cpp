#include "inputthread.h"
#include <QMessageBox>

InputThread::InputThread(QObject *parent)
    : QThread(parent),
      w_time(30),_width(0),_height(0),
      m_stop(false),m_pause(true),resetResolution(false)
{
    /* platform dependency code */
    #ifdef __gnu_linux__
        cap = nullptr;
        bgr = nullptr;
    #endif
    /* platform dependency code */

    qRegisterMetaType<cv::Mat>("cv::Mat");
}

InputThread::~InputThread()
{
    while(isRunning()) stop();

    qDebug() << "InputThread : Terminated" << endl;

    /* platform dependency code */
    #ifdef __gnu_linux__
        delete cap; cap = nullptr;
        delete bgr; bgr = nullptr;
    #endif
    /* platform dependency code */
}

void InputThread::getData(string fileName)
{
    pause();

    auto cvMat2QImage = [](cv::Mat & mat)->QImage
    {
        QImage image;

        switch(mat.type())
        {
        case CV_8UC4:
            image = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);
            break;
        case CV_8UC3:
            image = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
            image = image.rgbSwapped();
            break;
        case CV_8UC1: static QVector<QRgb> colorTable;
            if(colorTable.isEmpty())
                for(int i=0;i<256;++i) colorTable.push_back( qRgb(i,i,i) );
            image = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
            image.setColorTable(colorTable);
            break;
        }

        return image;
    };

    cv::Mat image = cv::imread(fileName);
    emit updateQData( cvMat2QImage(image) );
    emit updateMData( image );
}

void InputThread::run()
{
    while(1){
        if(m_stop){
            break;
        } else if(m_pause){
            mutex.lock();
            qDebug() << "InputThread : Waitting " << endl;
            pauseCondition.wait(&mutex);
            mutex.unlock();
        }

        //      running statment entry
        if(m_stop || m_pause) continue;
//        qDebug() << "updating Thread Running" << endl;
        capture();
        msleep(w_time);
    }
    qDebug() << "InputThread : Stoped" << endl;
}


//////////////////////////////
/* platform dependency code */
//////////////////////////////
#ifdef __gnu_linux__

/* To get resolution List from temp capture obj  */
void InputThread::openCamera(string dev)
{
    pause();

    cap = new V4L2Capture(dev.c_str());
    emit updateResolutionData( cap->getResolution() );
    _dev = dev;

    //current device is opened than re-open, set default resolution
    if(this->resetResolution) { delete cap; this->resetResolution = false; }
    V4L2Capture tempCap(_dev.c_str());
    emit updateResolutionData( tempCap.getResolution() );
    Resolution defResolution = tempCap.getResolution().at(0);
    tempCap.setResolution(defResolution.getWidth(), defResolution.getHeight());
}

void InputThread::openCamera(int dev)
{
    switch(dev)
    {
    case 0:
        openCamera("/dev/video0");
        break;
    case 1:
        openCamera("/dev/video1");
        break;
    case 2:
        openCamera("/dev/video2");
        break;
    default:
        qDebug() << "InputThread : Can not find Camera device!" << endl;
    }
}

void InputThread::setCamera(int index)
{
    pause();

    cap = new V4L2Capture(_dev.c_str());
    Resolution resolution = cap->getResolution().at(index);
    _width = resolution.getWidth(); _height = resolution.getHeight();
    cap->setResolution(_width, _height);

    resetResolution = true;

    qDebug() << "InputThread : set resolution" << endl
             << index << ":" << _width << "*" << _height << endl;

    delete[] bgr;
    bgr = new uint8_t[_width*_height*3];

    //pre heat camera buffers..
    for(int i=0;i<5;i++) cap->getBGRframe();

    resume();
}

void InputThread::capture()
{
    cap->getBGRframe(bgr);

    emit updateMData(cv::Mat(_height, _width, CV_8UC3, bgr));
    emit updateQData(QImage(bgr, _width, _height, QImage::Format_RGB888).rgbSwapped());
}

#elif _WIN32
/* To getting resolution List from temp capture obj  */
void InputThread::openCamera(string dev)
{
    pause();
    cap.open(dev);

    resolutionList.push_back(
                Resolution( static_cast<uint32_t>(cap.get(CV_CAP_PROP_FRAME_WIDTH)),
                            static_cast<uint32_t>(cap.get(CV_CAP_PROP_FRAME_HEIGHT)) )
                );

    //emit updateResolutionData( cap->getResolution() );
    _dev = dev;

    //current device is opened than close
    if(this->resetResolution) cap.release();

    //V4L2Capture tempCap(_dev.c_str());
    //emit updateResolutionData( tempCap.getResolution() );
    //Resolution defResolution = tempCap.getResolution().at(0);
    //tempCap.setResolution(defResolution.getWidth(), defResolution.getHeight());
}
void InputThread::openCamera(int dev)
{
    switch(dev)
    {
    case 0:
        openCamera("0");
        break;
    case 1:
        openCamera("1");
        break;
    case 2:
        openCamera("2");
        break;
    default:
        qDebug() << "Can not find Camera device!" << endl;
    }
}

void InputThread::setCamera(int index)
{
    pause();

    openCamera(_dev.c_str());

    Resolution resolution( static_cast<uint32_t>(cap.get(CV_CAP_PROP_FRAME_WIDTH)),
                           static_cast<uint32_t>(cap.get(CV_CAP_PROP_FRAME_HEIGHT)) );
    _width = resolution.getWidth(); _height = resolution.getHeight();
    //cap->setResolution(_width, _height);

    resetResolution = true;

    qDebug() << "received index : " << index << endl;
    qDebug() << _width << "*" << _height << endl;

    //pre heat camera buffers..
    for(int i=0;i<5;i++) cap.grab();

    resume();
}

void InputThread::capture()
{
    cv::Mat frame;
    cap >> frame;

    emit updateMData( frame );
    emit updateQData( mat2qimage(frame) );
}
#endif
/* platform dependency code */
