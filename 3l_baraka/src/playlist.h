#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "node.h"
#include <string>
#include <random>
#include <stack>
#include <BSTNode.h>
using namespace std;

class playList
{
private:
    BSTNode * root;
    string name;
    int count;
    node* head;
    node* tail;
    stack<song*> stack1;

public:
    playList(string);
    void addSong(song song);
    void removeSong(string name);
    void removeAllSongs();
    void displaySongs();
    //void search(string song);
    void shufflePlay();
    int getCount();
    int getRandomNumber();
    void swapSong(node*, node* );
    void sortByNoOfPlays();
    void sortReverseOfPlays();
    void sortByAlphSong();
    void sortByAlphArtist();
    void sortByRecent();
    void displaySum();
};

#endif // PLAYLIST_H