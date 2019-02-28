#include "houghcircle.h"
#include "ui_houghcircle.h"

HoughCircle::HoughCircle(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::HoughCircle)
{
    ui->setupUi(this);

    dp = 1;
    min_radius = 10;
    max_radius = 25;
    min_dist = (double) max_radius*2;

    connect(ui->minRad, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
    connect(ui->maxRad, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
}

HoughCircle::~HoughCircle()
{
    delete ui;
}

cv::Mat HoughCircle::runCpu(const cv::Mat &src)
{
    cv::Mat gray, dstImage;
    dstImage = src.clone();
    if(src.type() != CV_8UC1)
        cv::cvtColor(src, gray, cv::COLOR_RGB2GRAY);
    else gray = dstImage.clone();

//    cv::imshow("GG", gray);
//    cv::cvtColor(src, cimg, cv::COLOR_GRAY2BGR);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(gray, circles, CV_HOUGH_GRADIENT, dp, min_dist,\
                     50, min_radius*2, min_radius, max_radius);

    for(size_t i=0;i<circles.size();i++){
        cv::Vec3f c = circles[i];
        circle(dstImage, cv::Point(c[0], c[1]), c[2], cv::Scalar(0,0,255), 3, CV_AA);
        circle(dstImage, cv::Point(c[0], c[1]), 2, cv::Scalar(0,0,255), 3, CV_AA);
    }

    return dstImage;
}

void HoughCircle::valueCheck()
{
    min_radius = ui->minRad->value();
    ui->maxRad->setMinimum(min_radius+1);
    if(ui->maxRad->value() <= ui->minRad->value())
        ui->maxRad->setValue(min_radius+1);
    max_radius = ui->maxRad->value();

    emit valueChanged();
}
