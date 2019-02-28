#include "sharpen.h"
#include "ui_sharpen.h"

Sharpen::Sharpen(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::Sharpen)
{
    ui->setupUi(this);
    
    normal = new NormalBlur(ui->normal);
    gauss = new GaussianBlur(ui->gaussian);
    median = new MedianBlur(ui->median);
    bilateral = new BilateralFilter(ui->bilateral);

    connect(normal, SIGNAL(valueChanged()), this, SLOT(valueCheck()));
    connect(gauss, SIGNAL(valueChanged()), this, SLOT(valueCheck()));
    connect(median, SIGNAL(valueChanged()), this, SLOT(valueCheck()));
    connect(bilateral, SIGNAL(valueChanged()), this, SLOT(valueCheck()));

    connect(ui->window, SIGNAL(clicked(bool)), dialog, SLOT(setVisible(bool)));

    //Definition new gui signals
    connect(ui->alphaSild, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));

}

Sharpen::~Sharpen()
{
    delete normal;
    delete gauss;
    delete median;
    delete bilateral;

    delete ui;
}

cv::Mat Sharpen::runCpu(const cv::Mat &src)
{
    cv::Mat dstImage;
    cv::Mat ftdImage;

    switch(ui->tabWidget->currentIndex())
    {
    case 0:
        ftdImage = normal->runCpu(src); break;
    case 1:
        ftdImage = gauss->runCpu(src); break;
    case 2:
        ftdImage = median->runCpu(src); break;
    case 3:
        ftdImage = bilateral->runCpu(src); break;
    default:
        ftdImage = normal->runCpu(src); break;
    }

    dstImage = ((double)ui->alphaSild->value()/10) * (src-ftdImage) + src;

    dialog->setImage(dstImage);
    if(ui->window->isChecked()) dialog->show();

    return dstImage;
}

//cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src)
//{

//}

void Sharpen::valueCheck()
{
    emit valueChanged();
}
