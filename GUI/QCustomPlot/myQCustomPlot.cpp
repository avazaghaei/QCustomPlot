#include "myQCustomPlot.h"

myQCustomPlot *myQCustomPlot::getInstance()
{
    static myQCustomPlot* instance = nullptr;
    if(instance == nullptr)
        instance = new myQCustomPlot;
    return instance;
}

myQCustomPlot::myQCustomPlot(QObject *parent) : QObject(parent)
{
    init_classes();
    init_QCustomPlot();
}

void myQCustomPlot::init_classes()
{
    classCustomize = new customize();
}

void myQCustomPlot::init_QCustomPlot()
{
    customPlot = new QCustomPlot;
    customPlot->addGraph();
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->setInteraction(QCP::iRangeDrag,true);
    customPlot->setInteraction(QCP::iRangeZoom,true);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(150,0,0));
    customPlot->graph(0)->setPen(pen);

   customPlot->setBackground(Qt::lightGray);

   customPlot->setFixedWidth(classCustomize->max_width_plot);
   customPlot->setFixedWidth(classCustomize->max_height_plot);

   customPlot->xAxis->setRange(0, 100);
   customPlot->yAxis2->setRange(0,100);

   customPlot->xAxis->setLabel("X");
   customPlot->yAxis->setLabel("Y");
}

void myQCustomPlot::plot()
{

    customPlot->replot();
    customPlot->update();
}

void myQCustomPlot::slotRightYAxis()
{
    customPlot->yAxis->setVisible(false);
    customPlot->yAxis2->setVisible(true);
    plot();
}

void myQCustomPlot::slotLeftYAxis()
{
    customPlot->yAxis2->setVisible(false);
    customPlot->yAxis->setVisible(true);
    plot();
}

void myQCustomPlot::slotCustomScale(double minX, double maxX, double minY, double maxY)
{
    customPlot->xAxis->setRange(minX, maxX);
    customPlot->yAxis->setRange(minY, maxY);
    plot();
}

void myQCustomPlot::slotAutoScale()
{
    customPlot->xAxis->setRange(*std::min_element(qVectorX.begin(), qVectorX.end()) -2 , *std::max_element(qVectorX.begin(), qVectorX.end()) +2);
    customPlot->yAxis->setRange(*std::min_element(qVectorY.begin(), qVectorY.end()) -2 , *std::max_element(qVectorY.begin(), qVectorY.end()) +2);
    plot();
}

void myQCustomPlot::slotSetTicks(int ticks)
{
    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    customPlot->xAxis->setTicker(fixedTicker);
    if(ticks != 0)
    {
        fixedTicker->setTickStep(ticks); // tick step shall be 1.0
        plot();
    }
    else
    {
        fixedTicker->setTickStep(50); // tick step shall be 1.0
        plot();
    }
}

void myQCustomPlot::slotSavePlotImage(QString fileName, int width, int height, double scale, int quality)
{
    customPlot->saveJpg(fileName, width, height, 1.0, -1);
}

void myQCustomPlot::slotReverseXAxis(bool status)
{
    if(status)
    {
        customPlot->xAxis->setRangeReversed(true);
    }
    else
    {
        customPlot->xAxis->setRangeReversed(false);
    }
    plot();
}

void myQCustomPlot::slotFixDisplay(bool status)
{
    if(status)
    {
        connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), SLOT(clickedGraph(QMouseEvent*)));
        plot();
    }
    else
    {
        disconnect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this,  0);
        plot();
    }
}

void myQCustomPlot::slotZoomIn()
{
    double offset = customPlot->xAxis->range().size() * .1;


    double minX = customPlot->xAxis->range().lower;
    double maxX = customPlot->xAxis->range().upper;
    double minY = customPlot->yAxis->range().lower;
    double maxY = customPlot->yAxis->range().upper;

    customPlot->xAxis->setRange(minX + offset , maxX - offset);
    customPlot->yAxis->setRange(minY + offset , maxY - offset);
    plot();
}

void myQCustomPlot::slotZoomOut()
{
    double offset = customPlot->xAxis->range().size() * .1;


    double minX = customPlot->xAxis->range().lower;
    double maxX = customPlot->xAxis->range().upper;
    double minY = customPlot->yAxis->range().lower;
    double maxY = customPlot->yAxis->range().upper;

    customPlot->xAxis->setRange(minX - offset , maxX + offset);
    customPlot->yAxis->setRange(minY - offset , maxY + offset);
    plot();
}

void myQCustomPlot::slotAreaSelection()
{
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customPlot->axisRect()->setRangeDrag(Qt::Vertical);
    customPlot->axisRect()->setRangeZoom(Qt::Vertical);
    customPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal);
    customPlot->axisRect()->setRangeZoomAxes(customPlot->xAxis, customPlot->yAxis); //To block y axis zoom NULL axis as horizontal
    customPlot->setSelectionRectMode(QCP::srmZoom);
    plot();
}
