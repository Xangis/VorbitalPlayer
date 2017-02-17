#ifndef _AUDIOFILEFORMAT_H_
#define _AUDIOFILEFORMAT_H_

#include "Constants.h"

#include <QString>

class AudioFileFormat
{
public:
	AudioFileFormat() {}
	virtual ~AudioFileFormat() {}
	// For checking whether a file has the right extension for this format.
	virtual bool CheckExtension(const QString& filename) = 0;
	// Open a file for reading and get its properties (bit rate, sample rate, channels, etc.)
	virtual bool Open(const QString& filename) = 0;
	// Gets the file format enum.
	virtual int GetFormat() = 0;
	// Gets the bitrate of the file.
	virtual int GetBitrate() = 0;
	// Gets the number of channels for the file.
	virtual int GetChannels() = 0;
	// Gets the sample rate for the file.
	virtual int GetSampleRate() = 0;
    // Gets the length of the file in seconds, or -1 if unknown.
    virtual int GetLength() = 0;
    virtual int FillBuffer(unsigned char* buffer, unsigned int numBytes) = 0;
    virtual const char* GetArtistName() = 0;
    virtual const char* GetAlbumName() = 0;
    virtual const char* GetSongName() = 0;
    // Override this for file formats that have the ability to seek to a specific
    // position, in seconds, in the file.
    virtual bool SetPosition(unsigned int) { return false; }
    virtual bool CanSetPosition() { return false; }
	static bool Init();
};

#endif
