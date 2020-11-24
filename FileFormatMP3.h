#ifndef _FILEFORMATMP3_H_
#define _FILEFORMATMP3_H_

#include "AudioFileFormat.h"
#include "mpg123.h"

#include <QString>

class FileFormatMP3: public AudioFileFormat
{
public:
    ~FileFormatMP3();
    FileFormatMP3();
	virtual bool CheckExtension(const QString& filename);
	virtual bool Open(const QString& filename);
	virtual int GetFormat();
    virtual unsigned int GetBitrate();
    virtual unsigned int GetChannels();
    virtual unsigned int GetSampleRate();
    virtual unsigned int GetLength();
    virtual int FillBuffer(unsigned char* buffer, unsigned int numBytes);
	virtual const char* GetComment() { return NULL; }
    virtual const char* GetArtistName();
    virtual const char* GetAlbumName();
    virtual const char* GetSongName();
    static bool Init();
    virtual bool SetPosition(unsigned int seconds);
    virtual bool CanSetPosition();
private:
    mpg123_handle* _mpg123;
    mpg123_id3v1* _id3v1;
    mpg123_id3v2* _id3v2;
	int _channels;
	int _encoding;
	long _sampleRate;
    long _bitRate;
	int _filePosition;
    int _length; // File length in seconds;
};

#endif
