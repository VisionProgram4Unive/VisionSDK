#ifndef DETECTCIRCLE_H
#define DETECTCIRCLE_H

#include <QWidget>
#include <algorithm>
#include <math.h>
#include "abstructalgorithm.h"

namespace Ui {
class detectCircle;
}

class detectCircle : public AbstructAlgorithm
{
    Q_OBJECT

public:
    explicit detectCircle(QWidget *parent = 0);
    ~detectCircle();

    virtual cv::Mat runCpu(const cv::Mat &src);

private:
    Ui::detectCircle *ui;

private slots:
    virtual void valueCheck();
};
#endif // DETECTCIRCLE_H
