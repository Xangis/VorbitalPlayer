#include "FileFormatWavpack.h"

// TODO: Make this NOT depend on Qt.
#include <QMessageBox>
#include <QDebug>

FileFormatWavpack::FileFormatWavpack()
{
    _wavpackContext = NULL;
}

FileFormatWavpack::~FileFormatWavpack()
{
    if(_wavpackContext != NULL)
    {
        WavpackCloseFile(_wavpackContext);
        delete _wavpackContext;
    }
}

bool FileFormatWavpack::CheckExtension(const QString& filename)
{
    return filename.contains(".WV", Qt::CaseInsensitive);
}

bool FileFormatWavpack::Open(const QString& filename)
{
    if( _wavpackContext != NULL )
    {
        WavpackCloseFile(_wavpackContext);
    }

    char* error = NULL;
    _wavpackContext = WavpackOpenFileInput (filename.toStdString().c_str(), error, OPEN_WVC|OPEN_TAGS|OPEN_2CH_MAX|OPEN_NORMALIZE|OPEN_STREAMING, 1);

    if( error != NULL )
    {
        qDebug() << "Error opening wavpack file " << filename << ": " << error;
    }

    if( _wavpackContext == NULL )
    {
        qDebug() << "Could not open wavpack file " << filename;
        return false;
    }

    return true;
}

int FileFormatWavpack::GetBitrate()
{
    if(_wavpackContext != NULL)
    {
        return WavpackGetReducedChannels(_wavpackContext) * WavpackGetSampleRate(_wavpackContext) * (WavpackGetBitsPerSample(_wavpackContext) );
    }
    else
    {
        return -1;
    }
}

int FileFormatWavpack::GetChannels()
{
    if( _wavpackContext != NULL )
    {
        return WavpackGetReducedChannels(_wavpackContext);
    }
    else
    {
        return -1;
    }
}

int FileFormatWavpack::GetFormat()
{
    return FORMAT_VORBIS;
}

int FileFormatWavpack::GetSampleRate()
{
    if( _wavpackContext != NULL )
    {
        return WavpackGetSampleRate(_wavpackContext);
    }
    else
    {
        return -1;
    }
}

const char* FileFormatWavpack::GetArtistName()
{
    memset(_wavpackArtist, 0, 128);
    WavpackGetTagItem(_wavpackContext, "Artist", _wavpackArtist, 127);
    qDebug() << "Wavpack Artist: " << _wavpackArtist;
    return _wavpackArtist;
}

const char* FileFormatWavpack::GetAlbumName()
{
    memset(_wavpackAlbum, 0, 128);
    WavpackGetTagItem(_wavpackContext, "Album", _wavpackAlbum, 127);
    qDebug() << "Wavpack Album: " << _wavpackAlbum;
    return _wavpackAlbum;
}

const char* FileFormatWavpack::GetSongName()
{
    memset(_wavpackTrack, 0, 128);
    WavpackGetTagItem(_wavpackContext, "Title", _wavpackTrack, 127);
    qDebug() << "Wavpack Title: " << _wavpackTrack;
    return _wavpackTrack;
}

int FileFormatWavpack::GetLength()
{
    if( _wavpackContext != NULL )
    {
        int numSamples = WavpackGetNumSamples(_wavpackContext);
        int sampleRate = WavpackGetSampleRate(_wavpackContext);
        qDebug() << "Wavpack NumSamples: " << numSamples << ", SampleRate: " << sampleRate;
        if( sampleRate > 0 )
        {
            return numSamples / sampleRate;
        }
    }
    return -1;
}

bool FileFormatWavpack::Init()
{
    return true;
}

int FileFormatWavpack::FillBuffer(unsigned char* buffer, int numBytes)
{
    // Divide 16-bit times two channels to get the number of samples.
    int numSamples = numBytes / 4;
    int32_t* data = new int32_t[numSamples * this->GetChannels()];
    short* shortData = (short*)buffer;
    uint32_t numUnpacked = WavpackUnpackSamples(_wavpackContext, data, numSamples);
    int dataSize = numUnpacked * sizeof(short) * this->GetChannels();
    for( unsigned int i = 0; i < numUnpacked * this->GetChannels(); i++ )
    {
        shortData[i] = data[i];
    }

    delete[] data;

    //qDebug() << "Wavpack: Numbytes = " << numBytes << ", numUnpacked = " << numUnpacked << ", dataSize = " << dataSize;
    return dataSize;
}
