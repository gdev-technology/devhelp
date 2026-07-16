/* SPDX-FileCopyrightText: 2002 CodeFactory AB
 * SPDX-FileCopyrightText: 2002 Mikael Hallendal <micke@imendio.com>
 * SPDX-FileCopyrightText: 2004-2008 Imendio AB
 * SPDX-FileCopyrightText: 2010 Lanedo GmbH
 * SPDX-FileCopyrightText: 2017-2026 Sébastien Wilmet <swilmet@gnome.org>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "config.h"
#include "dh-book.h"
#include <glib/gi18n-lib.h>
#include "dh-link.h"
#include "dh-parser.h"
#include "dh-util-lib.h"

/**
 * SECTION:dh-book
 * @Title: DhBook
 * @Short_description: A book, usually the documentation for one library
 *
 * A #DhBook usually contains the documentation for one library (or
 * application), for example GLib or GTK. A #DhBook corresponds to one index
 * file. An index file is a file with the extension `*.devhelp2`.
 */

typedef struct {
        GFile *index_file;

        gchar *id;
        gchar *title;
        gchar *language;

        /* The book tree of DhLink*. */
        GNode *tree;

        /* List of DhLink*. */
        GList *links;

        DhCompletion *completion;
} DhBookPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (DhBook, dh_book, G_TYPE_OBJECT);

static void
dh_book_dispose (GObject *object)
{
        DhBookPrivate *priv = dh_book_get_instance_private (DH_BOOK (object));

        g_clear_object (&priv->completion);

        G_OBJECT_CLASS (dh_book_parent_class)->dispose (object);
}

static void
dh_book_finalize (GObject *object)
{
        DhBookPrivate *priv = dh_book_get_instance_private (DH_BOOK (object));

        g_clear_object (&priv->index_file);
        g_free (priv->id);
        g_free (priv->title);
        g_free (priv->language);
        _dh_util_free_book_tree (priv->tree);
        g_list_free_full (priv->links, (GDestroyNotify)dh_link_unref);

        G_OBJECT_CLASS (dh_book_parent_class)->finalize (object);
}

static void
dh_book_class_init (DhBookClass *klass)
{
        GObjectClass *object_class = G_OBJECT_CLASS (klass);

        object_class->dispose = dh_book_dispose;
        object_class->finalize = dh_book_finalize;
}

static void
dh_book_init (DhBook *book)
{
}

/**
 * dh_book_new:
 * @index_file: the index file.
 *
 * Returns: (nullable): a new #DhBook object, or %NULL if parsing the index file
 *   failed.
 */
DhBook *
dh_book_new (GFile *index_file)
{
        DhBookPrivate *priv;
        DhBook *book;
        gchar *language = NULL;
        GError *error = NULL;

        g_return_val_if_fail (G_IS_FILE (index_file), NULL);

        book = g_object_new (DH_TYPE_BOOK, NULL);
        priv = dh_book_get_instance_private (book);

        priv->index_file = g_object_ref (index_file);

        /* Parse file storing contents in the book struct. */
        if (!_dh_parser_read_file (priv->index_file,
                                   &priv->title,
                                   &priv->id,
                                   &language,
                                   &priv->tree,
                                   &priv->links,
                                   &error)) {
                /* It's fine if the file doesn't exist, because
                 * DhBookListDirectory tries to create a DhBook for each
                 * possible index file in a certain book directory.
                 */
                if (error != NULL &&
                    !g_error_matches (error, G_IO_ERROR, G_IO_ERROR_NOT_FOUND)) {
                        gchar *parse_name;

                        parse_name = g_file_get_parse_name (priv->index_file);

                        g_warning ("Failed to read “%s”: %s",
                                   parse_name,
                                   error->message);

                        g_free (parse_name);
                }

                g_clear_error (&error);
                g_object_unref (book);
                return NULL;
        }

        /* Rewrite language, if any, including the prefix we want to use when
         * seeing it, to standarize how the language group is shown.
         * FIXME: maybe instead of a string, have a DhLanguage object which
         * canonicalizes the string.
         */
        _dh_util_ascii_strtitle (language);
        priv->language = (language != NULL ?
                          g_strdup_printf (_("Language: %s"), language) :
                          g_strdup (_("Language: Undefined")));
        g_free (language);

        return book;
}

/**
 * dh_book_get_index_file:
 * @book: a #DhBook.
 *
 * Returns: (transfer none): the index file.
 */
GFile *
dh_book_get_index_file (DhBook *book)
{
        DhBookPrivate *priv;

        g_return_val_if_fail (DH_IS_BOOK (book), NULL);

        priv = dh_book_get_instance_private (book);

        return priv->index_file;
}

/**
 * dh_book_get_id:
 * @book: a #DhBook.
 *
 * Gets the book ID. In the Devhelp index file format version 2, it is actually
 * the “name”, not the ID, but “book ID” is clearer, “book name” can be confused
 * with the title.
 *
 * Returns: the book ID.
 */
