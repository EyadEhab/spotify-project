#ifndef SONG_H
#define SONG_H
#include "miniaudio.h"
#include "node.h"
#include <algorithm>
#include <stack>
#include <string>
using namespace std;

class song {
private:
  string title;   // Song title
  string artist;  // Artist name
  float duration; // Duration in seconds
  int plays;      // Play count
  string filepath;
  stack<song *> stack1;
  ma_engine engine;
  string timePlayed;

public:
  // Default constructor
  song()
      : title(""), artist(""), duration(0), plays(0),
        filepath("../resourses/media/"){};

  // Parameterized constructor
  song(const string title, const string artist, int duration);

  // Getters and Setters
  string getTitle() const;
  string getArtist() const;
  float getDuration() const;
  int getPlays() const;
  string getTimePlayed() const;
  void setTitle(const string &newTitle);
  void setArtist(const string &newArtist);
  void setDuration(float newDuration);
  void updateTimePlayed();
  // Functionalities
  bool playSong(const string& songName, node* currentSongNode = nullptr);
  void pauseSong(); // Add this for pausing playback
  void resumeSong(); // Add this for resuming playback
  void displaySongInfo() const;
  bool saveTimePlayedAndPlayCount(const string& filename);
  song* load(const string &, const string &);
  bool deleteSong(const string &filename, const string &titleToDelete);
  void searchAndPlay(const string &songName, const string &directory);
};

#endif