#ifndef MEDIANBLUR_H
#define MEDIANBLUR_H

#include <QWidget>
#include "abstructalgorithm.h"

namespace Ui {
class MedianBlur;
}

class MedianBlur : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit MedianBlur(QWidget *parent = 0);
    ~MedianBlur();

    virtual cv::Mat runCpu(const cv::Mat &src);
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src);

private:
    Ui::MedianBlur *ui;

    int mask;

private slots:
    virtual void valueCheck();
};

#endif // MEDIANBLUR_H
