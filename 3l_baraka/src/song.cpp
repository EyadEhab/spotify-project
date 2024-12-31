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
#include <termios.h>
#include <unistd.h>
#include <atomic>
#include <fcntl.h>
using namespace std;


// Function to set terminal to non-blocking mode
void setNonBlocking(bool enable) {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    if (enable) {
        ttystate.c_lflag &= ~ICANON; // Disable canonical mode
        ttystate.c_lflag &= ~ECHO;   // Disable echo
        ttystate.c_cc[VMIN] = 0;     // Minimum number of characters to read
        ttystate.c_cc[VTIME] = 0;    // Time to wait for input (0 = no wait)
    } else {
        ttystate.c_lflag |= ICANON;  // Enable canonical mode
        ttystate.c_lflag |= ECHO;    // Enable echo
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

// Function to check if a key is pressed
bool isKeyPressed() {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) == 1;
}

// Function to get the pressed key
char getKey() {
    char ch = 0;
    if (read(STDIN_FILENO, &ch, 1) != 1) {
        ch = 0;
    }
    return ch;
}
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

void song::playSong(const string& songName, node* currentSongNode) {
    cout << plays<<endl;
    plays++;
    cout << plays<<endl;
    updateTimePlayed();
    saveTimePlayedAndPlayCount("../resources/musics.txt");

    // Construct the full path to the audio file
    string fullPath = "../resources/media/" + songName + ".mp3";

    // Initialize sound object (local variable)
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

    // Display controls based on the mode
    if (currentSongNode) {
        cout << "Press 'p' to pause, 'r' to resume, 'n' for next, 'b' for previous, or 'q' to quit." << endl;
    } else {
        cout << "Press 'p' to pause, 'r' to resume, or 'q' to quit." << endl;
    }

    // Set terminal to non-blocking mode
    setNonBlocking(true);

    // Playback loop
    bool quit = false;
    bool paused = false;
    while (!quit) {
        if (!paused) {
            // Update progress bar only if the song is playing
            float currentPositionInSeconds;
            ma_sound_get_cursor_in_seconds(&sound, &currentPositionInSeconds);

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
        }

        // Check for user input
        if (isKeyPressed()) {
            char key = getKey();
            switch (key) {
                case 'p': // Pause
                    if (!paused) {
                        ma_sound_stop(&sound);
                        cout << "\nSong paused. Press 'r' to resume or Press 'q' to exit." << endl;
                        paused = true;
                    }
                    break;
                case 'r': // Resume
                    if (paused) {
                        ma_sound_start(&sound);
                        cout << "\nSong resumed." << endl;
                        paused = false;
                    }
                    break;
                case 'n': // Next song (only in playlist mode)
                    if (currentSongNode && currentSongNode->next) {
                        ma_sound_stop(&sound); // Stop the current song
                        ma_sound_uninit(&sound); // Clean up the current sound
                        currentSongNode = currentSongNode->next; // Move to the next song
                        currentSongNode->data->playSong(currentSongNode->data->getTitle(), currentSongNode); // Play the next song
                        quit = true; // Exit the current playback
                        return;
                    } else if (currentSongNode) {
                        cout << "\nEnd of playlist reached." << endl;
                    }
                    break;
                case 'b': // Previous song (only in playlist mode)
                    if (currentSongNode && currentSongNode->prev) {
                        ma_sound_stop(&sound); // Stop the current song
                        ma_sound_uninit(&sound); // Clean up the current sound
                        currentSongNode = currentSongNode->prev; // Move to the previous song
                        currentSongNode->data->playSong(currentSongNode->data->getTitle(), currentSongNode); // Play the previous song
                        quit = true; // Exit the current playback
                        return;
                    } else if (currentSongNode) {
                        cout << "\nBeginning of playlist reached." << endl;
                    }
                    break;
                case 'q': // Quit
                    quit = true;
                    ma_sound_stop(&sound);
                    cout << "\nPlayback stopped." << endl;
                    break;
                default:
                    break;
            }

            // Clear the input buffer to avoid unintended behavior
            while (isKeyPressed()) {
                getKey();
            }
        }

        // Sleep to reduce CPU usage
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    // Restore terminal to blocking mode
    setNonBlocking(false);

    if (!quit) {


        cout << "\nPlayback completed!" << endl;
    }

    // Cleanup
    ma_sound_uninit(&sound); // Clean up the sound object
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

bool song::saveTimePlayedAndPlayCount(const string& filename = "../resources/musics.txt") {
    ifstream inFile(filename);
    vector<string> lines;
    bool songFound = false;

    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << filename << endl;
        return false;
    }

    // Read all lines from the file
    string line;
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

    if (!songFound) {
        // Song is not in the file, add it
        string newLine = title + "," + artist + "," + to_string(duration) + "," +
                         to_string(plays) + "," + timePlayed;
        lines.push_back(newLine);
        cout << "Song '" << title << "' added to the music database." << endl;
    }

    // Write the updated content back to the file
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return false;
    }

    for (const auto& line : lines) {
        outFile << line << endl;
    }
    outFile.close();

    cout << "Successfully updated song '" << title << "' in " << filename << endl;
    return true;
}

// Load a single song from a text file
song* song::load(const string& songTitle, const string& filename="../resources/musics.txt") {
    ifstream file(filename);
    song* emptySong = new song("", "", 0.0f); // Return an empty song if not found

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, artist, timePlayed;
            float duration;
            int plays;

            // Parse each line
            getline(ss, title, ',');
            getline(ss, artist, ',');
            ss >> duration;
            ss.ignore(1); // Ignore the comma
            ss >> plays;
            ss.ignore(1); // Ignore the comma
            getline(ss, timePlayed);

            // If the title matches the requested song, return this song
            if (title == songTitle) {
                song* s = new song(title, artist, duration);
                s->plays = plays; // Set the plays value
                s->timePlayed = timePlayed; // Set the timePlayed value
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
