#include "VorbitalDlg.h"
#include "SettingsDlg.h"
#include "alut.h"
#ifndef WIN32
#include <sys/stat.h>
#include <unistd.h>
#endif

#include <QFile>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QBitmap>
#include <QSettings>
#include <QStringList>
#include <QMetaMethod>
#include <QCloseEvent>
#include <QDebug>
#include <QMimeData>
#include <QStandardPaths>

#include "add.xpm"
#include "folder.xpm"
#include "forward.xpm"
// For the settings dialog.
//#include "gear.xpm"
#include "normal.xpm"
#include "null.xpm"
#include "pause.xpm"
#include "play.xpm"
#include "question.xpm"
#include "random.xpm"
#include "remove.xpm"
#include "reverse.xpm"
#include "stop.xpm"
#include "speaker.xpm"
#include "speaker_quiet.xpm"

VorbitalDlg::~VorbitalDlg()
{
    _playlistThread->terminate();
    alutExit();
}

/*!
 * VorbitalDlg creator
 */
VorbitalDlg::VorbitalDlg( )
{
    // Remove the question mark from the top of the window.
    Qt::WindowFlags flags = windowFlags();
    flags = flags & (~Qt::WindowContextHelpButtonHint);
    // Add minimize button.
    flags = flags | Qt::WindowMinimizeButtonHint;
    setWindowFlags(flags);

    _device = nullptr;
    qDebug() << "VorbitalDlg Create.";
	_done = false;
	// OpenAL Initialization
    _device = alcOpenDevice(nullptr);
    _context = alcCreateContext(_device, nullptr);
    alcMakeContextCurrent(_context);
	alGetError();
	// Initialize position of the Listener.
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
	// Velocity of the Listener.
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
	// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
	// Also note that these should be units of '1'.
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);

    _volume = 100;
    _muted = false;
	_listPosition = 0;
    _musicStream = nullptr;
    _btnBrowse = nullptr;
    _btnBrowseFolder = nullptr;
    _btnPlay = nullptr;
    _btnStop = nullptr;
    _btnPause = nullptr;
    _btnForward = nullptr;
    _btnReverse = nullptr;
    _btnClear = nullptr;
    _btnRemove = nullptr;
    _btnSettings = nullptr;
    _btnAbout = nullptr;
    _btnRandomize = nullptr;
    _txtSampleRate = nullptr;
    _txtVersion = nullptr;
    _txtBitRate = nullptr;
    _txtChannels = nullptr;
    _txtComment = nullptr;
    _txtTime = nullptr;
    _txtTimeDivider = nullptr;
    _txtMaxTime = nullptr;
    _txtArtist = nullptr;
    _volumeSlider = nullptr;
    _positionSlider = nullptr;
    _msecElapsed = 0;
    _songLength = -1;
    qDebug() << "Setting VorbitalDlg play state to STOPPED.";
	_playState = STOPPED;
	_incrementNeeded = true;
    _randomize = false;
	_menuDoubleClicked = false;
    _lastSelectedDirectory = QString(QStandardPaths::MusicLocation);
    // TODO: Do we need to do this on Windows?
#ifdef linux
	srand((unsigned)time(0));
#endif
    CreateControls();
	LoadSettings();
    QIcon icon("vorbital.ico");
	setWindowIcon(icon);
    setWindowTitle("Vorbital Player");
	// Start up the playlist thread.
    _playlistThread = new PlaylistThread(this);
	_playlistThread->start();
}

void VorbitalDlg::LoadSettings()
{
	QSettings* configData = new QSettings("Zeta Centauri", "Vorbital Player");
    qDebug() << "LoadSettings loading file " << configData->fileName() << ".";

	// Randomizer setting.
	_randomize = configData->value( "randomize" ).toInt();
	if( _randomize )
	{
		_btnRandomize->setIcon(QPixmap(random_xpm));
	}
	else
	{
		_btnRandomize->setIcon(QPixmap(normal_xpm));
	}
	// Volume setting.
    int wantedVolume = configData->value("volume", 100).toInt();
    _volumeSlider->setValue(wantedVolume);
    int volume = _volumeSlider->value();
    float actualVol = float(volume / 100.0f);
    if( _musicStream != nullptr )
    {
        _musicStream->SetVolume( actualVol );
    }
	// Window size.
	int sizex = (configData->value( "sizex" )).toInt();
	int sizey = (configData->value( "sizey" )).toInt();
	if( sizex > 0 && sizey > 0 )
	{
        setFixedSize(sizex, sizey);
        setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
	}
    // Previous playlist.
    QString songs = configData->value("playlist").toString();
    QStringList songList = songs.split(";");
    for( int i = 0; i < songList.count(); i++ )
    {
        if( songList[i].length() < 2 )
        {
            continue;
        }
        QFileInfo info(songList[i]);
        if( info.exists() )
        {
            LoadFile(info.absoluteFilePath(), false);
        }
        else
        {
            qDebug() << "File" << songList[i] << " from last session not found. Not adding to playlist.";
        }
    }
    int playlistPos = (configData->value("playlistPosition")).toInt();
    if( playlistPos < _lstPlaylist->count())
    {
        _listPosition = playlistPos;
        _lstPlaylist->setCurrentRow(_listPosition);
    }
    QString lastDir = (configData->value("lastSelectedDirectory")).toString();
    if( lastDir.length() > 0)
    {
        _lastSelectedDirectory = lastDir;
    }
    qDebug() << "Loaded Settings: Randomize =" << _randomize << ", Volume =" << volume << ", Width =" << sizex <<
        ", Height =" << sizey << ", Playlist =" << songList.count() << " items, Last Directory = " << _lastSelectedDirectory;
	delete configData;
}

