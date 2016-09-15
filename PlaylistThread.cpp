#include "VorbitalDlg.h"
#include "PlaylistThread.h"
#include <QDebug>

PlaylistThread::PlaylistThread(VorbitalDlg* dlg)
{
    _dlg = dlg;
    _done = false;
}

PlaylistThread::~PlaylistThread()
{
    stop();
}

void PlaylistThread::stop()
{
    _done = true;
}

void PlaylistThread::run()
{
    printf("Entering playlist thread.\n");
	while( !_done )
	{
		if( !(_dlg->GetPlayState() == PLAYING) )
		{
#ifdef WIN32
			Sleep( 30 );
#else
            usleep(30000);
#endif
		}
		else
		{
			while( _dlg->GetPlayState() == PLAYING )
			{
                printf("Resetting time elapsed.\n");
                _dlg->ResetTime();
                if( _dlg->GetPlaylist()->count() > 0 )
                {
				    _dlg->GetPlaylist()->setCurrentRow( _dlg->GetListPosition() );
					if( _dlg->GetIncrementNeeded() == false )
					{
						_dlg->SetIncrementNeeded(true);
					}
                }
                else
                {
                    _dlg->SetPlayState(STOPPED);
                    break;
                }
                QString filename;
                int position = _dlg->GetListPosition();
                QListWidgetItem* item = _dlg->GetPlaylist()->item(position);
                QVariant variant = item->data(Qt::UserRole);
                filename = variant.toString();
				if( filename.isEmpty() )
				{
					_dlg->SetPlayState(STOPPED);
					break;
				}
				if( filename.length() < 1 )
				{
                    qDebug() << "Nothing to play.";
					_dlg->SetPlayState(STOPPED);
					break;
				}
                MusicStream* stream = _dlg->GetMusicStream();
                qDebug() << "Calling stream->Open on " << filename;
				if( stream->Open(filename) )
                {
				    _dlg->GetMusicStream()->Play();
                    qDebug() << "Updating channels, bitrate, sample rate, and length.";
                    _dlg->UpdateNumChannels(_dlg->GetMusicStream()->GetChannels() );
                    _dlg->UpdateBitrate(_dlg->GetMusicStream()->GetBitrate());
                    _dlg->UpdateSampleRate(_dlg->GetMusicStream()->GetRate());
                    _dlg->LoadAlbumArt(filename);
                    _dlg->UpdateSongLength(_dlg->GetMusicStream()->GetLength());
                    _dlg->UpdateArtist(_dlg->GetMusicStream()->GetArtist());
                    _dlg->UpdateAlbum(_dlg->GetMusicStream()->GetAlbum());
                    _dlg->UpdateSong(_dlg->GetMusicStream()->GetSong());
				}
                else
                {
                    qDebug() << "Stream open failed.";
                    _dlg->OnButtonForwardClick();
                }

				while( _dlg->GetMusicStream()->IsPlaying() || _dlg->GetMusicStream()->IsPaused() )
				{
                    //printf("Updating time.\n");
                    if( !_dlg->GetMusicStream()->IsPaused() )
                    {
                        _dlg->UpdateTime();
                    }
                    else
                    {
                        _dlg->PausedUpdateTime();
                    }
#ifdef WIN32
				    Sleep(50);
#else
                    usleep(50000);
#endif
				}
				if( _dlg->GetPlayState() == PLAYING )
				{
					// Set play pointer to next item.  We use a goofy bool to keep from
					// getting hosed on skip forward and skip back.
					if( _dlg->GetIncrementNeeded() == false )
					{
						_dlg->SetIncrementNeeded(true);
					}
					else
					{
						if( !_dlg->GetRandomize() )
						{
							_dlg->SetListPosition(_dlg->GetListPosition() + 1);
						}
						else
						{
							_dlg->SetListPosition( rand() % _dlg->GetPlaylist()->count() );
						}
					}
					// Wrap list if necessary.
					if( _dlg->GetListPosition() >= _dlg->GetPlaylist()->count() )
					{
						_dlg->SetListPosition(0);
					}
				}
			}
            printf("Skipped while playstate == PLAYING loop.\n");
		}
	}
    printf("Exiting playlist thread.\n");
	return;
}

