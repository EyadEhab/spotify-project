#include "playlist.h"
#include <algorithm>
#include <iostream>
#include <string>

playList::playList(string name) {
    head = nullptr;
    tail = nullptr;
    count = 0;
    this->name = name;

}

void playList::addSong(song songData) {
    node* newSong = new node(songData);

    if (head == nullptr) {  // If the list is empty
        head = tail = newSong;
    } else {  // Append to the end
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
    count++;
}

void playList::removeSong(string name) {
    if (head == nullptr) {
        cout << "Playlist is empty!" << endl;
        return;
    }

    node* temp = head;

    // Remove from head
    if (head->data.getTitle() == name) {
        temp = head->next;
        if (temp) temp->prev = nullptr;
        delete head;
        head = temp;
        if (!head) tail = nullptr;  // If the list is now empty
        count--;
        return;
    }

    // Remove from tail
    if (tail->data.getTitle() == name) {
        temp = tail->prev;
        if (temp) temp->next = nullptr;
        delete tail;
        tail = temp;
        if (!tail) head = nullptr;  // If the list is now empty
        count--;
        return;
    }

    // Remove from the middle
    while (temp && temp->data.getTitle() != name) {
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
}

void playList::removeAllSongs()
{
    node* temp = head;
    while (temp)
    {
        delete head;
        temp = temp->next;
        head = temp;
    }
    count = 0;
}

void playList::displaySongs() {
    node* temp = head;
    cout << "Playlist: " << this->name << endl;

    while (temp) {
        cout << temp->data.getTitle() << endl;
        temp = temp->next;
    }
}

void playList::shufflePlay()
{
    int random = getRandomNumber();
    node* temp = head;
    for (int i = 0; i < random; i++)
    {
        temp = temp->next;
    }
    temp->data.playSong(temp->data.getTitle());
}

int playList::getCount()
{
    return count;
}

void playList::displaySum() {
    cout << count << endl;
}

void playList::insertIntoBST(BSTNode*& root, const song& s)
{
    if (root == nullptr) {
        root = new BSTNode(s);
        return;
    }
    if (s.getTitle() < root->data.getTitle()) {
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

void playList::swapSong(node* a, node* b)
{
    node* temp = a;
    a = b;
    b = temp;
}
void playList::sortByNoOfPlays()
{
    vector<node> sortedByNoOfPlays;

    for (int i = 0; i < count; i++)
    {
        node* temp = head;
        int max = head->data.getPlays();
        while (temp)
        {
            if (temp->data.getPlays() > max)
            {
                max = temp->data.getPlays();
            }
        }
        sortedByNoOfPlays.push_back(*temp);
    }
    removeAllSongs();
    for (int i = 0; i < count; i++)
    {
        addSong(sortedByNoOfPlays.data);
        sortedByNoOfPlays.pop_back();
    }
}

void playList::sortReverseOfPlays()
{
    vector<node> sortedByNoOfPlays;

    for (int i = 0; i < count; i++)
    {
        node* temp = head;
        int min = head->data.getPlays();
        while (temp)
        {
            if (temp->data.getPlays() < min)
            {
                min = temp->data.getPlays();
            }
        }
        sortedByNoOfPlays.push_back(*temp);
    }
    removeAllSongs();
    for (int i = 0; i < count; i++)
    {
        addSong(sortedByNoOfPlays.data);
        sortedByNoOfPlays.pop_back();
    }
}

void playList::sortByAlphSong()
{
    vector<node> sortedByAlphSongs;

    for (int i = 0; i < count; i++)
    {
        node* temp = head;
        string max = head->data.getTitle();
        while (temp)
        {
            if (temp->data.getTitle() < max)
            {
                max = temp->data.getTitle();
            }
        }
        sortedByAlphSongs.push_back(*temp);
    }
    for (int i = 0; i < count; i++)
    {
        addSong(sortedByAlphSongs.data);
        sortedByAlphSongs.pop_back();
    }
}

void playList::sortByAlphArtist()
{
    vector<node> sortedByAlphSongs;

    for (int i = 0; i < count; i++)
    {
        node* temp = head;
        string max = head->data.getArtist();
        while (temp)
        {
            if (temp->data.getArtist() < max)
            {
                max = temp->data.getArtist();
            }
        }
        sortedByAlphSongs.push_back(*temp);
    }
    for (int i = 0; i < count; i++)
    {
        addSong(sortedByAlphSongs.data);
        sortedByAlphSongs.pop_back();
    }
}

void playList::sortByRecent()
{
    if (stack1.empty())
    {
        cout << "No recently played songs to sort by." << endl;
        return;
    }

    vector<node*> sortedByRecent; // Songs in the stack and in the playlist
    vector<node*> remainingSongs; // Songs not in the stack

    // Traverse the playlist and segregate songs
    node* current = head;
    while (current)
    {
        remainingSongs.push_back(current); // Add all songs to remaining by default
        current = current->next;
    }

    // Process the stack
    stack<song*> tempStack = stack1; // Copy the stack
    while (!tempStack.empty())
    {
        song* recentSong = tempStack.top();
        tempStack.pop();

        // Check if the song exists in the playlist
        for (auto it = remainingSongs.begin(); it != remainingSongs.end(); ++it)
        {
            if ((*it)->data.getTitle() == recentSong->getTitle())
            {
                sortedByRecent.push_back(*it); // Add to sorted list
                remainingSongs.erase(it);     // Remove from remaining songs
                break;
            }
        }
    }

    // Rebuild the playlist
    removeAllSongs(); // Clear the current playlist

    // Add stack-prioritized songs first
    for (int i = 0;i<sortedByRecent.size();i++)
    {
        addSong(sortedByRecent.data);
        sortedByRecent.pop_back();
    }

    // Add the remaining songs
    for (int i = 0;i<remainingSongs.size();i++)
    {
        addSong(remainingSongs.data);
        remainingSongs.pop_back();
    }

    cout << "Playlist sorted by recent songs." << endl;
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

void playList::rebuildLinkedListFromVector(const vector<song>& songs) {
    // Clear the existing linked list
    removeAllSongs();

    // Rebuild linked list from the vector
    for (const auto& s : songs) {
        addSong(s);
    }
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






