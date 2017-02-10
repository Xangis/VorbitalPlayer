NOTE: THIS SHOULD NOT BE BUILT USING VISUAL STUDIO. USE QT CREATOR.
      VISUAL STUDIO IS FOR DEBUGGING ONLY.

To debug on Visual Studio:

- Copy moc_*.cpp files from build output directory for the Qt Creator build. Rename them to have a
  leading underscore so they aren't deleted when Qt Creator runs.
- Fix the include paths in the MOC files.
  (you could probably skip these two steps by just including the moc files as is, where is in the solution...)
- Open .sln in Visual Studio and rebuild.
- Debug.

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

### Updating libmpg123 on Windows

The x86 precompiled download doesn't have a .lib file. Create one by going to a
Visual Studio commpand prompt in the extracted file directory and running:

lib /def:libmpg123-0.dll.def /OUT:libmpg123-0.lib

### 4.3 uses all 4.1/4.2 libraries with this update:

libmpg123 1.23.8

#### These libraries were used to build version 4.1 and 4.11 and 4.2 on Windows:

PortAudio ???
libogg version 1.3.2
libvorbis 1.3.5
libsndfile 1.0.27
Qt 5.7
wavpack version 4.80.0
libmpg123 version 1.14.2

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

Version 4.4 Changes (February 2017):

1. Added ability to drag song position slider to change location in MP3 files.
2. Added ability to drag song position slider to change location in Ogg Vorbis files.
3. Now reports length and play progress for Ogg Vorbis files.

??. Added ability to drag song position slider to change location in Wavpack files with length specified (unable to test).

Version 4.31 Changes (October 2016):

1. Improved display of songs with a period in the middle of the filename.

Version 4.3 Changes (Octtober 2016):

1. Added Support for FLAC file playback (already supported by libsndfile).
2. Bugfix for handling MP3 files with partial ID3v2 tags.
3. Added reading artist, album, and song name for currently playing song for Wavpack files.
4. Changed app url on about page from vorbitalplayer.com to zetacentauri.com.
5. Added (or re-added) playing files from the command line.
6. Updated mpg123 libraries from 1.14.2 to 1.23.8.
7. Remembers previous directory selection, and remembers previous section on next run.

Version 4.2 Changes:

1. Now shows artist, album, and song name for currently playing song for MP3 files.
2. Now shows a progress bar and the total time for MP3, Wav, AIFF, SND, and Ogg Vorbis files.
3. Added installer file association for MP3 files.
4. Fixed incorrect display of bitrate for Wavpack files.

Version 4.11 changes:

1. Now remembers the last song that was playing when saving/loading playlists so you can continue listening where you left off.
2. Add minimize button lost in switch to Qt.
3. No longer keeps open file locks for MP3 files after they're done playing.

Version 4.1 changes (2016):

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
