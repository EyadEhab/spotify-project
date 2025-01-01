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
    //cout << "7. Shuffle play" << endl;
    cout << "7. Sort options" << endl;
    cout << "8. Build and traverse BST" << endl;
    cout << "9. Play a song by name" << endl;
    cout << "10. Delete a song from the music database" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

void displaySortMenu() {
    cout << "\n=== Sort Options ===" << endl;
    cout << "1. Sort by number of plays (descending)" << endl;
    cout << "2. Sort by number of plays (ascending)" << endl;
    cout << "3. Sort by song name (A-Z)" << endl;
    cout << "4. Sort by song name (Z-A)" << endl;
    cout << "5. Sort by artist name (A-Z)" << endl;
    cout << "6. Sort by artist name (Z-A)" << endl;
    cout << "7. Sort by recently played (most recent first)" << endl;
    cout << "8. Sort by recently played (least recent first)" << endl;
    cout << "9. Sort by time played (most recent first)" << endl;
    cout << "10. Sort by time played (least recent first)" << endl;
    cout << "0. Cancel" << endl;
    cout << "Enter your choice: ";
}

void displayBSTMenu() {
    cout << "\n=== BST Operations ===" << endl;
    //cout << "1. Build BST" << endl;
    cout << "1. In-order traversal" << endl;
    cout << "2. Pre-order traversal" << endl;
    cout << "3. Post-order traversal" << endl;
    cout << "0. Cancel" << endl;
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

// Helper function to display all playlists and let the user choose one
string choosePlaylistFromFile(const string& filename = "../resources/playlist.txt") {
    ifstream playlistFile(filename);
    if (!playlistFile.is_open()) {
        cout << "\nError: Unable to open playlist file!" << endl;
        return "";
    }

    // Read all playlists from the file
    vector<string> playlists;
    string line;
    while (getline(playlistFile, line)) {
        stringstream ss(line);
        string playlistName;
        getline(ss, playlistName, ','); // Extract the playlist name
        playlists.push_back(playlistName);
    }
    playlistFile.close();

    // Check if there are any playlists
    if (playlists.empty()) {
        cout << "\nNo playlists found!" << endl;
        return "";
    }

    // Display all playlists with numbers
    cout << "\n=== Available Playlists ===" << endl;
    for (size_t i = 0; i < playlists.size(); ++i) {
        cout << i + 1 << ". " << playlists[i] << endl;
    }
    cout << "0. Cancel" << endl;

    // Get user choice
    int playlistChoice;
    while (true) {
        cout << "\nEnter the number of the playlist you want to load (1-" << playlists.size() << " or 0 to cancel): ";
        if (!(cin >> playlistChoice) || playlistChoice < 0 || playlistChoice > static_cast<int>(playlists.size())) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a number between 0 and " << playlists.size() << ": ";
            continue; // Stay in the loop until a valid input is entered
        }
        break; // Exit the loop if a valid choice is entered
    }
    cin.ignore(); // Ignore the newline character left in the input buffer

    // Validate user choice
    if (playlistChoice == 0) {
        cout << "\nOperation canceled." << endl;
        return "";
    }

    // Return the selected playlist name
    return playlists[playlistChoice - 1];
}


