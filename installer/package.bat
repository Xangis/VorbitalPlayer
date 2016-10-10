echo This program runs the desktop app packager command to create a Windows 10 store package from an existing installer.
pause
DesktopAppConverter.exe -Installer "C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer4.31Setup.exe" -PackageName "VorbitalPlayer" -Version 4.3.1.0 -Makeappx -Destination "C:\Users\Xangis\code\VorbitalPlayer\installer" -InstallerArguments "/VERYSILENT" -Publisher "CN=Jason Champion" -Sign
Certutil -addStore TrustedPeople VorbitalPlayer\auto-generated.cer



