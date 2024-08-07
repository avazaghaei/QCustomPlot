#ifndef MANIWINDOW_H
#define MANIWINDOW_H

#include <QWidget>
/*!
  Core libraries that are needed
 */
#include <QGridLayout>

/*!
  Custom classes for efficient handling
 */
#include <GUI/QCustomPlot/myQCustomPlot.h>
#include <GUI/Settings/settings.h>
#include <GUI/Settings/zoomSettings.h>
#include <GUI/Size/customize.h>

class maniWindow : public QWidget
{
private:
    customize* classCustomize;
    //Classes
    myQCustomPlot* ClassCustomPlot;
    settings*      ClassSettings;
    zoomSettings*  ClassZoomSettings;

    //functions
    void init_classes();
    void set_ftom();


public:
    maniWindow(QWidget *parent = nullptr);
};

#endif // MANIWINDOW_H
