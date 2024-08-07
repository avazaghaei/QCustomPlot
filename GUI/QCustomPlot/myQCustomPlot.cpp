#include "myQCustomPlot.h"

myQCustomPlot *myQCustomPlot::getInstance()
{
    static myQCustomPlot* instance = nullptr;
    if(instance == nullptr)
        instance = new myQCustomPlot;
    return instance;
}

myQCustomPlot::myQCustomPlot()
{
    initVariables();
    initClass();
    initTimer();
    setContextMenu();
    initFullWindow();

}

void myQCustomPlot::initVariables()
{
    firstX       = 0;
    firstY       = 0;
    secondX      = 0;
    secondY      = 0;
    deltaCounter = 0;
}

void myQCustomPlot::initClass()
{
    ClassCustomize = new customize();
    ClassCustomPlot = initQCustomPlot();
    ClassCustomPlot->setFixedWidth(ClassCustomize->max_width_plot);
    ClassCustomPlot->setFixedHeight(ClassCustomize->max_height_plot);
}

QCustomPlot* myQCustomPlot::initQCustomPlot()
{
    QCustomPlot* plot = new QCustomPlot;
    plot->addGraph();
    plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    plot->setInteraction(QCP::iRangeDrag,true);
    plot->setInteraction(QCP::iRangeZoom,true);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(150,0,0));
    plot->graph(0)->setPen(pen);

    plot->setBackground(Qt::lightGray);



    plot->xAxis->setRange(0, 100);
    plot->yAxis2->setRange(0,100);

    plot->xAxis->setLabel("X");
    plot->yAxis->setLabel("Y");

    return plot;
}

void myQCustomPlot::plot()
{

    ClassCustomPlot->replot();
    ClassCustomPlot->update();
}

void myQCustomPlot::addPoint(double x, double y)
{
    qVectorX.append(x);
    qVectorY.append(y);

    ClassCustomPlot->graph(0)->setData(qVectorX, qVectorY);

    emit signalAddedPoint();

    plot();
}

void myQCustomPlot::initTimer()
{
    // setup a timer that repeatedly calls
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &myQCustomPlot::slotGenerateRandomNumber);
    timer->start(millisecond);
}

void myQCustomPlot::initContextMenu()
{
    {
        //reverse x-axis
        actReverse = new QAction(tr("reverse"),this);
        actReverse->setIcon(QIcon(":/Source/Icon/reverse.png"));
        actReverse->setIconVisibleInMenu(true);
        connect(actReverse,SIGNAL(triggered()),this,SLOT(menuReverseXAxis()));
    }
    {
        //new window
        actNewWindow = new QAction(tr("new Window"),this);
        actNewWindow->setIcon(QIcon(":/Source/Icon/newWindow.png"));
        actNewWindow->setIconVisibleInMenu(true);
        connect(actNewWindow,SIGNAL(triggered()),this,SLOT(showFullWindow()));
    }
    {
        //export data
        actExportToExcel = new QAction(tr("export to file"),this);
        actExportToExcel->setIcon(QIcon(":/Source/Icon/export.png"));
        actExportToExcel->setIconVisibleInMenu(true);
        connect(actExportToExcel,SIGNAL(triggered()),this,SLOT(exportPlotToExcel()));
    }
    {
        //import data
        actImportFromExcel = new QAction(tr("import from file"),this);
        actImportFromExcel->setIcon(QIcon(":/Source/Icon/import.png"));
        actImportFromExcel->setIconVisibleInMenu(true);
        connect(actImportFromExcel,SIGNAL(triggered()),this,SLOT(importExcelToPlot()));
    }
    {
        //Implement generic graph context menu
        menuQCustopmPlotContextMenu = new QMenu(this);
        menuQCustopmPlotContextMenu->addAction(actReverse);
        menuQCustopmPlotContextMenu->addAction(actNewWindow);
        menuQCustopmPlotContextMenu->addAction(actExportToExcel);
        menuQCustopmPlotContextMenu->addAction(actImportFromExcel);
    }
}

void myQCustomPlot::setContextMenu()
{
    initContextMenu();

    // setup policy and connect slot for context menu popup:
    ClassCustomPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ClassCustomPlot, &QCustomPlot::customContextMenuRequested, this, &myQCustomPlot::contextMenuRequest);
}

void myQCustomPlot::initFullWindow()
{

    {
        widgetFullWindow = new QWidget();
        widgetFullWindow->setFixedWidth(ClassCustomize->parent_width);
        widgetFullWindow->setFixedHeight(ClassCustomize->parent_height*0.95);
    }
    {
        ClassNewFullCustomPlot = initQCustomPlot();
        ClassNewFullCustomPlot->setFixedWidth(ClassCustomize->parent_width);
        ClassNewFullCustomPlot->setFixedHeight(ClassCustomize->parent_height*0.9);
        ClassNewFullCustomPlot->setParent(widgetFullWindow);
    }
}


void myQCustomPlot::slotGenerateRandomNumber()
{
    srand(time(NULL));
    double x= rand() % 1000;
    double y= rand() % 1000;

    addPoint(x ,y );
}

