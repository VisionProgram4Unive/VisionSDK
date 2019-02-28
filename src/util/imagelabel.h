#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QDebug>
#include <opencv2/opencv.hpp>

class ImageLabel : public QLabel
{
public:
    ImageLabel(QLabel *parent = 0);

    void loadImage(const cv::Mat &);
    QImage matToQimg(const cv::Mat &mat);
private:
};

#endif // IMAGELABEL_H
