# VorbitalPlayer

A music player for Linux, Windows, and OSX with MP3, OGG, and WAV support. It was
originally released on http://zetacentauri.com and then vorbitalplayer.com and
via the Ubuntu Software Center. It was downloaded more than 80,000 times before
being open-sourced.

![Vorbital Player Screenshot](https://github.com/Xangis/VorbitalPlayer/blob/master/images/Vorbital4.png)

A pre-built Windows installer is available in the installer directory:

https://github.com/Xangis/VorbitalPlayer/blob/master/installer/VorbitalPlayer4.43Setup.exe

The Vorbital Player was originally written using wxWidgets, but has been ported
to Qt due to some multiplatform portability and consistency annoyances with
wxWidgets. It is written in C++ and uses a number of libraries for file format
support (mpg123, libsndfile, libogg, libvorbis, libwavpack, etc.)

It was written to work with Qt 5.

### Goals

The goal with Vorbital Player is/was to build a music player that loaded quickly and JUST
played music, without presuming to try to manage your music library (including all of
those "connect to the internet to download media information" features).

I want to hear a song instantly when I double-click on the file. I don't want to have to
wait for a software update to finish, for an app to phone home and check for music news,
wait for thousands of icons and images to load, or to be presented with a store. I just 
want the song to play, hassle-free.

# Building

In all cases, you'll need to set the paths in the Vorbital.pro project file to match where
the various audio libraries are located on your system.

The following libraries are required:

Qt 5 SDK
mpg123
OpenAL SDK
libsndfile
wavpack
libogg
libvorbis

### Building on Windows

NOTE: THIS SHOULD NOT BE BUILT USING VISUAL STUDIO. USE QT CREATOR.
      VISUAL STUDIO IS FOR DEBUGGING ONLY.

Building for Windows will be a nuisance because you will have to set paths to
all of the various audio libraries (the Windows build isn't as well-maintained
as the Linux build, and the Qt version hasn't been released on Windows yet). If
you just want the app, an installable version of Vorbital 4.0 for Windows is
available in the installer folder.

There is a package.bat script in the installer folder. It is designed to work
with the Desktop App Converter. Howver, I never was able to get a reliably working
appx installer package (certificate and permission problems never quite worked out).
The normal .exe installer works fine on Windows 10.

To debug on Visual Studio (it's easier to debug with than Qt Creator):

- Copy moc_*.cpp files from build output directory for the Qt Creator build. Rename them to have a
  leading underscore so they aren't deleted when Qt Creator runs.
- Fix the include paths in the MOC files.
  (you could probably skip these two steps by just including the moc files as is, where is in the solution...)
- Open .sln in Visual Studio and rebuild.
- Debug.

The included solution is for Visual Studio 2010, but should work fine with newer versions.

### Updating libmpg123 on Windows

The x86 precompiled download doesn't have a .lib file. Create one by going to a
Visual Studio commpand prompt in the extracted file directory and running:

lib /def:libmpg123-0.dll.def /OUT:libmpg123-0.lib

To build an installer for Windows, look in the /installer folder for NullSoft
Installer (NSIS) and InnoSetup projects. File paths may have changed, so you may
need to update them to build an installer. The NSIS files are no longer used,
but were used with older versions and are included in case you want to update
them and build with that instead.

### Building on Linux

To build on Linux, you will need Qt 5 and the following packages:

libsndfile-dev
libogg-dev
libvorbis-dev
libopenal-dev
libwavpack-dev
libmpg123-dev

Just do the standard "qmake" and then "make" to build.

A much older version of this app was available for free via the Ubuntu store at one point,
but that was a wxWidgets-based version.

### Building on OSX

You'll have to get the same dependencies mentioned for Linux and then use Qt to build
as normal.

In the installer folder, running OSXLibraryPaths.sh and then package.sh should get you
an app package.

I was able to get it to build and run on OSX, but was never able to get it to the point
of being accepted by the Apple Store.

# Changelog

### Version 4.43 Changes (November 2020):

Changed song display to a single label without colons.
Larger text with a different font. No colons on labels.
No periods on button hover text.
Default music open directory defaults to user default music directory on first load.
Can click speaker icon to mute or unmute audio
Drag and drop has been fixed

Updated libmpg123 1.23.8 => 1.26.3 (had to manually create lib file from .def)
Updated libogg 1.3.2 => 1.3.4
Updated libvorbis 1.3.5 => 1.3.7
Updated Qt 5.8 => 5.12.2
Updated Wavpack 5.1.0 => 5.3.0
libsndfile 1.0.28
So currently libmpg123 1.23.8

### Version 4.42 Changes (July 2017):

1. First open-source version under the MIT license
2. Updated libsndfile library from 1.0.27 to 1.0.28.

libogg version 1.3.2
libvorbis 1.3.5
libsndfile 1.0.28
Qt 5.8
wavpack version 5.1.0
libmpg123 1.23.8

### Version 4.41 Changes (February 2017):

1. Volume slider now defaults to 100% on a new install.
2. Adding songs while player is playing no longer makes next track jump to the beginning.

Same libraries as version 4.4.

### Version 4.4 Changes (February 2017):

1. Added ability to drag song position slider to change location in MP3 files.
2. Added ability to drag song position slider to change location in Ogg Vorbis files.
3. Added ability to drag song position slider to change location in WAV, SND, AIFF, and FLAC files.
4. Now reports length and play progress for Ogg Vorbis files.
5. Updated Qt from 5.7 to 5.8.
6. Updated Wavpack library from 4.80.0 to version 5.1.0
??. Added ability to drag song position slider to change location in Wavpack files with length specified (unable to test).

Libraries used to build version 4.4 on Windows:

PortAudio ???
libogg version 1.3.2
libvorbis 1.3.5
libsndfile 1.0.27
Qt 5.8
wavpack version 5.1.0
libmpg123 1.23.8

### Version 4.31 Changes (October 2016):

1. Improved display of songs with a period in the middle of the filename.

Libraries used to build version 4.31 on Windows:

PortAudio ???
libogg version 1.3.2
libvorbis 1.3.5
libsndfile 1.0.27
Qt 5.7
wavpack version 4.80.0
libmpg123 1.23.8

### Version 4.3 Changes (October 2016):

1. Added Support for FLAC file playback (already supported by libsndfile).
2. Bugfix for handling MP3 files with partial ID3v2 tags.
3. Added reading artist, album, and song name for currently playing song for Wavpack files.
4. Changed app url on about page from vorbitalplayer.com to zetacentauri.com.
5. Added (or re-added) playing files from the command line.
6. Updated mpg123 libraries from 1.14.2 to 1.23.8.
7. Remembers previous directory selection, and remembers previous section on next run.

Libraries used to build version 4.3 on Windows:

PortAudio ???
libogg version 1.3.2
libvorbis 1.3.5
libsndfile 1.0.27
Qt 5.7
wavpack version 4.80.0
libmpg123 1.23.8

### Version 4.2 Changes:

1. Now shows artist, album, and song name for currently playing song for MP3 files.
2. Now shows a progress bar and the total time for MP3, Wav, AIFF, SND, and Ogg Vorbis files.
3. Added installer file association for MP3 files.
4. Fixed incorrect display of bitrate for Wavpack files.

Libraries used to build version 4.2 on Windows:

PortAudio ???
libogg version 1.3.2
libvorbis 1.3.5
libsndfile 1.0.27
Qt 5.7
wavpack version 4.80.0
libmpg123 version 1.14.2

### Version 4.11 changes:

1. Now remembers the last song that was playing when saving/loading playlists so you can continue listening where you left off.
2. Add minimize button lost in switch to Qt.
3. No longer keeps open file locks for MP3 files after they're done playing.

Libraries used to build version 4.11 on Windows:

PortAudio ???
libogg version 1.3.2
libvorbis 1.3.5
libsndfile 1.0.27
Qt 5.7
wavpack version 4.80.0
libmpg123 version 1.14.2

### Version 4.1 changes (2016):

1. Switched Windows version fully over to Qt (4.0 was wxWidgets on Windows and Qt on Linux).
2. Updated ogg, vorbis, sndfile, and wavpack libraries.
3. Added loading of AlbumArtSmall.jpg as an album art fallback if Folder.jpg does not exist.
4. Album art displays larger.
5. Loading a folder now also loads everything in its subfolders.

Libraries used to build version 4.1 on Windows:

PortAudio ???
libogg version 1.3.2
libvorbis 1.3.5
libsndfile 1.0.27
Qt 5.7
wavpack version 4.80.0
libmpg123 version 1.14.2

### Version 4.0 Changes (????):

1. Support for playing .mp3 files.
2. Support for displaying album art (if exists as Folder.jpg in the same folder).
3. The program now remembers the volume setting, shuffle setting, and last window size when you exit, restoring them next time the program runs.
4. Clicking the vorbitaplayer.com website link in the about box now tells you if there's a newer version of the software when you visit the site.
5. Fixed a bug that could cause the program to crash on exit.
6. Fixed a bug that could cause an item in the playlist to play twice in a row when double-clicked.
7. Now available for Ubuntu Linux.

Libraries used to build version 4.0 on Windows:

OpenAL version 6.14.357.24.
wrap_oal.dll version 2.2.0.5.
libogg version 1.3.0.
libvorbis 1.3.3.
libsndfile 1.0.25.
wxWidgets 2.9.4.
wavpack version 4.60.1.
libmpg123 version 1.14.2.

### What's new in version 3.1 of Vorbital:

1. Support for Audio Interchange File Format (.aif and .aiff) files.
2. Support for Apple SND (.snd) files.

### What's new in version 3 of Vorbital:

1. Support for Wavpack (.wv) files.
2. Support for Wave (.wav) files.
3. User interface improvements.

### What's new in version 2 of Vorbital:

1. Added "randomize" button.
2. Fixed function of pause button so it behaves as a pause rather than stop.
3. Added "load directory" button.
4. Playlist now supports drag-and-drop.
5. Volume control slider added.
6. Added "clear playlist" button.
7. Fixed a handful of bugs and oddities.
8. Add file button now supports multiple selections.

# Development Status

The Vorbital Player was written as free but proprietary software. Various versions
have been released for Windows and Linux, but it has primarily been a Windows app.

I open-sourced it because there's no reason for it to remain proprietary anymore
since it's no longer part of a business.

I may work on this from time to time if I feel like it, but for the most part it's
an inactive project. I'll accept pull requests if you want to add something useful
or make the build process easier. It has only been worked on by one person, so there
are probably things that are specific to the development environments that I've used
that could be made more generic and portable.

I still sometimes use this app on Windows machines because it's nice to use an app
that doesn't try to manage your music library for you, even if it's not perfect.
