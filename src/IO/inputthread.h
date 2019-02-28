#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <QImage>
#include <QDebug>

#include <opencv2/opencv.hpp>

/* platform dependency code */
#ifdef __gnu_linux__
    #include "v4l2capture.h"
#elif _WIN32
//	#include <opencv2/videoio.hpp>
    struct Resolution
    {
    public :
        Resolution(uint32_t w, uint32_t h):width(w),height(h) {}
        uint32_t getWidth() { return width; }
        uint32_t getHeight() { return height; }

    private :
        uint32_t width;
        uint32_t height;
    };

#include <vector>

#endif
/* platform dependency code */

using namespace std;

class InputThread : public QThread
{
    Q_OBJECT
public:
    InputThread(QObject *parent = 0);
    ~InputThread();

	//camera
    void openCamera(string dev);
    void openCamera(int dev);
	//video
    void getData(string fileName);

signals:
    void updateQData(QImage image);
    void updateMData(cv::Mat mat);
//    void updateData(uchar data, int width, int height);
    void updateResolutionData(std::vector<Resolution> resolutionList);

public slots:
    void setCamera(int index);
    void run();

    void pause() { m_pause = true; }
    void resume() { m_pause = false; pauseCondition.wakeAll(); }
    void stop() { m_stop = true; resume(); }

private:
    void capture();

    unsigned long w_time;
	//camera values
    unsigned int _width;
    unsigned int _height;
    string _dev;

    bool m_stop;
    bool m_pause;
    QWaitCondition pauseCondition;
    QMutex mutex;

    bool resetResolution;

/* platform dependency code */
#ifdef __gnu_linux__
public:
    V4L2Capture *cap;

    uint8_t * bgr;
private:
#elif _WIN32
public:
    cv::VideoCapture cap;
private:
    std::vector<Resolution> resolutionList;
#endif
/* platform dependency code */
};

#endif // INPUTTHREAD_H
