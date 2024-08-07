#include "settings.h"

settings *settings::getInstance()
{
    static settings* instance = nullptr;
    if(instance == nullptr)
        instance = new settings;
    return instance;
}

settings::settings()
{
    initClasses();
    initLabels();
    initCheckBoxes();
    initSpinBoxes();
    initRadioButtons();
    initPushButtons();
    initGroupBoxes();

    setForm();
    setConnections();
}


void settings::initClasses()
{
    classCustomize = new customize();
}

void settings::initLabels()
{
    lblYaxisPlacement = new QLabel("Y-axis Placement:");
    lblScalingMode    = new QLabel("Scaling Mode:");
    lblXaxisRange     = new QLabel("X-axis Range:");
    lblYaxisRange     = new QLabel("Y-axis Range:");
    lblDeltaX         = new QLabel("Delta X:");
    lblDeltaY         = new QLabel("Delta Y:");

    const int n = 6;
    QLabel* lstLabels[n] =
    {
        lblYaxisPlacement, lblScalingMode, lblXaxisRange, lblYaxisRange, lblDeltaX, lblDeltaY
    };


    for(int i=0; i < n; ++i)
    {
        lstLabels[i]->setFont(classCustomize->lblFont);
        lstLabels[i]->setFixedWidth(classCustomize->max_width_label);
        lstLabels[i]->setFixedHeight(classCustomize->max_height_label);
        lstLabels[i]->setSizePolicy(classCustomize->spFixed);
        lstLabels[i]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        lstLabels[i]->setStyleSheet(classCustomize->lblStylSheet);
    }
}

void settings::initCheckBoxes()
{
    chkbCustomTicks  = new QCheckBox("Custom Ticks");
    chkbEnablePointSelection   = new QCheckBox("Enable point selection mode");
    chkbReverseXaxis = new QCheckBox("Reverse x axis");

    const int n = 3;
    QCheckBox* lstChechBoxes[n] =
    {
        chkbCustomTicks, chkbEnablePointSelection, chkbReverseXaxis
    };


    for(int i=0; i < n; ++i)
    {
        lstChechBoxes[i]->setFont(classCustomize->chkbFont);
        lstChechBoxes[i]->setFixedWidth(classCustomize->max_width_checkBox);
        lstChechBoxes[i]->setFixedHeight(classCustomize->max_height_checkBox);
        lstChechBoxes[i]->setSizePolicy(classCustomize->spFixed);
        lstChechBoxes[i]->setStyleSheet(classCustomize->chkbStylSheet);
    }
}


void settings::initSpinBoxes()
{
    dsbMaximumX   = new QDoubleSpinBox;
    dsbMinimumX   = new QDoubleSpinBox;
    dsbMaximumY   = new QDoubleSpinBox;
    dsbMinimumY   = new QDoubleSpinBox;
    sbCustomTicks = new QSpinBox;
    sbWidth       = new QSpinBox;
    sbHeight      = new QSpinBox;

    const int nn = 3;
    QSpinBox* lstSpinBoxes[nn] =
    {
        sbCustomTicks, sbWidth, sbHeight};

    for(int i = 0; i < nn; ++i)
    {
        lstSpinBoxes[i]->setFont(classCustomize->sbFont);
        lstSpinBoxes[i]->setFixedWidth(classCustomize->max_width_doubleSpinBox);
        lstSpinBoxes[i]->setFixedHeight(classCustomize->max_height_doubleSpinBox);
        lstSpinBoxes[i]->setSizePolicy(classCustomize->spExpanding);
        lstSpinBoxes[i]->setAlignment(Qt::AlignLeft);
        lstSpinBoxes[i]->setStyleSheet(classCustomize->sbStylSheet);
    }

    const int n = 4;
    QDoubleSpinBox* lstDoubleSpinBoxes[n] =
    {
        dsbMaximumX, dsbMinimumX, dsbMaximumY, dsbMinimumY
    };

    for(int i = 0; i < n; ++i)
    {
        lstDoubleSpinBoxes[i]->setFont(classCustomize->sbFont);
        lstDoubleSpinBoxes[i]->setFixedWidth(classCustomize->max_width_doubleSpinBox);
        lstDoubleSpinBoxes[i]->setFixedHeight(classCustomize->max_height_doubleSpinBox);
        lstDoubleSpinBoxes[i]->setSizePolicy(classCustomize->spExpanding);
        lstDoubleSpinBoxes[i]->setAlignment(Qt::AlignLeft);
        lstDoubleSpinBoxes[i]->setStyleSheet(classCustomize->sbStylSheet);
    }

    dsbMinimumX->setRange(0, 10000);
    dsbMaximumX->setRange(0, 10000);

    dsbMinimumY->setRange(0, 10000);
    dsbMaximumY->setRange(0, 10000);

    dsbMinimumX->setDisabled(true);
    dsbMaximumX->setDisabled(true);
    dsbMinimumY->setDisabled(true);
    dsbMaximumY->setDisabled(true);
}

