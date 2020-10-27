#include "GstWidget.h"
#include <QApplication>
#include <QGridLayout>
#include <QWidget>
#include <X11/Xlib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gst_init(&argc, &argv);

//    QWidget centralWidget;

//    QGridLayout *layout = new QGridLayout();
//    GstWidget *w = new GstWidget(&centralWidget);
//    GstWidget *w2 = new GstWidget(&centralWidget);

//    centralWidget.setLayout (layout);

//    layout->addWidget(w, 0, 0, 2, 2);
//    layout->addWidget(w2, 0, 0, 1, 1);

//    centralWidget.showFullScreen();
    GstWidget w;
    QPalette pal;

    // set pink background
    pal.setColor(QPalette::Background, 0xFF0000);
    w.setAutoFillBackground(true);
    w.setPalette(pal);

    w.showFullScreen();

    a.setOverrideCursor(QCursor(Qt::BlankCursor));

    return a.exec();
}
