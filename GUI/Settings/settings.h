#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <QTextStream>


#include <GUI/Size/customize.h>
class settings : public QWidget
{
    Q_OBJECT
private:

    //Classes
    customize* classCustomize;

    //GUI Elements

    //Labels
    QLabel* lblYaxisPlacement;
    QLabel* lblScalingMode;
    QLabel* lblXaxisRange;
    QLabel* lblYaxisRange;
    QLabel* lblDeltaX;
    QLabel* lblDeltaY;

    //check boxes
    QCheckBox* chkbCustomTicks;
    QCheckBox* chkbReverseXaxis;
    QCheckBox* chkbFixDisplay;

    //spin boxes
    QDoubleSpinBox* dsbMaximumX;
    QDoubleSpinBox* dsbMinimumX;
    QDoubleSpinBox* dsbMaximumY;
    QDoubleSpinBox* dsbMinimumY;
    QSpinBox* sbWidth;
    QSpinBox* sbHeight;
    QSpinBox* sbCustomTicks;

    //radio buttons
    QRadioButton* rdBtnLeftAxis;
    QRadioButton* rdBtnRightAxis;
    QRadioButton* rdBtnAutoScale;
    QRadioButton* rdBtnCustomScale;

    //push buttons
    QPushButton* btnSavePlotImage;






    //functions
    void init_classes();
    void init_labels();
    void init_checkBoxes();
    void init_spinBoxes();
    void init_radioButtons();
    void init_pushButtons();
    void init_groupBoxes();
    void set_form();

    void set_connections();

public:
    //GUI Elements
    //group box
    QGroupBox* grbForm;

    static settings* getInstance();
    settings();


signals:
    void signalLeftYAxis();
    void signalRightYAxis();

    void signalSpinBox(double minX, double maxX, double minY, double maxY);

    void signalRadioButtonAutoScale();

    void signalSetTicks(int ticks);

    void signalSavePloImage(QString fileName, int width, int height, double scale, int quality);

    void signalReverseXAxis(bool status);

    void signalFixDisplay(bool status);


private slots:
    void slotRadioButtonCustomScale();
    void slotSpinBox();

    void slotRadioButtonAutoScale();

    void slotSetTicks();

    void slotSavePlotImage();

    void slotReverseXAxis();


public slots:
    void slotSetValueDelta(double x, double y);
    void slotReverseXAxisMenuRequest();


};

#endif // SETTINGS_H
