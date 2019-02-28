#include "resolutiondlg.h"
#include "ui_resolutiondlg.h"

ResolutionDlg::ResolutionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResolutionDlg)
{
    ui->setupUi(this);

    connect(this->ui->pushButton, SIGNAL( clicked(bool) ),
            this, SLOT( select() ));
}

ResolutionDlg::~ResolutionDlg()
{
    delete ui;
}

void ResolutionDlg::setResolutionList(std::vector<Resolution> list)
{
    //remove before data
    ui->comboBox->clear();

    std::for_each(list.begin(), list.end(), [&](Resolution resolution)
    {
        this->ui->comboBox->addItem
                (QString::number(resolution.getWidth())+"*"+QString::number(resolution.getHeight()));
    });

    this->show();
}

void ResolutionDlg::select()
{
    qDebug() << "Throw index : " << ui->comboBox->currentIndex() << endl;
    emit selectResolution( ui->comboBox->currentIndex() );
    this->hide();
}
