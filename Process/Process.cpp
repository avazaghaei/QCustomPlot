#include "Process.h"

Process::Process()
{
    initClasses();
    setConnections();
}


void Process::initClasses()
{
    classCustomPlot   = myQCustomPlot::getInstance();
    classSettings     = settings::getInstance();
    classZoomSettings = zoomSettings::getInstance();
}

void Process::setConnections()
{
//Establish signal-slot connections:
    {
        //Signal:settings
        //Slots:myQCustomPlot
        {
            // x-axis replacement update
            connect(classSettings, &settings::signalRightYAxis, classCustomPlot, &myQCustomPlot::slotRightYAxis);
            connect(classSettings, &settings::signalLeftYAxis , classCustomPlot, &myQCustomPlot::slotLeftYAxis);
        }
        {
            //custom scale
            connect(classSettings, &settings::signalSpinBox, classCustomPlot, &myQCustomPlot::slotCustomScale);

            //auto scale
            connect(classSettings, &settings::signalRadioButtonAutoScale, classCustomPlot, &myQCustomPlot::slotAutoScale);
        }
        {
            //Ticks
            connect(classSettings, &settings::signalSetTicks, classCustomPlot, &myQCustomPlot::slotSetTicks);
        }
        {
            //save plot Image
            connect(classSettings, &settings::signalSavePloImage, classCustomPlot, &myQCustomPlot::slotSavePlotImage);
        }
        {
            //reverse x axis
            connect(classSettings, &settings::signalReverseXAxis, classCustomPlot, &myQCustomPlot::slotReverseXAxis);
        }
        {
            //Enable point selection mode
            connect(classSettings, &settings::signalEnablePointSelection, classCustomPlot, &myQCustomPlot::slotEnablePointSelection);
        }
    }

    {
        //Signal:myQCustomPlot
        //Slots:settings
        {
            //set value delta
            connect(classCustomPlot, &myQCustomPlot::signalSetValueDelta, classSettings, &settings::slotSetValueDelta);
        }
        {
            //reverse x-axis from menu request
            connect(classCustomPlot, &myQCustomPlot::signalReverseXAxis, classSettings, &settings::slotReverseXAxisMenuRequest);
        }
        {
            //point added event
            connect(classCustomPlot, &myQCustomPlot::signalAddedPoint, classSettings, &settings::slotAddedPoint);
        }
    }
    {
        //Signal:zoomSettings
        //Slots:myQCustomPlot
        {
            //zoom in
            connect(classZoomSettings, &zoomSettings::signalZoomIn, classCustomPlot, &myQCustomPlot::slotZoomIn);

            //zoom out
            connect(classZoomSettings, &zoomSettings::signalZoomOut, classCustomPlot, &myQCustomPlot::slotZoomOut);

            //area selection
            connect(classZoomSettings, &zoomSettings::signalAreaSelection, classCustomPlot, &myQCustomPlot::slotAreaSelection);

            //reset zoom
            connect(classZoomSettings, &zoomSettings::signalResetZoom, classCustomPlot, &myQCustomPlot::slotAutoScale);
        }
    }
}
