#include <QApplication>
#include <GUI/MainWindow/maniWindow.h>
#include <Process/Process.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Process* p = new Process;
//    window ww;
//    ww.show();
    maniWindow* w = new maniWindow;
    w->show();
    return a.exec();
}
