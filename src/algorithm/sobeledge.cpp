#include "sobeledge.h"
#include "ui_sobeledge.h"

SobelEdge::SobelEdge(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::SobelEdge)
{
    ui->setupUi(this);

    connect(ui->window, SIGNAL(clicked(bool)), dialog, SLOT(setVisible(bool)));

    //Definition new gui signals
    connect(ui->ordrX, SIGNAL(clicked(bool)), this, SLOT(valueCheck()));
    connect(ui->ordrY, SIGNAL(clicked(bool)), this, SLOT(valueCheck()));
}

SobelEdge::~SobelEdge()
{
    delete ui;
}

cv::Mat SobelEdge::runCpu(const cv::Mat &src)
{
    cv::Mat dstImage, gray,\
            edge_x, edge_y;

    if(src.type() == CV_8UC1)
        src.copyTo(gray);
    else
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    cv::blur(gray, gray, cv::Size(3,3));

    dstImage = cv::Mat::zeros(gray.rows, gray.cols, gray.type());

    if(ui->ordrX->isChecked()) {
        cv::Sobel(gray, edge_x, -1, 1, 0);
        dstImage += cv::abs(edge_x);
    }
    if(ui->ordrY->isChecked()) {
        cv::Sobel(gray, edge_y, -1, 0, 1);
        dstImage += cv::abs(edge_y);
    }

    dialog->setImage(dstImage);

    return dstImage;
}

//cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src)
//{
//    cv::gpu::GpuMat gray, edge_x, edge_y, dst;

//    if(src.type() != CV_8UC1)
//        cv::gpu::cvtColor(src, gray, CV_RGB2GRAY);
//    dst.upload(cv::Mat::zeros(src.rows, src.cols, CV_8UC1));

//    if(ui->ordrX->isChecked()) {
//        cv::gpu::Sobel(gray, edge_x, -1, 1, 0);
//        cv::gpu::abs(edge_x, edge_x);
//        cv::gpu::add(dst, edge_x, dst);
//    }
//    if(ui->ordrY->isChecked()) {
//        cv::gpu::Sobel(gray, edge_y, -1, 0, 1);
//        cv::gpu::abs(edge_y, edge_y);
//        cv::gpu::add(dst, edge_y, dst);
//    }
//    if(!ui->ordrX->isChecked() && !ui->ordrY->isChecked())
//        return src;

//    return dst;
//}

void SobelEdge::valueCheck()
{
    emit valueChanged();
}
