#ifndef HISTOGRAMEQ_H
#define HISTOGRAMEQ_H

#include <QWidget>
#include "abstructalgorithm.h"

namespace Ui {
class HistogramEq;
}

class HistogramEq : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit HistogramEq(QWidget *parent = 0);
    ~HistogramEq();

    virtual cv::Mat runCpu(const cv::Mat &src);
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src);

private:
    Ui::HistogramEq *ui;
private slots:
    virtual void valueCheck() {}
};

#endif // HISTOGRAMEQ_H