void VorbitalDlg::SaveSettings()
{
    qDebug() << "SaveSettings.";
	QSettings* configData = new QSettings("Zeta Centauri", "Vorbital Player");
	configData->setValue("randomize", _randomize);
	configData->setValue("volume", _volumeSlider->value());
	QSize wsize = size();
	configData->setValue("sizex", wsize.width());
	configData->setValue("sizey", wsize.height());
    QString playlistItems;
    for( int i = 0; i < _lstPlaylist->count(); i++ )
    {
        QListWidgetItem* item = _lstPlaylist->item(i);
        QVariant variant = item->data(Qt::UserRole);
        QString filename = variant.toString();
        qDebug() << "Saving Playlist Item: " << filename << "'.";
        if( i > 0 )
        {
            playlistItems += ";";
        }
		playlistItems += filename;
    }
    configData->setValue("playlist", playlistItems);
    configData->setValue("playlistPosition", _listPosition);
    configData->setValue("lastSelectedDirectory", _lastSelectedDirectory);
    configData->sync();
    qDebug() << "Saved Settings: Randomize =" << _randomize << ", Volume =" << _volumeSlider->value() <<
        ", Width =" << wsize.width() << ", Height =" << wsize.height() << ", Playlist =" << _lstPlaylist->count() <<
        " items, last selected directory = " << _lastSelectedDirectory;
	delete configData;
}

/*!
 * Control creation for VorbitalDlg
 */
