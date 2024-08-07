#include <QApplication>
#include <GUI/MainWindow/maniWindow.h>
#include <Process/Process.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Process* ClassProcess = new Process;

    maniWindow* ClassMainWindow = new maniWindow;
    ClassMainWindow->show();

    return a.exec();
}
