#ifndef SHARPEN_H
#define SHARPEN_H

#include <QWidget>
#include "abstructalgorithm.h"
#include "normalblur.h"
#include "gaussianblur.h"
#include "medianblur.h"
#include "bilateralfilter.h"

namespace Ui {
class Sharpen;
}

class Sharpen : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit Sharpen(QWidget *parent = 0);
    ~Sharpen();
    
    virtual cv::Mat runCpu(const cv::Mat &src);
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src);

private:
    Ui::Sharpen *ui;
    
    AbstructAlgorithm *normal;
    AbstructAlgorithm *gauss;
    AbstructAlgorithm *median;
    AbstructAlgorithm *bilateral;
private slots:
    virtual void valueCheck();
};

#endif // SHARPEN_H