void VorbitalDlg::CreateControls()
{
    qDebug() << "CreateControls.";
    QFont f( "Calibri", 10, QFont::Bold);
    setAcceptDrops(true);

    QVBoxLayout* rootLayout = new QVBoxLayout();
    setLayout(rootLayout);

    QHBoxLayout* firstRowLayout = new QHBoxLayout();
    rootLayout->addLayout(firstRowLayout);

    firstRowLayout->setContentsMargins(QMargins(0,0,0,0));
    firstRowLayout->setSpacing(2);

	_btnBrowse = new QPushButton( this );
    _btnBrowse->setIcon(QPixmap(add_xpm));
    //_btnBrowse->setFlat(true);
    _btnBrowse->setToolTip("Add file to playlist");
    connect(_btnBrowse, SIGNAL(released()), this, SLOT(OnButtonBrowseClick()));
    firstRowLayout->addWidget(_btnBrowse);

    _btnBrowseFolder = new QPushButton( this );
    _btnBrowseFolder->setIcon(QPixmap(folder_xpm));
    //_btnBrowseFolder->setFlat(true);
    _btnBrowseFolder->setToolTip("Add folder to playlist");
    connect(_btnBrowseFolder, SIGNAL(released()), this, SLOT(OnButtonBrowseFolderClick()));
    firstRowLayout->addWidget(_btnBrowseFolder);

    _btnRemove = new QPushButton( this );
    _btnRemove->setIcon(QPixmap(remove_xpm));
    //_btnRemove->setFlat(true);
    _btnRemove->setToolTip("Remove selected item from playlist");
    connect(_btnRemove, SIGNAL(released()), this, SLOT(OnButtonRemoveClick()));
    firstRowLayout->addWidget(_btnRemove);

    _btnClear = new QPushButton( this );
    _btnClear->setIcon(QPixmap(null_xpm));
    _btnClear->setToolTip("Clear playlist");
    connect(_btnClear, SIGNAL(released()), this, SLOT(OnButtonClearClick()));
    firstRowLayout->addWidget(_btnClear);

	_btnReverse = new QPushButton( this );
    _btnReverse->setIcon(QPixmap(reverse_xpm));
    _btnReverse->setToolTip("Previous track");
    connect(_btnReverse, SIGNAL(released()), this, SLOT(OnButtonReverseClick()));
    firstRowLayout->addWidget(_btnReverse);

	_btnPause = new QPushButton( this );
    _btnPause->setIcon(QPixmap(pause_xpm));
    _btnPause->setToolTip("Pause");
    connect(_btnPause, SIGNAL(released()), this, SLOT(OnButtonPauseClick()));
    firstRowLayout->addWidget(_btnPause);

	_btnStop = new QPushButton( this );
    _btnStop->setIcon(QPixmap(stop_xpm));
    _btnStop->setToolTip("Stop");
    connect(_btnStop, SIGNAL(released()), this, SLOT(OnButtonStopClick()));
    firstRowLayout->addWidget(_btnStop);

	_btnPlay = new QPushButton( this );
    _btnPlay->setIcon(QPixmap(play_xpm));
    _btnPlay->setToolTip("Play");
    connect(_btnPlay, SIGNAL(released()), this, SLOT(OnButtonPlayClick()));
    firstRowLayout->addWidget(_btnPlay);

    _btnForward = new QPushButton( this );
    _btnForward->setIcon(QPixmap(forward_xpm));
    _btnForward->setToolTip("Next track");
    connect(_btnForward, SIGNAL(released()), this, SLOT(OnButtonForwardClick()));
    firstRowLayout->addWidget(_btnForward);

    _btnRandomize = new QPushButton( this );
    _btnRandomize->setIcon(QPixmap(normal_xpm));
    _btnRandomize->setToolTip("Turn shuffle on or off");
    connect(_btnRandomize, SIGNAL(released()), this, SLOT(OnButtonRandomizeClick()));
    firstRowLayout->addWidget(_btnRandomize);

	_btnAbout = new QPushButton( this );
    _btnAbout->setIcon(QPixmap(question_xpm));
    _btnAbout->setToolTip("About Vorbital Player");
    connect(_btnAbout, SIGNAL(released()), this, SLOT(OnAbout()));
    firstRowLayout->addWidget(_btnAbout);

    QHBoxLayout* secondRowLayout = new QHBoxLayout();
    rootLayout->addLayout(secondRowLayout);

    secondRowLayout->insertSpacing(6, 6);

    _txtSampleRate = new QLabel(this);
    _txtSampleRate->setFont(f);
    _txtSampleRate->setText("");
    secondRowLayout->addWidget(_txtSampleRate);

	secondRowLayout->insertSpacing(4, 4);

    _txtBitRate = new QLabel(this);
    _txtBitRate->setFont(f);
    _txtBitRate->setText("");
    secondRowLayout->addWidget(_txtBitRate);

    secondRowLayout->insertSpacing(4, 4);

    _txtChannels = new QLabel(this);
    _txtChannels->setFont(f);
    _txtChannels->setText("");
    secondRowLayout->addWidget(_txtChannels);

	secondRowLayout->insertSpacing(10, 10);

    _btnVolume = new QPushButton(this);

    _speaker = new QPixmap(speaker_xpm);
    _speakerQuiet = new QPixmap(speaker_quiet_xpm);
    _btnVolume->setIcon(*_speaker);
    _btnVolume->setFlat(true);
    connect(_btnVolume, SIGNAL(released()), this, SLOT(OnSpeakerClicked()));
    secondRowLayout->addWidget(_btnVolume);

    _volumeSlider = new QSlider(Qt::Horizontal, this);
    _volumeSlider->setMinimum(0);
    _volumeSlider->setMaximum(100);
    _volumeSlider->setValue(100);
    _volumeSlider->setMaximumSize(100, 24);
    // This doesn't give any errors, but doesn't seem to work.
    //connect(this, SIGNAL(volumeChanged(int)), this, SLOT(OnVolume(int)), Qt::AutoConnection);
    connect(_volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(OnVolume(int)), Qt::AutoConnection);
    secondRowLayout->addWidget(_volumeSlider);

	secondRowLayout->insertSpacing(10, 10);

    QHBoxLayout* thirdRowLayout = new QHBoxLayout();
    rootLayout->addLayout(thirdRowLayout);
    rootLayout->setAlignment(thirdRowLayout, Qt::AlignHCenter);

	QBitmap* bitmap = new QBitmap(120, 120);
	_albumArt = new QLabel(this);
    _albumArt->setPixmap(*bitmap);
    thirdRowLayout->addWidget(_albumArt);
	_albumArt->setVisible(false);

    QHBoxLayout* fourthRowLayout = new QHBoxLayout();
    rootLayout->setAlignment(fourthRowLayout, Qt::AlignLeft);
    rootLayout->addLayout(fourthRowLayout);

    _txtArtist = new QLabel(this);
    _txtArtist->setText("");
    _txtArtist->setFont(f);
    fourthRowLayout->addWidget(_txtArtist);
    rootLayout->setAlignment(fourthRowLayout, Qt::AlignHCenter);

    fourthRowLayout->insertSpacing(16, 16);

    // Hide artist, album, and song unless there's data.
    _txtArtist->hide();

    QHBoxLayout* fifthRowLayout = new QHBoxLayout();
    rootLayout->addLayout(fifthRowLayout);

    _positionSlider = new QSlider(Qt::Horizontal, this);
    // Use a range 1000 values so slider can move more smoothly.
    _positionSlider->setMinimum(0);
    _positionSlider->setMaximum(1000);
    _positionSlider->setValue(0);
    connect(_positionSlider, SIGNAL(sliderReleased()), this, SLOT(OnPositionSlider()), Qt::AutoConnection);
    fifthRowLayout->addWidget(_positionSlider);

    _txtTime = new QLabel(this);
    _txtTime->setFont(f);
    _txtTime->setText("0:00");
    fifthRowLayout->addWidget(_txtTime);

    _txtTimeDivider = new QLabel(this);
    _txtTimeDivider->setText("/");
    fifthRowLayout->addWidget(_txtTimeDivider);

    _txtMaxTime = new QLabel(this);
    _txtMaxTime->setFont(f);
    _txtMaxTime->setText("0:00");
    fifthRowLayout->addWidget(_txtMaxTime);

    // Disable time slider.
    _positionSlider->setEnabled(false);

	_lstPlaylist = new QListWidget( this );
	rootLayout->addWidget(_lstPlaylist);
	connect(_lstPlaylist, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(OnPlaylistDoubleClick(QListWidgetItem*)), Qt::AutoConnection);

    connect(this, SIGNAL(bitrateChanged(int)), this, SLOT(OnBitrate(int)), Qt::AutoConnection);
    connect(this, SIGNAL(numchannelsChanged(int)), this, SLOT(OnNumChannels(int)), Qt::AutoConnection);
    connect(this, SIGNAL(samplerateChanged(int)), this, SLOT(OnSampleRate(int)), Qt::AutoConnection);
    connect(this, SIGNAL(timeChanged(int)), this, SLOT(OnTime(int)), Qt::AutoConnection);
    connect(this, SIGNAL(albumArtChanged(const QString&)), this, SLOT(OnAlbumArtChanged(const QString&)), Qt::AutoConnection);
    connect(this, SIGNAL(artistChanged(const QString&)), this, SLOT(OnArtistChanged(const QString&)), Qt::AutoConnection);
    connect(this, SIGNAL(albumChanged(const QString&)), this, SLOT(OnAlbumChanged(const QString&)), Qt::AutoConnection);
    connect(this, SIGNAL(songChanged(const QString&)), this, SLOT(OnSongChanged(const QString&)), Qt::AutoConnection);
    connect(this, SIGNAL(songLengthChanged(int)), this, SLOT(OnSongLengthChanged(int)), Qt::AutoConnection);
}

