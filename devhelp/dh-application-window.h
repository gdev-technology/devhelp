/* SPDX-FileCopyrightText: 2018 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <glib.h>
#include <devhelp/dh-notebook.h>
#include <devhelp/dh-sidebar.h>

G_BEGIN_DECLS

void    dh_application_window_bind_sidebar_and_notebook         (DhSidebar  *sidebar,
                                                                 DhNotebook *notebook);

G_END_DECLS
