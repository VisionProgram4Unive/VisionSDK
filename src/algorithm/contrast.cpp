#include "contrast.h"
#include "ui_contrast.h"

Contrast::Contrast(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::Contrast)
{
    ui->setupUi(this);

    contrast   = (double)ui->contrastSlider->value() / 10;
    brightness = ui->brightnessSlider->value();

    connect(ui->window, SIGNAL(clicked(bool)), dialog, SLOT(setVisible(bool)));

    //Definition new gui signals
    connect(ui->contrastSlider,   SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
    connect(ui->brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
}

Contrast::~Contrast()
{
    delete ui;
}

cv::Mat Contrast::runCpu(const cv::Mat &src)
{
    cv::Mat dstImage;

    src.convertTo(dstImage, -1,
                  contrast,  /* alpha */
                  brightness /* beta */
                  );

    dialog->setImage(dstImage);

    return dstImage;
}

//cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src)
//{

//}

void Contrast::valueCheck()
{
    contrast   = (double)ui->contrastSlider->value() / 10;
    brightness = ui->brightnessSlider->value();

    emit valueChanged();
}
