#include "queuethread.h"

QueueThread::QueueThread(QObject *parent) : QThread(parent)
{
    m_stop = false;
    s_pause = false;
    b_pause = true;
}

QueueThread::~QueueThread()
{
    stop();
    while(isRunning()) wait(100);

    qDebug() << "QueueThread : Terminated" << endl;
}

void QueueThread::move(int src, int dst)
{
    if(dst >= algorithmList.size()) dst = algorithmList.size()-1;

    mutex_list.lock();
        algorithmList.move(src, dst);
    mutex_list.unlock();
}

void QueueThread::setProcImage(const cv::Mat &value)
{
    //gpu///
    srcImage = value.clone();
}

void QueueThread::run()
{
    while(1){
        if(m_stop){
            for(int i=0;i<algorithmList.size();i++){
                algorithmList.at(i)->close();
                delete algorithmList.at(i);
                algorithmList.removeAt(i);
            }
            qDebug() << "QueueThread : Stop and Delete all widgets" << endl;
            break;
        } else if(b_pause){
            mutex_wait.lock();
            qDebug() << "QueueThread : Wait for RUN Button " << endl;
            b_pause = false;
            btnCondition.wait(&mutex_wait);
            mutex_wait.unlock();
        } else if(s_pause){
            mutex_wait.lock();
            qDebug() << "QueueThread : Wait for GUI Signal " << endl;
            s_pause = false;
            sigCondition.wait(&mutex_wait);
            mutex_wait.unlock();
        }

        //      running statment entry
        if(m_stop) continue;
        //        qDebug() << "Thread Running" << endl;
        step(srcImage);
        wait4sig();
    }
    qDebug() << "QueueThread : Stoped" << endl;
}

void QueueThread::step(cv::Mat procImage)
{
    mutex_list.lock();
    for(int i=0;i<algorithmList.size();i++)
        //            gpuImageMODE
        procImage = algorithmList.at(i)->runCpu(procImage);
    mutex_list.unlock();

    //TODO : emit gpuMODE
//    emit updateProcessing( mat2qimage(procImage) );
    emit updateProc(procImage);

    usleep(300);
}
