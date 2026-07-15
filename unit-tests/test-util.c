/* SPDX-FileCopyrightText: 2017 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "devhelp/dh-util-lib.h"

static void
check_get_index_file (const gchar *book_directory_path,
                      const gchar *book_basename)
{
        GFile *book_directory;
        GFile *index_file;
        gchar *expected_basename;
        gchar *basename;
        gchar *expected_path;
        const gchar *path;

        book_directory = g_file_new_for_path (book_directory_path);
        index_file = _dh_util_get_index_file (book_directory);
        g_assert_nonnull (index_file);

        expected_basename = g_strconcat (book_basename, ".devhelp2", NULL);
        basename = g_file_get_basename (index_file);
        g_assert_cmpstr (basename, ==, expected_basename);

        expected_path = g_build_filename (book_directory_path, expected_basename, NULL);
        path = g_file_peek_path (index_file);
        g_assert_cmpstr (path, ==, expected_path);

        g_object_unref (book_directory);
        g_object_unref (index_file);
        g_free (expected_basename);
        g_free (basename);
        g_free (expected_path);
}

static void
test_get_index_file (void)
{
        check_get_index_file ("/usr/share/gtk-doc/html/glib", "glib");
        check_get_index_file ("/usr/share/gtk-doc/html/glib/", "glib");
        check_get_index_file ("/usr/share/gtk-doc/html/gtk3", "gtk3");
        check_get_index_file ("/usr/share/gtk-doc/html/gtk3/", "gtk3");
}

int
main (int    argc,
      char **argv)
{
        g_test_init (&argc, &argv, NULL);

        g_test_add_func ("/util/get_index_file", test_get_index_file);

        return g_test_run ();
}
