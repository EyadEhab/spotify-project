#include "playlist.h"
#include <algorithm>
#include <iostream>
#include <string>

playList::playList(string name) {
    head = nullptr;
    tail = nullptr;
    root = nullptr;  // Initialize root
    count = 0;
    this->name = name;
}

void playList::addSong(song* songData) {
    node* newSong = new node(songData);

    if (head == nullptr) {  // If the list is empty
        head = tail = newSong;
    } else {  // Append to the end
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
    count++;
    save("../resources/playlist.txt");
}

string playList::getName()
{
    return this->name;
}

void playList::removeSong(string name) {
    if (head == nullptr) {
        cout << "Playlist is empty!" << endl;
        return;
    }

    node* temp = head;

    // Remove from head
    if (head->data->getTitle() == name) {
        temp = head->next;
        if (temp) temp->prev = nullptr;
        delete head;
        head = temp;
        if (!head) tail = nullptr;  // If the list is now empty
        count--;
        save("../resources/playlist.txt");
        return;
    }

    // Remove from tail
    if (tail->data->getTitle() == name) {
        temp = tail->prev;
        if (temp) temp->next = nullptr;
        delete tail;
        tail = temp;
        if (!tail) head = nullptr;  // If the list is now empty
        count--;
        save("../resources/playlist.txt");
        return;
    }

    // Remove from the middle
    while (temp && temp->data->getTitle() != name) {
        temp = temp->next;
    }

    if (!temp) {
        cout << "Song not found!" << endl;
        return;
    }

    temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;

    delete temp;
    count--;
    save("../resources/playlist.txt");
}

void playList::removeAllSongs() {
    while (head) {
        node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
    save("../resources/playlist.txt");
}

void playList::displaySongs() {
    node* temp = head;
    cout << "Playlist: " << this->name << endl;

    while (temp) {
        cout << "\t";
        cout << "\t  " << temp->data->getTitle() << endl;
        temp = temp->next;
    }
}

int playList::getCount()
{
    return count;
}

void playList::displaySum() {
    cout << count << endl;
}

void playList::insertIntoBST(BSTNode*& root, const song* s)
{
    if (root == nullptr) {
        root = new BSTNode(*s);
        return;
    }
    if (s->getTitle() < root->data.getTitle()) { //
        insertIntoBST(root->left, s);
    } else {
        insertIntoBST(root->right, s);
    }
}

void playList::clearBST(BSTNode*& root) {
    if (root == nullptr) return;
    clearBST(root->left);
    clearBST(root->right);
    delete root;
    root = nullptr;
}

void playList::buildTree(BSTNode* root) {
    // Clear the existing tree
    clearBST(this->root);
    this->root = nullptr;

    // Traverse linked list and build BST
    node* current = head;
    while (current != nullptr) {
        insertIntoBST(this->root, current->data);
        current = current->next;
    }
}



// int playList::getRandomNumber()
// {
//     random_device rd; // Obtain a random number from hardware
//     mt19937 gen(rd()); // Seed the generator
//     uniform_int_distribution<> distr(0, getCount() - 1); // Define the range [0, max - 1]
//
//     return distr(gen);
// }

void playList::swapSong(node* a, node* b) {
    song* temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void playList::bubbleSort(bool (*compare)(song*, song*)) {
    if (!head || !head->next) return;

    bool swapped;
    node* ptr1;
    node* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (compare(ptr1->data, ptr1->next->data)) {
                swapSong(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    save("../resources/playlist.txt");
}

// Original sorting functions
void playList::sortByNoOfPlays() {
    bubbleSort([](song* a, song* b) { return a->getPlays() < b->getPlays(); });
    cout << "\nPlaylist sorted by number of plays (descending)." << endl;
}

void playList::sortReverseOfPlays() {
    bubbleSort([](song* a, song* b) { return a->getPlays() > b->getPlays(); });
    cout << "\nPlaylist sorted by number of plays (ascending)." << endl;
}

void playList::sortByAlphSong() {
    bubbleSort([](song* a, song* b) { return a->getTitle() > b->getTitle(); });
    cout << "\nPlaylist sorted by song name (A-Z)." << endl;
}

void playList::sortByAlphArtist() {
    bubbleSort([](song* a, song* b) { return a->getArtist() > b->getArtist(); });
    cout << "\nPlaylist sorted by artist name (A-Z)." << endl;
}

void playList::sortByRecent() {
    bubbleSort([](song* a, song* b) { return a->getTimePlayed() < b->getTimePlayed(); });
    cout << "\nPlaylist sorted by recently played (most recent first)." << endl;
}

void playList::sortByTimePlayed() {
    bubbleSort([](song* a, song* b) { return a->getTimePlayed() < b->getTimePlayed(); });
    cout << "\nPlaylist sorted by time played (most recent first)." << endl;
}

// Reverse sorting functions
void playList::sortByNoOfPlaysReverse() {
    bubbleSort([](song* a, song* b) { return a->getPlays() > b->getPlays(); });
    cout << "\nPlaylist sorted by number of plays (ascending)." << endl;
}

void playList::sortByAlphSongReverse() {
    bubbleSort([](song* a, song* b) { return a->getTitle() < b->getTitle(); });
    cout << "\nPlaylist sorted by song name (Z-A)." << endl;
}

void playList::sortByAlphArtistReverse() {
    bubbleSort([](song* a, song* b) { return a->getArtist() < b->getArtist(); });
    cout << "\nPlaylist sorted by artist name (Z-A)." << endl;
}

void playList::sortByRecentReverse() {
    bubbleSort([](song* a, song* b) { return a->getTimePlayed() > b->getTimePlayed(); });
    cout << "\nPlaylist sorted by recently played (least recent first)." << endl;
}

void playList::sortByTimePlayedReverse() {
    bubbleSort([](song* a, song* b) { return a->getTimePlayed() > b->getTimePlayed(); });
    cout << "\nPlaylist sorted by time played (least recent first)." << endl;
}


void playList::inOrderTraversal(BSTNode* root, vector<song>& result) {
    if (root == nullptr) return;
    inOrderTraversal(root->left, result);
    result.push_back(root->data);
    inOrderTraversal(root->right, result);
}

void playList::preOrderTraversal(BSTNode* root, vector<song>& result) {
    if (root == nullptr) return;
    result.push_back(root->data);
    preOrderTraversal(root->left, result);
    preOrderTraversal(root->right, result);
}

void playList::postOrderTraversal(BSTNode* root, vector<song>& result) {
    if (root == nullptr) return;
    postOrderTraversal(root->left, result);
    postOrderTraversal(root->right, result);
    result.push_back(root->data);
}

void playList::rebuildLinkedListFromVector(vector<song>& songs) {
    // Clear the existing linked list
    removeAllSongs();
    // Rebuild the linked list from the vector
    for (auto& s : songs) {
        addSong(&s);  // Add song to the list
    }
}

// Wrapper for in-order traversal
void playList::inOrderRebuild() {
    if (!root) {
        buildTree(root);  // Build the BST if not already built
    }

    vector<song> result;
    inOrderTraversal(root, result);

    // Update existing nodes without deleting
    rebuildLinkedListFromVector(result);

    save("../resources/playlist.txt");
}

void playList::preOrderRebuild() {
    if (!root) {
        buildTree(root);
    }
    vector<song> result;
    preOrderTraversal(root, result);
    rebuildLinkedListFromVector(result);
    save("../resources/playlist.txt");
}

void playList::postOrderRebuild() {
    if (!root) {
        buildTree(root);
    }
    vector<song> result;
    postOrderTraversal(root, result);
    rebuildLinkedListFromVector(result);

    save("../resources/playlist.txt");
}


bool playList::load(const string& playlistName, const string& playlistFile, const string& musicFile) {
    ifstream file(playlistFile);
    if (!file.is_open()) {
        cerr << "Error: Unable to open playlist file: " << playlistFile << endl;
        return false;
    }

    string line;
    bool playlistFound = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string filePlaylistName;
        getline(ss, filePlaylistName, ','); // Extract the playlist name

        if (filePlaylistName != playlistName) {
            continue; // Skip if this is not the playlist we're looking for
        }

        playlistFound = true;
        name = filePlaylistName; // Set the playlist name

        int numberOfSongs;
        ss >> numberOfSongs; // Read the number of songs
        ss.ignore(1); // Ignore the comma

        string songName;
        while (getline(ss, songName, ',')) {
            song s;
            song* loadedSong = s.load(songName, musicFile);
            if (loadedSong->getTitle() != "") {
                addSong(loadedSong); // Add the song to the playlist
            } else {
                cerr << "Error: Failed to load song: " << songName << endl;
            }
        }

        break; // Exit the loop after loading the playlist
    }

    file.close();

    if (!playlistFound) {
        cerr << "Error: Playlist '" << playlistName << "' not found in " << playlistFile << endl;
        return false;
    }

    return true;
}

void playList::save(const string& filename = "../resources/playlist.txt") {
    // First read all existing playlists
    ifstream inFile(filename);
    vector<string> lines;
    bool playlistExists = false;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string existingPlaylistName;
            getline(ss, existingPlaylistName, ',');

            // If this is not our playlist, keep it
            if (existingPlaylistName != this->name) {
                lines.push_back(line);
            } else {
                playlistExists = true;
            }
        }
        inFile.close();
    }

    // Create the new line for our playlist
    stringstream playlistLine;
    playlistLine << this->name << "," << getCount();

    // Add all songs
    node* current = head;
    while (current) {
        playlistLine << "," << current->data->getTitle();
        current = current->next;
    }//

    // Add our playlist line to the vector
    lines.push_back(playlistLine.str());

    // Write all lines back to the file
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const string& line : lines) {
            outFile << line << endl;
        }
        outFile.close();
        // cout << "Playlist '" << this->name << "' "
        //      << (playlistExists ? "updated" : "saved")
        //      << " successfully!" << endl;
    } else {
        cout << "Error: Unable to open file for saving!" << endl;
    }  // Close the file
}

void playList::playSongs() {
    if (head == nullptr) {
        cout << "The playlist is empty!" << endl;
        return;
    }

    node* current = head;
    while (current) {
        // Play the current song
        current->data->playSong(current->data->getTitle(), current);

        // Move to the next song if playback was not interrupted

        current = current->next;

            // If playback was interrupted (e.g., user quit), stop the playlist
            return;
        }
    }


bool playList::doesPlaylistExist(const string& name, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string playlistName;
            getline(ss, playlistName, ',');
            if (playlistName == name) {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}

bool playList::containsSong(const string& songTitle) {
    node* current = head;
    while (current) {
        if (current->data->getTitle() == songTitle) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Update the shufflePlay function in playlist.cpp:


vector<string> playList::displaySongsInPlaylist() {
    vector<string> songTitles;
    node* temp = head;

    while (temp) {
        songTitles.push_back(temp->data->getTitle());
        temp = temp->next;
    }

    return songTitles;
}