void VorbitalDlg::OnBitrate(int value)
{
  qDebug() << "Bitrate changed to " << value << ".";
  _txtBitRate->setText(QString("%1 kbps").arg(value));
}

void VorbitalDlg::OnListPosition()
{
  //_lstPlaylist->SetSelection(event.GetString());
}

void VorbitalDlg::OnSpeakerClicked()
{
    if(_muted)
    {
        _muted = false;
        float actualVol = float(_volume / 100.0f);
        _musicStream->SetVolume( actualVol );
        _btnVolume->setIcon(*_speaker);
    }
    else
    {
        _muted = true;
        _musicStream->SetVolume(0.0f);
        _btnVolume->setIcon(*_speakerQuiet);
    }
    qDebug() << "Muted changed to " << _muted << ".";
}

void VorbitalDlg::OnNumChannels(int data)
{
  qDebug() << "Number of channels changed to " << data << ".";
  if( data == 1 )
  {
    _txtChannels->setText("Mono");
  }
  else
  {
    _txtChannels->setText("Stereo");
  }
}

void VorbitalDlg::OnTime(int milliseconds)
{
  int seconds = milliseconds / 1000;
  QString label;
  if( (seconds % 60) > 9 )
  {
 	  label = QString("%1:%2").arg(seconds / 60).arg(seconds % 60);
  }
  else
  {
      label = QString("%1:0%2").arg(seconds / 60).arg(seconds % 60);
  }
  //qDebug() << "Time changed to " << label;
  _txtTime->setText(label);
  if( _songLength > 0 )
  {
      int pos = milliseconds / _songLength;
      //qDebug() << "Position slider changed to " << pos;
      // Only update the slider if it's not currently being dragged,
      // otherwise it screws up our ability to drag it.
      if( !_positionSlider->isSliderDown() )
      {
          _positionSlider->setValue(pos);
      }
  }
}

void VorbitalDlg::OnSampleRate(int data)
{
  qDebug() << "Samplerate changed to " << data << ".";
  _txtSampleRate->setText(QString("%1 Hz").arg(data));
}

