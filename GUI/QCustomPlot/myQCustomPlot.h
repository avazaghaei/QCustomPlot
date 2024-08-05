#ifndef MYQCUSTOMPLOT_H
#define MYQCUSTOMPLOT_H

#include <QObject>


#include <Library/QCustomPlot/qcustomplot.h>
#include <GUI/Size/customize.h>
class myQCustomPlot : public QObject
{
    Q_OBJECT
private:
    //Classes
    customize* classCustomize;


    //array of double
    QVector<double> qVectorX;
    QVector<double> qVectorY;

    //functions
    void init_classes();
    void init_QCustomPlot();
    void plot();
public:
    //GUI Elements

    //QCustomPlot
    QCustomPlot* customPlot;

    static myQCustomPlot* getInstance();
    myQCustomPlot(QObject *parent = nullptr);

public slots:
    void slotRightYAxis();
    void slotLeftYAxis();
    void slotCustomScale(double minX, double maxX, double minY, double maxY);
    void slotAutoScale();
    void slotSetTicks(int ticks);
    void slotSavePlotImage(QString fileName, int width, int height, double scale, int quality);
    void slotReverseXAxis(bool status);
    void slotFixDisplay(bool status);

    void slotZoomIn();
    void slotZoomOut();
    void slotAreaSelection();
};

#endif // MYQCUSTOMPLOT_H
