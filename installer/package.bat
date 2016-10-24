echo This program runs the desktop app packager command to create a Windows 10 store package from an existing installer.
pause
DesktopAppConverter.exe -Installer "C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer4.31Setup.exe" -PackageName "VorbitalPlayer" -Version 4.3.1.0 -Makeappx -Destination "C:\Users\Xangis\code\VorbitalPlayer\installer" -InstallerArguments "/VERYSILENT" -Publisher "CN=Jason Champion"
"C:\Program Files (x86)\Windows Kits\10\bin\x64\signtool.exe" sign -f jc.pfx -fd SHA256 -v C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\VorbitalPlayer.appx
Certutil -addStore root jc.cer