/**
* Handles right mouse clicks on the playlist.
*/
// TODO: Reimplement this, and bind it to a right click signal.
// This could be used to show an ID3 tag editor.
void VorbitalDlg::OnRightClick()
{
	//int index = _lstPlaylist->itemAt(<< mouse position >>);
	//if( index > -1 )
	//{
	//	ShowFileInfo(index);
	//}
}

/**
* Shows file details for a playlist item.
*/
void VorbitalDlg::ShowFileInfo(int index)
{
    QListWidgetItem* item = _lstPlaylist->item(index);
    QVariant variant = item->data(Qt::UserRole);
    QString filename = variant.toString();
	QMessageBox(QMessageBox::Information, filename, "File Location", QMessageBox::Ok);
}

bool VorbitalDlg::ShowToolTips()
{
    return true;
}

void VorbitalDlg::OnButtonBrowseClick()
{
    QStringList filenames = QFileDialog::getOpenFileNames( this, "Choose a file", _lastSelectedDirectory,
        "Supported Files (*.aif *.aiff *.flac *.mp3 *.ogg *.snd *.wav *.wv)" );

	for( int i = 0; i < filenames.length(); i++ )
	{
        QFileInfo info(filenames[i]);
        LoadFile(info.absoluteFilePath(), false);
        // Use the first file to set the last selected directory.
        if( i == 0)
        {
            _lastSelectedDirectory = info.absoluteDir().path();
        }
	}

	if( _lstPlaylist->currentRow() < 0 )
	{
		_lstPlaylist->setCurrentRow(0);
		_listPosition = 0;
	}
}

void VorbitalDlg::AddFolderToPlaylist(const QString& folder)
{
    qDebug() << "Directory: " << folder << ".";
    QDir workingDirectory(folder);
    QStringList filters;
    filters << "*.wav" << "*.mp3" << "*.ogg" << "*.wv" << "*.snd" << "*.aif" << "*.aiff" << "*.flac";
    QFileInfoList files = workingDirectory.entryInfoList(filters, QDir::Files, QDir::Name);
    for( int i = 0; i < files.count(); i++ )
    {
        LoadFile(files[i].absoluteFilePath(), false);
    }
    QFileInfoList folders = workingDirectory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
    for( int i = 0; i < folders.count(); i++ )
    {
        qDebug() << "Need to recurse directory: " << folders[i].absoluteFilePath();
        AddFolderToPlaylist(folders[i].absoluteFilePath());
    }

    if( _lstPlaylist->currentRow() < 0 )
    {
        _lstPlaylist->setCurrentRow(0);
        _listPosition = 0;
    }
}

void VorbitalDlg::OnButtonBrowseFolderClick()
{
	QFileDialog fdialog( this, "Choose a directory", ".");
    QString dir = QFileDialog::getExistingDirectory(this, "Choose a directory", _lastSelectedDirectory, QFileDialog::ShowDirsOnly);
    AddFolderToPlaylist(dir);
    _lastSelectedDirectory = dir;
}

void VorbitalDlg::OnButtonStopClick()
{
    qDebug() << "Stop clicked.";
    qDebug() << "Setting VorbitalDlg play state to STOPPED.";
	_playState = STOPPED;

	if( _musicStream )
	{
		_musicStream->Stop();
	}
}

void VorbitalDlg::OnButtonPauseClick()
{
    qDebug() << "Pause clicked.";
	if( _playState == PLAYING )
	{
		_musicStream->PausePlayback();
	}
}

void VorbitalDlg::OnButtonSettingsClick()
{
	SettingsDlg* dlg = new SettingsDlg(this);
    dlg->setModal(true);
	dlg->show();
	delete dlg;
}

void VorbitalDlg::OnButtonReverseClick()
{
	if( _lstPlaylist->count() < 1 )
	{
		return;
	}

	bool playing = false;

	if( _musicStream )
	{
		if( _musicStream->IsPlaying() || _musicStream->IsPaused() )
		{
			_musicStream->Stop();
			playing = true;
		}
	}

	// Set play pointer to next item.
	if( !_randomize )
	{
		--_listPosition;
	}
	else
	{
		_listPosition = rand() % _lstPlaylist->count();
	}
	_incrementNeeded = false;
	// Wrap list if necessary.
	if( _listPosition < 0 )
	{
		_listPosition =  _lstPlaylist->count() - 1;
	}
	_lstPlaylist->setCurrentRow( _listPosition );

	if( playing == true )
	{
		OnButtonPlayClick();
	}
}

void VorbitalDlg::OnAlbumArtChanged(const QString& filename)
{
    QPixmap image;
    if( image.load(filename) )
    {
        image = image.scaled(QSize(150, 150), Qt::KeepAspectRatio);
        _albumArt->setPixmap(image);
        _albumArt->setVisible(true);
    }
}

