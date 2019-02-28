#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    thread_input = new InputThread();
    thread_input->start();
    connect(thread_input, SIGNAL(updateQData(QImage)),
            this, 		  SLOT(updateViewer(QImage)));

    thread_queue = new QueueThread();
    thread_queue->start();
    connect(thread_input, SIGNAL(updateMData(cv::Mat)),
            thread_queue, SLOT(setProcImage(cv::Mat)));

    result = new ImageDialog(this);
    result->setWindowTitle("Result");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    connect(thread_queue, SIGNAL(updateProc(cv::Mat)),
            result, 	  SLOT(setImage(cv::Mat)));

    /*
     * comment : basically, thread doesn't have a GUI component, except MainThread.
     *			 so, i implement this :(.
     */
    resol_dlg = new ResolutionDlg(this);
    resol_dlg->hide();
    connect(thread_input, SIGNAL( updateResolutionData(std::vector<Resolution>) ),
            resol_dlg,    SLOT( setResolutionList(std::vector<Resolution>) ));
    connect(resol_dlg,    SIGNAL( selectResolution(int) ),
            thread_input, SLOT( setCamera(int) ));

    connect(this->ui->openButton, SIGNAL(clicked(bool)), this, SLOT(readImage()));
}

MainWindow::~MainWindow()
{
    delete thread_queue;
    delete thread_input;
    delete ui;
    result->hide();
    delete result;
}

void MainWindow::readImage()
{
   if(this->ui->fileRadio->isChecked()){
       fileOpen();
   }
   if(this->ui->camRadio->isChecked()){
       camOpen();
   }
}

void MainWindow::updateViewer(QImage image)
{
    ui->roiButton->setIcon(QPixmap::fromImage(image));
//    result->resize( image.width(), image.height() );
}

void MainWindow::createWidget(const QString &name)
{
    AbstructAlgorithm *n_widget;

    if( name == "Normal Bluring")
        n_widget = new NormalBlur(ui->paramWidget);
    else if( name == "Gaussian Bluring")
        n_widget = new GaussianBlur(ui->paramWidget);
    else if( name == "Median Bluring")
        n_widget = new MedianBlur(ui->paramWidget);
    else if( name == "Bilateral Filtering")
        n_widget = new BilateralFilter(ui->paramWidget);
    else if( name == "Histogram Calculation")
        n_widget = new HistogramCalc(ui->paramWidget);
    else if( name == "Contrast")
        n_widget = new Contrast(ui->paramWidget);
    else if( name == "Histogram Equalization")
        n_widget = new HistogramEq(ui->paramWidget);
    else if( name == "Sharpen")
        n_widget = new Sharpen(ui->paramWidget);
    else if( name == "Threshold")
        n_widget = new Threshold(ui->paramWidget);
    else if( name == "CannyEdge")
        n_widget = new CannyEdge(ui->paramWidget);
    else if( name == "SobelEdge")
        n_widget = new SobelEdge(ui->paramWidget);
    else if( name == "HoughCircle")
        n_widget = new HoughCircle(ui->paramWidget);
    else if( name == "findCircle")
        n_widget = new detectCircle(ui->paramWidget);

    connect(n_widget, SIGNAL(valueChanged()), thread_queue, SLOT(wakeup()));

    n_widget->hide();
    thread_queue->append(n_widget);
}

void MainWindow::fileOpen()
{
    const QStringList picLocation = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QString selectFilter;
    QString fileName =
            QFileDialog::getOpenFileName (this, tr("Open Image File"),
                                 picLocation.first(),
                                 tr("Image Files (*.jpg *.bmp *.png *.ppm *.pgm);;\
                                     Video Files (*.avi)"),
                                 &selectFilter);

    //err processing
    if(fileName.isEmpty())
        QMessageBox::information
                (this, QGuiApplication::applicationDisplayName(),
                 tr("Can't load %1").arg(QDir::toNativeSeparators(fileName)));

    thread_input->getData(fileName.toStdString());
}

void MainWindow::camOpen()
{
    //TODO : camera dialog
    thread_input->openCamera(0);

    //if resolution is already setted disconnect slot
}

void MainWindow::on_algorithmWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QString itemName = item->text(column);
    QStringList egnore_item;
    egnore_item << "Smoothing" << "Transform" << "Histogram" << "Edge Filter" << "3D Reconstruction";

    for(int i=0;i<egnore_item.size();++i)
        if(egnore_item.at(i) == itemName) return;
    ui->queueListWidget->addItem(itemName);

    createWidget(itemName);
}

void MainWindow::on_queueListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int itemRow = item->listWidget()->row(item);
    thread_queue->remove(itemRow);
    delete item;
}

void MainWindow::on_queueListWidget_itemClicked(QListWidgetItem *item)
{
    int itemRow = item->listWidget()->row(item);
    for(int i=0;i<thread_queue->size();i++){
        thread_queue->hide(i);
    }
    thread_queue->show(itemRow);
}

void MainWindow::on_runButton_toggled(bool checked)
{
    if(thread_queue->size() <= 0){
        ui->runButton->setChecked(false);
        return;
    }

    if(checked){
        ui->runButton->setText("STOP");
        thread_queue->wakeBtn();
        result->show();
    }else{
        ui->runButton->setText("RUN");
        thread_queue->waitBtn();
        result->hide();
    }
}
