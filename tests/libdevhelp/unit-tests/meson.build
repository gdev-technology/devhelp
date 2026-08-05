# SPDX-FileCopyrightText: 2018-2026 Sébastien Wilmet <swilmet@gnome.org>
# SPDX-License-Identifier: GPL-3.0-or-later

unit_tests = [
  'test-search-context',
]

foreach test_name : unit_tests
  full_name = 'libdevhelp-' + test_name

  test_exe = executable(
    full_name,
    test_name + '.c',
    dependencies: LIBDEVHELP_STATIC_DEP
  )

  test(full_name, test_exe)
endforeach
