#include "node.h"

// Constructor
node::node(song* s)
    : next(NULL), prev(NULL) ,data(s){}