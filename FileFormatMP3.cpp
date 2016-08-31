#include "FileFormatMP3.h"
#include <stdio.h>
#include <QDebug>

FileFormatMP3::FileFormatMP3()
{
    int merr;
    _mpg123 = mpg123_new(0, &merr);
    if( merr )
    {
        qDebug() << "mpg123_new error: " << merr;
    }
    _channels = 0;
    _encoding = 0;
    _sampleRate = 0;
    _bitRate = 0;
    _filePosition = 0;
}

bool FileFormatMP3::CheckExtension(const QString& filename)
{
	return filename.contains(".MP3", Qt::CaseInsensitive);
}

bool FileFormatMP3::Open(const QString& filename)
{
	_filePosition = 0;
	const std::string fname = filename.toStdString();
	// Close existing file, if any.
	mpg123_close(_mpg123);
	int result = mpg123_open(_mpg123, fname.c_str());
	if( result != MPG123_OK )
	{
		qDebug() << "Could not open file. " << filename << ", mpg123 result = " << result;
		return false;
	}
	if( mpg123_getformat(_mpg123, &_sampleRate, &_channels, &_encoding) != MPG123_OK )
	{
		qDebug() << "Could not get format data from file " << filename;
		return false;
	}
    if(_encoding != MPG123_ENC_SIGNED_16 && _encoding != MPG123_ENC_FLOAT_32)
    {
        //cleanup(_mpg123);
        qDebug() << "Bad MP3 encoding for file " << filename << ": " << _encoding;
        return false;
    }
	mpg123_frameinfo info;
	mpg123_info(_mpg123, &info);
	qDebug() << "MPG123 Bitrate: " << info.bitrate << ", rate: " << info.rate << ", vbr: " << info.vbr;
	_bitRate = info.bitrate;
	qDebug() << "MPG123 loaded file " << filename;

	return true;
}

int FileFormatMP3::GetBitrate()
{
	return _bitRate;
}

int FileFormatMP3::GetChannels()
{
	return _channels;
}

int FileFormatMP3::GetFormat()
{
	return FORMAT_MP3;
}

int FileFormatMP3::GetSampleRate()
{
	return _sampleRate;
}

bool FileFormatMP3::Init()
{
    // Pass. This is a terrible place to initialize. We do it in main instead.
    return true;
}

int FileFormatMP3::FillBuffer(unsigned char* buffer, int numBytes)
{
	size_t numDone = 0;
	int err = MPG123_OK;
	err = mpg123_read(_mpg123, buffer, numBytes, &numDone);
	_filePosition += numDone;
	if( numDone == 0 || err == MPG123_DONE )
	{
		return -1;
	}
	return numDone;
}

FileFormatMP3::~FileFormatMP3()
{
    mpg123_close(_mpg123);
}
