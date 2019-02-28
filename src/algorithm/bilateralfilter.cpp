#include "bilateralfilter.h"
#include "ui_bilateralfilter.h"

BilateralFilter::BilateralFilter(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::BilateralFilter)
{
    ui->setupUi(this);

    dia = ui->diameter->value();
    color = ui->bi_spinColor->value();
    space = ui->bi_spinSpace->value();

    connect(ui->window, SIGNAL(clicked(bool)), dialog, SLOT(setVisible(bool)));

    //Definition new gui singals
    connect(ui->diameter, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
    connect(ui->bi_spinColor, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
    connect(ui->bi_spinSpace, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
}

BilateralFilter::~BilateralFilter()
{
    delete ui;
}

cv::Mat BilateralFilter::runCpu(const cv::Mat &src)
{
    cv::Mat dstImage;

    cv::bilateralFilter(src, dstImage,
                        dia, color, space);

    dialog->setImage(dstImage);

    if(ui->window->isChecked()) dialog->show();

    return dstImage;
}

//cv::gpu::GpuMat BilateralFilter::runGpu(const cv::gpu::GpuMat &src)
//{
//    cv::gpu::GpuMat dst;

//    cv::gpu::bilateralFilter(src, dst, dia, color, space);

//    return dst;
//}

void BilateralFilter::valueCheck()
{
    dia = ui->diameter->value();
    color = ui->bi_spinColor->value();
    space = ui->bi_spinSpace->value();

    emit valueChanged();
}
