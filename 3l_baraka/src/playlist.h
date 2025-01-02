#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "BSTNode.h"
#include "node.h"
#include <chrono>
#include <fstream>
#include <random>
#include <sstream>
#include <stack>
#include <string>
#include <thread>

using namespace std;

class playList {
private:
  BSTNode *root;
  string name;
  int count;
  node *head;
  node *tail;

public:
  playList(string);
  void addSong(song* song);
  string getName();
  node* getHead();
  void removeSong(string name);
  void removeAllSongs();
  void displaySongs();
  void buildTree(BSTNode *root);
  // void search(string song);
  bool doesPlaylistExist(const string& name, const string& filename = "../resources/playlist.txt");
  bool containsSong(const string& songTitle);
  void shufflePlay();
  vector<string> displaySongsInPlaylist();
  int getCount();
  int getRandomNumber();
  void swapSong(node *, node *);
  void bubbleSort(bool (*compare)(song*, song*));
  void sortByNoOfPlays();
  void sortReverseOfPlays();
  void sortByTimePlayed();
  void sortByNoOfPlaysReverse();
  void sortByAlphSong();
  void sortByAlphArtist();
  void sortByRecent();
  void displaySum();
  void insertIntoBST(BSTNode*& root, const song* s);
  void insertIntoBST(BSTNode *&, const song &);
  void clearBST(BSTNode*& root);
  void sortByAlphSongReverse();
  void sortByAlphArtistReverse();
  void sortByRecentReverse();
  void sortByTimePlayedReverse();
  void inOrderTraversal(BSTNode *, vector<song> &);
  void preOrderTraversal(BSTNode *, vector<song> &);
  void postOrderTraversal(BSTNode *, vector<song> &);
  void reverseOrderTraversal(BSTNode *, vector<song> &);
  void rebuildTree(BSTNode *root);
  void displayPlaylist();
  void rebuildLinkedListFromVector(vector<song>& songs);
  void inOrderRebuild();
  void preOrderRebuild();
  void inorderRebuild();
  void preorderRebuild();
  void save(const string &filename);
  void playSongs();
  void postOrderRebuild();
  bool load(const string &playlistName, const string &filename, const string &);
};

#endif // PLAYLIST_H