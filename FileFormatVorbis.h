#ifndef _FILEFORMATVORBIS_H_
#define _FILEFORMATVORBIS_H_

#include "AudioFileFormat.h"
#include "vorbisfile.h"

#include <QString>

class FileFormatVorbis: public AudioFileFormat
{
public:
	FileFormatVorbis();
	~FileFormatVorbis();
	virtual bool CheckExtension(const QString& filename);
	virtual bool Open(const QString& filename);
	virtual int GetFormat();
	virtual int GetBitrate();
	virtual int GetChannels();
	virtual int GetSampleRate();
    virtual int GetLength();
	virtual int FillBuffer(unsigned char* buffer, int numBytes);
	virtual const char* GetComment();
    virtual const char* GetArtistName();
    virtual const char* GetAlbumName();
    virtual const char* GetSongName();
	static bool Init();
	static const char* VorbisErrorString(int code);
private:
    static OggVorbis_File* _oggVorbisFile;
    vorbis_info* _vorbisInfo;
    vorbis_comment* _vorbisComment;
	int _filePosition;
};

#endif
