#include "../include/frontier.h"

#include <stdexcept>

FrontierItem::FrontierItem(const std::string& url, int depth)
    : url(url), depth(depth){}

bool FrontierItem::operator==(const FrontierItem& other) const{
    return (url == other.url && depth == other.depth);
}

void Frontier::enqueue(const std::string& url, int depth){
    frontier.insertBack(FrontierItem(url, depth));
}

