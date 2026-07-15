/* SPDX-FileCopyrightText: 2026 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "dh-web-view-zoom-controller.h"
#include <math.h>

/**
 * SECTION:dh-web-view-zoom-controller
 * @Title: DhWebViewZoomController
 * @Short_description: #WebKitWebView zoom controller
 *
 * #WebKitWebView zoom controller.
 */

struct _DhWebViewZoomControllerPrivate {
        /* Weak ref */
        WebKitWebView *web_view;

        gdouble total_scroll_delta_y;
};

static const gdouble zoom_levels[] = {
        0.5,            /* 50% */
        0.8408964152,   /* 75% */
        1.0,            /* 100% */
        1.1892071149,   /* 125% */
        1.4142135623,   /* 150% */
        1.6817928304,   /* 175% */
        2.0,            /* 200% */
        2.8284271247,   /* 300% */
        4.0             /* 400% */
};

static const guint n_zoom_levels = G_N_ELEMENTS (zoom_levels);

#define DEFAULT_ZOOM_LEVEL_INDEX (2)
#define DEFAULT_ZOOM_LEVEL_VALUE (zoom_levels[DEFAULT_ZOOM_LEVEL_INDEX])

G_DEFINE_TYPE_WITH_PRIVATE (DhWebViewZoomController, dh_web_view_zoom_controller, G_TYPE_OBJECT)

static gint
get_current_zoom_level_index (DhWebViewZoomController *zoom_controller)
{
        gdouble zoom_level;
        gdouble previous;
        guint i;

        if (zoom_controller->priv->web_view == NULL)
        {
                return DEFAULT_ZOOM_LEVEL_INDEX;
        }

        zoom_level = webkit_web_view_get_zoom_level (zoom_controller->priv->web_view);

        previous = zoom_levels[0];
        for (i = 1; i < n_zoom_levels; i++) {
                gdouble current = zoom_levels[i];
                gdouble mean = sqrt (previous * current);

                if (zoom_level <= mean)
                        return i - 1;

                previous = current;
        }

        return n_zoom_levels - 1;
}

static void
bump_zoom_level (DhWebViewZoomController *zoom_controller,
                 gint                     bump_amount)
{
        gint zoom_level_index;
        gdouble new_zoom_level;

        if (zoom_controller->priv->web_view == NULL ||
            bump_amount == 0)
                return;

        zoom_level_index = get_current_zoom_level_index (zoom_controller) + bump_amount;
        zoom_level_index = CLAMP (zoom_level_index, 0, (gint)n_zoom_levels - 1);
        new_zoom_level = zoom_levels[zoom_level_index];

        webkit_web_view_set_zoom_level (zoom_controller->priv->web_view, new_zoom_level);
}

#if 0
static gboolean
dh_web_view_scroll_event (GtkWidget      *widget,
                          GdkEventScroll *scroll_event)
{
        DhWebView *view = DH_WEB_VIEW (widget);
        gdouble delta_y;

        if ((scroll_event->state & GDK_CONTROL_MASK) == 0)
                goto chain_up;

        switch (scroll_event->direction) {
                case GDK_SCROLL_UP:
                        bump_zoom_level (view, 1);
                        return GDK_EVENT_STOP;

                case GDK_SCROLL_DOWN:
                        bump_zoom_level (view, -1);
                        return GDK_EVENT_STOP;

                case GDK_SCROLL_LEFT:
                case GDK_SCROLL_RIGHT:
                        break;

                case GDK_SCROLL_SMOOTH:
                        gdk_event_get_scroll_deltas ((GdkEvent *)scroll_event, NULL, &delta_y);
                        view->priv->total_scroll_delta_y += delta_y;

                        /* Avoiding direct float comparison.
                         * -1 and 1 are the thresholds for bumping the zoom level,
                         * which can be adjusted for taste.
                         */
                        if ((gint)view->priv->total_scroll_delta_y <= -1) {
                                view->priv->total_scroll_delta_y = 0.0;
                                bump_zoom_level (view, 1);
                        } else if ((gint)view->priv->total_scroll_delta_y >= 1) {
                                view->priv->total_scroll_delta_y = 0.0;
                                bump_zoom_level (view, -1);
                        }
                        return GDK_EVENT_STOP;

                default:
                        g_warn_if_reached ();
        }

chain_up:
        if (GTK_WIDGET_CLASS (dh_web_view_parent_class)->scroll_event == NULL)
                return GDK_EVENT_PROPAGATE;

        return GTK_WIDGET_CLASS (dh_web_view_parent_class)->scroll_event (widget, scroll_event);
}
#endif

static void
set_web_view (DhWebViewZoomController *zoom_controller,
              WebKitWebView           *web_view)
{
        g_assert (zoom_controller->priv->web_view == NULL);
        g_set_weak_pointer (&zoom_controller->priv->web_view, web_view);
}

static void
dh_web_view_zoom_controller_dispose (GObject *object)
{
        DhWebViewZoomController *zoom_controller = DH_WEB_VIEW_ZOOM_CONTROLLER (object);

        g_clear_weak_pointer (&zoom_controller->priv->web_view);

        G_OBJECT_CLASS (dh_web_view_zoom_controller_parent_class)->dispose (object);
}

