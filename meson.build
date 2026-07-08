# Convention:
# - Local variables in lower_case.
# - Global variables in UPPER_CASE.
# See: https://github.com/mesonbuild/meson/issues/2607

project(
  'devhelp', 'c',
  meson_version: '>= 0.59',
  version: '50.0',
  default_options: ['warning_level=2']
)

GNOME = import('gnome')
PKG_CONFIG = import('pkgconfig')
I18N = import('i18n')

SO_VERSION = 0

# API version, used for parallel installability.
LIBDEVHELP_API_VERSION = '3'

LIBDEVHELP_PUBLIC_DEPS = [
  dependency('gio-2.0', version: '>= 2.64'),
  dependency('gtk+-3.0', version: '>= 3.22'),
  dependency('webkit2gtk-4.1'),
]
LIBDEVHELP_PRIVATE_DEPS = [
  dependency('gsettings-desktop-schemas'),
]
LIBDEVHELP_DEPS = [
  LIBDEVHELP_PUBLIC_DEPS,
  LIBDEVHELP_PRIVATE_DEPS,
  meson.get_compiler('c').find_library('m'),
]

DEVHELP_APP_DEPS = [
  LIBDEVHELP_DEPS,
  dependency('libgedit-amtk-5'),
]

# config.h

config_data = configuration_data()
GETTEXT_PACKAGE_NAME = meson.project_name()
config_data.set_quoted('GETTEXT_PACKAGE', GETTEXT_PACKAGE_NAME)
config_data.set_quoted('DATADIR', get_option('prefix') / get_option('datadir'))
config_data.set_quoted('LOCALEDIR', get_option('prefix') / get_option('localedir'))
config_data.set_quoted('PACKAGE_VERSION', meson.project_version())
config_data.set_quoted('LIBDEVHELP_API_VERSION', LIBDEVHELP_API_VERSION)
config_data.set10('FLATPAK_BUILD', get_option('flatpak_build'))

configure_file(
  output: 'config.h',
  configuration: config_data
)

# Misc

# For #include <devhelp/something.h> or #include "config.h".
ROOT_INCLUDE_DIR = include_directories('.')

add_project_arguments(
  '-DG_LOG_DOMAIN="@0@"'.format(meson.project_name()),
  language: 'c'
)

#####
# CFLAGS
# Try to mimic the AX_COMPILER_FLAGS Autotools macro.
# Some flags are missing when using only the builtin warning_level meson option,
# even at the maximum level.
# The following warning_cflags suppose that warning_level=2.

warning_cflags = [
  '-fno-strict-aliasing',
  '-Wundef',
  '-Wnested-externs',
  '-Wwrite-strings',
  '-Wpointer-arith',
  '-Wmissing-declarations',
  '-Wmissing-prototypes',
  '-Wstrict-prototypes',
  '-Wredundant-decls',
  '-Wno-unused-parameter',
  '-Wno-missing-field-initializers',
  '-Wdeclaration-after-statement',
  '-Wformat=2',
  '-Wold-style-definition',
  '-Wcast-align',
  '-Wformat-nonliteral',
  '-Wformat-security',
  '-Wsign-compare',
  '-Wstrict-aliasing',
  '-Wshadow',
  '-Winline',
  '-Wpacked',
  '-Wmissing-format-attribute',
  '-Wmissing-noreturn',
  '-Winit-self',
  '-Wredundant-decls',
  '-Wmissing-include-dirs',
  '-Wunused-but-set-variable',
  '-Warray-bounds',
  '-Wimplicit-function-declaration',
  '-Wreturn-type',
  '-Wswitch-enum',
  '-Wswitch-default',
  '-Wduplicated-cond',
  '-Wduplicated-branches',
  '-Wlogical-op',
  '-Wrestrict',
  '-Wnull-dereference',
  '-Wjump-misses-init',
  '-Wdouble-promotion',

  # We are currently not actively porting the code.
  '-Wno-deprecated-declarations',
]

c_compiler = meson.get_compiler('c')
supported_warning_cflags = c_compiler.get_supported_arguments(warning_cflags)
add_project_arguments(supported_warning_cflags, language: 'c')
##### end CFLAGS

subdir('data')
subdir('plugins')
subdir('po')
subdir('help')
subdir('devhelp')
subdir('src')
subdir('unit-tests')

if get_option('gtk_doc')
  subdir('docs/reference')
endif

GNOME.post_install(
  glib_compile_schemas: true,
  gtk_update_icon_cache: true,
  update_desktop_database: true,
)

summary('Prefix', get_option('prefix'))
summary('API documentation', get_option('gtk_doc'))
summary('Flatpak build mode', get_option('flatpak_build'))
summary('Plugin for Emacs', get_option('plugin_emacs'))
summary('Plugin for Vim', get_option('plugin_vim'))
