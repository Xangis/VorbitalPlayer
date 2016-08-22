VorbitalPlayer
==============

A music player for Linux and Windows with MP3, OGG, and WAV support. It was
originally released on http://zetacentauri.com and then vorbitalplayer.com and
via the Ubuntu Software Center.

![Vorbital Player Screenshot](https://github.com/Xangis/VorbitalPlayer/blob/master/images/Vorbital4.png)

The Vorbital Player was originally written using wxWidgets, but has been ported
to Qt due to some multiplatform portability and consistency annoyances with
wxWidgets. It is written in C++ and uses a number of libraries for file format
support (mpg123, libsndfile, libogg, libvorbis, libwavpack, etc.)

### Building on Windows

Building for Windows will be a nuisance because you will have to set paths to
all of the various audio libraries (the Windows build isn't as well-maintained
as the Linux build, and the Qt version hasn't been released on Windows yet). If
you just want the app, an installable version of Vorbital 4.0 for Windows is
available in the installer folder.

#### These libraries were used to build version 4.1 on Windows:

PortAudio ???
libogg version 1.3.2
libvorbis 1.3.5
libsndfile 1.0.27
Qt 5.7
wavpack version 4.80.0
libmpg123 version 1.14.2 [should be updated to 1.23.4]

#### These libraries were used to build version 4.0 on Windows:

OpenAL version 6.14.357.24.            
wrap_oal.dll version 2.2.0.5.            
libogg version 1.3.0.            
libvorbis 1.3.3.          
libsndfile 1.0.25.          
wxWidgets 2.9.4.          
wavpack version 4.60.1.            
libmpg123 version 1.14.2.        

To build an installer for Windows, look in the /installer folder for NullSoft
Installer (NSIS) and InnoSetup projects. File paths may have changed, so you may
need to update them to build an installer.

### Building on Linux

To build on Linux, you will need Qt 5 and the following packages:

libsndfile-dev
libogg-dev
libvorbis-dev
libopenal-dev
libwavpack-dev
libmpg123-dev

Just do the standard "qmake" and then "make" to build.

### Changelog

Version 4.1 changes:

1. Switched Windows version fully over to Qt (4.0 was wxWidgets on Windows and Qt on Linux).
2. Updated ogg, vorbis, sndfile, and wavpack libraries.
3. Added loading of AlbumArtSmall.jpg as an album art fallback if Folder.jpg does not exist.
4. Album art displays larger.
5. Loading a folder now also loads everything in its subfolders.

What's new in version 4.0 of Vorbital Player:

1. Support for playing .mp3 files.
2. Support for displaying album art (if exists as Folder.jpg in the same folder).
3. The program now remembers the volume setting, shuffle setting, and last window size when you exit, restoring them next time the program runs.
4. Clicking the vorbitaplayer.com website link in the about box now tells you if there's a newer version of the software when you visit the site.
5. Fixed a bug that could cause the program to crash on exit.
6. Fixed a bug that could cause an item in the playlist to play twice in a row when double-clicked.
7. Now available for Ubuntu Linux.

What's new in version 3.1 of Vorbital:

1. Support for Audio Interchange File Format (.aif and .aiff) files.
2. Support for Apple SND (.snd) files.

What's new in version 3 of Vorbital:

1. Support for Wavpack (.wv) files.
2. Support for Wave (.wav) files.
3. User interface improvements.

What's new in version 2 of Vorbital:

1. Added "randomize" button.
2. Fixed function of pause button so it behaves as a pause rather than stop.
3. Added "load directory" button.
4. Playlist now supports drag-and-drop.
5. Volume control slider added.
6. Added "clear playlist" button.
7. Fixed a handful of bugs and oddities.
8. Add file button now supports multiple selections.
