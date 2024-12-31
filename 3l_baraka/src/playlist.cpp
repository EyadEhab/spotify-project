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
    if (s->getTitle() < root->data.getTitle()) {
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



int playList::getRandomNumber()
{
    random_device rd; // Obtain a random number from hardware
    mt19937 gen(rd()); // Seed the generator
    uniform_int_distribution<> distr(0, getCount() - 1); // Define the range [0, max - 1]

    return distr(gen);
}

void playList::swapSong(node* a, node* b) {
    // Swap the data of the two nodes
    song* temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void playList::sortByNoOfPlays() {
    if (!head || !head->next) {
        return;  // No need to sort if there's 0 or 1 song
    }

    bool swapped;
    node* ptr1;
    node* lptr = nullptr;  // Pointer to the last sorted element

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data->getPlays() < ptr1->next->data->getPlays()) {
                swapSong(ptr1, ptr1->next);  // Swap nodes
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;  // Update the last sorted node
    } while (swapped);

    save("../resources/playlist.txt");
    cout << "Sorted by No of Plays" << endl;
}


void playList::sortReverseOfPlays() {
    if (!head || !head->next) {
        return;  // No need to sort if there's 0 or 1 song
    }

    bool swapped;
    node* ptr1;
    node* lptr = nullptr;  // Pointer to the last sorted element

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data->getPlays() > ptr1->next->data->getPlays()) {
                swapSong(ptr1, ptr1->next);  // Swap nodes
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;  // Update the last sorted node
    } while (swapped);

    save("../resources/playlist.txt");
    cout << "Sorted by reverse No of Plays" << endl;
}


void playList::sortByAlphSong() {
    if (!head || !head->next) {
        return;  // No need to sort if there's 0 or 1 song
    }

    bool swapped;
    node* ptr1;
    node* lptr = nullptr;  // Pointer to the last sorted element

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data->getTitle() > ptr1->next->data->getTitle()) {
                swapSong(ptr1, ptr1->next);  // Swap nodes
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;  // Update the last sorted node
    } while (swapped);

    save("../resources/playlist.txt");
    cout << "Sorted by Song Title" << endl;
}

void playList::sortByAlphArtist() {
    if (!head || !head->next) {
        return;  // No need to sort if there's 0 or 1 song
    }

    bool swapped;
    node* ptr1;
    node* lptr = nullptr;  // Pointer to the last sorted element

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data->getArtist() > ptr1->next->data->getArtist()) {
                swapSong(ptr1, ptr1->next);  // Swap nodes
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;  // Update the last sorted node
    } while (swapped);

    save("../resources/playlist.txt");
    cout << "Sorted by Artist" << endl;
}

void playList::sortByRecent() {
    if (!head || !head->next) {
        return;  // No need to sort if there's 0 or 1 song
    }

    bool swapped;
    node* ptr1;
    node* lptr = nullptr;  // Pointer to the last sorted element

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data->getTimePlayed() < ptr1->next->data->getTimePlayed()) {
                swapSong(ptr1, ptr1->next);  // Swap nodes
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;  // Update the last sorted node
    } while (swapped);

    save("../resources/playlist.txt");
    cout << "Sorted by Most Recently Played" << endl;
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

    // Rebuild linked list from the vector
    for (auto& s : songs) {
        addSong(&s);
    }
    save("../resources/playlist.txt");
}

// Wrapper for in-order traversal
void playList::inOrderRebuild() {
    vector<song> result;
    inOrderTraversal(root, result);
    rebuildLinkedListFromVector(result);
    cout << "Rebuilt linked list in in-order:" << endl;
    displaySongs();
}

// Wrapper for pre-order traversal
void playList::preOrderRebuild() {
    vector<song> result;
    preOrderTraversal(root, result);
    rebuildLinkedListFromVector(result);
    cout << "Rebuilt linked list in pre-order:" << endl;
    displaySongs();
}

// Wrapper for post-order traversal
void playList::postOrderRebuild() {
    vector<song> result;
    postOrderTraversal(root, result);
    rebuildLinkedListFromVector(result);
    cout << "Rebuilt linked list in post-order:" << endl;
    displaySongs();
}



bool playList::load(const string& playlistName, const string& playlistFile = "../resources/playlist.txt", const string& musicFile = "../resources/musics.txt") {
    ifstream file(playlistFile);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << playlistFile << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string filePlaylistName, songName;
        int numberOfSongs;

        // Read the playlist name and count
        getline(ss, filePlaylistName, ',');
        if (filePlaylistName != playlistName) continue;
        ss >> numberOfSongs;  // Read the song count
        ss.ignore(1);  // Ignore the comma

        name = filePlaylistName;

        // Read song names
        while (getline(ss, songName, ',')) {
            song s;
            if (s.load(songName, musicFile)->getArtist() != "") {
                addSong(s.load(songName, musicFile));
            } else {
                cerr << "Failed to load song: " << songName << endl;
            }
        }

        file.close();
        return true;
    }

    file.close();
    cerr << "Playlist not found in playlist.txt: " << playlistName << endl;
    return false;
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
    }

    // Add our playlist line to the vector
    lines.push_back(playlistLine.str());

    // Write all lines back to the file
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const string& line : lines) {
            outFile << line << endl;
        }
        outFile.close();
        cout << "Playlist '" << this->name << "' "
             << (playlistExists ? "updated" : "saved")
             << " successfully!" << endl;
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

        // Move to the next song
        current = current->next;
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
void playList::shufflePlay() {
    if (head == nullptr) {
        cout << "\nPlaylist is empty!" << endl;
        return;
    }

    int random = getRandomNumber();
    node* temp = head;
    for (int i = 0; i < random && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp && temp->data) {
        cout << "\nNow playing random song:" << endl;
        temp->data->playSong(temp->data->getTitle());
    } else {
        cout << "\nError: Could not play random song." << endl;
    }
}

vector<string> playList::displaySongsInPlaylist() {
    vector<string> songTitles;
    node* temp = head;

    while (temp) {
        songTitles.push_back(temp->data->getTitle());
        temp = temp->next;
    }

    return songTitles;
}










