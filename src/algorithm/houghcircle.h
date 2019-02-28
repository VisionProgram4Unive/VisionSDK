#ifndef HOUGHCIRCLE_H
#define HOUGHCIRCLE_H

#include <QWidget>
#include "abstructalgorithm.h"

namespace Ui {
class HoughCircle;
}

class HoughCircle : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit HoughCircle(QWidget *parent = 0);
    ~HoughCircle();

    virtual cv::Mat runCpu(const cv::Mat &src);

private:
    Ui::HoughCircle *ui;

    double dp;
    double min_dist;
    int min_radius;
    int max_radius;


private slots:
    virtual void valueCheck();
};

#endif // HOUGHCIRCLE_H
