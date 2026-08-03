# SPDX-FileCopyrightText: 2026 Sébastien Wilmet <swilmet@gnome.org>
# SPDX-License-Identifier: GPL-3.0-or-later

libdevhelp_glib_public_headers = [
  'devhelp-glib.h',
  'dh-completion.h',
]

libdevhelp_glib_public_c_files = [
  'dh-completion.c',
]

install_headers(
  libdevhelp_glib_public_headers,
  install_dir: get_option('includedir') / 'devhelp-@0@/devhelp-glib/'.format(LIBDEVHELP_API_VERSION),
)

libdevhelp_glib_static_lib = static_library(
  'devhelp-glib-static',
  libdevhelp_glib_public_c_files,
  pic: true, # libdevhelp_glib_static_lib is linked in a shared library.
  include_directories: ROOT_INCLUDE_DIR,
  dependencies: LIBDEVHELP_DEPS # TODO: depend only on GIO.
)

# For unit tests, to be able to test private functions.
LIBDEVHELP_GLIB_STATIC_DEP = declare_dependency(
  include_directories: ROOT_INCLUDE_DIR,
  link_with: libdevhelp_glib_static_lib,
  dependencies: LIBDEVHELP_DEPS # TODO: depend only on GIO.
)

symbol_map = meson.current_source_dir() / 'symbol.map'

libdevhelp_glib_shared_lib = shared_library(
  'devhelp-glib-@0@'.format(LIBDEVHELP_API_VERSION),
  link_whole: libdevhelp_glib_static_lib,
  link_args: '-Wl,--version-script,' + symbol_map,
  link_depends: symbol_map,
  soversion: SO_VERSION_FOR_LIBDEVHELP_GLIB,
  install: true
)

LIBDEVHELP_GLIB_SHARED_LIB_DEP = declare_dependency(
  include_directories: ROOT_INCLUDE_DIR,
  link_with: libdevhelp_glib_shared_lib,
  dependencies: LIBDEVHELP_DEPS # TODO: depend only on GIO.
)

# TODO: adapt more.
PKG_CONFIG.generate(
  filebase: 'libdevhelp-glib-@0@'.format(LIBDEVHELP_API_VERSION),
  name: meson.project_name(),
  description: meson.project_name(),
  libraries: libdevhelp_glib_shared_lib,
  subdirs: 'devhelp-@0@'.format(LIBDEVHELP_API_VERSION),
  requires: LIBDEVHELP_PUBLIC_DEPS,
  requires_private: LIBDEVHELP_PRIVATE_DEPS
)
