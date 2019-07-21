#include "MusicStream.h"
#include "FileFormatMP3.h"
#include "FileFormatVorbis.h"
#include "FileFormatWavpack.h"

#include <QMessageBox>
#include <QDebug>

MusicStream::MusicStream(QDialog* parent)
{
	_audioFile = NULL;
	_parent = parent;
	//speex_bits_init(&_bits);
	//_speexDecoderState = speex_lib_get_mode(SPEEX_GET_HIGH_MODE);
	//speex_decoder_ctl(_speexDecoderState, SPEEX_GET_FRAME_SIZE, &_speexFrameSize);
    _musicFile = NULL;
	_buffers[0] = 0;
	_buffers[1] = 0;
	_format = 0;
    qDebug() << "Setting MusicStream play state to STOPPED.";
	_playState = STOPPED;
	FileFormatVorbis::Init();
	FileFormatMP3::Init();
}

MusicStream::~MusicStream()
{
	//speex_bits_destroy(&_bits);
	//speex_decoder_destroy(_speexDecoderState);
	Release();
}

bool MusicStream::Open(QString file)
{
    if( _audioFile != NULL )
    {
        qDebug() << "Deleting existing _audioFile.";
        delete _audioFile;
        _audioFile = NULL;
    }
    qDebug() << "Loading file: " << file;

	//else if( file.Contains(".spx"))
/*	{
		_fileFormat = FORMAT_SPEEX;
	}
	else*/
	if( file.contains(".mp3", Qt::CaseInsensitive) )
	{
		_audioFile = new FileFormatMP3();
		bool opened = _audioFile->Open(file);
        if( !opened ) return false;
		_fileFormat = _audioFile->GetFormat();
		if( _audioFile->GetChannels() == 1 )
		{
            _format = RTAUDIO_SINT16;
		}
		else
		{
            _format = RTAUDIO_SINT16;
		}
	}
	else if( file.contains(".wav", Qt::CaseInsensitive) )
	{
		_wavePosition = 0;
		_fileFormat = FORMAT_WAVE;
		_waveFile.Load(file.toStdString().c_str());
		_format = GetRtAudioFormatFromFile(&_waveFile);
	}
	else if( file.contains(".snd", Qt::CaseInsensitive) )
	{
		_wavePosition = 0;
		_fileFormat = FORMAT_WAVE;
		_waveFile.Load(file.toStdString().c_str());
		_format = GetRtAudioFormatFromFile(&_waveFile);
	}
    else if( file.contains(".flac", Qt::CaseInsensitive) )
    {
        _wavePosition = 0;
        _fileFormat = FORMAT_WAVE;
        _waveFile.Load(file.toStdString().c_str());
        _format = GetRtAudioFormatFromFile(&_waveFile);
    }
	else if( file.contains(".aif", Qt::CaseInsensitive) || file.contains(".aiff", Qt::CaseInsensitive) )
	{
		_wavePosition = 0;
		_fileFormat = FORMAT_WAVE;
		_waveFile.Load(file.toStdString().c_str());
		_format = GetRtAudioFormatFromFile(&_waveFile);
	}
	else if( file.contains(".wv", Qt::CaseInsensitive) )
	{
        _audioFile = new FileFormatWavpack();
        _fileFormat = FORMAT_WAVPACK;
        bool opened = _audioFile->Open(file);
        if( !opened ) return false;
        if( _audioFile->GetChannels() == 1 )
		{
            _format = RTAUDIO_SINT16;
		}
		else
		{
            _format = RTAUDIO_SINT16;
		}
	}
	else if( file.contains(".ogg", Qt::CaseInsensitive) )
	{
        _audioFile = new FileFormatVorbis();
		bool opened = _audioFile->Open(file);
        if( !opened ) return false;
		_fileFormat = _audioFile->GetFormat();
		if( _audioFile->GetChannels() == 1 )
		{
            _format = RTAUDIO_SINT16;
		}
		else
		{
            _format = RTAUDIO_SINT16;
		}
	}

    // TODO: FIXME: Create buffers for SDL_Mixer
    //alGenBuffers(2, _buffers);

	return true;
}

void MusicStream::Release()
{
    // TODO: FIXME: Delete buffers and shut down SDL_Mixer.
    //alSourceStop(_source);
    //Empty();
    //alDeleteBuffers(2, _buffers);
    //Check();
    //if( _audioFile != NULL )
    //{
    //	delete _audioFile;
    //}
}

/**
* Gets the number of channels in the currently playing file.
*/
int MusicStream::GetChannels()
{
	if( _fileFormat == FORMAT_SPEEX )
	{
		return 1;
	}
    else if( _fileFormat == FORMAT_VORBIS || _fileFormat == FORMAT_MP3 || _fileFormat == FORMAT_WAVPACK )
	{
		return _audioFile->GetChannels();
	}
	else if( _fileFormat == FORMAT_WAVE )
	{
		return _waveFile.GetNumChannels();
	}
	return 2;
}

