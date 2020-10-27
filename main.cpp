#include "GstWidget.h"
#include <QApplication>
#include <QGridLayout>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gst_init(&argc, &argv);

    QWidget centralWidget;

    QGridLayout *layout = new QGridLayout();
    GstWidget *w = new GstWidget(&centralWidget);
    GstWidget *w2 = new GstWidget(&centralWidget);

    centralWidget.setLayout (layout);

    layout->addWidget(w, 0, 0, 2, 2);
    layout->addWidget(w2, 0, 0, 1, 1);

    centralWidget.showFullScreen();

    return a.exec();
}
