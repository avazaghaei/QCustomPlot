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
    initClass();
    initTimer();
    setContextMenu();
}

void myQCustomPlot::initClass()
{
    ClassCustomize = new customize();
    initQCustomPlot();
}

void myQCustomPlot::initQCustomPlot()
{
    ClassCustomPlot = new QCustomPlot;
    ClassCustomPlot->addGraph();
    ClassCustomPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ClassCustomPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ClassCustomPlot->setInteraction(QCP::iRangeDrag,true);
    ClassCustomPlot->setInteraction(QCP::iRangeZoom,true);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(150,0,0));
    ClassCustomPlot->graph(0)->setPen(pen);

   ClassCustomPlot->setBackground(Qt::lightGray);

   ClassCustomPlot->setFixedWidth(ClassCustomize->max_width_plot);
   ClassCustomPlot->setFixedWidth(ClassCustomize->max_height_plot);

   ClassCustomPlot->xAxis->setRange(0, 100);
   ClassCustomPlot->yAxis2->setRange(0,100);

   ClassCustomPlot->xAxis->setLabel("X");
   ClassCustomPlot->yAxis->setLabel("Y");
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

//    if(rdBTNAutoScale->isChecked())
//    {
//        rdBTNAutoScale->clicked();
//    }
    plot();
}

void myQCustomPlot::initTimer()
{
    // setup a timer that repeatedly calls
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &myQCustomPlot::slotGenerateRandomNumber);
    timer->start(millisecond);
}

void myQCustomPlot::setContextMenu()
{
    // setup policy and connect slot for context menu popup:
    ClassCustomPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ClassCustomPlot, &QCustomPlot::customContextMenuRequested, this, &myQCustomPlot::contextMenuRequest);
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

void myQCustomPlot::slotFixDisplay(bool status)
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
    //qcustomplot.cpp lines :29657,12484,28842
    if((phaseTracer->position->key() == 5000000 ) && ( phaseTracer->position->value()== 5000000))
    {
        //If the algorithm select the number 5,000,000, we will disable this point and we will not continue the algorithm.
        //Assuming the user does not generate 5,000,000, data
        phaseTracer->setVisible(false);
    }

    else
    {
        // add label for phase tracer:
        QCPItemText *phaseTracerText = new QCPItemText(ClassCustomPlot);
        phaseTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
        phaseTracerText->setPositionAlignment(Qt::AlignRight|Qt::AlignTop);
        phaseTracerText->position->setTypeY(QCPItemPosition::ptPlotCoords);
        phaseTracerText->position->setTypeX(QCPItemPosition::ptPlotCoords);
        phaseTracerText->position->setCoords(phaseTracer->position->key(), phaseTracer->position->value());
        phaseTracerText->setText("X : " + QString::number(phaseTracer->position->key())  + "\ny : " + QString::number(phaseTracer->position->value()) );
        phaseTracerText->setTextAlignment(Qt::AlignRight);
//        phaseTracerText->setFont(QFont(font().family(), 9));
        phaseTracerText->setPadding(QMargins(0,0,0,10));


        /*
        // add arrow pointing at phase tracer, coming from label:
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

*/
        //calculate delta
        deltaCounter = deltaCounter + 1;
        qDebug() << deltaCounter % 2;
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

        double x = firstX - secondX;
        double y = firstY - secondY;

        emit signalSetValueDelta(x, y);
    }
    plot();
}

void myQCustomPlot::contextMenuRequest(QPoint pos)
{
    //Play Action, makes the video play.
    QAction* reverse = new QAction(tr("reverse"),this);
    reverse->setIcon(QIcon(":/Source/Icon/reverse.png"));
    reverse->setIconVisibleInMenu(true);
    connect(reverse,SIGNAL(triggered()),this,SLOT(menuReverseXAxis()));

    QAction* newWindow = new QAction(tr("new Window"),this);
    newWindow->setIcon(QIcon(":/Source/Icon/newWindow.png"));
    newWindow->setIconVisibleInMenu(true);
    connect(newWindow,SIGNAL(triggered()),this,SLOT(showFullWindow()));

    //export data
    QAction* exportToExcel = new QAction(tr("export to file"),this);
    exportToExcel->setIcon(QIcon(":/Source/Icon/export.png"));
    exportToExcel->setIconVisibleInMenu(true);
    connect(exportToExcel,SIGNAL(triggered()),this,SLOT(exportPlotToExcel()));


    //import data
    QAction* importFromExcel = new QAction(tr("import from file"),this);
    importFromExcel->setIcon(QIcon(":/Source/Icon/import.png"));
    importFromExcel->setIconVisibleInMenu(true);
    connect(importFromExcel,SIGNAL(triggered()),this,SLOT(importExcelToPlot()));

    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    // general context menu on graphs requested
    menu->addAction(reverse);
    menu->addAction(newWindow);
    menu->addAction(exportToExcel);
    menu->addAction(importFromExcel);
    menu->popup(ClassCustomPlot->mapToGlobal(pos));
}

void myQCustomPlot::menuReverseXAxis()
{
    emit signalReverseXAxis();

}

void myQCustomPlot::exportPlotToExcel()
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
        auto line = xin.readLine();
        auto values = line.split(",");
        auto cryptFirstColumn = values.at(0);
        auto cryptSecondColumn = values.at(1);

        QString decryptFirstColumn = crypto.decryptToString(cryptFirstColumn);
        QString decryptSecondColumn = crypto.decryptToString(cryptSecondColumn);

        qDebug() <<decryptFirstColumn <<decryptSecondColumn;
        addPoint(decryptFirstColumn.toDouble(), decryptSecondColumn.toDouble());
    }
}

void myQCustomPlot::importExcelToPlot()
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
    QWidget *newWindow = new QWidget();
    newWindow->setFixedWidth(ClassCustomize->parent_width);
    newWindow->setFixedHeight(ClassCustomize->parent_height);

    ClassNewWindowCustomPlot = new QCustomPlot(newWindow);
    ClassNewWindowCustomPlot->addGraph();
    ClassNewWindowCustomPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ClassNewWindowCustomPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ClassNewWindowCustomPlot->setInteraction(QCP::iRangeDrag,true);
    ClassNewWindowCustomPlot->setInteraction(QCP::iRangeZoom,true);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(150,0,0));
    ClassNewWindowCustomPlot->graph(0)->setPen(pen);
    ClassNewWindowCustomPlot->setBackground(Qt::lightGray);

    ClassNewWindowCustomPlot->setFixedWidth(ClassCustomize->parent_width);
    ClassNewWindowCustomPlot->setFixedHeight(ClassCustomize->parent_height);

    ClassNewWindowCustomPlot->xAxis->setLabel("X");
    ClassNewWindowCustomPlot->yAxis->setLabel("Y");

    ClassNewWindowCustomPlot->xAxis->setRange(*std::min_element(qVectorX.begin(), qVectorX.end()) -2 , *std::max_element(qVectorX.begin(), qVectorX.end()) +2);
    ClassNewWindowCustomPlot->yAxis->setRange(*std::min_element(qVectorY.begin(), qVectorY.end()) -2 , *std::max_element(qVectorY.begin(), qVectorY.end()) +2);

    ClassNewWindowCustomPlot->graph(0)->setData(qVectorX, qVectorY);
    ClassNewWindowCustomPlot->replot();
    ClassNewWindowCustomPlot->update();
    newWindow->show();
}
