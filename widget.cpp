#include "widget.h"

#include <QDebug>
#include <QGuiApplication>
#include <gst/wayland/wayland.h>
#include <qpa/qplatformnativeinterface.h>

static GstBusSyncReply _bus_callback (GstBus */*bus*/, GstMessage *message, gpointer user_data)
{
    Widget* widget = static_cast<Widget*>(user_data);

    if (gst_is_wayland_display_handle_need_context_message (message)) {
      GstContext *context;
      qDebug() << "Need Context";

      QPlatformNativeInterface *native =
              QGuiApplication::platformNativeInterface();
      struct wl_display *display_handle = (struct wl_display *)
              native->nativeResourceForWindow("display", NULL);

      context = gst_wayland_display_handle_context_new (display_handle);
      gst_element_set_context (GST_ELEMENT (GST_MESSAGE_SRC (message)), context);

      goto drop;
    } else if (gst_is_video_overlay_prepare_window_handle_message (message)) {
        qDebug() << "Prepare window handle";

      QPlatformNativeInterface *native =
              QGuiApplication::platformNativeInterface();
      struct wl_surface *surface = static_cast<struct wl_surface *>(
                  native->nativeResourceForWindow("surface", widget->windowHandle()));

      gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (GST_MESSAGE_SRC (message)), (guintptr) surface);
      gst_video_overlay_set_render_rectangle (GST_VIDEO_OVERLAY (GST_MESSAGE_SRC (message)), widget->x(), widget->y(), widget->width(), widget->height());

      goto drop;
    }

    return GST_BUS_PASS;

  drop:
    gst_message_unref (message);
    return GST_BUS_DROP;

}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    GstElement *source;
    GstElement *sink;
    _pipeline = gst_pipeline_new ("waylandsinktest");

    source = gst_element_factory_make("videotestsrc", "mysource");
    sink = gst_element_factory_make("waylandsink", "myvideosink");

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

    gst_element_set_state (_pipeline, GST_STATE_PLAYING);

}

Widget::~Widget()
{

}
