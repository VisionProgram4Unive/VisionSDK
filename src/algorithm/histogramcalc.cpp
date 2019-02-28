#include "histogramcalc.h"
#include "ui_histogramcalc.h"

HistogramCalc::HistogramCalc(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::HistogramCalc)
{
    ui->setupUi(this);

    dialogTitle = "visionSDK";

    //Definition new gui signals
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(valueCheck()));
}

HistogramCalc::~HistogramCalc()
{
    delete ui;
}

cv::Mat HistogramCalc::runCpu(const cv::Mat &src)
{
    cv::Mat *out_hist;
    cv::Mat histogram(400, 512, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Scalar rgb[3];
                rgb[0] = cv::Scalar(255, 0, 0);
                rgb[1] = cv::Scalar(0, 255, 0);
                rgb[2] = cv::Scalar(0, 0, 255);
    std::vector<cv::Mat> channel;
    int loopCnt = 1;

    int histSize = 256;
    float range[] = {0, 256};
    const float *histRange = {range};

    if(src.type() == CV_8UC1){
        channel.push_back(src);
        out_hist = new cv::Mat;
    }
    else {
        cv::split(src, channel);
        out_hist = new cv::Mat[3];
        loopCnt = 3;
    }

    for(int i=0;i<loopCnt;++i){
        cv::calcHist(&channel[i] /* Source */,
                1 			     /* no. of image */,
                0 			     /* channel */,
                cv::Mat() 	 	 /* mask 8bit array */,
                out_hist[i]	 	 /* out */,
                1 			     /* histogram dimesion */,
                &histSize, &histRange,
                true 		   	 /* uniform */,
                false		   	 /* accumulate */);

        cv::normalize(out_hist[i], out_hist[i], 0, histogram.rows,
                      cv::NORM_MINMAX, -1, cv::Mat());
    }

    int bin_w = (int) 512/256+0.5;
    for(int i=1;i<histSize;++i){
        for(int j=0;j<loopCnt;++j){
            line(histogram,
                 cv::Point(bin_w*(i-1), 400 - (int)(out_hist[j].at<float>(i-1)+0.5 )),
                 cv::Point(bin_w*(i), 	400 - (int)(out_hist[j].at<float>(i)+0.5 )),
                 rgb[j], 2, 8, 0);
        }
    }

    if(src.type() == CV_8UC1) delete   out_hist;
    else  					  delete[] out_hist;
    out_hist = NULL;

    dialog->setImage(histogram);
    dialog->setWindowTitle(dialogTitle);
    dialog->show();

    return src;
}

//cv::gpu::GpuMat runGpu(const cv::gpu::GpuMat &src)
//{

//}

void HistogramCalc::valueCheck()
{
    dialogTitle = ui->lineEdit->displayText();
    emit valueChanged();
}
