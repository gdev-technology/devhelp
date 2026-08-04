subdir('xml')

gtkdoc_module_name = 'libdevhelp-glib'
html_dir = get_option('prefix') / GNOME.gtkdoc_html_dir(gtkdoc_module_name)

glib_docpath = dependency('glib-2.0').get_variable(pkgconfig: 'prefix') / 'share/gtk-doc/html/glib'
gobject_docpath = dependency('gobject-2.0').get_variable(pkgconfig: 'prefix') / 'share/gtk-doc/html/gobject'
gio_docpath = dependency('gio-2.0').get_variable(pkgconfig: 'prefix') / 'share/gtk-doc/html/gio'

GNOME.gtkdoc(
  gtkdoc_module_name,
  main_xml: 'libdevhelp-glib-docs.xml',
  src_dir: include_directories('../../../devhelp-glib/'),
  dependencies: LIBDEVHELP_GLIB_SHARED_LIB_DEP,
  scan_args: ['--rebuild-types'],
  gobject_typesfile: 'libdevhelp-glib.types',
  fixxref_args: [
    '--html-dir=@0@'.format(html_dir),
    '--extra-dir=@0@'.format(glib_docpath),
    '--extra-dir=@0@'.format(gobject_docpath),
    '--extra-dir=@0@'.format(gio_docpath),
  ],
  install: true,
)
