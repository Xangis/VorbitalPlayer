######################################################################
# Automatically generated by qmake (3.0) Wed Aug 21 00:06:57 2013
######################################################################

# Note: If OSX says that xcode is misconfigured, this might be the problem:
# http://stackoverflow.com/questions/39492617/xcode-8-error-project-error-xcode-not-set-up-properly-even-though-the-licens

TEMPLATE = app
TARGET = Vorbital
QT += core gui widgets
win32:RC_ICONS += vorbital.ico

linux:INCLUDEPATH += /usr/include/qt5/QtWidgets/
linux:INCLUDEPATH += /usr/include/AL
linux:INCLUDEPATH += /usr/include/vorbis
linux:INCLUDEPATH += /usr/include/wavpack
linux:INCLUDEPATH += /home/xangis/lib/rtaudio-5.1.0/
linux:INCLUDEPATH += /usr/include/rtmidi
linux:INCLUDEPATH += /home/xangis/lib/mpg123-1.25.10/src/libmpg123
linux:INCLUDEPATH += /home/xangis/lib/libvorbis-1.3.6/include/vorbis
linux:INCLUDEPATH += /home/xangis/lib/libogg-1.3.3/include
linux:INCLUDEPATH += /home/xangis/lib/wavpack-5.1.0/include

win32:INCLUDEPATH += F:\lib\mpg123-1.23.8-x86
win32:INCLUDEPATH += "F:\lib\OpenAL 1.1 SDK\include"
win32:INCLUDEPATH += F:\lib\libsndfile-1.0.28\include
win32:INCLUDEPATH += F:\lib\wavpack-5.1.0-dll
win32:INCLUDEPATH += F:\lib\libvorbis-1.3.5\include\vorbis
win32:INCLUDEPATH += F:\lib\libogg-1.3.2\include

macx:INCLUDEPATH += "/Users/xangis/lib/OpenAL 1.1 SDK/include"
macx:INCPUDEPATH += /Users/xangis/lib/libsndfile-1.0.28/src/
macx:INCLUDEPATH += /Users/xangis/lib/mpg123-1.25.10/src/libmpg123
macx:INCLUDEPATH += /Users/xangis/lib/libvorbis-1.3.6/include/vorbis
macx:INCLUDEPATH += /Users/xangis/lib/libogg-1.3.3/include
macx:INCLUDEPATH += /Users/xangis/lib/wavpack-5.1.0/include
macx:INCLUDEPATH += /Users/xangis/lib/rtaudio-5.1.0/

win32:LIBS += -LF:\lib\mpg123-1.23.8-x86 \
    #-LF:\lib\mpg123-1.14.2-x86 \
    -L"F:\lib\OpenAL 1.1 SDK\libs\Win32" \
    -LF:\lib\libsndfile-1.0.28\lib \
    -LF:\lib\wavpack-5.1.0-dll \
    -LF:\lib\libvorbis-1.3.6\win32\VS2010\Win32\Release \
    -LF:\lib\libogg-1.3.3\win32\VS2010\Win32\Release \
    -LC:\Users\Xangis\code\AudioFile\ \
    -llibmpg123-0 -lOpenAL32 -lalut -lwavpackdll -llibvorbis_static -llibvorbisfile_static -llibogg_static -llibsndfile-1

linux:LIBS += -lsndfile -lmpg123 -lwavpack -lvorbisfile -lvorbisfile -lrtaudio

macx:LIBS += -L/usr/local/lib -logg -lvorbisfile -lvorbis -lmpg123 -lwavpack -lsndfile -lrtaudio\
    -L"/Users/xangis/lib/libogg-1.3.3/src/.libs/" \
    -L"/Users/xangis/lib/libvorbis-1.3.6/lib/.libs/" \
    -L"/Users/xangis/lib/libsndfile-1.0.28/src/.libs/" \
    -L"/Users/xangis/lib/mpg123-1.25.10/src/libmpg123/.libs/" \
    -L"/Users/xangis/lib/wavpack-5.1.0/src/.libs/"
    -L"/Users/xangis/lib/rtaudio-5.1.0/.libs/"

# Input
HEADERS += AudioFileFormat.h \
           Constants.h \
           FileFormatMP3.h \
           FileFormatVorbis.h \
           MusicStream.h \
           resource.h \
           SettingsDlg.h \
           VorbitalDlg.h \
           PlaylistThread.h \
    ../AudioFile/wavefile.h \
    FileFormatWavpack.h

SOURCES += SettingsDlg.cpp \
           Main.cpp \
           FileFormatMP3.cpp \
           FileFormatVorbis.cpp \
           MusicStream.cpp \
           VorbitalDlg.cpp \
           PlaylistThread.cpp \
    ../AudioFile/wavefile.cpp \
    FileFormatWavpack.cpp

DISTFILES += \
    README.md \
    TODO.md

