#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <gst/gst.h>
#include <gst/gstelement.h>
#include <gst/video/videooverlay.h>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    GstElement *_pipeline;

};

#endif // WIDGET_H