/**
 * Gets the length of a stream in seconds, or -1 if unknown.
 */
int MusicStream::GetLength()
{
    if( _fileFormat == FORMAT_VORBIS || _fileFormat == FORMAT_MP3 || _fileFormat == FORMAT_WAVPACK )
    {
        return _audioFile->GetLength();
    }
    else if( _fileFormat == FORMAT_WAVE )
    {
        return _waveFile.GetLength();
    }
    return -1;
}

const char* MusicStream::GetArtist()
{
    if( _fileFormat == FORMAT_VORBIS || _fileFormat == FORMAT_MP3 || _fileFormat == FORMAT_WAVPACK )
    {
        return _audioFile->GetArtistName();
    }
    return NULL;
}

const char* MusicStream::GetAlbum()
{
    if( _fileFormat == FORMAT_VORBIS || _fileFormat == FORMAT_MP3 || _fileFormat == FORMAT_WAVPACK )
    {
        return _audioFile->GetAlbumName();
    }
    return NULL;
}

const char* MusicStream::GetSong()
{
    if( _fileFormat == FORMAT_VORBIS || _fileFormat == FORMAT_MP3 || _fileFormat == FORMAT_WAVPACK )
    {
        return _audioFile->GetSongName();
    }
    return NULL;
}

/**
* Gets the sample rate for the currently playing file.
*/
int MusicStream::GetRate()
{
	if( _fileFormat == FORMAT_SPEEX )
	{
		return 1;
	}
	else if( _fileFormat == FORMAT_WAVE )
	{
		return _waveFile.GetSampleRate();
	}
    else if( _fileFormat == FORMAT_MP3 || _fileFormat == FORMAT_WAVPACK || _fileFormat == FORMAT_VORBIS )
	{
		if( _audioFile != NULL )
		{
			return _audioFile->GetSampleRate();
		}
	}
	return 0;
}

/**
* Gets the bitrate for the currently playing file.  For most formats, this is the sample
* rate times the block alignment.
*/
int MusicStream::GetBitrate()
{
	if( _fileFormat == FORMAT_SPEEX )
	{
		return 1;
	}
    else if( _fileFormat == FORMAT_VORBIS || _fileFormat == FORMAT_MP3 || _fileFormat == FORMAT_WAVPACK )
	{
        int bitrate = _audioFile->GetBitrate();
        qDebug() << "File bitrate is " << bitrate;
        return bitrate;
	}
	else if( _fileFormat == FORMAT_WAVE )
	{
		return _waveFile.GetSampleRate() * _waveFile.GetBlockAlign() * 8;
	}
	return 0;
}

// TODO: Refactor this so that playback and update both use a common code block to
// buffer a block of data.
bool MusicStream::Playback()
{
    if( _playState == PAUSED )
    {
        return false;
    }

    if(Playing() )
    {
        return true;
    }

	if( _fileFormat == FORMAT_SPEEX )
	{
		if( !DecodeSpeex(_buffers[0]))
			return false;

		if( !DecodeSpeex(_buffers[1]))
			return false;
        // TODO: FIXME: Enqueue buffers.
        //alSourceQueueBuffers(_source, 2, _buffers);
	}
    else if( _fileFormat == FORMAT_VORBIS || _fileFormat == FORMAT_MP3 || _fileFormat == FORMAT_WAVPACK )
	{
		bool result = FillBuffer(_buffers[0]);
		if( !result )
		{
			return false;
		}
		result = FillBuffer(_buffers[1]);
		if( !result )
		{
			return false;
		}
        // TODO: FIXME: Enqueue buffers.
        //alSourceQueueBuffers(_source, 2, _buffers );
	}
	else if( _fileFormat == FORMAT_WAVE )
	{
		unsigned int totalSamples = _waveFile.GetNumSamples();
		int avail = totalSamples - _wavePosition;
		if( avail > WAVE_CHUNK_SIZE )
		{
			avail = WAVE_CHUNK_SIZE;
		}
		short* chunk1 = _waveFile.GetChunk(_wavePosition,_wavePosition + avail);
        // TODO: FIXME: Buffer data.
        //alBufferData(_buffers[0], _format, chunk1, avail*_waveFile.GetNumChannels()*2, _waveFile.GetSampleRate());
		delete[] chunk1;
		_wavePosition += avail;
		avail = totalSamples - _wavePosition;
		if( avail > WAVE_CHUNK_SIZE )
		{
			avail = WAVE_CHUNK_SIZE;
		}
		short* chunk2 = _waveFile.GetChunk(_wavePosition,_wavePosition + avail);
        // TODO: FIXME: Buffer data.
        //alBufferData(_buffers[1], _format, chunk2, avail*_waveFile.GetNumChannels()*2, _waveFile.GetSampleRate());
		delete[] chunk2;
		_wavePosition += avail;
        // TODO: FIXME: Enqueue buffers.
        //alSourceQueueBuffers(_source, 2, _buffers );
	}

    // TODO: FIXME: Play source.
    //alSourcePlay(_source);

    return true;
}

