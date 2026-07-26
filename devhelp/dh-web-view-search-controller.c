/* SPDX-FileCopyrightText: 2026 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "dh-web-view-search-controller.h"

/**
 * SECTION:dh-web-view-search-controller
 * @Title: DhWebViewSearchController
 * @Short_description: #WebKitWebView search controller
 *
 * #WebKitWebView search controller providing a more convenient API (for Devhelp
 * needs) on top of #WebKitFindController.
 */

struct _DhWebViewSearchControllerPrivate {
        /* Weak ref */
        WebKitWebView *web_view;

        gchar *search_text;
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
        DhWebViewSearchController *search_controller = DH_WEB_VIEW_SEARCH_CONTROLLER (object);

        g_free (search_controller->priv->search_text);

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

/**
 * dh_web_view_search_controller_set_search_text:
 * @search_controller: a #DhWebViewSearchController.
 * @search_text: (nullable): the search string, or %NULL.
 *
 * Sets the text to search.
 *
 * If @search_text is %NULL or is the empty string, it cancels the search.
 */
void
dh_web_view_search_controller_set_search_text (DhWebViewSearchController *search_controller,
                                               const gchar               *search_text)
{
        WebKitFindController *find_controller;

        g_return_if_fail (DH_IS_WEB_VIEW_SEARCH_CONTROLLER (search_controller));

        if (search_controller->priv->web_view == NULL)
                return;

        if (g_strcmp0 (search_controller->priv->search_text, search_text) == 0)
                return;

        g_free (search_controller->priv->search_text);
        search_controller->priv->search_text = g_strdup (search_text);

        find_controller = webkit_web_view_get_find_controller (search_controller->priv->web_view);

        if (search_text != NULL && search_text[0] != '\0') {
                /* If webkit_find_controller_search() is called a second time
                 * with the same parameters it's not a NOP, it launches a new
                 * search, apparently, which ruins search_next() and
                 * search_previous(). So we must call it only once for the same
                 * search string.
                 */
                webkit_find_controller_search (find_controller,
                                               search_text,
                                               WEBKIT_FIND_OPTIONS_WRAP_AROUND |
                                               WEBKIT_FIND_OPTIONS_CASE_INSENSITIVE,
                                               G_MAXUINT);
        } else {
                /* It's fine to call it several times. But unfortunately it
                 * doesn't change the WebKitFindController:text property. So we
                 * must store our own search_text.
                 */
                webkit_find_controller_search_finish (find_controller);
        }
}

/**
 * dh_web_view_search_controller_search_next:
 * @search_controller: a #DhWebViewSearchController.
 *
 * Go to the next occurrence.
 *
 * This function immediately returns if there is no text to search.
 */
void
dh_web_view_search_controller_search_next (DhWebViewSearchController *search_controller)
{
        WebKitFindController *find_controller;

        g_return_if_fail (DH_IS_WEB_VIEW_SEARCH_CONTROLLER (search_controller));

        if (search_controller->priv->web_view == NULL)
                return;

        if (search_controller->priv->search_text == NULL ||
            search_controller->priv->search_text[0] == '\0')
                return;

        find_controller = webkit_web_view_get_find_controller (search_controller->priv->web_view);
        webkit_find_controller_search_next (find_controller);
}

/**
 * dh_web_view_search_controller_search_previous:
 * @search_controller: a #DhWebViewSearchController.
 *
 * Go to the previous occurrence.
 *
 * This function immediately returns if there is no text to search.
 */
void
dh_web_view_search_controller_search_previous (DhWebViewSearchController *search_controller)
{
        WebKitFindController *find_controller;

        g_return_if_fail (DH_IS_WEB_VIEW_SEARCH_CONTROLLER (search_controller));

        if (search_controller->priv->web_view == NULL)
                return;

        if (search_controller->priv->search_text == NULL ||
            search_controller->priv->search_text[0] == '\0')
                return;

        find_controller = webkit_web_view_get_find_controller (search_controller->priv->web_view);
        webkit_find_controller_search_previous (find_controller);
}
