#!/bin/bash
otool -L *.app/Contents/Frameworks/*.dylib|grep -v /System/Library/Frameworks|grep -v libSystem||grep -v libz|grep -v libiconv\
 |grep -v executable_path|grep -v libobjc|grep -v libc++|grep -v libgcc|grep -v libbz|grep -v libexpat
DYLD_PRINT_LIBRARIES=1 ./DrumPads.app/Contents/MacOS/Vorbital
