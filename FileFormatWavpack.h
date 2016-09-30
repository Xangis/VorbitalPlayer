#ifndef FILEFORMATWAVPACK_H
#define FILEFORMATWAVPACK_H

// TODO: Implement this. Right now it's just a placeholder until we can convert wavpack code to use it.

#include "AudioFileFormat.h"
#include "wavpack.h"

#include <QString>

class FileFormatWavpack: public AudioFileFormat
{
public:
    FileFormatWavpack();
    ~FileFormatWavpack();
    virtual bool CheckExtension(const QString& filename);
    virtual bool Open(const QString& filename);
    virtual int GetFormat();
    virtual int GetBitrate();
    virtual int GetChannels();
    virtual int GetSampleRate();
    virtual int GetLength();
    virtual int FillBuffer(unsigned char* buffer, int numBytes);
    virtual const char* GetArtistName();
    virtual const char* GetAlbumName();
    virtual const char* GetSongName();
    static bool Init();
private:
    //int _filePosition;
    WavpackContext * _wavpackContext;
    // We need to have these variables because wavpack needs a place to store data.
    char _wavpackArtist[128];
    char _wavpackAlbum[128];
    char _wavpackTrack[128];
};
#endif // FILEFORMATWAVPACK_H
