#ifndef GSTWIDGET_H
#define GSTWIDGET_H

#include <QWidget>
#include <gst/gst.h>
#include <gst/gstelement.h>
#include <gst/video/videooverlay.h>

class GstWidget : public QWidget
{
    Q_OBJECT

public:
    GstWidget(QWidget *parent = 0, unsigned int rotation = 0);
    ~GstWidget();

    WId _window;

    WId getWinId() const {return _window;}


    GstElement *_pipeline;

};

#endif // GSTWIDGET_H
