/* SPDX-FileCopyrightText: 2026 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <webkit2/webkit2.h>

G_BEGIN_DECLS

#define DH_TYPE_WEB_VIEW_SEARCH_CONTROLLER             (dh_web_view_search_controller_get_type ())
#define DH_WEB_VIEW_SEARCH_CONTROLLER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), DH_TYPE_WEB_VIEW_SEARCH_CONTROLLER, DhWebViewSearchController))
#define DH_WEB_VIEW_SEARCH_CONTROLLER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), DH_TYPE_WEB_VIEW_SEARCH_CONTROLLER, DhWebViewSearchControllerClass))
#define DH_IS_WEB_VIEW_SEARCH_CONTROLLER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DH_TYPE_WEB_VIEW_SEARCH_CONTROLLER))
#define DH_IS_WEB_VIEW_SEARCH_CONTROLLER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), DH_TYPE_WEB_VIEW_SEARCH_CONTROLLER))
#define DH_WEB_VIEW_SEARCH_CONTROLLER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), DH_TYPE_WEB_VIEW_SEARCH_CONTROLLER, DhWebViewSearchControllerClass))

typedef struct _DhWebViewSearchController         DhWebViewSearchController;
typedef struct _DhWebViewSearchControllerClass    DhWebViewSearchControllerClass;
typedef struct _DhWebViewSearchControllerPrivate  DhWebViewSearchControllerPrivate;

struct _DhWebViewSearchController {
        GObject parent;
        DhWebViewSearchControllerPrivate *priv;
};

struct _DhWebViewSearchControllerClass {
        GObjectClass parent_class;
};

GType                           dh_web_view_search_controller_get_type          (void);

DhWebViewSearchController *     dh_web_view_search_controller_new               (WebKitWebView *web_view);

G_END_DECLS
