# SPDX-FileCopyrightText: 2018-2026 Sébastien Wilmet <swilmet@gnome.org>
# SPDX-License-Identifier: GPL-3.0-or-later

devhelp_app_sources = [
  'dh-app.c',
  'dh-main.c',
  'dh-preferences.c',
  'dh-settings-app.c',
  'dh-util-app.c',
  'dh-window.c'
]

devhelp_app_sources += GNOME.compile_resources(
  'dh-resources',
  'dh.gresource.xml'
)

executable(
  'devhelp',
  devhelp_app_sources,
  dependencies: [DEPS_FOR_DEVHELP_APP, LIBDEVHELP_STATIC_DEP],
  install: true
)
