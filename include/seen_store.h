#ifndef SEEN_STORE_H
#define SEEN_STORE_H

#include <string>
#include "hash_map.h"

class SeenStore
{
private:
    HashMap<std::string, bool> visitedURLs;

public:
    SeenStore();

    bool contains(const std::string& url) const;
    void insert(const std::string& url);

    int count() const;
    bool isEmpty() const;
    void clear();
};

#endif