void VorbitalDlg::UpdateSongName()
{
    _txtArtist->setText(QString("%1 - %2 - %3").arg(_artist, _album, _song));
    _txtArtist->show();
}

void VorbitalDlg::OnArtistChanged(const QString& artist)
{
    _artist = artist;
    UpdateSongName();
}

void VorbitalDlg::OnAlbumChanged(const QString& album)
{
    _album = album;
    UpdateSongName();
}

void VorbitalDlg::OnSongChanged(const QString& song)
{
    _song = song;
    UpdateSongName();
}

void VorbitalDlg::OnButtonForwardClick()
{
	if( _lstPlaylist->count() < 1 )
	{
		return;
	}

	bool playing = false;

	if( _musicStream )
	{
		if( _musicStream->IsPlaying() || _musicStream->IsPaused() )
		{
			_musicStream->Stop();
			playing = true;
		}
	}

	// Set play pointer to next item.
	if( !_randomize )
	{
		++_listPosition;
	}
	else
	{
		_listPosition = rand() % _lstPlaylist->count();
	}
	_incrementNeeded = false;
	// Wrap list if necessary.
	if( _listPosition >= _lstPlaylist->count() )
	{
		_listPosition = 0;
	}
	_lstPlaylist->setCurrentRow( _listPosition );

	if( playing == true )
	{
		OnButtonPlayClick();
	}
}

void VorbitalDlg::OnButtonRandomizeClick()
{
	_randomize = !_randomize;
	if( _randomize )
	{
		_btnRandomize->setIcon( QPixmap(random_xpm) );
	}
	else
	{
		_btnRandomize->setIcon( QPixmap(normal_xpm) );
	}
}

/*!
 * Remove from playlist butto handler.
 */
void VorbitalDlg::OnButtonRemoveClick()
{
	// Can't delete from a blank list.
	if( _lstPlaylist->count() < 1 )
	{
		return;
	}

    int removePosition = _lstPlaylist->currentRow();

	// Remove the currently selected item from the playlist, or the first item if nothing is selected.
	if( removePosition == -1 && _lstPlaylist->count() > 0 )
	{
		removePosition = 0;
	}
	QListWidgetItem* item = _lstPlaylist->takeItem( removePosition );
    delete item;

	if( _lstPlaylist->count() > 0 )
	{
		// Decrement the list position if it was at the end.
		if( _listPosition >= _lstPlaylist->count() )
		{
			--_listPosition;
		}
		if( removePosition >= _lstPlaylist->count() )
		{
			--removePosition;
		}
		_lstPlaylist->setCurrentRow( removePosition );
	}
}

void VorbitalDlg::OnButtonClearClick()
{
    _lstPlaylist->clear();
    _listPosition = 0;
    qDebug() << "Setting VorbitalDlg play state to STOPPED.";
    _playState = STOPPED;
}

void VorbitalDlg::OnPlaylistDoubleClick(QListWidgetItem*)
{
    _incrementNeeded = false;
	if( _musicStream )
	{
		_musicStream->Stop();
	}
    qDebug() << "Setting VorbitalDlg play state to STOPPED.";
	_playState = STOPPED;
	_listPosition = _lstPlaylist->currentRow();
    qDebug() << "Setting playlist position to " << _listPosition << ".";
	OnButtonPlayClick();
}

/*!
 * Play button handler.
 */
void VorbitalDlg::OnButtonPlayClick()
{
    qDebug() << "Play clicked.";
	if( !_musicStream )
	{
        qDebug() << "Creating new MusicStream instance.";
		_musicStream = new MusicStream(this);
		int volume = _volumeSlider->value();
        float actualVol = float(volume / 100.0f);
        if( _musicStream != nullptr )
		{
			_musicStream->SetVolume( actualVol );
		}
        qDebug() << "Playing new MusicStream instance.";
        _musicStream->start();
        _musicStream->Play();
	}

    if( _musicStream->IsPaused() )
    {
        _musicStream->PausePlayback();
    }
    else if( !_musicStream->IsPlaying() )
    {
    	_lastTimeUpdate = QDateTime::currentDateTime();
        _msecElapsed = 0;
    }

    qDebug() << "Setting VorbitalDlg play state to PLAYING.";
	_playState = PLAYING;
}

/**
* Quit handler.
*/
void VorbitalDlg::OnQuit()
{
	SaveSettings();
	_done = true;
#ifdef WIN32
	Sleep(50);
#elif linux
    usleep(50);
#endif
#ifndef __APPLE__
    // alcDestroyContext crashes the app on OSX.
    qDebug() << "Closing OpenAL context and device.";
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(_context);
    alcCloseDevice(_device);
    _device = nullptr;
#endif
}

