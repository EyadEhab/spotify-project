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
  stack<song *> stack1;

public:
  playList(string);
  void addSong(song* song);
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
  void sortByNoOfPlays();
  void sortReverseOfPlays();
  void sortByAlphSong();
  void sortByAlphArtist();
  void sortByRecent();
  void displaySum();
  void insertIntoBST(BSTNode*& root, const song* s);
  void insertIntoBST(BSTNode *&, const song &);
  void clearBST(BSTNode*& root);
  void inOrderTraversal(BSTNode *, vector<song> &);
  void preOrderTraversal(BSTNode *, vector<song> &);
  void postOrderTraversal(BSTNode *, vector<song> &);
  void reverseOrderTraversal(BSTNode *, vector<song> &);
  void rebuildTree(BSTNode *root);
  void displayPlaylist();
  void rebuildLinkedListFromVector(vector<song> &);
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