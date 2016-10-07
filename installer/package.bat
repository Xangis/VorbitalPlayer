echo This program runs the desktop app packager command to create a Windows 10 store package from an existing installer.
pause
DesktopAppConverter.exe -Installer "C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer4.3Setup.exe" -PackageName "VorbitalPlayer" -Version 4.3.0.0 -Makeappx -Destination "C:\Users\angis\code\VorbitalPlayer\installer" -InstallerArguments "/VERYSILENT" -Publisher "CN=Jason Champion"

