#include "abstructalgorithm.h"

AbstructAlgorithm::AbstructAlgorithm(QWidget *parent) : QWidget(parent)
{
    dialog = new ImageDialog(this);
}
AbstructAlgorithm::~AbstructAlgorithm()
{
    delete dialog;
}