void settings::initRadioButtons()
{
    rdBtnLeftAxis    = new QRadioButton("Left");
    rdBtnRightAxis   = new QRadioButton("Right");
    rdBtnAutoScale   = new QRadioButton("Auto Scale");
    rdBtnCustomScale = new QRadioButton("Custom Scale");

    QButtonGroup *rdBtnGroupPlacement = new QButtonGroup();
    QButtonGroup *rdBtnGroupScale     = new QButtonGroup();

    rdBtnGroupPlacement->addButton(rdBtnLeftAxis);
    rdBtnGroupPlacement->addButton(rdBtnRightAxis);

    rdBtnGroupScale->addButton(rdBtnAutoScale);
    rdBtnGroupScale->addButton(rdBtnCustomScale);

    const int n = 4;
    QRadioButton* lstRadioButtons[n] = {rdBtnLeftAxis, rdBtnRightAxis, rdBtnAutoScale, rdBtnCustomScale};


    for(int i=0; i < n; ++i)
    {
        lstRadioButtons[i]->setFont(classCustomize->rdbtnFont);
        lstRadioButtons[i]->setFixedWidth(classCustomize->max_width_radioButton);
        lstRadioButtons[i]->setFixedHeight(classCustomize->max_height_radioButton);
        lstRadioButtons[i]->setSizePolicy(classCustomize->spExpanding);
        lstRadioButtons[i]->setStyleSheet(classCustomize->rdbtnStylSheet);
    }

    rdBtnAutoScale->setChecked(true);
    rdBtnLeftAxis->setChecked(true);
}

void settings::initPushButtons()
{
    btnSavePlotImage = new QPushButton("Save Plot Image");

    btnSavePlotImage->setFont(classCustomize->btnFont);
    btnSavePlotImage->setFixedWidth(classCustomize->max_width_pushButton);
    btnSavePlotImage->setFixedHeight(classCustomize->max_height_pushButton);
    btnSavePlotImage->setSizePolicy(classCustomize->spExpanding);
    btnSavePlotImage->setStyleSheet(classCustomize->btnStylSheet);
}

void settings::initGroupBoxes()
{
    grbForm = new QGroupBox();

    grbForm->setTitle("Settinhgs");
    grbForm->setFixedWidth(classCustomize->max_width_groupBox);
    grbForm->setFixedHeight(classCustomize->max_height_groupBox * .8);
    grbForm->setStyleSheet(classCustomize->grbtnStylSheet);
    grbForm->setSizePolicy(classCustomize->spFixed);
}

void settings::setForm()
{
    QGridLayout* grl = new QGridLayout();

    grl = new QGridLayout();
    grl->addWidget(lblYaxisPlacement , 0, 0);
    grl->addWidget(rdBtnLeftAxis     , 0, 1);
    grl->addWidget(rdBtnRightAxis    , 0, 2);

    grl->addWidget(lblScalingMode    , 1, 0);
    grl->addWidget(rdBtnAutoScale    , 1, 1);
    grl->addWidget(rdBtnCustomScale  , 1, 2);

    grl->addWidget(lblXaxisRange     , 2, 0);
    grl->addWidget(dsbMinimumX       , 2, 1);
    grl->addWidget(dsbMaximumX       , 2, 2);

    grl->addWidget(lblYaxisRange     , 3, 0);
    grl->addWidget(dsbMinimumY       , 3, 1);
    grl->addWidget(dsbMaximumY       , 3, 2);

    grl->addWidget(chkbCustomTicks   , 4, 0);
    grl->addWidget(sbCustomTicks     , 4, 1);

    grl->addWidget(chkbEnablePointSelection    , 5, 0);
    grl->addWidget(lblDeltaX         , 5, 1);
    grl->addWidget(lblDeltaY         , 5, 2);

    grl->addWidget(chkbReverseXaxis  , 6, 0);

    grl->addWidget(btnSavePlotImage  , 7, 0);
    grl->addWidget(sbWidth           , 7, 1);
    grl->addWidget(sbHeight          , 7, 2);

    grbForm->setLayout(grl);

}

