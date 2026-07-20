#ifndef FRONTIER_H
#define FRONTIER_H

#include <string>

#include "linked_list.h"

struct FrontierItem
{
    std::string url;
    int depth;

    FrontierItem(const std::string& url, int depth);

    bool operator==(const FrontierItem& other) const;
};

class Frontier
{
public:
    Frontier() = default;

    void enqueue(const std::string& url, int depth);

    FrontierItem dequeue();

    const FrontierItem& front() const;

    bool isEmpty() const;

    int size() const;

    void clear();

private:
    LinkedList<FrontierItem> frontier;
};

#endif