# SPDX-FileCopyrightText: 2026 Sébastien Wilmet <swilmet@gnome.org>
# SPDX-License-Identifier: GPL-3.0-or-later

libdevhelp_glib_public_c_files = [
  'dh-completion.c',
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
