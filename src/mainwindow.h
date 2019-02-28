#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <opencv2/opencv.hpp>

#include "util/imagedialog.h"
#include "queuethread.h"

#include "algorithm/abstructalgorithm.h"
#include "algorithm/bilateralfilter.h"
#include "algorithm/cannyedge.h"
#include "algorithm/contrast.h"
#include "algorithm/contrast.h"
#include "algorithm/gaussianblur.h"
#include "algorithm/histogramcalc.h"
#include "algorithm/histogrameq.h"
#include "algorithm/medianblur.h"
#include "algorithm/normalblur.h"
#include "algorithm/sharpen.h"
#include "algorithm/sobeledge.h"
#include "algorithm/threshold.h"
#include "algorithm/houghcircle.h"
#include "algorithm/detectcircle.h"

/* platform dependency code */
#ifdef __gnu_linux__
#elif _WIN32
#endif
/* platform dependency code */
#include "IO/inputthread.h"
#include "IO/resolutiondlg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QueueThread *thread_queue;
    InputThread *thread_input;
    ImageDialog *result;
    ResolutionDlg *resol_dlg;

    void fileOpen();
    void camOpen();

    void createWidget(const QString &name);

private slots:
    //read data method
    void readImage();
    void updateViewer(QImage image);

    void on_algorithmWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_queueListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_queueListWidget_itemClicked(QListWidgetItem *item);
    void on_runButton_toggled(bool checked);

signals:
    void getImage(cv::Mat Mat);
//    void updateMData(cv::Mat mat);
};

#endif // MAINWINDOW_H
