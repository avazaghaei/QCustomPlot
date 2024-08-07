#include "zoomSettings.h"

zoomSettings *zoomSettings::getInstance()
{
    static zoomSettings* instance = nullptr;
    if(instance == nullptr)
        instance = new zoomSettings;
    return instance;
}

zoomSettings::zoomSettings()
{
    initClasses();
    initPushButtons();
    initGroupBoxes();
    initSpacer();
    setForm();

    setConnections();
}

void zoomSettings::initClasses()
{
    classCustomize = new customize();
}

void zoomSettings::initPushButtons()
{
    btnZoomIn        = new QPushButton("Zoom In");
    btnZoomOut       = new QPushButton("Zoom Out");
    btnResetZoom     = new QPushButton("Reset Zoom");
    btnAreaSelection = new QPushButton("Area Selection");


    const int n = 4;
    QPushButton* lstButtons [n] =
    {
        btnZoomIn, btnZoomOut, btnResetZoom, btnAreaSelection
    };
    for(int i = 0; i < n; ++i)
    {
        lstButtons[i]->setFont(classCustomize->btnFont);
        lstButtons[i]->setFixedWidth(classCustomize->max_width_pushButton);
        lstButtons[i]->setFixedHeight(classCustomize->max_height_pushButton);
        lstButtons[i]->setSizePolicy(classCustomize->spExpanding);
        lstButtons[i]->setStyleSheet(classCustomize->btnStylSheet);
    }
}

void zoomSettings::initGroupBoxes()
{
    grbForm = new QGroupBox();
    grbForm->setTitle("Zoom Settinhgs");
    grbForm->setFixedWidth(classCustomize->max_width_groupBox );
    grbForm->setFixedHeight(classCustomize->max_height_groupBox * .2);
    grbForm->setStyleSheet(classCustomize->grbtnStylSheet);
    grbForm->setSizePolicy(classCustomize->spFixed);
}

void zoomSettings::initSpacer()
{
    spacerZoomSettings = new QSpacerItem(40, 130, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void zoomSettings::setForm()
{
    QGridLayout* grl = new QGridLayout();

    grl->addItem(spacerZoomSettings, 0, 0);

    grl->addWidget(btnZoomIn       , 1, 0);
    grl->addWidget(btnResetZoom    , 1, 1);

    grl->addWidget(btnZoomOut      , 2, 0);
    grl->addWidget(btnAreaSelection, 2, 1);

    grbForm->setLayout(grl);
}

void zoomSettings::setConnections()
{
    connect(btnZoomIn,        &QPushButton::clicked, this, &zoomSettings::signalZoomIn);
    connect(btnZoomOut,       &QPushButton::clicked, this, &zoomSettings::signalZoomOut);
    connect(btnAreaSelection, &QPushButton::clicked, this, &zoomSettings::signalAreaSelection);
    connect(btnResetZoom,     &QPushButton::clicked, this, &zoomSettings::signalResetZoom);
}
