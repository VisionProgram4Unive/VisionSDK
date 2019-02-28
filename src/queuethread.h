#ifndef QUEUETHEAD_H
#define QUEUETHEAD_H

#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <QImage>
#include <QDebug>

#include <opencv2/opencv.hpp>

#include "algorithm/abstructalgorithm.h"

class QueueThread : public QThread
{
    Q_OBJECT
public:
    QueueThread(QObject *parent = 0);
    ~QueueThread();

    /* Wrapped QList Methods */
    int  size() { return algorithmList.size(); }
    void show(const int &value) { algorithmList.at(value)->show(); }
    void hide(const int &value) { algorithmList.at(value)->hide(); }
    void move(int src, int dst);
    void append(AbstructAlgorithm *value) { mutex_list.lock();
                                      algorithmList.append(value);
                                      mutex_list.unlock();}
    void remove(const int &value){ mutex_list.lock();
                                   delete algorithmList.at(value);
                                   algorithmList.removeAt(value);
                                   mutex_list.unlock();}

    /* Thread control Method */
    void waitBtn() { b_pause = true; sigCondition.wakeAll(); }
    void wakeBtn() { btnCondition.wakeAll(); }
    void stop() { sigCondition.wakeAll(); btnCondition.wakeAll();
                  m_stop = true; }


signals:
    void updateProcessing(QImage image);
    void updateProc(const cv::Mat & mat);

public slots:
    void run();
    void wakeup() { sigCondition.wakeAll(); }
    void setProcImage(const cv::Mat &value);

private:
    void step(cv::Mat procImage);
    void wait4sig() { s_pause = true; btnCondition.wakeAll(); }

    bool m_stop;
    bool s_pause;
    bool b_pause;
    QWaitCondition btnCondition;
    QWaitCondition sigCondition;
    QMutex mutex_wait;
    QMutex mutex_list;

    cv::Mat srcImage;
    QList<AbstructAlgorithm *> algorithmList;

};

#endif // QUEUETHEAD_H