void settings::setConnections()
{
    {
        connect(rdBtnRightAxis, &QRadioButton::clicked, this, &settings::signalRightYAxis);
        connect(rdBtnLeftAxis,  &QRadioButton::clicked, this, &settings::signalLeftYAxis);
    }
    {
        connect(rdBtnCustomScale , &QRadioButton::clicked, this, &settings::slotRadioButtonCustomScale);
        connect(rdBtnAutoScale,    &QRadioButton::clicked, this, &settings::slotRadioButtonAutoScale);

        connect(dsbMinimumX, SIGNAL(valueChanged(double)), this, SLOT(slotSpinBox()));
        connect(dsbMaximumX, SIGNAL(valueChanged(double)), this, SLOT(slotSpinBox()));
        connect(dsbMinimumY, SIGNAL(valueChanged(double)), this, SLOT(slotSpinBox()));
        connect(dsbMaximumY, SIGNAL(valueChanged(double)), this, SLOT(slotSpinBox()));
    }
    {
        //custom Ticks
        connect(chkbCustomTicks   , &QCheckBox::clicked,       this, &settings::slotSetTicks);
        connect(sbCustomTicks     , SIGNAL(valueChanged(int)), this, SLOT(slotSetTicks()));
    }
    {
        //save Image
        connect(btnSavePlotImage   , &QCheckBox::clicked, this, &settings::slotSavePlotImage);
    }
    {
        //reverse x-axis
        connect(chkbReverseXaxis   , &QCheckBox::clicked, this, &settings::slotReverseXAxis);
    }
    {
        //Enable point selection mode
        connect(chkbEnablePointSelection   , &QCheckBox::clicked, this, &settings::signalEnablePointSelection);
    }
}

void settings::slotRadioButtonCustomScale()
{
    dsbMinimumX->setDisabled(false);
    dsbMaximumX->setDisabled(false);
    dsbMinimumY->setDisabled(false);
    dsbMaximumY->setDisabled(false);
}

void settings::slotSpinBox()
{
    double minX = dsbMinimumX->value();
    double maxX = dsbMaximumX->value();
    double minY = dsbMinimumY->value();
    double maxY = dsbMaximumY->value();

    emit signalSpinBox(minX, maxX, minY, maxY);
}

void settings::slotRadioButtonAutoScale()
{
    dsbMinimumX->setDisabled(true);
    dsbMaximumX->setDisabled(true);
    dsbMinimumY->setDisabled(true);
    dsbMaximumY->setDisabled(true);

    emit signalRadioButtonAutoScale();
}

void settings::slotSetTicks()
{
    if(chkbCustomTicks->isChecked())
    {

        signalSetTicks(sbCustomTicks->value());
    }
    else
    {
        signalSetTicks(0);
    }
}

void settings::slotSavePlotImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "/home/jana/untitled.png",
                                tr("Images (*.png *.xpm *.jpg)"));


    int width  = sbWidth->value();
    int height = sbHeight->value();
    signalSavePloImage(fileName, width, height, 1.0, -1);
}

void settings::slotReverseXAxis()
{
    if(chkbReverseXaxis->isChecked())
    {
        signalReverseXAxis(true);
    }
    else
    {
        signalReverseXAxis(false);
    }
}

void settings::slotSetValueDelta(double x, double y)
{
    lblDeltaX->setText("Delta X : " + QString::number(x));
    lblDeltaY->setText("Delta Y : " + QString::number(y));
}

void settings::slotReverseXAxisMenuRequest()
{
    chkbReverseXaxis->setChecked(!chkbReverseXaxis->isChecked());
    chkbReverseXaxis->clicked();
}

void settings::slotAddedPoint()
{
    if(rdBtnAutoScale->isChecked())
    {
        rdBtnAutoScale->clicked();
    }
}

