#ifndef HISTOGRAMCALC_H
#define HISTOGRAMCALC_H

#include <QWidget>
#include "abstructalgorithm.h"

namespace Ui {
class HistogramCalc;
}

class HistogramCalc : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit HistogramCalc(QWidget *parent = 0);
    ~HistogramCalc();

    virtual cv::Mat runCpu(const cv::Mat &src);
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src);

private:
    Ui::HistogramCalc *ui;

    QString dialogTitle;
private slots:
    virtual void valueCheck();
};

#endif // HISTOGRAMCALC_H
