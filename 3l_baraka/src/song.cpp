#include "song.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Constructor
song::song(const string& title, const string& artist, int duration)
    : title(title), artist(artist), duration(duration), plays(0), filepath("../resources/media/") {
    ma_engine_init(NULL, &engine);
}

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
void song::playSong(string songName) {
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
    playSong(songName);
}

void song::displaySongInfo() const {
    cout << "Song Info:" << endl;
    cout << "Title: " << title << endl;
    cout << "Artist: " << artist << endl;
    cout << "Duration: " << duration << " seconds" << endl;
    cout << "Plays: " << plays << endl;
}

// Load a single song from a text file
song song::loadSong(const string& filename="../resources/musics.txt", const string& songTitle) {
    ifstream file(filename);
    song emptySong("", "", 0); // Return an empty song if not found

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, artist;
            int duration, plays;

            // Parse each line
            getline(ss, title, ',');
            getline(ss, artist, ',');
            ss >> duration;
            ss.ignore(1); // Ignore the comma
            ss >> plays;

            // If the title matches the requested song, return this song
            if (title == songTitle) {
                song s(title, artist, duration);
                s.plays = plays;
                file.close();
                return s;
            }
        }
        file.close();
        cout << "Song with title \"" << songTitle << "\" not found." << endl;
    } else {
        cerr << "Unable to open file for reading: " << filename << endl;
    }

    // Return an empty song if not found
    return emptySong;
}

// Delete a specific song from the text file
bool song::deleteSong(const string& filename="../resources/musics.txt", const string& titleToDelete) {
    ifstream file(filename);
    vector<string> lines;

    if (file.is_open()) {
        string line;
        bool found = false;

        // Read all lines and filter out the song to delete
        while (getline(file, line)) {
            stringstream ss(line);
            string title;
            getline(ss, title, ','); // Extract the title

            if (title == titleToDelete) {
                found = true;
            } else {
                lines.push_back(line);
            }
        }
        file.close();

        if (!found) {
            cout << "Song with title \"" << titleToDelete << "\" not found." << endl;
            return false;
        }

        // Write the remaining lines back to the file
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& remainingLine : lines) {
                outFile << remainingLine << endl;
            }
            outFile.close();
            cout << "Deleted song \"" << titleToDelete << "\" from " << filename << endl;
            return true;
        } else {
            cerr << "Unable to open file for writing: " << filename << endl;
            return false;
        }
    } else {
        cerr << "Unable to open file for reading: " << filename << endl;
        return false;
    }
}
