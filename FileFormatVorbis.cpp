#include "FileFormatVorbis.h"

// TODO: Make this NOT depend on Qt.
#include <QMessageBox>
#include <QDebug>

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
#ifdef WIN32
        QMessageBox( QMessageBox::Critical, QString("Could not open ogg file '%1': %2").arg(filename).arg(VorbisErrorString(result)), "Error", QMessageBox::Ok );
#endif
		return false;
	}

	_vorbisInfo = ov_info(_oggVorbisFile, -1);
	_vorbisComment = ov_comment(_oggVorbisFile, -1);

	return true;
}

unsigned int FileFormatVorbis::GetBitrate()
{
	return _vorbisInfo->bitrate_nominal;
}

unsigned int FileFormatVorbis::GetChannels()
{
	return _vorbisInfo->channels;
}

int FileFormatVorbis::GetFormat()
{
	return FORMAT_VORBIS;
}

unsigned int FileFormatVorbis::GetSampleRate()
{
	return _vorbisInfo->rate;
}

const char* FileFormatVorbis::GetArtistName()
{
    if( this->_vorbisComment != NULL )
    {
        for( int i = 0; i < _vorbisComment->comments; i++)
        {
            //qDebug() << "Vorbis Comment: " << _vorbisComment->user_comments[i];
            if( strstr( _vorbisComment->user_comments[i], "ARTIST="))
            {
                qDebug() << "Vorbis Artist found: " << &(_vorbisComment->user_comments[i][7]);
                return &(_vorbisComment->user_comments[i][7]);
            }
        }
    }
    return NULL;
}

const char* FileFormatVorbis::GetAlbumName()
{
    if( this->_vorbisComment != NULL )
    {
        for( int i = 0; i < _vorbisComment->comments; i++)
        {
            //qDebug() << "Vorbis Comment: " << _vorbisComment->user_comments[i];
            if( strstr( _vorbisComment->user_comments[i], "ALBUM="))
            {
                qDebug() << "Vorbis Album found: " << &(_vorbisComment->user_comments[i][6]);
                return &(_vorbisComment->user_comments[i][6]);
            }
        }
    }
    return NULL;
}

const char* FileFormatVorbis::GetSongName()
{
    if( this->_vorbisComment != NULL )
    {
        for( int i = 0; i < _vorbisComment->comments; i++)
        {
            //qDebug() << "Vorbis Comment: " << _vorbisComment->user_comments[i];
            if( strstr( _vorbisComment->user_comments[i], "TITLE="))
            {
                qDebug() << "Vorbis Song title found: " << &(_vorbisComment->user_comments[i][6]);
                return &(_vorbisComment->user_comments[i][6]);
            }
        }
    }
    return NULL;
}

unsigned int FileFormatVorbis::GetLength()
{
    // http://stackoverflow.com/questions/20794204/how-to-determine-length-of-ogg-file
    if( _oggVorbisFile == NULL )
    {
        return -1;
    }
    double totalTime = ov_time_total(_oggVorbisFile, -1);
    return int(totalTime);
}

bool FileFormatVorbis::Init()
{
	_oggVorbisFile = new OggVorbis_File();
	return true;
}

int FileFormatVorbis::FillBuffer(unsigned char* buffer, unsigned int numBytes)
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

bool FileFormatVorbis::SetPosition(unsigned int seconds)
{
    qDebug() << "FileFormatVorbis::SetPosition called with seconds = " << seconds;
    if( _oggVorbisFile == NULL )
    {
        return false;
    }
    int result = ov_time_seek(_oggVorbisFile, seconds);
    if( result == 0 )
    {
        qDebug() << "FileFormatVorbis::Seeked to time " << seconds;
        return true;
    }
    else
    {
        qDebug() << "Error seeking frame: " << result;
        return false;
    }
}

bool FileFormatVorbis::CanSetPosition()
{
    return true;
}
