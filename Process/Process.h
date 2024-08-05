#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>

#include <GUI/QCustomPlot/myQCustomPlot.h>
#include <GUI/Settings/settings.h>
#include <GUI/Settings/zoomSettings.h>

class Process : public QObject
{
    Q_OBJECT
private:
    //classes:
    myQCustomPlot* classCustomPlot;
    settings* classSettings;
    zoomSettings* classZoomSettings;


    //function
    void init_classes();
    void set_connections();
public:
    Process();
};

#endif // PROCESS_H
