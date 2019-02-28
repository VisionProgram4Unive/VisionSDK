#ifndef SOBELEDGE_H
#define SOBELEDGE_H

#include <QWidget>
#include "abstructalgorithm.h"
#include <QDebug>

namespace Ui {
class SobelEdge;
}

class SobelEdge : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit SobelEdge(QWidget *parent = 0);
    ~SobelEdge();

    virtual cv::Mat runCpu(const cv::Mat &src);
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src);
private:
    Ui::SobelEdge *ui;

private slots:
    virtual void valueCheck();
};

#endif // SOBELEDGE_H