/**
* Shows the about box.
*/
void VorbitalDlg::OnAbout()
{
#ifdef WIN32
    QMessageBox::about(this, "Vorbital Player 4.43", "Vorbital Player 4.43\nCopyright 2006-2020 Jason Champion.\nDeveloped by Jason Champion.\nThe Vorbital Player is free software and may be distributed freely under the terms of the MIT license.\n\nhttps://zetacentauri.com/software_vorbital.htm\n\nVorbital uses the Qt 5.8, libogg 1.3.2, libvorbis 1.3.7, wavpack 5.3.0, mpg123 1.26.3, and libsndfile 1.0.28 libraries.");
#else
    QMessageBox::about(this, "Vorbital Player 4.43", "Vorbital Player 4.43\nCopyright 2006-2020 Jason Champion.\nDeveloped by Jason Champion.\nThe Vorbital Player is free software and may be distributed freely under the terms of the MIT license.\n\nhttps://zetacentauri.com/software_vorbital.htm\n\nVorbital uses the Qt, libogg, libvorbis, wavpack, mpg123, and libsndfile libraries.");
#endif
}

/**
* Drag and drop receiver.
*/
void VorbitalDlg::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();
    QString filenames = mimeData->text();
    if( mimeData->hasUrls() )
    {
        qDebug() << "MIME data has URLs from drop action.";
        QList<QUrl> urlList = mimeData->urls();
        for (int i = 0; i < urlList.size() && i < 32; ++i)
        {
            QFileInfo info(urlList[i].toLocalFile());
            QListWidgetItem* item = new QListWidgetItem(info.baseName());
            item->setData(Qt::UserRole, QVariant(info.absoluteFilePath()));
            qDebug() << "Adding to playlist: " << urlList[i];
            _lstPlaylist->addItem(item);
        }
    }
    qDebug() << "Files dropped: " << filenames;
    event->acceptProposedAction();
}

void VorbitalDlg::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "QDragEnterEvent, mime hasText = " << event->mimeData()->hasText() << ", text = " << event->mimeData()->text();
    if (event->mimeData()->hasText())
    {
        event->acceptProposedAction();
    }
}

void VorbitalDlg::LoadFile( const QString& filename, bool play )
{
    if( _lstPlaylist != nullptr )
    {
        QListWidgetItem* item = new QListWidgetItem(ExtractFilename(filename));
        item->setData(Qt::UserRole, QVariant(filename));
        _lstPlaylist->addItem(item);
        if( GetPlayState() != PLAYING )
        {
            _lstPlaylist->setCurrentRow( _lstPlaylist->count() - 1);
            _listPosition = _lstPlaylist->count() - 1;
        }
        else
        {
            if( _listPosition >= 0 && _listPosition < _lstPlaylist->count() )
            {
                _lstPlaylist->setCurrentRow( _listPosition );
            }
        }
    }
    if( play )
    {
        OnButtonPlayClick();
    }
}

void VorbitalDlg::OnVolume(int volume)
{
    qDebug() << "Volume changed to " << volume;
    _volume = volume;
    if(_volume > 0 && _muted)
    {
        _muted = false;
        _btnVolume->setIcon(*_speaker);
    }
    if( _musicStream )
    {
        float actualVol = float(_volume / 100.0f);
        _musicStream->SetVolume( actualVol );
    }
}

void VorbitalDlg::OnPositionSlider()
{
    // The trouble is, if music is playing while we drag the slider, the value will
    // change WHILE we are dragging, and probably before and during release.
    // To do this right, we need to DISABLE slider updates while dragging.
    unsigned int position = (unsigned int)_positionSlider->value();
    qDebug() << "Position slider released, value: " << position;
    if( _musicStream != nullptr)
    {
        if( _musicStream->CanSetPosition() )
        {
            unsigned int seconds = ((_musicStream->GetLength() * position) / 1000);
            qDebug() << "Setting position to " << seconds << " out of " << _musicStream->GetLength();
            if( _musicStream->SetPosition(seconds) )
            {
                QDateTime currTime = QDateTime::currentDateTime();
                _msecElapsed = seconds * 1000;
                _lastTimeUpdate = currTime;
            }
        }
        else
        {
            qDebug() << "Cannot set position on file, skipping event";
        }
    }
    // TODO: Allow position slider to change, but don't react to events triggered
    // by value changes.
    // We may need to change this from a value changed event to a click event handler.
    //qDebug() << "Position slider changed to " << position;
    //if( _musicStream )
    //{
    //    qDebug() << "TODO: Change song position to " << position;
    //}
}

