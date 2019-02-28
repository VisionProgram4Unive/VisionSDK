#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include <QWidget>
#include "abstructalgorithm.h"

namespace Ui {
class GaussianBlur;
}

class GaussianBlur : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit GaussianBlur(QWidget *parent = 0);
    ~GaussianBlur();

    virtual cv::Mat runCpu(const cv ::Mat &src);
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src);

private:
    Ui::GaussianBlur *ui;

    int c_H;
    int c_W;
    double c_X;
    double c_Y;

private slots:
    virtual void valueCheck();
};

#endif // GAUSSIANBLUR_H
