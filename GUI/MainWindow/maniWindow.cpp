#include "maniWindow.h"


maniWindow::maniWindow(QWidget *parent) : QWidget(parent)
{
    init_classes();
    set_ftom();
}

void maniWindow::init_classes()
{
    classCustomPlot   = myQCustomPlot::getInstance();
    classSettings     = settings::getInstance();
    classZoomSettings = zoomSettings::getInstance();
}

void maniWindow::set_ftom()
{
    QGridLayout* grl = new QGridLayout();

    grl->addWidget(classCustomPlot->ClassCustomPlot, 0, 0, 2, 1);
    grl->addWidget(classSettings->grbForm, 0, 1);
    grl->addWidget(classZoomSettings->grbForm, 1, 1);

    this->setLayout(grl);

}