void VorbitalDlg::OnSongLengthChanged(int length)
{
    qDebug() << "Received songLengthChanged as " << length;
    _songLength = length;
    if( length <= 0 )
    {
        _positionSlider->setEnabled(false);
        _txtMaxTime->hide();
        _txtTimeDivider->hide();
    }
    else
    {
        _positionSlider->setEnabled(true);
        _positionSlider->setValue(0);
        QString label;
        if( (length % 60) > 9 )
        {
            label = QString("%1:%2").arg(length / 60).arg(length % 60);
        }
        else
        {
            label = QString("%1:0%2").arg(length / 60).arg(length % 60);
        }
        _txtMaxTime->setText(label);
        _txtMaxTime->show();
        _txtTimeDivider->show();
    }
}

/*
* Rips the extension and directory path off of a filename for prettier playlist display.
*/
QString VorbitalDlg::ExtractFilename(const QString& filename)
{
    int lastRightSlash = filename.lastIndexOf(QChar('/'));
    QString newFilename;
    if( lastRightSlash != -1 && lastRightSlash < (filename.length()-1))
    {
        newFilename = filename.mid(lastRightSlash+1, (filename.length() - lastRightSlash+1));
    }
    else
    {
        newFilename = filename;
    }
    int startPos = newFilename.lastIndexOf(QChar('\\'));
    if( startPos == newFilename.length() || startPos == -1 )
		startPos = 0;
	if( startPos != 0 )
		startPos += 1;
    int endPos = newFilename.lastIndexOf(QChar('.'));
    QString strng = newFilename.mid(startPos, endPos-startPos);
	return strng;
}

bool VorbitalDlg::SetArtFile(const QString& filename)
{
    qDebug() << "Loading album art file: " << filename;
    QFile file(filename);
    if( !file.exists() )
    {
        return false;
    }
    UpdateAlbumArt(filename);
    return true;
}

void VorbitalDlg::LoadAlbumArt(const QString& filename)
{
	int endPos = filename.lastIndexOf(QChar('/'));
	QString dirname = filename.mid(0, endPos+1);
    qDebug() << "Looking for album art in folder: " << dirname;
	QString artFile = QString("%1%2").arg(dirname).arg("Folder.jpg");
    //QString altArtFile = QString("%1%2").arg(dirname).arg("folder.jpg"); // Not necessary on Windows.
    QString altArtFile = QString("%1%2").arg(dirname).arg("AlbumArtSmall.jpg");
    // Also Try: AlbumArtSmall, folder.jpg (no capital F).
    // Maybe also look for images with the same filename as the song (see Andy Rumsey album) and Au4 - On Audio.
    // And One folder has some strange GUID-based artwork. Not sure whether there is any way
    // to tie that back to an album/song... might be some weird Windows Media Player or iTunes thing.
    if( !SetArtFile(artFile) )
    {
        if( !SetArtFile(altArtFile) )
        {
            qDebug() << "Album art not found for " << filename;
            _albumArt->setVisible(false);
        }
    }
}

void VorbitalDlg::UpdateTime()
{
    QDateTime currTime = QDateTime::currentDateTime();
    int mseconds = _lastTimeUpdate.msecsTo(currTime);
    //qDebug() << "Milliseconds elapsed: " << mseconds << ", total: " << _msecElapsed;
    _msecElapsed += mseconds;
    _lastTimeUpdate = currTime;
    emit timeChanged(_msecElapsed);
}

void VorbitalDlg::PausedUpdateTime()
{
    // Discard the seconds that pass while we are paused.
    _lastTimeUpdate = QDateTime::currentDateTime();
}

void VorbitalDlg::ResetTime()
{
    _msecElapsed = 0;
    _lastTimeUpdate = QDateTime::currentDateTime();
    emit timeChanged(_msecElapsed);
}

void VorbitalDlg::UpdateNumChannels(int channels)
{
    if( channels == 1 )
    {
        emit numchannelsChanged(1);
    }
    else
    {
        // Pretend that 2 or more channels is stereo.  0 channels will also show as this... if possible.
        emit numchannelsChanged(2);
    }
}

void VorbitalDlg::UpdateBitrate(int bitrate)
{
    emit bitrateChanged(bitrate);
}

void VorbitalDlg::UpdateSongLength(int length)
{
    qDebug() << "Emitting songLengthChanged as " << length;
    emit songLengthChanged(length);
}

void VorbitalDlg::UpdateSampleRate(int samplerate)
{
    emit samplerateChanged(samplerate);
}

void VorbitalDlg::UpdateVolume(int volume)
{
	emit volumeChanged(volume);
}

void VorbitalDlg::UpdateAlbumArt(const QString& filename)
{
    emit albumArtChanged(filename);
}

void VorbitalDlg::UpdateArtist(const QString& artist)
{
    emit artistChanged(artist);
}

void VorbitalDlg::UpdateAlbum(const QString& album)
{
    emit albumChanged(album);
}

void VorbitalDlg::UpdateSong(const QString& song)
{
    emit songChanged(song);
}

void VorbitalDlg::closeEvent(QCloseEvent* event)
{
    OnQuit();
    event->accept();
}
