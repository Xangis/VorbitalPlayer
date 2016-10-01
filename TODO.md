Immediate TODO:

- Needs time slider to work for skipping forward or back in a track.
  (start with MP3 only)
- Needs to be able to calculate length of a Wavpack file.
- Needs to read metadata from .wav files.
- Change open button to allow selecting files or folders, and handle accordingly.
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

