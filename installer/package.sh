#!/bin/bash
#cp -R ../samples_v2/*.wav DrumPads.app/Contents/Resources/Samples/
codesign --deep -f -s "3rd Party Mac Developer Application: Jason Champion (G6PFF85X2R)" Vorbital.app --entitlements Vorbital.app/Contents/Resources/Entitlements.plist
productbuild --sign "3rd Party Mac Developer Installer: Jason Champion (G6PFF85X2R)" --component Vorbital.app /Applications Vorbital.pkg