void myQCustomPlot::slotRightYAxis()
{
    ClassCustomPlot->yAxis->setVisible(false);
    ClassCustomPlot->yAxis2->setVisible(true);
    plot();
}

void myQCustomPlot::slotLeftYAxis()
{
    ClassCustomPlot->yAxis2->setVisible(false);
    ClassCustomPlot->yAxis->setVisible(true);
    plot();
}

void myQCustomPlot::slotCustomScale(double minX, double maxX, double minY, double maxY)
{
    ClassCustomPlot->xAxis->setRange(minX, maxX);
    ClassCustomPlot->yAxis->setRange(minY, maxY);
    plot();
}

void myQCustomPlot::slotAutoScale()
{
    ClassCustomPlot->xAxis->setRange(*std::min_element(qVectorX.begin(), qVectorX.end()) -2 , *std::max_element(qVectorX.begin(), qVectorX.end()) +2);
    ClassCustomPlot->yAxis->setRange(*std::min_element(qVectorY.begin(), qVectorY.end()) -2 , *std::max_element(qVectorY.begin(), qVectorY.end()) +2);
    plot();
}

void myQCustomPlot::slotSetTicks(int ticks)
{
    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    ClassCustomPlot->xAxis->setTicker(fixedTicker);
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
    ClassCustomPlot->saveJpg(fileName, width, height, 1.0, -1);
}

void myQCustomPlot::slotReverseXAxis(bool status)
{
    if(status)
    {
        ClassCustomPlot->xAxis->setRangeReversed(true);
    }
    else
    {
        ClassCustomPlot->xAxis->setRangeReversed(false);
    }
    plot();
}

void myQCustomPlot::slotEnablePointSelection(bool status)
{
    if(status)
    {
        connect(ClassCustomPlot, &QCustomPlot::mousePress, this, &myQCustomPlot::clickedGraph);

    }
    else
    {
        disconnect(ClassCustomPlot, SIGNAL(mousePress(QMouseEvent*)), this,  0);
    }
    plot();
}

void myQCustomPlot::slotZoomIn()
{
    double offset = ClassCustomPlot->xAxis->range().size() * .1;


    double minX = ClassCustomPlot->xAxis->range().lower;
    double maxX = ClassCustomPlot->xAxis->range().upper;
    double minY = ClassCustomPlot->yAxis->range().lower;
    double maxY = ClassCustomPlot->yAxis->range().upper;

    ClassCustomPlot->xAxis->setRange(minX + offset , maxX - offset);
    ClassCustomPlot->yAxis->setRange(minY + offset , maxY - offset);
    plot();
}

void myQCustomPlot::slotZoomOut()
{
    double offset = ClassCustomPlot->xAxis->range().size() * .1;


    double minX = ClassCustomPlot->xAxis->range().lower;
    double maxX = ClassCustomPlot->xAxis->range().upper;
    double minY = ClassCustomPlot->yAxis->range().lower;
    double maxY = ClassCustomPlot->yAxis->range().upper;

    ClassCustomPlot->xAxis->setRange(minX - offset , maxX + offset);
    ClassCustomPlot->yAxis->setRange(minY - offset , maxY + offset);
    plot();
}

void myQCustomPlot::slotAreaSelection()
{
    ClassCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ClassCustomPlot->axisRect()->setRangeDrag(Qt::Vertical);
    ClassCustomPlot->axisRect()->setRangeZoom(Qt::Vertical);
    ClassCustomPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    ClassCustomPlot->axisRect()->setRangeZoom(Qt::Horizontal);
    ClassCustomPlot->axisRect()->setRangeZoomAxes(ClassCustomPlot->xAxis, ClassCustomPlot->yAxis); //To block y axis zoom NULL axis as horizontal
    ClassCustomPlot->setSelectionRectMode(QCP::srmZoom);
    plot();
}

