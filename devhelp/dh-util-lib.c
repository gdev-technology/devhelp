/* SPDX-FileCopyrightText: 2001 Mikael Hallendal <micke@imendio.com>
 * SPDX-FileCopyrightText: 2004, 2008 Imendio AB
 * SPDX-FileCopyrightText: 2015-2026 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "config.h"
#include "dh-util-lib.h"
#include <devhelp-glib/dh-link.h>

/* We're only going to expect ASCII strings here, so there's no point in
 * playing with g_unichar_totitle() and such.
 * Note that we modify the string in place.
 */
void
_dh_util_ascii_strtitle (gchar *str)
{
        gboolean word_start;

        if (str == NULL)
                return;

        word_start = TRUE;
        while (*str != '\0') {
                if (g_ascii_isalpha (*str)) {
                        *str = (word_start ?
                                g_ascii_toupper (*str) :
                                g_ascii_tolower (*str));
                        word_start = FALSE;
                } else {
                        word_start = TRUE;
                }
                str++;
        }
}

static gboolean
unref_node_link (GNode    *node,
                 gpointer  data)
{
        dh_link_unref (node->data);
        return FALSE;
}

void
_dh_util_free_book_tree (GNode *book_tree)
{
        if (book_tree == NULL)
                return;

        g_node_traverse (book_tree,
                         G_IN_ORDER,
                         G_TRAVERSE_ALL,
                         -1,
                         unref_node_link,
                         NULL);

        g_node_destroy (book_tree);
}

static void
sidebar_link_selected_cb (DhSidebar  *sidebar,
                          DhLink     *link,
                          DhNotebook *notebook)
{
        gchar *uri;
        DhWebView *web_view;

        uri = dh_link_get_uri (link);
        if (uri == NULL)
                return;

        web_view = dh_notebook_get_active_web_view (notebook);
        if (web_view != NULL)
                webkit_web_view_load_uri (WEBKIT_WEB_VIEW (web_view), uri);

        g_free (uri);
}

static void
sync_active_web_view_uri_to_sidebar (DhNotebook *notebook,
                                     DhSidebar  *sidebar)
{
        DhWebView *web_view;
        const gchar *uri = NULL;

        g_signal_handlers_block_by_func (sidebar,
                                         sidebar_link_selected_cb,
                                         notebook);

        web_view = dh_notebook_get_active_web_view (notebook);
        if (web_view != NULL)
                uri = webkit_web_view_get_uri (WEBKIT_WEB_VIEW (web_view));
        if (uri != NULL)
                dh_sidebar_select_uri (sidebar, uri);

        g_signal_handlers_unblock_by_func (sidebar,
                                           sidebar_link_selected_cb,
                                           notebook);
}

static DhNotebook *
get_notebook_containing_web_view (DhWebView *web_view)
{
        GtkWidget *widget;

        widget = GTK_WIDGET (web_view);

        while (widget != NULL) {
                widget = gtk_widget_get_parent (widget);

                if (DH_IS_NOTEBOOK (widget))
                        return DH_NOTEBOOK (widget);
        }

        g_return_val_if_reached (NULL);
}

static void
web_view_load_changed_cb (DhWebView       *web_view,
                          WebKitLoadEvent  load_event,
                          DhSidebar       *sidebar)
{
        DhNotebook *notebook;

        notebook = get_notebook_containing_web_view (web_view);

        if (load_event == WEBKIT_LOAD_COMMITTED &&
            web_view == dh_notebook_get_active_web_view (notebook)) {
                sync_active_web_view_uri_to_sidebar (notebook, sidebar);
        }
}

static void
notebook_page_added_after_cb (GtkNotebook *notebook,
                              GtkWidget   *child,
                              guint        page_num,
                              DhSidebar   *sidebar)
{
        DhTab *tab;
        DhWebView *web_view;

        g_return_if_fail (DH_IS_TAB (child));

        tab = DH_TAB (child);
        web_view = dh_tab_get_web_view (tab);

        g_signal_connect_object (web_view,
                                 "load-changed",
                                 G_CALLBACK (web_view_load_changed_cb),
                                 sidebar,
                                 G_CONNECT_DEFAULT);
}

static void
notebook_switch_page_after_cb (DhNotebook *notebook,
                               GtkWidget  *new_page,
                               guint       new_page_num,
                               DhSidebar  *sidebar)
{
        sync_active_web_view_uri_to_sidebar (notebook, sidebar);
}

void
_dh_util_bind_sidebar_and_notebook (DhSidebar  *sidebar,
                                    DhNotebook *notebook)
{
        g_return_if_fail (DH_IS_SIDEBAR (sidebar));
        g_return_if_fail (DH_IS_NOTEBOOK (notebook));
        g_return_if_fail (dh_notebook_get_active_tab (notebook) == NULL);

        g_signal_connect_object (sidebar,
                                 "link-selected",
                                 G_CALLBACK (sidebar_link_selected_cb),
                                 notebook,
                                 G_CONNECT_DEFAULT);

        g_signal_connect_object (notebook,
                                 "page-added",
                                 G_CALLBACK (notebook_page_added_after_cb),
                                 sidebar,
                                 G_CONNECT_AFTER);

        g_signal_connect_object (notebook,
                                 "switch-page",
                                 G_CALLBACK (notebook_switch_page_after_cb),
                                 sidebar,
                                 G_CONNECT_AFTER);
}
