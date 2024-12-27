#ifndef SONG_H
#define SONG_H
#include <stack>
#include <string>
#include <node.h>
#include <stack>
#include "miniaudio.h"
using namespace std;

class song {
private:
    string title;    // Song title
    string artist;   // Artist name
    float duration;  // Duration in seconds
    int plays;       // Play count
    string filepath;
    stack <song*> stack1;
    ma_engine engine;

public:
    // Default constructor
    song() : title(""), artist(""), duration(0), plays(0),filepath("../resourses/media/") {};

    // Parameterized constructor
    song(const string& title, const string& artist, int duration);

    // Getters and Setters
    string getTitle() const;
    string getArtist() const;
    float getDuration() const;
    int getPlays() const;
    void setTitle(const string& newTitle);
    void setArtist(const string& newArtist);
    void setDuration(float newDuration);
    void playSong()
    // Functionalities
    void playSong(string);
    void displaySongInfo() const;
    void searchAndPlay(const string& songName, const string& directory);
};

#endif