int main() {
    playList* currentPlaylist = nullptr;
    int choice;
    string playlistName;

    do {
        cout << endl;  // Add a newline before menu for better spacing
        displayMenu();

        // Handle invalid input (non-numeric or out-of-range)
        while (!(cin >> choice) || choice < 0 || choice > 10) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "Invalid choice! Please enter a number between 0 and 10: ";
        }
        cin.ignore();  // Ignore the newline character left in the input buffer

        switch (choice) {
            case 1: {  // Create new playlist
                cout << "Enter playlist name: ";
                getline(cin, playlistName);

                // Check if playlist already exists
                if (currentPlaylist && currentPlaylist->doesPlaylistExist(playlistName)) {
                    cout << "\nError: A playlist with this name already exists!" << endl;
                    break;
                }

                currentPlaylist = new playList(playlistName);
                cout << "\nPlaylist created successfully!" << endl;
                break;
            }

        case 2: {  // Load existing playlist
                    string selectedPlaylist;
                    while (true) {
                        selectedPlaylist = choosePlaylistFromFile();
                        if (selectedPlaylist.empty()) {
                            cout << "Invalid input! Please enter a number between 0 and the number of playlists: ";
                            continue; // Stay in the loop until a valid input is entered
                        }
                        break; // Exit the loop if a valid playlist is selected
                    }

                    // Delete existing playlist if any
                    delete currentPlaylist;
                    currentPlaylist = nullptr;

                    // Create new playlist object and load the selected playlist
                    currentPlaylist = new playList(selectedPlaylist);
                    if (currentPlaylist->load(selectedPlaylist, "../resources/playlist.txt", "../resources/musics.txt")) {
                        cout << "\nPlaylist '" << selectedPlaylist << "' loaded successfully!" << endl;
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
                while (!(cin >> songId) || songId < 0 || songId > static_cast<int>(songTitles.size())) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number between 0 and " << songTitles.size() << ": ";
                }
                cin.ignore();

                if (songId == 0) {
                    cout << "\nNo song selected to add!" << endl;
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

                // Show the list of available songs in the playlist
                cout << "\n=== Available Songs in Playlist ===" << endl;
                cout << "ID\tTitle\t\tArtist\t\tDuration\tPlays" << endl;
                cout << "------------------------------------------------" << endl;

                for (size_t i = 0; i < songTitles.size(); ++i) {
                    string songTitle = songTitles[i];
                    song s;
                    song* loadedSong = s.load(songTitle, "../resources/musics.txt");
                    cout << i + 1 << ". " << songTitle << "\t" << loadedSong->getArtist() << "\t\t"
                         << loadedSong->getDuration() << "s\t\t" << loadedSong->getPlays() << endl;
                }

                // Add the cancel option
                cout << "0. Do not remove any song." << endl;

                // Ask user to choose a song to remove
                int songId;
                cout << "\nEnter the ID of the song you want to remove (1-" << songTitles.size() << " or 0 to cancel): ";
                while (!(cin >> songId) || songId < 0 || songId > static_cast<int>(songTitles.size())) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number between 0 and " << songTitles.size() << ": ";
                }
                cin.ignore();

                if (songId == 0) {
                    cout << "\nNo song selected to remove!" << endl;
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

        case 7: {  // Sort options
                    if (!currentPlaylist) {
                        cout << "Please create or load a playlist first!" << endl;
                        break;
                    }
                    displaySortMenu();
                    int sortChoice;
                    while (!(cin >> sortChoice) || sortChoice < 0 || sortChoice > 10) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input! Please enter a number between 0 and 10: ";
                    }
                    cin.ignore();
                    if (sortChoice == 0) {
                        cout << "\nSort operation canceled." << endl;
                        break; // Exit the case if the user chooses to cancel
                    }

                    switch (sortChoice) {
                    case 1:
                        currentPlaylist->sortByNoOfPlays();
                        break;
                    case 2:
                        currentPlaylist->sortReverseOfPlays();
                        break;
                    case 3:
                        currentPlaylist->sortByAlphSong();
                        break;
                    case 4:
                        currentPlaylist->sortByAlphSongReverse();
                        break;
                    case 5:
                        currentPlaylist->sortByAlphArtist();
                        break;
                    case 6:
                        currentPlaylist->sortByAlphArtistReverse();
                        break;
                    case 7:
                        currentPlaylist->sortByRecent();
                        break;
                    case 8:
                        currentPlaylist->sortByRecentReverse();
                        break;
                    case 9:
                        currentPlaylist->sortByTimePlayed();
                        break;
                    case 10:
                        currentPlaylist->sortByTimePlayedReverse();
                        break;
                    default:
                        cout << "\nError: Invalid sort option!" << endl;
                    }
                    break;
        }

            case 8: {  // BST operations
                    if (!currentPlaylist) {
                        cout << "Please create or load a playlist first!" << endl;
                        break;
                    }
                displayBSTMenu();
                int bstChoice;
                while (!(cin >> bstChoice) || bstChoice < 0 || bstChoice > 3) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number between 0 and 3: ";
                }
                cin.ignore();
                    if (bstChoice == 0) {
                        cout << "\nSort operation canceled." << endl;
                        break; // Exit the case if the user chooses to cancel
                    }

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
                break;
            }

            case 9: {  // Play a song by its name
                vector<string> songTitles = displayAvailableSongs();

                if (songTitles.empty()) {
                    cout << "\nNo songs available to play!" << endl;
                    break;
                }

                int songId;
                cout << "\nEnter the ID of the song you want to play (1-" << songTitles.size() << " or 0 to cancel): ";
                while (!(cin >> songId) || songId < 0 || songId > static_cast<int>(songTitles.size())) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number between 0 and " << songTitles.size() << ": ";
                }
                cin.ignore();

                if (songId == 0) {
                    cout << "\nOperation canceled." << endl;
                    break;
                }

                string selectedSong = songTitles[songId - 1];

                song s;
                song* loadedSong = s.load(selectedSong, "../resources/musics.txt");
                if (loadedSong->getTitle() != "") {
                    loadedSong->playSong(selectedSong);
                } else {
                    cout << "\nError: Failed to load song!" << endl;
                }
                break;
            }
        case 10: {  // Delete a song from the music database
    // Display all available songs
    vector<string> songTitles = displayAvailableSongs();

    if (songTitles.empty()) {
        cout << "\nNo songs available to delete!" << endl;
        break;
    }

    // Get user choice for song to delete
    int songId;
    while (true) {
        cout << "\nEnter the ID of the song you want to delete (1-" << songTitles.size() << " or 0 to cancel): ";
        if (!(cin >> songId) || songId < 0 || songId > static_cast<int>(songTitles.size())) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a number between 0 and " << songTitles.size() << ": ";
            continue; // Stay in the loop until a valid input is entered
        }
        break; // Exit the loop if a valid choice is entered
    }
    cin.ignore(); // Ignore the newline character left in the input buffer

    if (songId == 0) {
        cout << "\nOperation canceled." << endl;
        break;
    }

    // Get the selected song name
    string selectedSong = songTitles[songId - 1];

    // Delete the selected song from the music database
    song s;
    if (s.deleteSong(selectedSong, "../resources/musics.txt")) {
        cout << "\nSong '" << selectedSong << "' deleted successfully!" << endl;

        // Remove the song from all playlists
        ifstream playlistFile("../resources/playlist.txt");
        vector<string> playlistLines;

        if (playlistFile.is_open()) {
            string line;
            while (getline(playlistFile, line)) {
                stringstream ss(line);
                string playlistName;
                getline(ss, playlistName, ','); // Extract the playlist name

                // Create a temporary playlist object to remove the song
                playList tempPlaylist(playlistName);
                if (tempPlaylist.load(playlistName, "../resources/playlist.txt", "../resources/musics.txt")) {
                    tempPlaylist.removeSong(selectedSong); // Remove the song from the playlist
                    tempPlaylist.save("../resources/playlist.txt"); // Save the updated playlist
                }
            }
            playlistFile.close();
            cout << "Song '" << selectedSong << "' removed from all playlists." << endl;
        } else {
            cerr << "Error: Unable to open playlist file!" << endl;
        }
    } else {
        cout << "\nError: Failed to delete song '" << selectedSong << "'." << endl;
    }
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