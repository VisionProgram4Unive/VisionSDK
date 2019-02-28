#include "imagedialog.h"
#include "ui_imagedialog.h"

ImageDialog::ImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);
    ui->label->resize(this->size());
}

ImageDialog::~ImageDialog()
{
    delete ui;
}

void ImageDialog::setImage(const cv::Mat &src)
{
    ui->label->setPixmap( cvMat2Qpixmap(src) );
}

void ImageDialog::resizeEvent(QResizeEvent *)
{
    ui->label->resize(this->size());

    QSize size = this->size();
    if( size.height() > image.size().height() || size.width() > image.size().width() )
    {
        size = image.size();
        ui->label->resize(size);
    }
    ui->label->setPixmap( QPixmap::fromImage(image).scaled(size,
                                                    Qt::KeepAspectRatio) );
}

QPixmap ImageDialog::cvMat2Qpixmap(const cv::Mat &mat)
{
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

    return QPixmap::fromImage(image).scaled(this->size(), Qt::KeepAspectRatio);
}
