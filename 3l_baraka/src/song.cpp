#include "song.h"
#include <iostream>

// Constructor
song::song(const string& title, const string& artist, int duration)
    : title(title), artist(artist), duration(duration), plays(0) {}

// Getters
string song::getTitle() const { return title; }
string song::getArtist() const { return artist; }
float song::getDuration() const { return duration; }
int song::getPlays() const { return plays; }

// Setters
void song::setTitle(const string& newTitle) { title = newTitle; }
void song::setArtist(const string& newArtist) { artist = newArtist; }
void song::setDuration(float newDuration) { duration = newDuration; }

// Functionalities
void song::playSong() {
    // Increment the play counter
    plays++;

    // Simulate playing the song
    cout << "Now playing: " << title << " by " << artist << endl;
    cout << "Play count for this song: " << plays << endl;
}

void song::searchAndPlay(const string& songName, const string& directory) {
    // Simplified version without Qt file operations
    cout << "Searching for song: " << songName << " in directory: " << directory << endl;
    cout << "File operations will need to be implemented using standard C++ file handling" << endl;
    playSong();
}

void song::displaySongInfo() const {
    cout << "Song Info:" << endl;
    cout << "Title: " << title << endl;
    cout << "Artist: " << artist << endl;
    cout << "Duration: " << duration << " seconds" << endl;
    cout << "Plays: " << plays << endl;
}