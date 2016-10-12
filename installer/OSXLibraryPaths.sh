#!/bin/bash
install_name_tool -change @rpath/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change @rpath/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/opt/libogg/lib/libogg.0.dylib @executable_path/../Frameworks/libogg.0.dylib Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/lib/libsndfile.1.dylib @executable_path/../Frameworks/libsndfile.1.dylib Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/opt/libvorbis/lib/libvorbisfile.3.dylib @executable_path/../Frameworks/libvorbisfile.3.dylib Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/opt/libvorbis/lib/libvorbis.0.dylib @executable_path/../Frameworks/libvorbis.0.dylib Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/opt/mpg123/lib/libmpg123.0.dylib @executable_path/../Frameworks/libmpg123.0.dylib Vorbital.app/Contents/MacOS/Vorbital
install_name_tool -change /usr/local/opt/wavpack/lib/libwavpack.1.dylib @executable_path/../Frameworks/libwavpack.1.dylib Vorbital.app/Contents/MacOS/Vorbital
otool -L Vorbital.app/Contents/MacOS/Vorbital
