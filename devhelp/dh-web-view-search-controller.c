/* SPDX-FileCopyrightText: 2026 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "dh-web-view-search-controller.h"

/**
 * SECTION:dh-web-view-search-controller
 * @Title: DhWebViewSearchController
 * @Short_description: #WebKitWebView search controller
 *
 * #WebKitWebView search controller.
 */

struct _DhWebViewSearchControllerPrivate {
        /* Weak ref */
        WebKitWebView *web_view;
};

G_DEFINE_TYPE_WITH_PRIVATE (DhWebViewSearchController, dh_web_view_search_controller, G_TYPE_OBJECT)

static void
set_web_view (DhWebViewSearchController *search_controller,
              WebKitWebView             *web_view)
{
        g_assert (search_controller->priv->web_view == NULL);
        g_set_weak_pointer (&search_controller->priv->web_view, web_view);
}

static void
dh_web_view_search_controller_dispose (GObject *object)
{
        DhWebViewSearchController *search_controller = DH_WEB_VIEW_SEARCH_CONTROLLER (object);

        g_clear_weak_pointer (&search_controller->priv->web_view);

        G_OBJECT_CLASS (dh_web_view_search_controller_parent_class)->dispose (object);
}

static void
dh_web_view_search_controller_finalize (GObject *object)
{

        G_OBJECT_CLASS (dh_web_view_search_controller_parent_class)->finalize (object);
}

static void
dh_web_view_search_controller_class_init (DhWebViewSearchControllerClass *klass)
{
        GObjectClass *object_class = G_OBJECT_CLASS (klass);

        object_class->dispose = dh_web_view_search_controller_dispose;
        object_class->finalize = dh_web_view_search_controller_finalize;
}

static void
dh_web_view_search_controller_init (DhWebViewSearchController *search_controller)
{
        search_controller->priv = dh_web_view_search_controller_get_instance_private (search_controller);
}

/**
 * dh_web_view_search_controller_new:
 * @web_view: a #WebKitWebView.
 *
 * Returns: (transfer full): a new #DhWebViewSearchController.
 */
DhWebViewSearchController *
dh_web_view_search_controller_new (WebKitWebView *web_view)
{
        DhWebViewSearchController *search_controller;

        g_return_val_if_fail (WEBKIT_IS_WEB_VIEW (web_view), NULL);

        search_controller = g_object_new (DH_TYPE_WEB_VIEW_SEARCH_CONTROLLER, NULL);

        set_web_view (search_controller, web_view);

        return search_controller;
}
