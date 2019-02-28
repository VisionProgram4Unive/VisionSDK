#include "medianblur.h"
#include "ui_medianblur.h"

MedianBlur::MedianBlur(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::MedianBlur)
{
    ui->setupUi(this);

    mask = ui->median_spin->value();

    connect(ui->window, SIGNAL(clicked(bool)), dialog, SLOT(setVisible(bool)));

    //Definition new gui signals
    connect(ui->median_spin, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
}

MedianBlur::~MedianBlur()
{
    delete ui;
}
cv::Mat MedianBlur::runCpu(const cv::Mat &src)
{
    cv::Mat dstImage;

    cv::medianBlur(src, dstImage, mask);

    dialog->setImage(dstImage);

    return dstImage;
}

//cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src)
//{

//}

void MedianBlur::valueCheck()
{
    mask = ui->median_spin->value();
    emit valueChanged();
}
