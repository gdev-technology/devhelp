gtkdocentities_conf_data = configuration_data()
gtkdocentities_conf_data.set('PACKAGE_NAME', 'libdevhelp-glib')
gtkdocentities_conf_data.set('PACKAGE_VERSION', meson.project_version())

gtkdocentities_filename = 'gtkdocentities.ent'

configure_file(
  input: gtkdocentities_filename + '.in',
  output: gtkdocentities_filename,
  configuration: gtkdocentities_conf_data
)
