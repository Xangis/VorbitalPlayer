TODO:

- Needs to be able to calculate length of a Wavpack file. (may work, don't have good files to test)
- Needs to read metadata from .wav files.
- Change open button to allow selecting files or folders, and handle accordingly. This will let us
  have just one open button instead of a separate "open file" and "open folder" button.
  (Needs a custom control, not possible in core Qt).
- Needs a right-click menu item to view filename and edit tags.

Things to add or improve:
-------------------------
- Make right-click on playlist for file info work. Best if this also shows some basic
  file details, where appropriate (metadata - bitrate, artist, album, track number, track
  name, modified date, etc.)
- Add support for Speex.
- Test 8-bit, 32-bit, and mono versions of file formats because we're probably not
  handling some of them properly. Ogg, wavpack, and wave most likely don't work in
  32-bit and wavpack most likely doesn't work in 8-bit mono, but this is unverified.
- Allow user to configure interface colors and/or modify/skin the interface.
- Add support for loading playlists (m3u, etc.).
- Add support for displaying and editing ID3 tags (via playlist right-click).
- Player sometimes glitches up and stutters. This may happen when the PC is starved for CPU
  or when a file takes too long to load. It appears to be caused by not being able to fill
  and audio buffer fast enough, and then the buffers get stuck. I've gone months without
  it happening, and have also had it happen multiple times in a day. Haven't been able to
  reliably reproduce it, so haven't fixed it.
