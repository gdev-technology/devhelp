# SPDX-FileCopyrightText: 2026 Sébastien Wilmet <swilmet@gnome.org>
# SPDX-License-Identifier: GPL-3.0-or-later

unit_tests = [
  'test-completion',
]

foreach test_name : unit_tests
  test_exe = executable(
    test_name,
    test_name + '.c',
    dependencies: LIBDEVHELP_GLIB_STATIC_DEP
  )
  test(test_name, test_exe)
endforeach
