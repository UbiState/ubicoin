
Debian
====================
This directory contains files used to package ubicoind/ubicoin-qt
for Debian-based Linux systems. If you compile ubicoind/ubicoin-qt yourself, there are some useful files here.

## ubicoin: URI support ##


ubicoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ubicoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ubicoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/ubicoin128.png` to `/usr/share/pixmaps`

ubicoin-qt.protocol (KDE)

