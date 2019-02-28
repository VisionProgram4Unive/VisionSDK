#ifndef PARAMWIDGET_H
#define PARAMWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//#include <opencv2/gpu/gpu.hpp>

#include "util/imagedialog.h"

// TODO
// unexpect crush issue relate show/hide dialog

class AbstructAlgorithm : public QWidget
{
    Q_OBJECT
public:
    explicit AbstructAlgorithm(QWidget *parent = 0);
    virtual ~AbstructAlgorithm();
    virtual cv::Mat runCpu(const cv::Mat &src) = 0;
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src) = 0;

protected:
    ImageDialog *dialog;

signals:
    void valueChanged();

private slots:
    virtual void valueCheck() = 0;
};

#endif // PARAMWIDGET_H
