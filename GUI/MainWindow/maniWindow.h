#ifndef MANIWINDOW_H
#define MANIWINDOW_H

#include <QWidget>
#include <QGridLayout>


#include <GUI/QCustomPlot/myQCustomPlot.h>
#include <GUI/Settings/settings.h>
#include <GUI/Settings/zoomSettings.h>

class maniWindow : public QWidget
{
private:

    //Classes
    myQCustomPlot* classCustomPlot;
    settings* classSettings;
    zoomSettings* classZoomSettings;



    //functions
    void init_classes();
    void set_ftom();


public:
    maniWindow(QWidget *parent = nullptr);
};

#endif // MANIWINDOW_H
