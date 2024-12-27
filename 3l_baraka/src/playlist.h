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
    void buildTree(BSTNode * root);
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
    void insertIntoBST(BSTNode*& , const song& );
    void buildTree(BSTNode*);
    void inOrderTraversal(BSTNode* , vector<song>& );
    void preOrderTraversal(BSTNode* , vector<song>& );
    void postOrderTraversal(BSTNode* , vector<song>& );
    void reverseOrderTraversal(BSTNode* , vector<song>& );
    void rebuildTree(BSTNode* root);
    void displayPlaylist();
    void rebuildLinkedListFromVector(const vector<song>& );
    void inorderRebuild(BSTNode* root);
    void preorderRebuild(BSTNode* root);
    void postorderRebuild(BSTNode* root);
};

#endif // PLAYLIST_H