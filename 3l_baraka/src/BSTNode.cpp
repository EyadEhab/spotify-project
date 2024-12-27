//
// Created by eyad on 12/25/24.
//

#include "BSTNode.h"

BSTNode::BSTNode(const song& s, BSTNode* leftNode, BSTNode* rightNode)
:data(s), left(leftNode), right(rightNode){}
