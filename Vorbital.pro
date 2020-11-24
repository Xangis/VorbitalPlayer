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

win32:INCLUDEPATH += E:\lib\mpg123-1.26.3-x86
win32:INCLUDEPATH += "E:\lib\OpenAL 1.1 SDK\include"
win32:INCLUDEPATH += E:\lib\libsndfile-1.0.28\include
win32:INCLUDEPATH += E:\lib\wavpack-5.3.0-dll
win32:INCLUDEPATH += E:\lib\libvorbis-1.3.7\include\vorbis
win32:INCLUDEPATH += E:\lib\libogg-1.3.2\include

macx:INCLUDEPATH += "/Users/Apple/lib/OpenAL 1.1 SDK/include"
macx:INCLUDEPATH += "/Users/Apple/lib/libsndfile-1.0.28/include"
macx:INCLUDEPATH += /Users/Apple/lib/mpg123-1.23.8-x86
macx:INCLUDEPATH += /Users/Apple/lib/libvorbis-1.3.5/include/vorbis
macx:INCLUDEPATH += /Users/Apple/lib/libogg-1.3.2/include
macx:INCLUDEPATH += /Users/Apple/lib/wavpackdll-4.80.0

win32:LIBS += -LF:\lib\mpg123-1.23.8-x86 \
    -LE:\lib\mpg123-1.26.3-x86 \
    -L"E:\lib\OpenAL 1.1 SDK\libs\Win32" \
    -LE:\lib\libsndfile-1.0.28\lib \
    -LE:\lib\wavpack-5.3.0-dll \
    -LE:\lib\libvorbis-1.3.7\win32\VS2010\Win32\Release \
    -LE:\lib\libogg-1.3.2\win32\VS2010\Win32\Release \
    -LE:\code\AudioFile\ \
    -llibmpg123-0 -lOpenAL32 -lalut -lwavpackdll -llibvorbis_static -llibvorbisfile_static -llibogg_static -llibsndfile-1

linux:LIBS += -lsndfile -lmpg123 -lopenal -lwavpack -lvorbisfile -lvorbis -lalut

macx:LIBS += -L/usr/local/lib -logg -lsndfile -lvorbisfile -lvorbis -lmpg123 -lwavpack -framework OpenAL

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