static void
dh_web_view_zoom_controller_class_init (DhWebViewZoomControllerClass *klass)
{
        GObjectClass *object_class = G_OBJECT_CLASS (klass);

        object_class->dispose = dh_web_view_zoom_controller_dispose;
}

static void
dh_web_view_zoom_controller_init (DhWebViewZoomController *zoom_controller)
{
        zoom_controller->priv = dh_web_view_zoom_controller_get_instance_private (zoom_controller);
        zoom_controller->priv->total_scroll_delta_y = 0.0;
}

/**
 * dh_web_view_zoom_controller_new:
 * @web_view: a #WebKitWebView.
 *
 * Returns: (transfer full): a new #DhWebViewZoomController.
 */
DhWebViewZoomController *
dh_web_view_zoom_controller_new (WebKitWebView *web_view)
{
        DhWebViewZoomController *zoom_controller;

        g_return_val_if_fail (WEBKIT_IS_WEB_VIEW (web_view), NULL);

        zoom_controller = g_object_new (DH_TYPE_WEB_VIEW_ZOOM_CONTROLLER, NULL);

        set_web_view (zoom_controller, web_view);

        return zoom_controller;
}

/**
 * dh_web_view_zoom_controller_can_zoom_in:
 * @zoom_controller: a #DhWebViewZoomController.
 *
 * Returns: whether calling dh_web_view_zoom_controller_zoom_in() will have an
 *   effect.
 */
gboolean
dh_web_view_zoom_controller_can_zoom_in (DhWebViewZoomController *zoom_controller)
{
        gint zoom_level_index;

        g_return_val_if_fail (DH_IS_WEB_VIEW_ZOOM_CONTROLLER (zoom_controller), FALSE);

        if (zoom_controller->priv->web_view == NULL)
                return FALSE;

        zoom_level_index = get_current_zoom_level_index (zoom_controller);
        return zoom_level_index < ((gint)n_zoom_levels - 1);
}

/**
 * dh_web_view_zoom_controller_can_zoom_out:
 * @zoom_controller: a #DhWebViewZoomController.
 *
 * Returns: whether calling dh_web_view_zoom_controller_zoom_out() will have an
 *   effect.
 */
gboolean
dh_web_view_zoom_controller_can_zoom_out (DhWebViewZoomController *zoom_controller)
{
        gint zoom_level_index;

        g_return_val_if_fail (DH_IS_WEB_VIEW_ZOOM_CONTROLLER (zoom_controller), FALSE);

        if (zoom_controller->priv->web_view == NULL)
                return FALSE;

        zoom_level_index = get_current_zoom_level_index (zoom_controller);
        return zoom_level_index > 0;
}

/**
 * dh_web_view_zoom_controller_can_reset_zoom:
 * @zoom_controller: a #DhWebViewZoomController.
 *
 * Returns: whether calling dh_web_view_zoom_controller_reset_zoom() will have
 *   an effect.
 */
gboolean
dh_web_view_zoom_controller_can_reset_zoom (DhWebViewZoomController *zoom_controller)
{
        gint zoom_level_index;

        g_return_val_if_fail (DH_IS_WEB_VIEW_ZOOM_CONTROLLER (zoom_controller), FALSE);

        if (zoom_controller->priv->web_view == NULL)
                return FALSE;

        zoom_level_index = get_current_zoom_level_index (zoom_controller);
        return zoom_level_index != DEFAULT_ZOOM_LEVEL_INDEX;
}

/**
 * dh_web_view_zoom_controller_zoom_in:
 * @zoom_controller: a #DhWebViewZoomController.
 *
 * Makes the text larger.
 */
void
dh_web_view_zoom_controller_zoom_in (DhWebViewZoomController *zoom_controller)
{
        g_return_if_fail (DH_IS_WEB_VIEW_ZOOM_CONTROLLER (zoom_controller));

        bump_zoom_level (zoom_controller, 1);
}

/**
 * dh_web_view_zoom_controller_zoom_out:
 * @zoom_controller: a #DhWebViewZoomController.
 *
 * Makes the text smaller.
 */
void
dh_web_view_zoom_controller_zoom_out (DhWebViewZoomController *zoom_controller)
{
        g_return_if_fail (DH_IS_WEB_VIEW_ZOOM_CONTROLLER (zoom_controller));

        bump_zoom_level (zoom_controller, -1);
}

/**
 * dh_web_view_zoom_controller_reset_zoom:
 * @zoom_controller: a #DhWebViewZoomController.
 *
 * Reset the text size to the normal size.
 */
void
dh_web_view_zoom_controller_reset_zoom (DhWebViewZoomController *zoom_controller)
{
        g_return_if_fail (DH_IS_WEB_VIEW_ZOOM_CONTROLLER (zoom_controller));

        if (zoom_controller->priv->web_view == NULL)
                return;

        webkit_web_view_set_zoom_level (zoom_controller->priv->web_view, DEFAULT_ZOOM_LEVEL_VALUE);
}
