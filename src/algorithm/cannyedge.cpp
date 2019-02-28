#include "cannyedge.h"
#include "ui_cannyedge.h"

CannyEdge::CannyEdge(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::CannyEdge)
{
    ui->setupUi(this);

    edgeThresh = 1;

    connect(ui->window, SIGNAL(clicked(bool)), dialog, SLOT(setVisible(bool)));

    //Definition new gui signals
    connect(ui->valueSild, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
    connect(ui->image_color, SIGNAL(toggled(bool)), this, SLOT(valueCheck()));
    connect(ui->image_grey, SIGNAL(toggled(bool)), this, SLOT(valueCheck()));
}

CannyEdge::~CannyEdge()
{
    delete ui;
}

cv::Mat CannyEdge::runCpu(const cv::Mat &src)
{
    cv::Mat dstImage, gray, edge;

    if(src.type() == CV_8UC1)
        src.copyTo(gray);
    else
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    cv::blur(gray, edge, cv::Size(3,3));

    cv::Canny(edge, edge, edgeThresh, edgeThresh*3);

//    int outType;
//    if(ui->image_grey->isChecked()) outType = CV_8UC1;
//    else							outType = src.type();
//    dstImage.create(src.size(), outType);
//    dstImage = cv::Scalar::all(0);

    if(ui->image_grey->isChecked()) gray.copyTo(dstImage, edge);
    else							src.copyTo(dstImage, edge);

    dialog->setImage(dstImage);

    return dstImage;
}

//cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src)
//{
//    cv::gpu::GpuMat gray, edge;

//    if(CV_8UC1 != src.type())
//        cv::gpu::cvtColor(src, gray, CV_RGB2GRAY);

//    cv::gpu::Canny(gray, edge, edgeThresh, edgeThresh*3);

//    return edge;
//}

void CannyEdge::valueCheck()
{
    edgeThresh = (double)ui->valueSild->value();

    emit valueChanged();
}
