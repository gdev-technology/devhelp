/* SPDX-FileCopyrightText: 2001 Mikael Hallendal <micke@imendio.com>
 * SPDX-FileCopyrightText: 2004, 2008 Imendio AB
 * SPDX-FileCopyrightText: 2015-2026 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "dh-utils-glib.h"

/**
 * SECTION:dh-utils-glib
 * @Title: DhUtils
 * @Short_description: Utility functions
 *
 * Utility functions.
 */

/**
 * dh_utils_queue_concat:
 * @q1: a #GQueue.
 * @q2: (nullable): a #GQueue.
 *
 * Adds @q2 onto the end of @q1, and frees @q2.
 */
void
dh_utils_queue_concat (GQueue *q1,
                       GQueue *q2)
{
        g_return_if_fail (q1 != NULL);

        if (q2 == NULL)
                return;

        if (q1->head == NULL) {
                g_assert_cmpint (q1->length, ==, 0);
                g_assert (q1->tail == NULL);

                q1->head = q2->head;
                q1->tail = q2->tail;
                q1->length = q2->length;
        } else if (q2->head != NULL) {
                g_assert_cmpint (q1->length, >, 0);
                g_assert_cmpint (q2->length, >, 0);
                g_assert (q1->tail != NULL);
                g_assert (q2->tail != NULL);

                q1->tail->next = q2->head;
                q2->head->prev = q1->tail;

                q1->tail = q2->tail;
                q1->length += q2->length;
        } else {
                g_assert_cmpint (q2->length, ==, 0);
                g_assert (q2->tail == NULL);
        }

        q2->head = NULL;
        q2->tail = NULL;
        q2->length = 0;
        g_queue_free (q2);
}

/**
 * dh_utils_get_index_file:
 * @book_directory: a directory.
 *
 * Returns: (transfer full): the index file inside @book_directory. It is not
 *   guaranteed that the index file actually exists.
 */
GFile *
dh_utils_get_index_file (GFile *book_directory)
{
        gchar *directory_name;
        gchar *index_file_name;
        GFile *index_file;

        g_return_val_if_fail (G_IS_FILE (book_directory), NULL);

        directory_name = g_file_get_basename (book_directory);
        g_return_val_if_fail (directory_name != NULL, NULL);

        /* The name of the directory the index file is in and the name
         * of the index file (minus the extension) must match.
         */
        index_file_name = g_strconcat (directory_name, ".devhelp2", NULL);

        index_file = g_file_get_child (book_directory, index_file_name);

        g_free (directory_name);
        g_free (index_file_name);
        return index_file;
}
