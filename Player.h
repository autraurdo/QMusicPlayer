#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QApplication>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

class Player : public QWidget {

    Q_OBJECT
public:
    Player(QWidget* parent = 0);
private slots:
    void slotOpen();
    void slotPlay();
    void slotNext();
    void slotPrev();
    void slotSetMediaPosition(int);
    void slotSetSliderPosition(qint64);
    void slotSetDuration(qint64);
    void slotStatusChanged(QMediaPlayer::State);
    void slotAddPlaylist();
private:
    QMediaPlayer* mplayer;
    QPushButton* play;
    QPushButton* next;
    QPushButton* prev;
    QPushButton* medialist;
    QSlider* slider;
    QLabel* currentTime;
    QLabel* remainTime;
    QMediaPlaylist* playlist;
    QLabel* artistLabel;
    QLabel* trackLabel;

    QString msecsToString(qint64 n);
};

#endif // PLAYER_H
