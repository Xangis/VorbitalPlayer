Immediate TODO:

- Needs a time slider so we can skip forward or back in a track.
- Needs to show artist, album, track number, track name metadata for a track in either
  the playlist (ideal) or in the player header (less ideal).
- Does not appear to set volume when settings are loaded (if volume is turned down, still loads /set/ at full volume
  even though the slider is set correctly.
- Change open button to allow selecting files or folders, and handle accordingly.
  Also remember directory changes.

Things to add or improve:
-------------------------
- Make right-click on playlist for file info work. Best if this also shows some basic
  file details, where appropriate (metadata - bitrate, artist, album, track number, track
  name, modified date, etc.)
- Disable all qDebug statements.
- Add support for FLAC.
- Add support for Speex.
- Test 8-bit, 32-bit, and mono versions of file formats because we're probably not
  handling some of them properly. Ogg, wavpack, and wave most likely don't work in
  32-bit and wavpack most likely doesn't work in 8-bit mono, but this is unverified.
- Allow user to configure interface colors and/or modify/skin the interface.
- Add support for loading playlists (m3u, etc.).
- Add support for displaying and editing ID3 tags (via playlist right-click).

