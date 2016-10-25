echo This program runs the desktop app packager command to create a Windows 10 store package from an existing installer and replaces the icons with the correct ones.
pause
DesktopAppConverter.exe -Installer "C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer4.31Setup.exe" -PackageName "VorbitalPlayer" -Version 4.3.1.0 -Makeappx -Destination "C:\Users\Xangis\code\VorbitalPlayer\installer" -InstallerArguments "/VERYSILENT" -Publisher "CN=Jason Champion"
rd /s /q C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\Unpacked
makeappx unpack /p C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\VorbitalPlayer.appx /d C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\Unpacked
del C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\VorbitalPlayer.appx
del C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\Unpacked\Assets\SampleAppx.*.png
copy C:\Users\Xangis\code\VorbitalPlayer\images\vorbital44px.png C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\Unpacked\Assets\
copy C:\Users\Xangis\code\VorbitalPlayer\images\vorbital50px.png C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\Unpacked\Assets\
copy C:\Users\Xangis\code\VorbitalPlayer\images\vorbital150px.png C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\Unpacked\Assets\
copy /Y C:\Users\Xangis\code\VorbitalPlayer\installer\AppxManifest.xml C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\Unpacked\
makeappx pack /p "C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\VorbitalPlayer.appx" /d "C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\Unpacked"
"C:\Program Files (x86)\Windows Kits\10\bin\x64\signtool.exe" sign -f jc.pfx -fd SHA256 -v C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\VorbitalPlayer.appx
Certutil -addStore root jc.cer
