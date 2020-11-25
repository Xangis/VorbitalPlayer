#include "FileFormatWavpack.h"

// TODO: Make this NOT depend on Qt.
#include <QMessageBox>
#include <QDebug>

FileFormatWavpack::FileFormatWavpack()
{
    _wavpackContext = nullptr;
}

FileFormatWavpack::~FileFormatWavpack()
{
    if(_wavpackContext != nullptr)
    {
        WavpackCloseFile(_wavpackContext);
    }
}

bool FileFormatWavpack::CheckExtension(const QString& filename)
{
    return filename.contains(".WV", Qt::CaseInsensitive);
}

bool FileFormatWavpack::Open(const QString& filename)
{
    if( _wavpackContext != nullptr )
    {
        qDebug() << "Closing current wavpack file before opening another";
        WavpackCloseFile(_wavpackContext);
    }

    char* error = nullptr;
    _wavpackContext = WavpackOpenFileInput (filename.toStdString().c_str(), error, OPEN_WVC|OPEN_TAGS|OPEN_2CH_MAX|OPEN_NORMALIZE|OPEN_STREAMING, 1);

    if( error != nullptr )
    {
        qDebug() << "Error opening wavpack file " << filename << ": " << error;
    }

    if( _wavpackContext == nullptr )
    {
        qDebug() << "Could not open wavpack file " << filename;
        return false;
    }

    return true;
}

unsigned int FileFormatWavpack::GetBitrate()
{
    if(_wavpackContext != nullptr)
    {
        return WavpackGetReducedChannels(_wavpackContext) * WavpackGetSampleRate(_wavpackContext) * (WavpackGetBitsPerSample(_wavpackContext) );
    }
    else
    {
        return 0;
    }
}

unsigned int FileFormatWavpack::GetChannels()
{
    if( _wavpackContext != nullptr )
    {
        return WavpackGetReducedChannels(_wavpackContext);
    }
    else
    {
        return 0;
    }
}

int FileFormatWavpack::GetFormat()
{
    return FORMAT_VORBIS;
}

unsigned int FileFormatWavpack::GetSampleRate()
{
    if( _wavpackContext != nullptr )
    {
        return WavpackGetSampleRate(_wavpackContext);
    }
    else
    {
        return 0;
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

unsigned int FileFormatWavpack::GetLength()
{
    if( _wavpackContext != nullptr )
    {
#ifdef WIN32
        int64_t numSamples = WavpackGetNumSamples64(_wavpackContext);
#else
        int numSamples = WavpackGetNumSamples(_wavpackContext);
#endif
        unsigned int sampleRate = WavpackGetSampleRate(_wavpackContext);
        qDebug() << "Wavpack NumSamples: " << numSamples << ", SampleRate: " << sampleRate;
        if( sampleRate > 0 )
        {
            return numSamples / sampleRate;
        }
    }
    return 0;
}

bool FileFormatWavpack::Init()
{
    return true;
}

int FileFormatWavpack::FillBuffer(unsigned char* buffer, unsigned int numBytes)
{
    // Divide 16-bit times two channels to get the number of samples.
    int numSamples = numBytes / 4;
    int32_t* data = new int32_t[numSamples * this->GetChannels()];
    short* shortData = (short*)buffer;
    uint32_t numUnpacked = WavpackUnpackSamples(_wavpackContext, data, numSamples);
    unsigned int dataSize = numUnpacked * sizeof(short) * this->GetChannels();
    for( unsigned int i = 0; i < numUnpacked * this->GetChannels(); i++ )
    {
        shortData[i] = data[i];
    }

    delete[] data;

    qDebug() << "Wavpack: Numbytes = " << numBytes << ", numUnpacked = " << numUnpacked << ", dataSize = " << dataSize;
    return dataSize;
}

bool FileFormatWavpack::SetPosition(unsigned int seconds)
{
    qDebug() << "FileFormatWavpack::SetPosition called with seconds = " << seconds;

    if( _wavpackContext == nullptr )
    {
        return false;
    }

    unsigned int sampleRate = WavpackGetSampleRate(_wavpackContext);
    uint64_t targetPosition = sampleRate * seconds;
    qDebug() << "Wavpack Target Position: " << targetPosition << ", SampleRate: " << sampleRate;
#ifdef WIN32
    unsigned int result = WavpackSeekSample64(_wavpackContext, targetPosition);
#else
    int result = WavpackSeekSample(_wavpackContext, targetPosition);
#endif
    if( result == 1 ) // TRUE is success.
    {
        qDebug() << "FileFormatWavpack: seeked to frame " << targetPosition;
        return true;
    }
    else
    {
        qDebug() << "Fatal Error seeking frame: " << result;
        return false;
    }
}

bool FileFormatWavpack::CanSetPosition()
{
    return true;
}

