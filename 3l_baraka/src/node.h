#ifndef NODE_H
#define NODE_H

#include <iostream>

// Forward declaration of song class
class song;

using namespace std;

class node {
public:
    song* data;   // Pointer to song
    node* next;
    node* prev;

    // Constructor that takes a const pointer to song
    node(song* s);
};

#endif // NODE_H
