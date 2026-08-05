# SPDX-FileCopyrightText: 2018-2026 Sébastien Wilmet <swilmet@gnome.org>
# SPDX-License-Identifier: GPL-3.0-or-later

libdevhelp_public_headers = [
  'devhelp.h',
  'dh-application-window.h',
  'dh-book.h',
  'dh-book-list.h',
  'dh-book-list-builder.h',
  'dh-book-list-directory.h',
  'dh-book-tree.h',
  'dh-init.h',
  'dh-keyword-model.h',
  'dh-notebook.h',
  'dh-profile.h',
  'dh-profile-builder.h',
  'dh-search-bar.h',
  'dh-settings.h',
  'dh-settings-builder.h',
  'dh-sidebar.h',
  'dh-tab.h',
  'dh-tab-label.h',
  'dh-web-view.h',
  'dh-web-view-search-controller.h',
  'dh-web-view-zoom-controller.h',
]

libdevhelp_public_c_files = [
  'dh-application-window.c',
  'dh-book.c',
  'dh-book-list.c',
  'dh-book-list-builder.c',
  'dh-book-list-directory.c',
  'dh-book-tree.c',
  'dh-init.c',
  'dh-keyword-model.c',
  'dh-notebook.c',
  'dh-profile.c',
  'dh-profile-builder.c',
  'dh-search-bar.c',
  'dh-settings.c',
  'dh-settings-builder.c',
  'dh-sidebar.c',
  'dh-tab.c',
  'dh-tab-label.c',
  'dh-web-view.c',
  'dh-web-view-search-controller.c',
  'dh-web-view-zoom-controller.c',
]

libdevhelp_private_c_files = [
  'dh-book-list-simple.c',
  'dh-parser.c',
  'dh-search-context.c',
  'dh-util-lib.c'
]

libdevhelp_enum_types = GNOME.mkenums_simple(
  'dh-enum-types',
  sources: libdevhelp_public_headers,
)

libdevhelp_static_lib = static_library(
  'devhelp-static',
  [libdevhelp_public_c_files,
   libdevhelp_private_c_files,
   libdevhelp_enum_types],
  include_directories: ROOT_INCLUDE_DIR,
  dependencies: [ALL_DEPS_FOR_LIBDEVHELP, LIBDEVHELP_GLIB_STATIC_DEP],
)

LIBDEVHELP_STATIC_DEP = declare_dependency(
  include_directories: ROOT_INCLUDE_DIR,
  link_with: libdevhelp_static_lib,
  sources: libdevhelp_enum_types[1],
  dependencies: ALL_DEPS_FOR_LIBDEVHELP,
)

# Do not install it, it's for GTK-Doc.
libdevhelp_shared_lib = shared_library(
  'devhelp-shared',
  dependencies: ALL_DEPS_FOR_LIBDEVHELP,
  link_whole: libdevhelp_static_lib,
)

LIBDEVHELP_SHARED_LIB_DEP = declare_dependency(
  link_with: libdevhelp_shared_lib,
  dependencies: ALL_DEPS_FOR_LIBDEVHELP,
)
