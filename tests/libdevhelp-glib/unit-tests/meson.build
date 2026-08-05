# SPDX-FileCopyrightText: 2026 Sébastien Wilmet <swilmet@gnome.org>
# SPDX-License-Identifier: GPL-3.0-or-later

unit_tests = [
  'test-completion',
  'test-link',
]

foreach test_name : unit_tests
  full_name = 'libdevhelp-glib-' + test_name

  test_exe = executable(
    full_name,
    test_name + '.c',
    dependencies: LIBDEVHELP_GLIB_SHARED_LIB_DEP
  )

  test(full_name, test_exe)
endforeach
