#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "playlist.h"
#include "song.h"

using namespace std;

// void clearInputBuffer() {
//     cin.clear();
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');
// }
//
// void waitForEnter() {
//     cout << "\nPress Enter to continue...";
//     clearInputBuffer();
// }

void displayMenu() {
    cout << "\n=== Music Player Menu ===" << endl;
    cout << "1. Create new playlist" << endl;
    cout << "2. Load existing playlist" << endl;
    cout << "3. Add song to playlist" << endl;
    cout << "4. Remove song from playlist" << endl;
    cout << "5. Display all songs" << endl;
    cout << "6. Play all songs" << endl;
    cout << "7. Shuffle play" << endl;
    cout << "8. Sort options" << endl;
    cout << "9. Build and traverse BST" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

void displaySortMenu() {
    cout << "\n=== Sort Options ===" << endl;
    cout << "1. Sort by number of plays (descending)" << endl;
    cout << "2. Sort by number of plays (ascending)" << endl;
    cout << "3. Sort by song name" << endl;
    cout << "4. Sort by artist name" << endl;
    cout << "5. Sort by recently played" << endl;
    cout << "Enter your choice: ";
}

void displayBSTMenu() {
    cout << "\n=== BST Operations ===" << endl;
    cout << "1. Build BST" << endl;
    cout << "2. In-order traversal" << endl;
    cout << "3. Pre-order traversal" << endl;
    cout << "4. Post-order traversal" << endl;
    cout << "Enter your choice: ";
}

vector<string> displayAvailableSongsToAdd(playList* currentPlaylist, const string& filename = "../resources/musics.txt") {
    ifstream file(filename);
    vector<string> availableSongs;

    if (!file.is_open()) {
        cout << "Error: Unable to open music database file!" << endl;
        return availableSongs;
    }

    // Get songs already in the playlist
    vector<string> playlistSongs = currentPlaylist->displaySongsInPlaylist();

    // Display available songs
    cout << "\n=== Available Songs ===" << endl;
    cout << "ID\tTitle\t\tArtist\t\tDuration\tPlays" << endl;
    cout << "------------------------------------------------" << endl;

    string line;
    int id = 1;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, artist, duration, plays;

        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, duration, ',');
        getline(ss, plays, ',');

        // Only add songs that are not already in the playlist
        if (find(playlistSongs.begin(), playlistSongs.end(), title) == playlistSongs.end()) {
            cout << id << ". " << title << "\t\t" << artist << "\t\t" << duration << "s\t\t" << plays << endl;
            availableSongs.push_back(title);
            id++;
        }
    }

    // Option to not add any song
    cout << "0. Do not add any song." << endl;

    file.close();
    return availableSongs;
}