bool MusicStream::FillBuffer(double* buffer)
{
	bool result = false;
	unsigned char* chunk = new unsigned char[BUFFER_SIZE];
	memset(chunk, 0, BUFFER_SIZE);
	int numDone = _audioFile->FillBuffer(chunk, BUFFER_SIZE);
	if( numDone > 0 )
	{
        // TODO: FIXME: Copy data into buffer.
        //alBufferData(buffer, _format, chunk, numDone, _audioFile->GetSampleRate());
		result = true;
	}
	delete[] chunk;
    Check();
	return result;
}

bool MusicStream::DecodeSpeex(double* buffer)
{
	int chunkSize;
	char cbits[256];
	float* output = new float[_speexFrameSize];
	short* out = new short[_speexFrameSize];
	int numRead = fread(&chunkSize, sizeof(int), 1, _musicFile);
	numRead = fread(cbits, 1, chunkSize, _musicFile);
	//speex_bits_read_from(&_bits, cbits, chunkSize);
	//speex_decode(_speexDecoderState, &_bits, output);
	for( int i = 0; i < _speexFrameSize; i++ )
	{
		out[i] = output[i];
	}
    // TODO: FIXME: Copy data into buffer
    //alBufferData(buffer, RTAUDIO_SINT16, out, _speexFrameSize*2, 44100);
	return true;
}

bool MusicStream::PausePlayback()
{
    if( _playState != PAUSED )
    {
        qDebug() << "Setting MusicStream play state to PAUSED.";
	    _playState = PAUSED;
        // TODO: FIXME: Pause audio.
        //alSourcePause( _source );
    }
    else if( _playState == PAUSED )
    {
        qDebug() << "Setting MusicStream play state to PLAYING.";
        _playState = PLAYING;
        // TODO: FIXME: Resume audio.
        //alSourcePlay( _source );
    }
    // Do nothing if we are in stopped state.
	return true;
}

bool MusicStream::Playing()
{
    // TODO: FIXME: Query SDL_mixer play state and return the results.
    return _playState == PLAYING;

    //ALenum state;
    //alGetSourcei(_source, AL_SOURCE_STATE, &state);
    //bool retval = (state == AL_PLAYING);
    //return retval;
}

bool MusicStream::IsPlaying()
{
	return ( _playState == PLAYING );
}

bool MusicStream::IsPaused()
{
    return ( _playState == PAUSED );
}

bool MusicStream::Update()
{
    int processed = 0;
    bool result = true;

    // TODO: FIXME: Get buffers processed if necessary.
    //alGetSourcei(_source, AL_BUFFERS_PROCESSED, &processed);

    while(processed--)
    {
        //ALuint buffer;

        // TODO: FIXME: Unqueue buffers.
        //alSourceUnqueueBuffers(_source, 1, &buffer);
        Check();

        if( _fileFormat == FORMAT_VORBIS || _fileFormat == FORMAT_MP3 || _fileFormat == FORMAT_WAVPACK )
		{
            // TODO: FIXME: Fill buffer.
            //bool result = FillBuffer(buffer);
			if( !result )
			{
				return false;
			}
            // TODO: FIXME: Enqueue buffers.
            //alSourceQueueBuffers(_source, 1, &buffer );
		}
        /*else if( _fileFormat == FORMAT_WAVPACK )
		{
			int size = WAVE_CHUNK_SIZE * this->GetChannels(); // 8820 samples x 2 channels = 17640 ints of data samples for stereo.
			int32_t* data = new int32_t[size]; // 17640 shorts of data for 8820 stereo samples
			short* shortData = new short[size];
			uint32_t numUnpacked = WavpackUnpackSamples(_wavpackContext, data, WAVE_CHUNK_SIZE);
			if( numUnpacked < 1 )
			{
				result = false;
			}
			else
			{
				for( unsigned int i = 0; i < numUnpacked * this->GetChannels(); i++ )
				{
					shortData[i] = data[i];
				}
				int dataSize = numUnpacked * sizeof(short) * this->GetChannels();
				int rate = GetRate();
				alBufferData(buffer, _format, shortData, dataSize, rate);
				alSourceQueueBuffers(_source, 1, &buffer);
			}
			delete[] data;
			delete[] shortData;

		}
        */
		else if( _fileFormat == FORMAT_WAVE )
		{
			unsigned int totalSamples = _waveFile.GetNumSamples();
			int avail = totalSamples - _wavePosition;
			if( avail < 2 )
			{
				result = false;
			}
			else if( avail > WAVE_CHUNK_SIZE )
			{
				avail = WAVE_CHUNK_SIZE;
			}
			short* chunk = _waveFile.GetChunk(_wavePosition,_wavePosition + avail);
            // TODO: FIXME: Buffer data.
            //alBufferData(buffer, _format, chunk, avail*_waveFile.GetNumChannels()*2, _waveFile.GetSampleRate());
			delete[] chunk;
			_wavePosition += avail;
            // TODO: FIXME: Enqueue buffers.
            //alSourceQueueBuffers(_source, 1, &buffer );
		}
    }

    return result;
}

