#include "gaussianblur.h"
#include "ui_gaussianblur.h"

GaussianBlur::GaussianBlur(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::GaussianBlur)
{
    ui->setupUi(this);

    c_H = ui->gau_spinH->value();
    c_W = ui->gau_spinW->value();
    c_X = ui->gau_spinX->value();
    c_Y = ui->gau_spinY->value();

    connect(ui->window, SIGNAL(clicked(bool)), dialog, SLOT(setVisible(bool)));

    //Definition new gui signals
    connect(ui->gau_spinH, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
    connect(ui->gau_spinW, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
    connect(ui->gau_spinX, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
    connect(ui->gau_spinY, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
}

GaussianBlur::~GaussianBlur()
{
    delete ui;
}

cv::Mat GaussianBlur::runCpu(const cv::Mat &src)
{
    cv::Mat dstImage;

    cv::GaussianBlur(src, dstImage,
             cv::Size(c_W, c_H),
                     c_X, c_Y);

    dialog->setImage(dstImage);

    return dstImage;
}

//cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src)
//{
//    cv::gpu::GpuMat dst;

//    cv::gpu::GaussianBlur(src, dst,
//                          cv::Size(c_W, c_H),
//                          c_X, c_Y);

////    dialog->setImage((cv::Mat) dst);

//    return dst;
//}

void GaussianBlur::valueCheck()
{
    c_H = ui->gau_spinH->value();
    c_W = ui->gau_spinW->value();
    c_X = (double)ui->gau_spinX->value();
    c_Y = (double)ui->gau_spinY->value();

    emit valueChanged();
}
