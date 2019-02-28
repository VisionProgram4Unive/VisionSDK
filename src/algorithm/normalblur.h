#ifndef NORMALBLUR_H
#define NORMALBLUR_H

#include <QWidget>
#include "abstructalgorithm.h"

namespace Ui {
class NormalBlur;
}

class NormalBlur : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit NormalBlur(QWidget *parent = 0);
    ~NormalBlur();

    virtual cv::Mat runCpu(const cv::Mat &src);
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src);

private:
    Ui::NormalBlur *ui;
    int c_H;
    int c_W;
private slots:
    virtual void valueCheck();

};

#endif // NORMALBLUR_H
