/* SPDX-FileCopyrightText: 2001-2002 Mikael Hallendal <micke@imendio.com>
 * SPDX-FileCopyrightText: 2004,2008 Imendio AB
 * SPDX-FileCopyrightText: 2015-2026 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <gio/gio.h>

G_BEGIN_DECLS

void            dh_utils_queue_concat                   (GQueue *q1,
                                                         GQueue *q2);

GFile *         dh_utils_get_index_file                 (GFile *book_directory);

G_END_DECLS
