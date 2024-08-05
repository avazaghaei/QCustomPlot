#ifndef ZOOMSETTINGS_H
#define ZOOMSETTINGS_H

#include <QObject>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>

#include <GUI/Size/customize.h>
class zoomSettings : public QObject
{
    Q_OBJECT
private:

    //Classes
    customize* classCustomize;

    //GUI Elements

    //push buttons
    QPushButton* btnZoomIn;
    QPushButton* btnZoomOut;
    QPushButton* btnResetZoom;
    QPushButton* btnAreaSelection;

    //spacer
    QSpacerItem* spacerZoomSettings;



    //functions
    void init_classes();
    void init_pushButtons();
    void init_groupBoxes();
    void init_spacer();
    void set_form();

    void set_connections();

public:
    //GUI Elements
    //group box
    QGroupBox* grbForm;

    static zoomSettings* getInstance();
    zoomSettings();

signals:
    void signalZoomIn();
    void signalZoomOut();
    void signalAreaSelection();
    void signalResetZoom();
};

#endif // ZOOMSETTINGS_H
