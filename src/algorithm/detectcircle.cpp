#include "detectcircle.h"
#include "ui_detectcircle.h"

detectCircle::detectCircle(QWidget *parent) :
    AbstructAlgorithm(parent),
    ui(new Ui::detectCircle)
{
    ui->setupUi(this);
}

detectCircle::~detectCircle()
{
    delete ui;
}

cv::Mat detectCircle::runCpu(const cv::Mat &src)
{
    cv::Mat roiImage = src.clone();
    if(src.type() != CV_8UC1)
        cv::cvtColor(roiImage, roiImage, CV_RGB2GRAY);
    //Threshold
    cv::Mat thrImage;
    cv::threshold(roiImage, thrImage, 100, 255, CV_THRESH_BINARY_INV);
    //Morphology, image close
    cv::Mat morphImage, element;
    element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
    cv::dilate(thrImage, morphImage, element, cv::Point(-1, -1), 5);
    cv::erode(morphImage, morphImage, element, cv::Point(-1, -1), 7);
//    cv::morphologyEx(thrImage, morphImage, CV_MOP_CLOSE, element);
    //smoothing
    cv::medianBlur(morphImage, morphImage, 29);
    cv::Point posmin, posmax;
    bool exitloop = false;
    for(int y=0;y<morphImage.rows && !exitloop;y++)
        for(int x=0;x<morphImage.cols && !exitloop;x++)
            if(morphImage.at<uchar>(y, x) == 255){
                posmin.y = y;
                exitloop = true;
            }
    exitloop = false;
    for(int x=0;x<morphImage.cols && !exitloop;x++)
        for(int y=0;y<morphImage.rows && !exitloop;y++)
            if(morphImage.at<uchar>(y, x) == 255){
                posmin.x = x;
                exitloop = true;
            }
    exitloop = false;
    for(int y=morphImage.rows; y>0 && !exitloop;y--)
        for(int x=morphImage.cols; x>0 && !exitloop;x--)
            if(morphImage.at<uchar>(y, x) == 255){
                posmax.y = y;
                exitloop = true;
                break;
            }
    exitloop = false;
    for(int x=morphImage.cols; x>0 && !exitloop;x--)
        for(int y=morphImage.rows; y>0 && !exitloop;y--)
            if(morphImage.at<uchar>(y, x) == 255){
                posmax.x = x;
                exitloop = true;
            }
    cv::Point circleCenter = cv::Point(posmin.x+(posmax.x-posmin.x)/2, posmin.y+(posmax.y-posmin.y)/2);
    int radiuss[4] = {0, 0, 0, 0};
    for(int x=circleCenter.x;x<morphImage.cols;x++){
        radiuss[0]++;
        if(morphImage.at<uchar>(circleCenter.y, x) == 255) break;
    }
    for(int x=circleCenter.x;x>0;x--){
        radiuss[1]++;
        if(morphImage.at<uchar>(circleCenter.y, x) == 255) break;
    }
    for(int y=circleCenter.y;y<morphImage.rows;y++){
        radiuss[2]++;
        if(morphImage.at<uchar>(y, circleCenter.x) == 255) break;
    }
    for(int y=circleCenter.y;y>0;y--){
        radiuss[3]++;
        if(morphImage.at<uchar>(y, circleCenter.x) == 255) break;
    }
    int radius = INT_MAX;
    for(int i=0;i<4;i++){
        if(radius > radiuss[i]) radius = radiuss[i];

    }
    std::cout << "getting radious" << std::endl;

    cv::Mat dstImage = src.clone();
    cv::circle(dstImage, circleCenter, radius, cv::Scalar(255,255,0));
    cv::circle(dstImage, circleCenter, 2, cv::Scalar(2, 45, 120), 2);

    qDebug() << "center x:" << circleCenter.x << ", y:" << circleCenter.y << " rad:" << radius << endl;

    return dstImage;
}

void detectCircle::valueCheck()
{

}
