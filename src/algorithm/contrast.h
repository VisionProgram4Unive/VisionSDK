#ifndef CONTRAST_H
#define CONTRAST_H

#include <QWidget>
#include "abstructalgorithm.h"

namespace Ui {
class Contrast;
}

class Contrast : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit Contrast(QWidget *parent = 0);
    ~Contrast();

    virtual cv::Mat runCpu(const cv::Mat &src);
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src);

private:
    Ui::Contrast *ui;

    double contrast;
    int brightness;

private slots:
    virtual void valueCheck();
};

#endif // CONTRAST_H
