#include "threshold.h"
#include "ui_threshold.h"

Threshold::Threshold(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::Threshold)
{
    ui->setupUi(this);

    loopCnt = 1;
    max_value = 255;

    type = cv::THRESH_BINARY; value = 0;
    mask = 3; constant = 5.0; method = cv::ADAPTIVE_THRESH_MEAN_C;

    connect(ui->window, SIGNAL(clicked(bool)), dialog, SLOT(setVisible(bool)));

    //Definition new gui signals
    connect(ui->manualValue, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
    connect(ui->typeBox, SIGNAL(highlighted(int)), this, SLOT(valueCheck()));
    connect(ui->radioAdap, SIGNAL(toggled(bool)), this, SLOT(valueCheck()));
    connect(ui->mask, SIGNAL(valueChanged(int)), this, SLOT(valueCheck()));
    connect(ui->constant, SIGNAL(valueChanged(double)), this, SLOT(valueCheck()));
    connect(ui->methodBox, SIGNAL(highlighted(int)), this, SLOT(valueCheck()));
    connect(ui->image_color, SIGNAL(toggled(bool)), this, SLOT(valueCheck()));
}

Threshold::~Threshold()
{
    delete ui;
}

cv::Mat Threshold::runCpu(const cv::Mat &src)
{
    cv::Mat dstImage;
	std::vector<cv::Mat> channel;

    // in/out image channel check
    if(src.type() == CV_8UC1){
        ui->image_color->setCheckable(false);
        ui->image_grey->setChecked(true);
    } else {
        ui->image_color->setCheckable(true);
        ui->image_grey->setChecked(false);
    }

    if(ui->image_color->isChecked()){
        loopCnt = 3;
        cv::split(src, channel);
    } else {
		loopCnt = 1;
        if(src.type() == CV_8UC1) src.copyTo(dstImage);
        else		cv::cvtColor(src, dstImage, CV_RGB2GRAY);
        channel.push_back(dstImage);
    }

    for(int i=0;i<loopCnt;++i){

        /* Global threshold */
        if(ui->radioMan->isChecked())
            cv::threshold(channel[i], channel[i],
                      value, max_value, type );

        /*
         * Locally adaptive thresholding
         * calculated individually for each pixel
         * T(x,y) = 1/n^2 * sumOfx(sumOfy(pix_x+xi,pix_y+yi)) - C
         */
        else
            cv::adaptiveThreshold(channel[i], channel[i], max_value,
                          method, type, mask, constant);
        // adaptiveMethod : ADAPTIVE_THRESH_MEAN_C or ADAPTIVE_THRESH_GAUSSIAN_C
        // thresholdType  : THRESH_BINARY or THRESH_BINARY_INV
        // blockSize	  : odd numbers
        // C			  : constant
    }

    cv::merge(channel, dstImage);

    dialog->setImage(dstImage);

    return dstImage;
}

//cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src)
//{
//    cv::gpu::GpuMat dst;

//    std::vector<cv::gpu::GpuMat> channel;

//    if(src.type() != CV_8UC1) {
//        cv::gpu::split(src, channel);
//        loopCnt = 3;
//    } else{
//        cv::gpu::cvtColor(src, dst, CV_RGB2GRAY);
//        channel.push_back(dst);
//        loopCnt = 1;
//    }

//    for(int i=0;i<loopCnt;++i)
//        cv::gpu::threshold(channel[i], channel[i], value, max_value, type);
//    cv::gpu::merge(channel, dst);

//    return dst;
//}

void Threshold::valueCheck()
{
    // Threshold type check
    switch(ui->typeBox->currentIndex())
    {
    case 1:
        type = cv::THRESH_BINARY;
        break;
    case 2:
        type = cv::THRESH_BINARY_INV;
        break;
    case 3:
        type = cv::THRESH_TRUNC;
        break;
    case 4:
        type = cv::THRESH_TOZERO;
        break;
    case 5:
        type = cv::THRESH_TOZERO_INV;
        break;
    default:
        type = cv::THRESH_BINARY;
    }

    if(ui->radioAdap->isChecked())
        type = (type == cv::THRESH_BINARY_INV) ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;

    value = (double)ui->manualValue->value();
    mask = ui->mask->value();
    constant = ui->constant->value();
    method = (ui->methodBox->currentIndex() == 1) ? cv::ADAPTIVE_THRESH_MEAN_C : cv::ADAPTIVE_THRESH_GAUSSIAN_C;

	emit valueChanged();
}
