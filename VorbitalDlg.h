#ifndef _VORBITALDLG_H_
#define _VORBITALDLG_H_

#include "MusicStream.h"
#include "PlaylistThread.h"
#include "al.h"
#include "alc.h"

#include <QDialog>
#include <QThread>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QListWidget>
#include <QDateTime>

class VorbitalDlg: public QDialog
{
    Q_OBJECT
public:
    VorbitalDlg( );
    ~VorbitalDlg( );
    void CreateControls();
    void LoadFile( const QString& filename, bool play = true );
    void OnMouseWheel();
    void OnListPosition();
    void OnQuit();
    void OnRightClick();
    void ShowFileInfo(int index);
    static bool ShowToolTips();
    QString ExtractFilename(const QString& filename);
    void LoadAlbumArt(const QString& filename);
    bool SetArtFile(const QString& filename);
    void AddFolderToPlaylist(const QString& folder);
    void LoadSettings();
    void SaveSettings();
    QListWidget* GetPlaylist() { return _lstPlaylist; }
    MusicStream* GetMusicStream() { return _musicStream; }
    void SetIncrementNeeded(bool value) { _incrementNeeded = value; }
    bool GetIncrementNeeded() { return _incrementNeeded; }
    bool GetRandomize() { return _randomize; }
    void SetListPosition(int value) { _listPosition = value; }
    int GetListPosition() { return _listPosition; }
    int GetPlayState() { return _playState; }
    void SetPlayState(int value) { _playState = value; printf("PlayState changed to %d\n", value); }
    void UpdateTime();
    void PausedUpdateTime();
    void ResetTime();
    void UpdateNumChannels(int channels);
    void UpdateBitrate(int bitrate);
    void UpdateSampleRate(int samplerate);
	void UpdateVolume(int volume);
    void UpdateAlbumArt(const QString& filename);
    void UpdateSongLength(int length);
    void UpdateArtist(const QString& artist);
    void UpdateAlbum(const QString& album);
    void UpdateSong(const QString& song);
    void closeEvent(QCloseEvent* event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
public slots:
    void OnPlaylistDoubleClick(QListWidgetItem* item);
    void OnNumChannels(int value);
    void OnBitrate(int bitrate);
    void OnSampleRate(int rate);
    void OnTime(int milliseconds);
    void OnButtonBrowseClick();
    void OnButtonBrowseFolderClick();
    void OnButtonPlayClick();
    void OnButtonStopClick();
    void OnButtonForwardClick();
    void OnButtonReverseClick();
    void OnButtonPauseClick();
    void OnButtonRemoveClick();
    void OnButtonSettingsClick();
    void OnButtonClearClick();
    void OnButtonRandomizeClick();
    void OnAbout();
    void OnVolume(int value);
    void OnPositionSlider();
    void OnAlbumArtChanged(const QString& filename);
    void OnSongLengthChanged(int length);
    void OnArtistChanged(const QString& filename);
    void OnAlbumChanged(const QString& filename);
    void OnSongChanged(const QString& filename);
    void UpdateSongName();
private:
    ALCdevice *_device;
    ALCcontext *_context;
    QPushButton* _btnBrowse;
    QPushButton* _btnBrowseFolder;
    QPushButton* _btnPlay;
    QPushButton* _btnStop;
    QPushButton* _btnForward;
    QPushButton* _btnReverse;
    QPushButton* _btnPause;
    QPushButton* _btnRemove;
    QPushButton* _btnClear;
    QPushButton* _btnAbout;
    QPushButton* _btnSettings;
    QPushButton* _btnRandomize;
    QLabel* _txtSampleRate;
    QLabel* _txtVersion;
    QLabel* _txtBitRate;
    QLabel* _txtChannels;
    QLabel* _txtComment;
    QLabel* _txtTime;
    QLabel* _txtMaxTime;
    QLabel* _txtTimeDivider;
    QListWidget* _lstPlaylist;
    QSlider* _volumeSlider;
    QSlider* _positionSlider;
	QLabel* _albumArt;
    QLabel* _txtArtist;
    //std::list<QString *> _playlist;
    MusicStream* _musicStream;
    int _listPosition;
    int _playState;
    bool _incrementNeeded;
    bool _randomize;
	bool _menuDoubleClicked;
	bool _done;
    QDateTime _lastTimeUpdate;
    int _msecElapsed;
    int _songLength;
    QIcon _icon;
    PlaylistThread* _playlistThread;
    QString _lastSelectedDirectory;
    QString _artist;
    QString _album;
    QString _song;
    QString _filename;
signals:
    void numchannelsChanged(int channels);
    void bitrateChanged(int bitrate);
    void bitdepthChanged(int bitdepth);
    void samplerateChanged(int samplerate);
    void timeChanged(int time);
	void volumeChanged(int volume);
    void positionSliderChanged(int position);
    void albumArtChanged(const QString& filename);
    void songLengthChanged(int length);
    void artistChanged(const QString& artist);
    void albumChanged(const QString& album);
    void songChanged(const QString& song);
};

#endif
