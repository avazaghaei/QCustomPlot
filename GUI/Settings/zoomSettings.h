#ifndef ZOOMSETTINGS_H
#define ZOOMSETTINGS_H

/*!
  Core libraries that are needed
 */
#include <QObject>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>

/*!
  Custom classes for efficient handling
 */
#include <GUI/Size/customize.h>

class zoomSettings : public QObject
{
    Q_OBJECT
private:
//Variables

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

/***********************************************************/
//Functions

    /*!
     * \brief Instantiate custom class objects
     */
    void initClasses();

    /*!
     * \brief Instantiate custom push buttons
     */
    void initPushButtons();

    /*!
     * \brief Instantiate custom group boxes
     */
    void initGroupBoxes();

    /*!
     * \brief Instantiate custom spacer
     */
    void initSpacer();

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
    static zoomSettings* getInstance();


    zoomSettings();

signals:
    /*!
     * \brief Enable plot magnification
     */
    void signalZoomIn();

    /*!
     * \brief Enable plot reduction
     */
    void signalZoomOut();

    /*!
     * \brief Interactive plot area selection
     */
    void signalAreaSelection();

    /*!
     * \brief Interactive plot area selection
     */
    void signalResetZoom();
};

#endif // ZOOMSETTINGS_H
