#ifndef RESOLUTIONDLG_H
#define RESOLUTIONDLG_H

#include <QDialog>
#include <QDebug>

/* platform dependency code */
#ifdef __gnu_linux__
    #include "v4l2capture.h"
#elif _WIN32
#endif
/* platform dependency code */

namespace Ui {
class ResolutionDlg;
}

class ResolutionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ResolutionDlg(QWidget *parent = 0);
    ~ResolutionDlg();

public slots:
    void setResolutionList(std::vector<Resolution> list);

signals:
    void selectResolution(int index);

private:
    Ui::ResolutionDlg *ui;

private slots:
    void select();

};

#endif // RESOLUTIONDLG_H
