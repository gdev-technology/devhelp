/* SPDX-FileCopyrightText: 2026 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "dh-web-view-zoom-controller.h"

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
};

G_DEFINE_TYPE_WITH_PRIVATE (DhWebViewZoomController, dh_web_view_zoom_controller, G_TYPE_OBJECT)

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
