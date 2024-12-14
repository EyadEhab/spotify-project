#ifndef PLAYLIST_H
#define PLAYLIST_H


class playList
{
private:

    Qstring name;
    int count;
    node * head,tail;
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
