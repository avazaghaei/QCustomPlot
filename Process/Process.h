#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>

/*!
  Custom classes for efficient handling
 */
#include <GUI/QCustomPlot/myQCustomPlot.h>
#include <GUI/Settings/settings.h>
#include <GUI/Settings/zoomSettings.h>

class Process : public QObject
{
    Q_OBJECT
private:

    /*!
     * \brief custom class objects
     */
    myQCustomPlot* classCustomPlot;
    settings* classSettings;
    zoomSettings* classZoomSettings;


/***********************************************************/
//Functions

    /*!
     * \brief Instantiate custom class objects
     */
    void initClasses();

    /*!
     * \brief Establish object relationships and dependencies. Establish signal-slot connections between custom plot and GUI
     */
    void setConnections();
public:
    Process();
};

#endif // PROCESS_H
