#ifndef NODE_H
#define NODE_H
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QStringList>

#include "song.h"

class node {
public:
    song data;
    node* next;
    node* prev;

    // Constructor
    node(const song& s, node* nextNode = nullptr, node* prevNode = nullptr);
};

#endif // NODE_H
