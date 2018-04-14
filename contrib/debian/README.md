
Debian
====================
This directory contains files used to package gdrcoind/gdrcoin-qt
for Debian-based Linux systems. If you compile gdrcoind/gdrcoin-qt yourself, there are some useful files here.

## gdrcoin: URI support ##


gdrcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install gdrcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your gdrcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/gdrcoin128.png` to `/usr/share/pixmaps`

gdrcoin-qt.protocol (KDE)

