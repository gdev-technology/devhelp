Devhelp
=======

The Devhelp web page:

https://github.com/gdev-technology/devhelp

Dependencies
------------

- GLib
- GTK 3
- WebKitGTK
- [libgedit-amtk](https://gedit-text-editor.org/technology.html)
- gsettings-desktop-schemas

Description
-----------

Devhelp is a developer tool for browsing and searching API documentation.
It provides an easy way to navigate through libraries and to search by
function, struct, or macro.

The documentation must be installed locally, so an internet connection is
not needed to use Devhelp.

Devhelp works natively with GTK-Doc, so the GTK and GNOME libraries are
well supported. But other development platforms can be supported as well,
as long as the API documentation is available in HTML and a `*.devhelp2`
index file is generated.

Other developer tools can interact with the Devhelp application. As such,
plugins are available for different text editors (Emacs, Geany, Vim, …).

Re-usable code is also available to integrate Devhelp features into an
IDE.

Integration with other developer tools
--------------------------------------

Devhelp provides some command line options, such as `--search`. A text editor
plugin can for example launch the command `devhelp --search function_name` when
a keyboard shortcut is pressed, with the `function_name` under the cursor.

Devhelp also provides re-usable code, to integrate the features inside an IDE.

For the `--search` command line option, see the class description of
DhKeywordModel, the search string supports additional features useful for IDEs
or other developer tools.

Other documentation
-------------------

- There is user documentation written in the Mallard format in the `help/C/`
  directory. You can open that documentation with the `yelp help/C/` command,
  or pressing F1 in the Devhelp application.

- For the re-usable code that Devhelp provides, there are API reference manuals
  built with GTK-Doc, see the `gtk_doc` build option.
