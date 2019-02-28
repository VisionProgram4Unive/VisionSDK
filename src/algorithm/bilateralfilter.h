#ifndef BILATERALFILTER_H
#define BILATERALFILTER_H

#include <QWidget>
#include "abstructalgorithm.h"

namespace Ui {
class BilateralFilter;
}

class BilateralFilter : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit BilateralFilter(QWidget *parent = 0);
    ~BilateralFilter();

    virtual cv::Mat runCpu(const cv::Mat &src);
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src);

private:
    Ui::BilateralFilter *ui;

    short dia;
    int color, space;

private slots:
    virtual void valueCheck();
};

#endif // BILATERALFILTER_H
