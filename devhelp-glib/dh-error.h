/* SPDX-FileCopyrightText: 2002 CodeFactory AB
 * SPDX-FileCopyrightText: 2002 Mikael Hallendal <micke@imendio.com>
 * SPDX-FileCopyrightText: 2018-2026 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <glib.h>

G_BEGIN_DECLS

#define DH_ERROR (dh_error_quark ())

/**
 * DhError:
 * @DH_ERROR_MALFORMED_BOOK: Malformed book.
 */
typedef enum {
        DH_ERROR_MALFORMED_BOOK,
} DhError;

GQuark dh_error_quark (void);

G_END_DECLS