vector<string> displayAvailableSongs(const string& filename = "../resources/musics.txt") {
    ifstream file(filename);
    vector<string> songTitles;

    if (!file.is_open()) {
        cout << "Error: Unable to open music database file!" << endl;
        return songTitles;
    }

    cout << "\n=== Available Songs ===" << endl;
    cout << "ID\tTitle\t\tArtist\t\tDuration\tPlays" << endl;
    cout << "------------------------------------------------" << endl;

    string line;
    int id = 1;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, artist, duration, plays;

        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, duration, ',');
        getline(ss, plays, ',');

        cout << id << "\t" << title << "\t\t" << artist << "\t\t"
             << duration << "s\t\t" << plays << endl;

        songTitles.push_back(title);
        id++;
    }
    if (!songTitles.empty()) {
        cout << "0. Do not add any song." << endl;
    }

    file.close();
    return songTitles;
}
int main() {
    playList* currentPlaylist = nullptr;
    int choice;
    string playlistName;

    do {
        cout << endl;  // Add a newline before menu for better spacing
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {  // Create new playlist
                cout << "Enter playlist name: ";
                getline(cin, playlistName);

                // Check if playlist already exists
                if (currentPlaylist->doesPlaylistExist(playlistName)) {
                    cout << "\nError: A playlist with this name already exists!" << endl;
                    break;
                }

                currentPlaylist = new playList(playlistName);
                cout << "\nPlaylist created successfully!" << endl;
                break;
            }

            case 2: {  // Load existing playlist
                cout << "Enter playlist name to load: ";
                getline(cin, playlistName);

                // Create new playlist object
                currentPlaylist = new playList(playlistName);
                if (currentPlaylist->load(playlistName, "../resources/playlist.txt", "../resources/musics.txt")) {
                    cout << "\nPlaylist loaded successfully!" << endl;
                } else {
                    cout << "\nError: Failed to load playlist." << endl;
                    delete currentPlaylist;
                    currentPlaylist = nullptr;
                }
                break;
            }

        case 3: {  // Add song
                    if (!currentPlaylist) {
                        cout << "\nPlease create or load a playlist first!" << endl;
                        break;
                    }

                    // Display available songs to add
                    vector<string> songTitles = displayAvailableSongsToAdd(currentPlaylist);

                    if (songTitles.empty()) {
                        cout << "\nNo songs available to add!" << endl;
                        break;
                    }

                    // Get user choice for song
                    int songId;
                    cout << "\nEnter the ID of the song you want to add (1-" << songTitles.size() << " or 0 to cancel): ";
                    cin >> songId;

                    if (songId == 0) {
                        cout << "\nNo song selected to add!" << endl;
                        break;
                    }

                    if (songId < 1 || songId > static_cast<int>(songTitles.size())) {
                        cout << "\nError: Invalid song ID!" << endl;
                        break;
                    }

                    string selectedSong = songTitles[songId - 1];

                    // Add the selected song to the playlist
                    song s;
                    song* loadedSong = s.load(selectedSong, "../resources/musics.txt");
                    if (loadedSong->getTitle() != "") {
                        currentPlaylist->addSong(loadedSong);
                        cout << "\nSong '" << selectedSong << "' added successfully!" << endl;
                    }
                    break;
        }

        case 4: {  // Remove song
                    if (!currentPlaylist) {
                        cout << "\nPlease create or load a playlist first!" << endl;
                        break;
                    }

                    // Display all songs in the current playlist
                    vector<string> songTitles = currentPlaylist->displaySongsInPlaylist();

                    if (songTitles.empty()) {
                        cout << "\nNo songs available in the playlist!" << endl;
                        break;
                    }

                    // Show the list of available songs in the playlist in the desired format
                    cout << "\n=== Available Songs in Playlist ===" << endl;
                    cout << "ID\tTitle\t\tArtist\t\tDuration\tPlays" << endl;
                    cout << "------------------------------------------------" << endl;

                    for (size_t i = 0; i < songTitles.size(); ++i) {
                        string songTitle = songTitles[i];

                        // Assuming you have a method to get song details like artist, duration, and plays.
                        song s;
                        song* loadedSong = s.load(songTitle, "../resources/musics.txt");

                        // Display song information with ID
                        cout << i + 1 << ". " << songTitle << "\t" << loadedSong->getArtist() << "\t\t"
                             << loadedSong->getDuration() << "s\t\t" << loadedSong->getPlays() << endl;
                    }

                    // Add the cancel option
                    cout << "0. Do not remove any song." << endl;

                    // Ask user to choose a song to remove
                    int songId;
                    cout << "\nEnter the ID of the song you want to remove (1-" << songTitles.size() << " or 0 to cancel): ";
                    cin >> songId;

                    if (songId == 0) {
                        cout << "\nNo song selected to remove!" << endl;
                        break;
                    }

                    if (songId < 1 || songId > static_cast<int>(songTitles.size())) {
                        cout << "\nError: Invalid song ID!" << endl;
                        break;
                    }

                    string songTitle = songTitles[songId - 1];

                    // Remove the song from the playlist
                    currentPlaylist->removeSong(songTitle);
                    cout << "\nSong '" << songTitle << "' removed successfully!" << endl;
                    break;
        }

        case 5: {  // Display songs
                    if (!currentPlaylist) {
                        cout << "Please create or load a playlist first!" << endl;
                        break;
                    }
                    currentPlaylist->displaySongs();
                    break;
        }

        case 6: {  // Play all songs
                    if (!currentPlaylist) {
                        cout << "Please create or load a playlist first!" << endl;
                        break;
                    }
                    currentPlaylist->playSongs();
                    break;
        }

            case 7: {  // Shuffle play
                if (!currentPlaylist) {
                    cout << "\nPlease create or load a playlist first!" << endl;
                    break;
                }
                cout << endl;  // Add newline before playing
                currentPlaylist->shufflePlay();
                break;
            }

        case 8: {  // Sort options
                    displaySortMenu();
                    int sortChoice;
                    if (!(cin >> sortChoice)) {
                        cout << "\nError: Invalid input!" << endl;
                        //clearInputBuffer();
                        //waitForEnter();
                        break;
                    }
                    //clearInputBuffer();

                    switch (sortChoice) {
                    case 1:
                        currentPlaylist->sortByNoOfPlays();
                        cout << "\nPlaylist sorted by number of plays (descending)." << endl;
                        break;
                    case 2:
                        currentPlaylist->sortReverseOfPlays();
                        cout << "\nPlaylist sorted by number of plays (ascending)." << endl;
                        break;
                    case 3:
                        currentPlaylist->sortByAlphSong();
                        cout << "\nPlaylist sorted by song name." << endl;
                        break;
                    case 4:
                        currentPlaylist->sortByAlphArtist();
                        cout << "\nPlaylist sorted by artist name." << endl;
                        break;
                    case 5:
                        currentPlaylist->sortByRecent();
                        cout << "\nPlaylist sorted by recently played." << endl;
                        break;
                    default:
                        cout << "\nError: Invalid sort option!" << endl;
                    }
                    //waitForEnter();
                    break;
        }
        case 9: {  // BST operations
                    displayBSTMenu();
                    int bstChoice;
                    if (!(cin >> bstChoice)) {
                        cout << "\nError: Invalid input!" << endl;
                        //clearInputBuffer();
                        //waitForEnter();
                        break;
                    }
                    //clearInputBuffer();

                    switch (bstChoice) {
                    case 1:
                        currentPlaylist->inOrderRebuild();
                        break;
                    case 2:
                        currentPlaylist->preOrderRebuild();
                        break;
                    case 3:
                        currentPlaylist->postOrderRebuild();
                        break;
                    default:
                        cout << "\nError: Invalid BST option!" << endl;
                    }
                    //waitForEnter();
                    break;
        }

            case 0:
                cout << "\nThank you for using the Music Player!" << endl;
                break;

            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }

    } while (choice != 0);

    // Cleanup
    delete currentPlaylist;
    return 0;
}