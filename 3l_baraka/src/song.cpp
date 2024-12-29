#include "song.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include "miniaudio.h"
#include <iomanip>
#include <ctime>
using namespace std;

// Constructor
song::song(const string title, const string artist, int duration)
    : title(title), artist(artist), duration(duration), plays(0), filepath("../resources/media/") ,timePlayed(""){
    ma_engine_init(NULL, &engine);
}

// Getters
string song::getTitle() const { return title; }
string song::getArtist() const { return artist; }
float song::getDuration() const { return duration; }
int song::getPlays() const { return plays; }

string song::getTimePlayed() const
{
    return timePlayed;
}

// Setters
void song::setTitle(const string& newTitle) { title = newTitle; }
void song::setArtist(const string& newArtist) { artist = newArtist; }
void song::setDuration(float newDuration) { duration = newDuration; }

void song::updateTimePlayed() {
    // Get the current time
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);

    // Create stringstream for formatting
    stringstream ss;

    // Format: YYYYMMDDHHMMSS
    ss << (1900 + ltm->tm_year)  // Year
       << setfill('0') << setw(2) << (1 + ltm->tm_mon)  // Month
       << setfill('0') << setw(2) << ltm->tm_mday       // Day
       << setfill('0') << setw(2) << ltm->tm_hour       // Hour
       << setfill('0') << setw(2) << ltm->tm_min        // Minute
       << setfill('0') << setw(2) << ltm->tm_sec;       // Seconds

    // Save the formatted string
    timePlayed = ss.str();
}


void song::playSong(const string& songName) {
    // Construct the full path to the audio file
    string fullPath = "../resources/" + songName;  // Using the class member filepath

    // Initialize sound object
    ma_sound sound;
    ma_result result = ma_sound_init_from_file(&engine, fullPath.c_str(), 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS) {
        cerr << "Failed to load sound file: " << fullPath << endl;
        cerr << "Error: " << ma_result_description(result) << endl;
        return;
    }

    // Start playing the sound
    result = ma_sound_start(&sound);
    if (result != MA_SUCCESS) {
        cerr << "Failed to start playback: " << ma_result_description(result) << endl;
        ma_sound_uninit(&sound);
        return;
    }

    // Get the duration in seconds
    float totalDuration;
    ma_sound_get_length_in_seconds(&sound, &totalDuration);

    if (totalDuration <= 0) {
        cerr << "Invalid sound duration" << endl;
        ma_sound_uninit(&sound);
        return;
    }

    // Display initial song info
    cout << "\nNow playing: " << title << " by " << artist << endl;
    cout << "Play count: " << plays << endl;
    cout << "Duration: " << static_cast<int>(totalDuration) << " seconds" << endl;

    // Progress bar loop
    while (ma_sound_is_playing(&sound)) {
        float currentPositionInSeconds;
        ma_sound_get_cursor_in_seconds(&sound, &currentPositionInSeconds);  // Fixed function name

        // Calculate progress percentage
        int progress = static_cast<int>((currentPositionInSeconds / totalDuration) * 100);
        progress = min(100, max(0, progress)); // Ensure progress stays between 0-100

        // Display progress bar
        cout << "\rProgress: [";
        int barWidth = 50;
        int pos = barWidth * progress / 100;

        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) cout << "=";
            else if (i == pos) cout << ">";
            else cout << " ";
        }

        cout << "] " << progress << "% ("
             << static_cast<int>(currentPositionInSeconds) << "/"
             << static_cast<int>(totalDuration) << "s)" << flush;

        // Sleep to reduce CPU usage
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    plays++;
    updateTimePlayed();
    if (saveTimePlayedAndPlayCount("../resources/musics.txt"))
        cout << "\n song updated successfully " << endl;
    else
        cout << "\n song updated failed " << endl;

    cout << "\nPlayback completed!" << endl;

    // Cleanup
    ma_sound_uninit(&sound);
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
    cout << "Time Played: " << timePlayed << endl;
}

bool song::saveTimePlayedAndPlayCount(const string& filename = "../resources/musics.txt")
{
    ifstream inFile(filename);
    vector<string> lines;
    bool songFound = false;

    if (inFile.is_open()) {
        string line;
        // Read all lines from the file
        while (getline(inFile, line)) {
            stringstream ss(line);
            string existingTitle;
            getline(ss, existingTitle, ','); // Extract the title

            if (existingTitle == title) {
                // Song found, update its play count and time played
                songFound = true;
                string updatedLine = title + "," + artist + "," + to_string(duration) + "," +
                                     to_string(plays) + "," + timePlayed;
                lines.push_back(updatedLine);
            } else {
                // Keep the line as is
                lines.push_back(line);
            }
        }
        inFile.close();
    } else {
        cerr << "Unable to open file for reading: " << filename << endl;
        return false;
    }

    if (!songFound) {
        // Song is not in the file, add it
        cerr << "Unable to find song for writing" << endl;
        return false;
    }

    // Write the updated content back to the file
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& line : lines) {
            outFile << line << endl;
        }
        outFile.close();
        cout << "Successfully updated song play count and time played in " << filename << endl;
        return true;
    } else {
        cerr << "Unable to open file for writing: " << filename << endl;
        return false;
    }
}

// Load a single song from a text file
song* song::load(const string& songTitle, const string& filename="../resources/musics.txt") {
    ifstream file(filename);
    song* emptySong = new song("", "", 0); // Return an empty song if not found

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
                song* s=new song(title, artist, duration);
                s->plays = plays;
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
bool song::deleteSong(const string& titleToDelete, const string& filename="../resources/musics.txt") {
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
