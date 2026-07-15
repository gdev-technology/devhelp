/* SPDX-FileCopyrightText: 2026 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <webkit2/webkit2.h>

G_BEGIN_DECLS

#define DH_TYPE_WEB_VIEW_ZOOM_CONTROLLER             (dh_web_view_zoom_controller_get_type ())
#define DH_WEB_VIEW_ZOOM_CONTROLLER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), DH_TYPE_WEB_VIEW_ZOOM_CONTROLLER, DhWebViewZoomController))
#define DH_WEB_VIEW_ZOOM_CONTROLLER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), DH_TYPE_WEB_VIEW_ZOOM_CONTROLLER, DhWebViewZoomControllerClass))
#define DH_IS_WEB_VIEW_ZOOM_CONTROLLER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DH_TYPE_WEB_VIEW_ZOOM_CONTROLLER))
#define DH_IS_WEB_VIEW_ZOOM_CONTROLLER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), DH_TYPE_WEB_VIEW_ZOOM_CONTROLLER))
#define DH_WEB_VIEW_ZOOM_CONTROLLER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), DH_TYPE_WEB_VIEW_ZOOM_CONTROLLER, DhWebViewZoomControllerClass))

typedef struct _DhWebViewZoomController         DhWebViewZoomController;
typedef struct _DhWebViewZoomControllerClass    DhWebViewZoomControllerClass;
typedef struct _DhWebViewZoomControllerPrivate  DhWebViewZoomControllerPrivate;

struct _DhWebViewZoomController {
        GObject parent;
        DhWebViewZoomControllerPrivate *priv;
};

struct _DhWebViewZoomControllerClass {
        GObjectClass parent_class;
};

GType                           dh_web_view_zoom_controller_get_type            (void);

DhWebViewZoomController *       dh_web_view_zoom_controller_new                 (WebKitWebView *web_view);

gboolean                        dh_web_view_zoom_controller_can_zoom_in         (DhWebViewZoomController *zoom_controller);

gboolean                        dh_web_view_zoom_controller_can_zoom_out        (DhWebViewZoomController *zoom_controller);

gboolean                        dh_web_view_zoom_controller_can_reset_zoom      (DhWebViewZoomController *zoom_controller);

void                            dh_web_view_zoom_controller_zoom_in             (DhWebViewZoomController *zoom_controller);

void                            dh_web_view_zoom_controller_zoom_out            (DhWebViewZoomController *zoom_controller);

void                            dh_web_view_zoom_controller_reset_zoom          (DhWebViewZoomController *zoom_controller);

G_END_DECLS
