#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "node.h"
#include <string>
using namespace std;

class playList
{
private:
    string name;
    int count;
    node* head;
    node* tail;
    int capacity;

public:
    playList(string);
    void addSong(song song);
    void removeSong(string name);
    void displaySongs();
    //void search(string song);
    void shufflePlay();
    void sortNoOfPlays();
    void sortReverseOfPlays();
    void sortByAlphSong();
    void sortByAlphArtist();
    void sortByRecent();
    void displaySum();
};

#endif // PLAYLIST_H