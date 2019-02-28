#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <QWidget>
#include "abstructalgorithm.h"

namespace Ui {
class Threshold;
}

class Threshold : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit Threshold(QWidget *parent = 0);
    ~Threshold();

    virtual cv::Mat runCpu(const cv::Mat &src);
//    virtual cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src);

private:
    Ui::Threshold *ui;

	int type;
	int loopCnt;
	double value;
    int max_value;

    int mask;
    double constant;
    int method;

private slots:
    virtual void valueCheck();
};

#endif // THRESHOLD_H