void MusicStream::Empty()
{
    int queued = 0;

    //alGetSourcei(_source, AL_BUFFERS_QUEUED, &queued);

    while(queued--)
    {
        // TODO: FIXME: Unqueue buffers.
        //ALuint buffer;
        //alSourceUnqueueBuffers(_source, 1, &buffer);
        Check();
    }
}

void MusicStream::Check()
{
}

int MusicStream::Play()
{
    if( _playState == PAUSED )
    {
        // TODO: FIXME: Play source.
        //alSourcePlay( _source );
    }
    qDebug() << "Setting MusicStream play state to PLAYING.";
	_playState = PLAYING;

	return 0;
}

int MusicStream::PlayFile(QString file)
{
	if( !Open(file) )
	{
		return -1;
	}
    qDebug() << "Setting MusicStream play state to PLAYING.";
	_playState = PLAYING;

	return 0;
}

void MusicStream::Stop()
{
    qDebug() << "Setting MusicStream play state to STOPPED.";
	_playState = STOPPED;
}

void MusicStream::run()
{
    qDebug() << "Music playback thread started.";
	while( 1 )
	{
		if( !(_playState == PLAYING) )
		{
#ifdef WIN32
			Sleep( 50 );
#else
            usleep(50000);
#endif
		}
		else
		{
			if(!Playback())
			{
#ifdef WIN32
                QMessageBox( QMessageBox::Information, "Song Refused to Play", "ERROR", QMessageBox::Ok );
#endif
				return;
			}
			while(Update() && (_playState == PLAYING || _playState == PAUSED) )
			{
				if(!Playing() && _playState != PAUSED )
				{
					if( !Playback() )
					{
#ifdef WIN32
                        QMessageBox( QMessageBox::Information, "Song abruptly stopped", "ERROR", QMessageBox::Ok );
#endif
						return;
					}
					else
					{
						//MessageBox( NULL, "Ogg stream was interrupted", "ERROR", MB_OK );
					}
				}
#ifdef WIN32
				Sleep(1);
#else
                usleep(1000);
#endif
			}
            qDebug() << "Setting MusicStream play state to STOPPED.";
			_playState = STOPPED;
		}
	}
    qDebug() << "Music playback thread exiting.";
	return;
}

void MusicStream::SetVolume( float volume )
{
    if( volume > 1.0f )
    {
        volume = 1.0f;
    }

    // TODO: FIXME: Set volume.
    //alSourcef( _source, AL_GAIN, volume );
}

RtAudioFormat MusicStream::GetRtAudioFormatFromFile(WaveFile* file)
{
	int channels = file->GetNumChannels();

	// TODO: FIXME
	// Note: Any 32-bit .wav file that is loaded passes through this function
	// and is assigned a 16-bit OpenAL format and sounds terrible when played.
	// We need to fix this.

	if( channels == 1 )
	{
        return RTAUDIO_SINT16;
	}
	else if( channels == 2)
	{
        return RTAUDIO_SINT16;
	}

    return RTAUDIO_SINT16;
}

bool MusicStream::SetPosition(unsigned int position)
{
    if( _fileFormat == FORMAT_WAVE )
    {
        unsigned int pos = GetRate() * position;
        qDebug() << "SetPosition on FORMAT_WAVE: Bitrate = " << this->GetRate() << ", Seconds = " << position << ", Sample position = " << pos;
        if( pos >= _waveFile.GetDataLength())
        {
            qDebug() << "Trying to seek past end of file, cannot set position";
            return false;
        }
        else if( pos >= 0 )
        {
            this->_wavePosition = pos;
            return true;
        }
        else
        {
            qDebug() << "Negative value, cannot set position.";
            return false;
        }
    }
    else if( _audioFile != NULL )
    {
        return _audioFile->SetPosition(position);
    }
    return false;
}

bool MusicStream::CanSetPosition()
{
    if( _fileFormat == FORMAT_WAVE )
    {
        return true;
    }
    else if( _audioFile != NULL )
    {
        return _audioFile->CanSetPosition();
    }
    return false;
}
