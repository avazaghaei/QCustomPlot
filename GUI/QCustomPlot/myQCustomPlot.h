/***********************************************************
 * @author: Mohammadreza Avazaghaei <avazaghaei2yahoo.com> *
 * @github: @avazaghaei                                    *
 * @license: MIT                                           *
 ***********************************************************/
#ifndef MYQCUSTOMPLOT_H
#define MYQCUSTOMPLOT_H

/*!
  Core libraries that are needed
 */
#include <QWidget>
#include <QMenu>
#include <fstream> //export to excell
#include "qaxobject.h" //read from excel

/*!
  Custom classes for efficient handling
 */
#include <Library/QCustomPlot/qcustomplot.h>
#include <GUI/Size/customize.h>
#include <Process/Encryption/simplecrypt.h>

class myQCustomPlot : public QWidget
{
    Q_OBJECT
private:
//Variables
    /*!
     * \brief custom class objects
     */
    customize*   ClassCustomize;
    QCustomPlot* ClassNewWindowCustomPlot;

    /*!
     * \brief Point selection interaction handler
     */
    QCPItemTracer *phaseTracer;

    /*!
     * \brief Introduce a delay (e.g., 3 seconds)
     */
    int millisecond = 3000;

    /*!
     Calculate the difference between two points on a plot
    */
    double firstX    = 0;
    double firstY    = 0;
    double secondX   = 0;
    double secondY   = 0;
    int deltaCounter = 0;

    //
    /*!
     * \brief Array of double values to store plot coordinates
     */
    QVector<double> qVectorX;
    QVector<double> qVectorY;
/***********************************************************/
//Functions

    /*!
     * \brief Instantiate custom class objects
     */
    void initClass();

    /*!
     * \brief Instantiate QCustopmPlot class objects
     */
    void initQCustomPlot();


    /*!
     * \brief Trigger replot and update after changes to QCustomPlot
     */
    void plot();

    /*!
     * \brief Obtain x and y coordinates for new plot point
     * \param x for horizontal position
     * \param y for vertical position
     */
    void addPoint(double x, double y);

    /*!
     * \brief Initialize and start timer for periodic random data generation
    */
    void initTimer();


    void setContextMenu();

public:
//Variables
    /*!
     * \brief QCustomPlot class objects
     */
    QCustomPlot* ClassCustomPlot;
/***********************************************************/
//Functions
    /*!
     * \brief Singleton is a creational design pattern that lets you ensure that a class has only one instance, while providing a global access point to this instance.
     * Enforce single instance and global access point
     * \return
     */
    static myQCustomPlot* getInstance();


    myQCustomPlot();

public slots:
/***********************************************************/
//Slot Functions
//These are public for external signal connections
    /*!
     * \brief Generate random data point for plot update
     */
    void slotGenerateRandomNumber();

    /*!
     * \brief Position Y-axis on the right side of the plot area
     */
    void slotRightYAxis();

    /*!
     * \brief Position Y-axis on the Left side of the plot area
     */
    void slotLeftYAxis();

    /*!
     * \brief Custom scaling applied to plot axes
     * \param minX
     * \param maxX
     * \param minY
     * \param maxY
     */
    void slotCustomScale(double minX, double maxX, double minY, double maxY);

    /*!
     * \brief Dynamic axis scaling for full data visibility
     */
    void slotAutoScale();

    /*!
     * \brief User-defined x-axis tick intervals
     * \param ticks
     */
    void slotSetTicks(int ticks);

    /*!
     * \brief Export plot as image file
     * \param fileName
     * \param width
     * \param height
     * \param scale
     * \param quality
     */
    void slotSavePlotImage(QString fileName, int width, int height, double scale, int quality);

    /*!
     * \brief Invert x-axis direction
     * \param status
     */
    void slotReverseXAxis(bool status);

    /*!
     * \brief Optimized plot scaling for precise point selection
     * \param status
     */
    void slotFixDisplay(bool status);

    /*!
     * \brief Enable plot magnification
     */
    void slotZoomIn();

    /*!
     * \brief Enable plot reduction
     */
    void slotZoomOut();

    /*!
     * \brief Interactive plot area selection
     */
    void slotAreaSelection();

    /*!
     * \brief Display context-sensitive menu options
     * \param event
     */
    void clickedGraph(QMouseEvent *event);

private slots:
/***********************************************************/
//Slot Functions
//These are private for internal signal connections
    /*!
     * \brief Display context-sensitive menu options
     * \param event
     */
    void contextMenuRequest(QPoint pos);

    /*!
     * \brief Invert x-axis direction
     * \param status
     */
    void menuReverseXAxis();

    /*!
     * \brief Write plot data to Excel format
     */
    void exportPlotToExcel();

    /*!
     * \brief Read data from Excel file for plot
     */
    void importExcelToPlot();

    /*!
     * \brief Maximize plot window and freeze data input
     */
    void showFullWindow();

signals:
/***********************************************************/
//Slot Functions
//These are public for external slot connections
    /*!
     * \brief Emit calculated point difference to GUI
     * \param x
     * \param y
     */
    void signalSetValueDelta(double x, double y);

    /*!
     * \brief Context menu option to trigger x-axis inversion and GUI update
     */
    void signalReverseXAxis();
};

#endif // MYQCUSTOMPLOT_H
