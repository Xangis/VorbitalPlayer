#include "FileFormatVorbis.h"

#include <QMessageBox>

OggVorbis_File* FileFormatVorbis::_oggVorbisFile;

FileFormatVorbis::FileFormatVorbis()
{
    _vorbisInfo = NULL;
    _vorbisComment = NULL;
}

FileFormatVorbis::~FileFormatVorbis()
{
	ov_clear(_oggVorbisFile);
}

bool FileFormatVorbis::CheckExtension(const QString& filename)
{
    return filename.contains(".OGG", Qt::CaseInsensitive);
}

bool FileFormatVorbis::Open(const QString& filename)
{
	int result = ov_fopen(filename.toStdString().c_str(), _oggVorbisFile);

	if( result < 0)
	{
		//fclose(_musicFile);
#ifdef WIN32
        QMessageBox( QMessageBox::Critical, QString("Could not open ogg file '%1': %2").arg(filename).arg(VorbisErrorString(result)), "Error", QMessageBox::Ok );
#endif
		return false;
	}

	_vorbisInfo = ov_info(_oggVorbisFile, -1);
	_vorbisComment = ov_comment(_oggVorbisFile, -1);

	return true;
}

int FileFormatVorbis::GetBitrate()
{
	return _vorbisInfo->bitrate_nominal;
}

int FileFormatVorbis::GetChannels()
{
	return _vorbisInfo->channels;
}

int FileFormatVorbis::GetFormat()
{
	return FORMAT_VORBIS;
}

int FileFormatVorbis::GetSampleRate()
{
	return _vorbisInfo->rate;
}

bool FileFormatVorbis::Init()
{
	_oggVorbisFile = new OggVorbis_File();
	return true;
}

int FileFormatVorbis::FillBuffer(unsigned char* buffer, int numBytes)
{
	char* buf = (char*)buffer;
	size_t numDone = 0;
    int  section;
    int  result;

    while(numDone < numBytes)
    {
        result = ov_read(_oggVorbisFile, buf + numDone, numBytes - numDone, 0, 2, 1, &section);

        if(result > 0)
		{
            numDone += result;
		}
        else
		{
            if(result < 0)
			{
                QMessageBox(QMessageBox::Critical, VorbisErrorString(result), "ERR", QMessageBox::Ok);
				return false;
			}
            else
			{
                break;
			}
		}
    }

    if(numDone == 0)
    {
        return false;
    }

	return numDone;
}

const char* FileFormatVorbis::GetComment()
{
	QString comment(QChar(' '));
	for( int i = 0; i < _vorbisComment->comments; i++ )
	{
		comment += QString(_vorbisComment->user_comments[i]);
		comment += '\n';
	}
	return comment.toStdString().c_str();
}

const char * FileFormatVorbis::VorbisErrorString(int code)
{
    switch(code)
    {
        case OV_EREAD:
            return "Read from media.";
        case OV_ENOTVORBIS:
            return "Not Vorbis data.";
        case OV_EVERSION:
            return "Vorbis version mismatch.";
        case OV_EBADHEADER:
            return "Invalid Vorbis header.";
        case OV_EFAULT:
            return "Internal logic fault (bug or heap/stack corruption.)";
        default:
            return "Unknown Ogg error.";
    }
}
