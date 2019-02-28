#ifndef CANNYEDGE_H
#define CANNYEDGE_H

#include <QWidget>
#include "abstructalgorithm.h"

namespace Ui {
class CannyEdge;
}

class CannyEdge : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit CannyEdge(QWidget *parent = 0);
    ~CannyEdge();

    virtual cv::Mat runCpu(const cv::Mat &src);
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src);

private:
    Ui::CannyEdge *ui;
    double edgeThresh;

private slots:
    virtual void valueCheck();
};

#endif // CANNYEDGE_H
