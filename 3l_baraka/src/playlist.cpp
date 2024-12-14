#include "playlist.h"

playList::playList(Qstring name) {
    head = null; tail = null;
    count = 0; this->name = name;
    capacity = 10;
    song * newsong = new song[capacity];
}

void playList::addSong(song song){

    node * newsong = new node;
    if(head ==null){
        head = newsong;
        tail = newsong;
    }
    else{
        tail->next=newsong;
        newsong->prev=tail;
        tail=newsong;
    }
    count++;
}

void playList::removeSong(QString name){
    node * temp =head;
    if(head->data->name==name){
        temp = head->next;
        head->next->prev = null;
        delete head;
        head=temp;
        count --;
        return;
    }
    if(tail->data->name==name){
        temp->prev->next=null;
        temp = temp->prev;
        delete tail;
        tail=temp;
        count --;
        return;
    }
    while(temp->data->name!=name){
        if(temp==null){
            qDebug << notfound;
            return;
        }
        temp = temp->next;
    }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        count --;
}

void playList::displaySongs(){
    node*temp=head;
    qDebug << this->name;
    while(temp){
        qdebug << temp->data->name;
        temp=temp->next
    }
}

void displaySum(){
    qDebug << this->count;
}











