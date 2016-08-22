######################################################################
# Automatically generated by qmake (3.0) Wed Aug 21 00:06:57 2013
######################################################################

TEMPLATE = app
TARGET = Vorbital
QT += core gui widgets
win32:RC_ICONS += vorbital.ico

linux:INCLUDEPATH += /usr/include/qt5/QtWidgets/
win32:INCLUDEPATH += F:\lib\mpg123-1.14.2-x86
win32:INCLUDEPATH += "F:\lib\OpenAL 1.1 SDK\include"
win32:INCLUDEPATH += F:\lib\libsndfile-1.0.27\include
win32:INCLUDEPATH += F:\lib\wavpackdll-4.80.0
win32:INCLUDEPATH += F:\lib\libvorbis-1.3.5\include\vorbis
win32:INCLUDEPATH += F:\lib\libogg-1.3.2\include

win32:LIBS += -LF:\lib\mpg123-1.14.2-x86 \
    -L"F:\lib\OpenAL 1.1 SDK\libs\Win32" \
    -LF:\lib\libsndfile-1.0.27\lib \
    -LF:\lib\wavpackdll-4.80.0 \
    -LF:\lib\libvorbis-1.3.5\win32\VS2010\Win32\Release \
    -LF:\lib\libogg-1.3.2\win32\VS2010\Win32\Release \
    -llibmpg123-0 -lOpenAL32 -lalut -lwavpackdll -llibvorbis_static -llibvorbisfile_static -llibogg_static -llibsndfile-1

linux:LIBS += -lsndfile -lmpg123 -lopenal -lwavpack -lvorbisfile -lvorbis

# Input
HEADERS += AudioFileFormat.h \
           Constants.h \
           FileFormatMP3.h \
           FileFormatVorbis.h \
           MusicStream.h \
           resource.h \
           SettingsDlg.h \
           VorbitalDlg.h \
           WaveFile.h \
           PlaylistThread.h

SOURCES += WaveFile.cpp \
           SettingsDlg.cpp \
           Main.cpp \
           FileFormatMP3.cpp \
           FileFormatVorbis.cpp \
           MusicStream.cpp \
           VorbitalDlg.cpp \
           PlaylistThread.cpp

DISTFILES += \
    README.md \
    TODO.md
