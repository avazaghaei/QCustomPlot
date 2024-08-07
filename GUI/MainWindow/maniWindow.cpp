#include "maniWindow.h"


maniWindow::maniWindow(QWidget *parent) : QWidget(parent)
{
    init_classes();
    set_ftom();
}

void maniWindow::init_classes()
{
    ClassCustomPlot   = myQCustomPlot::getInstance();
    ClassSettings     = settings::getInstance();
    ClassZoomSettings = zoomSettings::getInstance();
}

void maniWindow::set_ftom()
{
    QGridLayout* grl = new QGridLayout();

    grl->addWidget(ClassCustomPlot->ClassCustomPlot, 0, 0, 2, 1);
    grl->addWidget(ClassSettings->grbForm, 0, 1);
    grl->addWidget(ClassZoomSettings->grbForm, 1, 1);

    this->setLayout(grl);

}
