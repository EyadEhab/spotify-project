#include <iostream>
#include "song.h"
#ifndef BSTNODE_H
#define BSTNODE_H
using namespace std;

class BSTNode {
public:
    song data;
    BSTNode* left;
    BSTNode* right;

    // Constructor
    BSTNode(const song& s, BSTNode* leftNode = nullptr, BSTNode* rightNode = nullptr);
};



#endif //BSTNODE_H
