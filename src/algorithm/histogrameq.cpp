#include "histogrameq.h"
#include "ui_histogrameq.h"

HistogramEq::HistogramEq(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::HistogramEq)
{
    ui->setupUi(this);
}

HistogramEq::~HistogramEq()
{
    delete ui;
}

cv::Mat HistogramEq::runCpu(const cv::Mat &src)
{
    std::vector<cv::Mat> channel;
    cv::Mat dstImage;

    if(src.type() == CV_8UC1)
        channel.push_back(src);
    else{
        cv::cvtColor(src, dstImage, CV_BGR2YCrCb);
        cv::split(dstImage, channel);
    }

    cv::equalizeHist(channel[0], channel[0]);
    cv::merge(channel, dstImage);

    if(src.type() != CV_8UC1)
        cv::cvtColor(dstImage, dstImage, CV_YCrCb2BGR);

    dialog->setImage(dstImage);
    if(ui->window->isChecked()) dialog->show();

    return dstImage;
}

//cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src)
//{
//    std::vector<cv::gpu::GpuMat> channel;
//    cv::gpu::GpuMat dst;

//    if(src.type() == CV_8UC1)
//        channel.push_back(src);
//    else{
//        cv::gpu::cvtColor(src, dst, CV_BGR2YCrCb);
//        cv::gpu::split(dst, channel);
//    }

//    cv::gpu::equalizeHist(channel[0], channel[0]);
//    cv::gpu::merge(channel, dst);

//    if(src.type() != CV_8UC1)
//        cv::gpu::cvtColor(dst, dst, CV_YCrCb2BGR);

////    dialog->setImage((cv::Mat) dst);
////    if(ui->window->isChecked()) dialog->show();

//    return dst;
//}
