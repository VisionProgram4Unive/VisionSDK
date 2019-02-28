#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QDialog>
#include <QDebug>
#include <opencv2/opencv.hpp>

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageDialog(QWidget *parent = 0);
    ~ImageDialog();

public slots:
    void setImage(const cv::Mat & src);

protected:
    void resizeEvent(QResizeEvent *);

private:
    QPixmap cvMat2Qpixmap(const cv::Mat & mat);

    Ui::ImageDialog *ui;
    QImage image;
};

#endif // IMAGEDIALOG_H