const gchar *
dh_book_get_id (DhBook *book)
{
        DhBookPrivate *priv;

        g_return_val_if_fail (DH_IS_BOOK (book), NULL);

        priv = dh_book_get_instance_private (book);

        return priv->id;
}

/**
 * dh_book_get_title:
 * @book: a #DhBook.
 *
 * Returns: the book title.
 */
const gchar *
dh_book_get_title (DhBook *book)
{
        DhBookPrivate *priv;

        g_return_val_if_fail (DH_IS_BOOK (book), NULL);

        priv = dh_book_get_instance_private (book);

        return priv->title;
}

/**
 * dh_book_get_language:
 * @book: a #DhBook.
 *
 * Returns: the programming language used in @book.
 */
const gchar *
dh_book_get_language (DhBook *book)
{
        DhBookPrivate *priv;

        g_return_val_if_fail (DH_IS_BOOK (book), NULL);

        priv = dh_book_get_instance_private (book);

        return priv->language;
}

/**
 * dh_book_get_links:
 * @book: a #DhBook.
 *
 * Returns: (element-type DhLink) (transfer none): the list of
 * <emphasis>all</emphasis> #DhLink's part of @book.
 */
GList *
dh_book_get_links (DhBook *book)
{
        DhBookPrivate *priv;

        g_return_val_if_fail (DH_IS_BOOK (book), NULL);

        priv = dh_book_get_instance_private (book);

        return priv->links;
}

/**
 * dh_book_get_tree:
 * @book: a #DhBook.
 *
 * Gets the general structure of the book, as a tree. The tree contains only
 * #DhLink's of type %DH_LINK_TYPE_BOOK or %DH_LINK_TYPE_PAGE. The other
 * #DhLink's are not contained in the tree. To have a list of
 * <emphasis>all</emphasis> #DhLink's part of the book, you need to call
 * dh_book_get_links().
 *
 * Returns: (transfer none): the tree of #DhLink's part of @book.
 */
GNode *
dh_book_get_tree (DhBook *book)
{
        DhBookPrivate *priv;

        g_return_val_if_fail (DH_IS_BOOK (book), NULL);

        priv = dh_book_get_instance_private (book);

        return priv->tree;
}

/**
 * dh_book_get_completion:
 * @book: a #DhBook.
 *
 * Returns: (transfer none): the #DhCompletion of @book.
 */
DhCompletion *
dh_book_get_completion (DhBook *book)
{
        DhBookPrivate *priv;

        g_return_val_if_fail (DH_IS_BOOK (book), NULL);

        priv = dh_book_get_instance_private (book);

        if (priv->completion == NULL) {
                GList *l;

                priv->completion = dh_completion_new ();

                for (l = priv->links; l != NULL; l = l->next) {
                        DhLink *link = l->data;
                        const gchar *str;

                        /* Do not provide completion for book titles. Normally
                         * the user doesn't need it, it's more convenient to
                         * choose a book with the DhBookTree.
                         */
                        if (dh_link_get_link_type (link) == DH_LINK_TYPE_BOOK)
                                continue;

                        str = dh_link_get_name (link);
                        dh_completion_add_string (priv->completion, str);
                }

                dh_completion_sort (priv->completion);
        }

        return priv->completion;
}

/**
 * dh_book_cmp_by_id:
 * @a: a #DhBook.
 * @b: a #DhBook.
 *
 * Compares the #DhBook's by their IDs, with g_ascii_strcasecmp().
 *
 * Returns: an integer less than, equal to, or greater than zero, if @a is <, ==
 * or > than @b.
 */
gint
dh_book_cmp_by_id (DhBook *a,
                   DhBook *b)
{
        DhBookPrivate *priv_a;
        DhBookPrivate *priv_b;

        if (a == NULL || b == NULL)
                return -1;

        priv_a = dh_book_get_instance_private (a);
        priv_b = dh_book_get_instance_private (b);

        if (priv_a->id == NULL || priv_b->id == NULL)
                return -1;

        return g_ascii_strcasecmp (priv_a->id, priv_b->id);
}

/**
 * dh_book_cmp_by_title:
 * @a: a #DhBook.
 * @b: a #DhBook.
 *
 * Compares the #DhBook's by their title.
 *
 * Returns: an integer less than, equal to, or greater than zero, if @a is <, ==
 * or > than @b.
 */
gint
dh_book_cmp_by_title (DhBook *a,
                      DhBook *b)
{
        DhBookPrivate *priv_a;
        DhBookPrivate *priv_b;

        if (a == NULL || b == NULL)
                return -1;

        priv_a = dh_book_get_instance_private (a);
        priv_b = dh_book_get_instance_private (b);

        if (priv_a->title == NULL || priv_b->title == NULL)
                return -1;

        return g_utf8_collate (priv_a->title, priv_b->title);
}
