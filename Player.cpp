#include <QWidget>
#include <QVBoxLayout>
#include <QTime>
#include <QDial>
#include <QLabel>
#include <QStyle>
#include <QFileDialog>
#include <QTime>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QPixmap>
#include "Player.h"

Player::Player(QWidget *parent)
    : QWidget(parent) {

    QVBoxLayout* vbox = new QVBoxLayout();
    QHBoxLayout* hboxIn1 = new QHBoxLayout();
    QHBoxLayout* hboxIn2 = new QHBoxLayout();
    QHBoxLayout* hboxIn3 = new QHBoxLayout();
    QHBoxLayout* hboxIn4 = new QHBoxLayout();
    QHBoxLayout* hboxEx1 = new QHBoxLayout();

    //QHBoxLayout* hboxForImg = new QHBoxLayout();

    play = new QPushButton();
    next = new QPushButton();
    prev = new QPushButton();
    medialist = new QPushButton("playlist");
    QPushButton* open = new QPushButton("open");

    QDial* volume = new QDial;

    slider = new QSlider(Qt::Horizontal);

    currentTime = new QLabel(msecsToString(0));
    remainTime = new QLabel(msecsToString(0));

    mplayer = new QMediaPlayer;

    artistLabel = new QLabel;
    trackLabel = new QLabel;

    //QPixmap coverMap("D:/made_IN/Qt_Dev/playia/playia/no_cover.png");
    //QLabel cover;
    //cover.setPixmap(QPixmap("D:/made_IN/Qt_Dev/playia/no_cover.png"));

    //play->setEnabled(false);
    play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    next->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    prev->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));

    slider->setRange(0, 0);
    int defaultVolume = 50;
    mplayer->setVolume(defaultVolume);
    volume->setValue(defaultVolume);

    playlist = new QMediaPlaylist(mplayer);

    connect(open, &QPushButton::clicked, this, &Player::slotOpen);
    connect(play, &QPushButton::clicked, this, &Player::slotPlay);
    connect(next, &QPushButton::clicked, this, &Player::slotNext);
    connect(prev, &QPushButton::clicked, this, &Player::slotPrev);
    connect(medialist, &QPushButton::clicked, this, &Player::slotAddPlaylist);
    connect(volume, SIGNAL(valueChanged(int)), mplayer, SLOT(setVolume(int)));
    connect(slider, SIGNAL(sliderMoved(int)), SLOT(slotSetMediaPosition(int)));
    connect(mplayer, SIGNAL(positionChanged(qint64)), SLOT(slotSetSliderPosition(qint64)));
    connect(mplayer, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));
    connect(mplayer, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(slotStatusChanged(QMediaPlayer::State)));

    hboxIn1->addWidget(open);
    hboxIn1->addWidget(prev);
    hboxIn1->addWidget(play);
    hboxIn1->addWidget(next);

    hboxIn2->addWidget(currentTime);
    hboxIn2->addWidget(slider);
    hboxIn2->addWidget(remainTime);

    hboxIn3->addWidget(medialist);

    hboxIn4->addWidget(artistLabel);
    hboxIn4->addWidget(trackLabel);

    //hboxForImg->addWidget(&cover);

    //vbox->addLayout(hboxForImg);
    vbox->addLayout(hboxIn4);
    vbox->addLayout(hboxIn2);
    vbox->addLayout(hboxIn1);
    vbox->addLayout(hboxIn3);

    hboxEx1->addLayout(vbox);
    hboxEx1->addWidget(volume);

    setLayout(hboxEx1);
}

void Player::slotOpen() {
    QString strFile = QFileDialog::getOpenFileName(this, "Open file");
    if (!strFile.isEmpty()) {
        mplayer->setMedia(QUrl::fromLocalFile(strFile));        
    }
    QString artistName = mplayer->metaData(QMediaMetaData::Author).toString();
    QString title = mplayer->metaData(QMediaMetaData::Title).toString();
    if (artistName != "" && title != "") {
        artistLabel->setText(artistName);
        trackLabel->setText(title);
    } else {
        artistLabel->setText("unknown");
        trackLabel->setText("untitled");
    }
}

void Player::slotPlay() {
    switch (mplayer->state()) {
    case QMediaPlayer::PlayingState:
        mplayer->pause();
        break;
    default:
        mplayer->play();
        break;
    }
}

void Player::slotSetMediaPosition(int n) {
    mplayer->setPosition(n);
}

QString Player::msecsToString(qint64 n) {
    int nHours = (n / (60 * 60 * 1000));
    int nMinutes = ((n % (60 * 60 * 1000)) / (60 * 1000));
    int nSeconds = ((n % (60 * 1000)) / 1000);

    return QTime(nHours, nMinutes, nSeconds).toString("hh:mm:ss");
}

void Player::slotSetDuration(qint64 duration) {
    slider->setRange(0, duration);
    currentTime->setText(msecsToString(0));
    remainTime->setText(msecsToString(duration));
}

void Player::slotSetSliderPosition(qint64 value) {
    slider->setValue(value);
    currentTime->setText(msecsToString(value));
    int duration = slider->maximum();
    remainTime->setText(msecsToString(duration - value));
}

void Player::slotStatusChanged(QMediaPlayer::State state) {
    switch(state) {
    case QMediaPlayer::PlayingState:
        play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void Player::slotNext() {
    playlist->next();
}

void Player::slotPrev() {
    playlist->previous();
}

void Player::slotAddPlaylist() {
    QStringList strFiles = QFileDialog::getOpenFileNames(this, "Open folder");
    for (const QString& file : strFiles) {
        playlist->addMedia(QMediaContent(QUrl::fromLocalFile(file)));
    }
    mplayer->setPlaylist(playlist);
    QString artistName = mplayer->metaData(QMediaMetaData::Author).toString();
    QString title = mplayer->metaData(QMediaMetaData::Title).toString();
    if (artistName != "" && title != "") {
        artistLabel->setText(artistName);
        trackLabel->setText(title);
    } else {
        artistLabel->setText("unknown");
        trackLabel->setText("untitled");
    }
}