void myQCustomPlot::clickedGraph(QMouseEvent *event)
{
    double x = ClassCustomPlot->xAxis->pixelToCoord(event->pos().x());
    double y = ClassCustomPlot->yAxis->pixelToCoord(event->pos().y());


     // add the phase tracer (red circle) which sticks to the graph data
    phaseTracer = new QCPItemTracer(ClassCustomPlot);
    phaseTracer = new QCPItemTracer(ClassCustomPlot);
    phaseTracer->setGraph( ClassCustomPlot->graph(0));
    phaseTracer->selectable();
    phaseTracer->setGraphKey(x);
    phaseTracer->setInterpolating(false);
    phaseTracer->setStyle(QCPItemTracer::tsCircle);
    phaseTracer->setPen(QPen(Qt::red));
    phaseTracer->setBrush(Qt::red);
    phaseTracer->setSize(7);
    phaseTracer->updatePosition(y);


    //By default, if a point is entered outside the range of points, the algorithm selects 5,000,000.
    //qcustomplot.cpp lines :29657, and 12484, and 28842
    if((phaseTracer->position->key() == 5000000 ) && ( phaseTracer->position->value()== 5000000))
    {
        //If the algorithm select the number 5,000,000, we will disable this point and we will not continue the algorithm.
        //Assuming the user does not generate 5,000,000, data
        phaseTracer->setVisible(false);
    }

    else
    {
        // Create text label for phase tracer
        QCPItemText *phaseTracerText = new QCPItemText(ClassCustomPlot);
        {
            // Create text label for phase tracer
            phaseTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
            phaseTracerText->setPositionAlignment(Qt::AlignRight|Qt::AlignTop);
            phaseTracerText->position->setTypeY(QCPItemPosition::ptPlotCoords);
            phaseTracerText->position->setTypeX(QCPItemPosition::ptPlotCoords);
            phaseTracerText->position->setCoords(phaseTracer->position->key(), phaseTracer->position->value());
            phaseTracerText->setText("X : " + QString::number(phaseTracer->position->key())  + "\ny : " + QString::number(phaseTracer->position->value()) );
            phaseTracerText->setTextAlignment(Qt::AlignRight);
            phaseTracerText->setFont(QFont(font().family(), 9));
            phaseTracerText->setPadding(QMargins(0,0,0,10));
        }
        {
            // Create arrow indicator from label to phase tracer
            QCPItemCurve *phaseTracerArrow = new QCPItemCurve(ClassCustomPlot);
            phaseTracerArrow->start->setParentAnchor(phaseTracerText->right);
            phaseTracerArrow->startDir->setParentAnchor(phaseTracerArrow->start);
            phaseTracerArrow->startDir->setCoords(0, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
            phaseTracerArrow->end->setParentAnchor(phaseTracer->position);
            phaseTracerArrow->end->setCoords(10, 10);
            phaseTracerArrow->endDir->setParentAnchor(phaseTracerArrow->end);
            phaseTracerArrow->endDir->setCoords(5, 5);
            phaseTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
            phaseTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (phaseTracerText->bottom->pixelPosition().y()-phaseTracerText->top->pixelPosition().y())*0.85));

        }
        {
            //Calculate and emit point difference (delta)
            deltaCounter = deltaCounter + 1;
            if(!(deltaCounter % 2))
            {
                firstX = phaseTracer->position->key();
                firstY = phaseTracer->position->value();
            }
            else
            {
                secondX = phaseTracer->position->key();
                secondY = phaseTracer->position->value();
            }

            deltaX = firstX - secondX;
            deltaY = firstY - secondY;

            emit signalSetValueDelta(deltaX, deltaY);
        }
    }
    plot();
}

void myQCustomPlot::contextMenuRequest(QPoint pos)
{

    menuQCustopmPlotContextMenu->popup(ClassCustomPlot->mapToGlobal(pos));
}

void myQCustomPlot::menuReverseXAxis()
{
    emit signalReverseXAxis();

}

void myQCustomPlot::importExcelToPlot()
{
    //public key creyption/decryption
    //some random number
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));

    QString fileName = QFileDialog::getOpenFileName(this, tr("open File"), "Desktop/test.hdy", tr("*.hdy"));

    //linux & windows
    if(fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream xin(&file);
    while(!xin.atEnd())
    {
        //read line
        auto line              = xin.readLine();

        //Parse line for two numeric values
        auto values            = line.split(",");

        //read two numeric values that are crypted
        auto cryptFirstColumn  = values.at(0);
        auto cryptSecondColumn = values.at(1);

        //decrypt two numeric values that are string
        QString decryptFirstColumn  = crypto.decryptToString(cryptFirstColumn);
        QString decryptSecondColumn = crypto.decryptToString(cryptSecondColumn);

        addPoint(decryptFirstColumn.toDouble(), decryptSecondColumn.toDouble());
    }
}

void myQCustomPlot::exportPlotToExcel()
{
    //public key creyption/decryption
    //some random number
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "Desktop/test.hdy", tr("personal (*.hdy)"));

    QString path = fileName;
    std::ofstream myfile;
    myfile.open(path.toStdString());
    for (int i = 0 ; i<qVectorX.length() ;i++ )
    {
        std::string X = (crypto.encryptToString(QString::number(qVectorX[i]))).toLocal8Bit().constData();
        std::string Y = (crypto.encryptToString(QString::number(qVectorY[i]))).toLocal8Bit().constData();
        myfile << X << "," << Y << std::endl;

    }
}

void myQCustomPlot::showFullWindow()
{
    ClassNewFullCustomPlot->xAxis->setRange(*std::min_element(qVectorX.begin(), qVectorX.end()) -2 , *std::max_element(qVectorX.begin(), qVectorX.end()) +2);
    ClassNewFullCustomPlot->yAxis->setRange(*std::min_element(qVectorY.begin(), qVectorY.end()) -2 , *std::max_element(qVectorY.begin(), qVectorY.end()) +2);

    ClassNewFullCustomPlot->graph(0)->setData(qVectorX, qVectorY);
    ClassNewFullCustomPlot->replot();
    ClassNewFullCustomPlot->update();


    widgetFullWindow->show();
}
