#ifndef CUSTOMIZE_H
#define CUSTOMIZE_H

#include <QObject>
#include <QDesktopWidget>
class customize : public QObject
{
    Q_OBJECT
public:


    int max_width_label;
    int max_height_label;

    int max_width_checkBox;
    int max_height_checkBox;

    int max_width_lineEdit;
    int max_height_lineEdit;

    int max_width_doubleSpinBox;
    int max_height_doubleSpinBox;

    int max_width_radioButton;
    int max_height_radioButton;

    int max_width_pushButton;
    int max_height_pushButton;

    int max_width_groupBox;
    int max_height_groupBox;

    int parent_width;
    int parent_height;

    int max_width_plot;
    int max_height_plot;

    QSizePolicy spExpanding = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSizePolicy spFixed = QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QFont lblFont     = QFont("Times", 9);
    QFont sbFont      = QFont("Times", 9);
    QFont btnFont     = QFont("Times", 9);
    QFont chkbFont    = QFont("Times", 9);
    QFont rdbtnFont   = QFont("Times", 9);
    QFont leFont      = QFont("Times", 9);


    QString lblStylSheet   = "background-color: transparent ; color: black";
    QString chkbStylSheet  = "background-color: transparent ; color: black";
    QString sbStylSheet    = "background-color: white       ; color: blue ";
    QString rdbtnStylSheet = "background-color: transparent ; color: black";
    QString btnStylSheet   = "background-color: silver      ; color: black";
    QString leStylSheet    = "background-color: #e8eae6     ; color: black";
    QString formStylSheet  = "background-color: lightgray   ; font-weight:bold;";


    QString grbtnStylSheet = "QGroupBox {"

                             "border: 2px solid cfdac8;"
                             "background-color: transparent;"

                             "}"
                             "QGroupBox::title {"
                             "subcontrol-origin: margin;"
                             "padding:0 3px;"
                             "subcontrol-position: top center;"
                             "border-top-left-radius: 15px;"
                             "border-top-right-radius: 15px;"
                             "padding: 5px 150px;"
                             "background-color: #7c9473;"
                             "color: black;"
                             "font-weight: Bold;"
                             "}";

    void init_sizes();

    explicit customize(QObject *parent = nullptr);

signals:

};

#endif // CUSTOMIZE_H
