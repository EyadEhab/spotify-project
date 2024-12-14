#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <node.h>
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QStringList>

class playList
{
private:

    QString name;
    int count;
    node * head;
    node * tail;
    int capacity;

public:
    playList(QString);
    void addSong(song song);
    void removeSong(QString name);
    void displaySongs();
    //void search(QString song);
    void shufflePlay();
    void sortNoOfPlays();
    void sortReverseOfPlays();
    void sortByAlphSong();
    void sortByAlphArtist();
    void sortByRecent();
    void displaySum();


};

#endif // PLAYLIST_H
