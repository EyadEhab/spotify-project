#ifndef NODE_H
#define NODE_H
#include <string>
#include "song.h"
using namespace std;

class node {
public:
    song data;
    node* next;
    node* prev;

    // Constructor
    node(const song& s, node* nextNode = nullptr, node* prevNode = nullptr);
};

#endif // NODE_H