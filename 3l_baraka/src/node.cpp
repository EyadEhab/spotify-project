#include "node.h"

// Constructor
node::node(const song& s, node* nextNode, node* prevNode)
    : data(s), next(nextNode), prev(prevNode) {}