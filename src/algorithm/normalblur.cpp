#include "normalblur.h"
#include "ui_normalblur.h"

NormalBlur::NormalBlur(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::NormalBlur)
{
    ui->setupUi(this);

    c_H = c_W = 1;

    connect(ui->window, SIGNAL(clicked(bool)), dialog, SLOT(setVisible(bool)));

    //Definition new gui signals
    connect(ui->normal_spinH, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
    connect(ui->normal_spinW, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
}

NormalBlur::~NormalBlur()
{
    delete ui;
}

cv::Mat NormalBlur::runCpu(const cv::Mat &src)
{
    cv::Mat dstImage;


    cv::blur(src, dstImage,
             cv::Size(c_W, c_H),
             cv::Point(-1, -1) );

    dialog->setImage(dstImage);
    if(ui->window->isChecked()) dialog->show();

    return dstImage;
}

//cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src)
//{
//    cv::gpu::GpuMat dst, gray;

//    if(CV_8UC1 != src.type() )
//        cv::gpu::cvtColor(src, gray, CV_RGB2GRAY);

//    cv::gpu::blur(gray, dst,
//             cv::Size(c_W, c_H));

////    dialog->setImage((cv::Mat) dst);
////    if(ui->window->isChecked()) dialog->show();

//    return dst;
//}

void NormalBlur::valueCheck()
{
    c_H = ui->normal_spinH->value();
    c_W = ui->normal_spinW->value();

    emit valueChanged();
}
