#include "customize.h"

customize::customize(QObject *parent) : QObject(parent)
{
    init_sizes();
}

void customize::init_sizes()
{
    QDesktopWidget desktop;
    int max_width  = desktop.width();
    int max_height = desktop.height();

    max_width_label          = max_width  * 0.08;
    max_height_label         = max_height * 0.02;

    max_width_checkBox      = max_width_label;
    max_height_checkBox      = max_height * 0.03;

    max_width_lineEdit       = max_width_label;
    max_height_lineEdit      = max_height * 0.03;

    max_width_doubleSpinBox  = max_width_label;
    max_height_doubleSpinBox = max_height * 0.03;

    max_width_radioButton    = max_width_label;
    max_height_radioButton   = max_height * 0.05;

    max_width_pushButton     = max_width_label;
    max_height_pushButton    = max_height * 0.03;

    max_width_groupBox       = max_width  * 0.3;
    max_height_groupBox      = max_height * .6;

    parent_width             = max_width;
    parent_height            = max_height;

    max_width_plot         = max_width  * 0.5;
    max_height_plot        = max_height_groupBox;

    //max_width_progress     = max_width  * 0.5;
    //max_height_progress    = max_height * 0.03;

}
