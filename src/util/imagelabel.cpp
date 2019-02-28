#include "imagelabel.h"

ImageLabel::ImageLabel(QLabel *parent) : QLabel(parent)
{
}

void ImageLabel::loadImage(const cv::Mat &mat)
{
    QImage image = matToQimg(mat);

    image = image.scaled(size(), Qt::KeepAspectRatio);
    setPixmap(QPixmap::fromImage(image));
}

QImage ImageLabel::matToQimg(const cv::Mat &mat)
{
    QImage image;

    switch(mat.type())
    {
    case CV_8UC4: image = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);
                  break;
    case CV_8UC3: image = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
                  image = image.rgbSwapped();
                  break;
    case CV_8UC1: static QVector<QRgb> colorTable;
                  if(colorTable.isEmpty())
                    for(int i=0;i<256;++i) colorTable.push_back( qRgb(i,i,i) );
                  image = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
                  image.setColorTable(colorTable);
                  break;
    }

    return image;
}
