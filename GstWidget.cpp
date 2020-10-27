#include "GstWidget.h"

#include <QDebug>
#include <QGuiApplication>

static GstBusSyncReply _bus_callback (GstBus */*bus*/, GstMessage *message, gpointer user_data)
{
    GstWidget* widget = static_cast<GstWidget*>(user_data);
    if(gst_is_video_overlay_prepare_window_handle_message(message)) {
        qDebug() <<  "setting window handle" << widget->getWinId();
        gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY (message->src), widget->getWinId());
        gst_message_unref (message);
        return GST_BUS_DROP;
    }

    return GST_BUS_PASS;

}


GstWidget::GstWidget(QWidget *parent)
    : QWidget(parent)
{
    GstElement *source;
    GstElement *sink;
    _pipeline = gst_pipeline_new ("videosinktest");

    source = gst_element_factory_make("videotestsrc", "mysource");
    sink = gst_element_factory_make("xvimagesink", "myvideosink");

    if(!_pipeline || !source || !sink) {
        qDebug() <<  "Not all elements could be created.";
    }

    gst_bin_add_many(GST_BIN(_pipeline), source, sink, NULL);

    gst_element_link(source,sink);

    // monitor sync to pass along window id
    GstBus * bus = gst_pipeline_get_bus(GST_PIPELINE(_pipeline));
    gst_bus_enable_sync_message_emission (bus);
    gst_bus_set_sync_handler (bus, _bus_callback, this, NULL);
    gst_object_unref (bus);

    show();
    _window = winId();

    gst_element_set_state (_pipeline, GST_STATE_PLAYING);

}

GstWidget::~GstWidget()
{

}