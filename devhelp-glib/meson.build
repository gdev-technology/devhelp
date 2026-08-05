# SPDX-FileCopyrightText: 2026 Sébastien Wilmet <swilmet@gnome.org>
# SPDX-License-Identifier: GPL-3.0-or-later

libdevhelp_glib_public_c_files = [
  'dh-completion.c',
  'dh-link.c',
]

libdevhelp_glib_static_lib = static_library(
  'devhelp-glib-static',
  libdevhelp_glib_public_c_files,
  include_directories: ROOT_INCLUDE_DIR,
  dependencies: PUBLIC_DEPS_FOR_LIBDEVHELP_GLIB,
)

LIBDEVHELP_GLIB_STATIC_DEP = declare_dependency(
  include_directories: ROOT_INCLUDE_DIR,
  link_with: libdevhelp_glib_static_lib,
  dependencies: PUBLIC_DEPS_FOR_LIBDEVHELP_GLIB,
)

# Do not install it, it's for internal use.
libdevhelp_glib_shared_lib = shared_library(
  'devhelp-glib-shared',
  dependencies: PUBLIC_DEPS_FOR_LIBDEVHELP_GLIB,
  link_whole: libdevhelp_glib_static_lib,
)

LIBDEVHELP_GLIB_SHARED_LIB_DEP = declare_dependency(
  link_with: libdevhelp_glib_shared_lib,
  dependencies: PUBLIC_DEPS_FOR_LIBDEVHELP_GLIB,
  include_directories: ROOT_INCLUDE_DIR,
)
