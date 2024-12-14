#include "playlist.h"

playList::playList(QString name) {
    head = nullptr; tail = nullptr;
    count = 0; this->name = name;
    capacity = 10;
    new song[capacity];
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


void playList::removeSong(QString name) {
    if (head == nullptr) {
        qDebug() << "Playlist is empty!";
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
        qDebug() << "Song not found!";
        return;
    }

    temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;

    delete temp;
    count--;
}


void playList::displaySongs() {
    node* temp = head;
    qDebug() << "Playlist: " << this->name;

    while (temp) {
        qDebug() << temp->data.getTitle();
        temp = temp->next;
    }
}


void playList::displaySum(){
    qDebug() << count;
}











