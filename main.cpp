#include "GstWidget.h"
#include <QApplication>
#include <QGridLayout>
#include <QWidget>
#include <X11/Xlib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gst_init(&argc, &argv);

    QWidget centralWidget;

    QGridLayout *layout = new QGridLayout();
    GstWidget *w1 = new GstWidget(&centralWidget, 0);
    GstWidget *w2 = new GstWidget(&centralWidget, 1);
    GstWidget *w3 = new GstWidget(&centralWidget, 2);
    GstWidget *w4 = new GstWidget(&centralWidget, 3);
    GstWidget *w5 = new GstWidget(&centralWidget, 4);
    GstWidget *w6 = new GstWidget(&centralWidget, 5);
    GstWidget *w7 = new GstWidget(&centralWidget, 6);
    GstWidget *w8 = new GstWidget(&centralWidget, 7);
    centralWidget.setLayout (layout);

    layout->addWidget(w1, 0, 0, 1, 1);
    layout->addWidget(w2, 1, 0, 1, 1);
    layout->addWidget(w3, 2, 0, 1, 1);
    layout->addWidget(w4, 3, 0, 1, 1);
    layout->addWidget(w5, 0, 1, 1, 1);
    layout->addWidget(w6, 1, 1, 1, 1);
    layout->addWidget(w7, 2, 1, 1, 1);
    layout->addWidget(w8, 3, 1, 1, 1);

    centralWidget.setFixedWidth(1280);
    centralWidget.setFixedHeight(800);
    centralWidget.show();

    return a.exec();
}
