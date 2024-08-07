#ifndef SETTINGS_H
#define SETTINGS_H

/*!
  Core libraries that are needed
 */
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


/*!
  Custom classes for efficient handling
 */
#include <GUI/Size/customize.h>

class settings : public QWidget
{
    Q_OBJECT
private:
/***********************************************************/
//Variables

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
    QCheckBox* chkbEnablePointSelection;

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
/***********************************************************/
//Functions

    /*!
     * \brief Instantiate custom class objects
     */
    void initClasses();


    /*!
     * \brief Instantiate custom labels
     */
    void initLabels();

    /*!
     * \brief Instantiate custom check boxes
     */
    void initCheckBoxes();

    /*!
     * \brief Instantiate custom spin boxes
     */
    void initSpinBoxes();

    /*!
     * \brief Instantiate custom redio buttons
     */
    void initRadioButtons();

    /*!
     * \brief Instantiate custom push buttons
     */
    void initPushButtons();

    /*!
     * \brief Instantiate custom group boxes
     */
    void initGroupBoxes();

    /*!
     * \brief Configure complete form layout and components
     */
    void setForm();

    /*!
     * \brief Establish object relationships and dependencies
     */
    void setConnections();

public:
//GUI Elements

    /*!
     * \brief Expose object for external configuration
     */
    QGroupBox* grbForm;

    /*!
     * \brief Singleton is a creational design pattern that lets you ensure that a class has only one instance, while providing a global access point to this instance.
     * Enforce single instance and global access point
     * \return
     */
    static settings* getInstance();


    settings();


signals:

    /*!
     * \brief Signal for x-axis replacement update
     */
    void signalLeftYAxis();
    void signalRightYAxis();

    /*!
     * \brief Signal for custom plot autoscaling
     */
    void signalRadioButtonAutoScale();

    /*!
     * \brief Apply custom scaling on plot activation
     * \param minX
     * \param maxX
     * \param minY
     * \param maxY
     */
    void signalSpinBox(double minX, double maxX, double minY, double maxY);

    /*!
     * \brief signal User-defined x-axis tick intervals
     * \param ticks
     */
    void signalSetTicks(int ticks);

    /*!
     * \brief signal Export plot as image file
     * \param fileName
     * \param width
     * \param height
     * \param scale
     * \param quality
     */
    void signalSavePloImage(QString fileName, int width, int height, double scale, int quality);

    /*!
     * \brief signal Invert x-axis direction
     * \param status
     */
    void signalReverseXAxis(bool status);

    /*!
     * \brief Signal for enabling point selection
     * \param status
     */
    void signalEnablePointSelection(bool status);


private slots:
//Internal class-specific slot implementations

    /*!
     * \brief Slot for determining plot scale from input data
     */
    void slotRadioButtonCustomScale();

    /*!
     * \brief Slot for dynamic plot scale adjustment based on data
     */
    void slotSpinBox();

    void slotRadioButtonAutoScale();

    void slotSetTicks();

    void slotSavePlotImage();

    void slotReverseXAxis();


public slots:
//Internal slots for handling QCustomPlot-specific events
    /*!
     * \brief Handle point selection, calculate difference, and emit result
     * \param x
     * \param y
     */
    void slotSetValueDelta(double x, double y);

    /*!
     * \brief Handle x-axis replacement menu request


     */
    void slotReverseXAxisMenuRequest();

    /*!
     * \brief Monitor random data generation for dynamic GUI scaling
     */
    void slotAddedPoint();


};

#endif // SETTINGS_H
