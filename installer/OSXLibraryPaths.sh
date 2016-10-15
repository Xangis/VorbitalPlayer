#!/bin/bash
# You may need to change this path if you're on another system or different version of Qt.
cp ../../build-Vorbital-Desktop_Qt_5_7_0_clang_64bit-Release/Vorbital.app/Contents/MacOS/Vorbital Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/opt/libogg/lib/libogg.0.dylib @executable_path/../Frameworks/libogg.0.dylib Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/lib/libsndfile.1.dylib @executable_path/../Frameworks/libsndfile.1.dylib Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/opt/libvorbis/lib/libvorbisfile.3.dylib @executable_path/../Frameworks/libvorbisfile.3.dylib Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/opt/libvorbis/lib/libvorbis.0.dylib @executable_path/../Frameworks/libvorbis.0.dylib Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/opt/mpg123/lib/libmpg123.0.dylib @executable_path/../Frameworks/libmpg123.0.dylib Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/opt/wavpack/lib/libwavpack.1.dylib @executable_path/../Frameworks/libwavpack.1.dylib Vorbital.app/Contents/MacOS/Vorbital
# Framework sub-dependencies.
install_name_tool -change /usr/local/lib/libogg.0.dylib @executable_path/../Frameworks/libogg.0.dylib Vorbital.app/Contents/Frameworks/libvorbis.0.dylib
install_name_tool -change /usr/local/lib/libogg.0.dylib @executable_path/../Frameworks/libogg.0.dylib Vorbital.app/Contents/Frameworks/libvorbisfile.3.dylib
install_name_tool -change /usr/local/Cellar/libvorbis/1.3.5/lib/libvorbis.0.dylib @executable_path/../Frameworks/libvorbis.0.dylib Vorbital.app/Contents/Frameworks/libvorbisfile.3.dylib
# Qt
/Users/Apple/Qt/5.7/clang_64/bin/macdeployqt Vorbital.app -appstore-compliant
otool -L Vorbital.app/Contents/MacOS/Vorbital
