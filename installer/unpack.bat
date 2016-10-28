rd /s /q C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\Unpacked
makeappx unpack /p C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\VorbitalPlayer.appx /d C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\Unpacked
del C:\Users\Xangis\code\VorbitalPlayer\installer\VorbitalPlayer\Unpacked\Assets\SampleAppx.*.png
echo off
echo Here's what to do next:
echo Copy your 44px, 50px, and 150px files into \Unpacked\Assets\
echo Then update the AppxManifest.xml to reflect the icons you've added, edit these two sections:
echo "<Logo>Assets\vorbital50px.png</Logo>"
echo "<uap:VisualElements DisplayName="VorbitalPlayer" Description="VorbitalPlayer" BackgroundColor="#777777" Square150x150Logo="Assets\vorbital150px.png" Square44x44Logo="Assets\vorbital44px.png" />"
