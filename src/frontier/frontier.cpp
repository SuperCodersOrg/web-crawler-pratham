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

FrontierItem Frontier::dequeue(){
    if (frontier.isEmpty()){
        throw std::underflow_error("Frontier is empty");
    }

    FrontierItem item = frontier.front();
    frontier.deleteFront();
    return item;
}

const FrontierItem& Frontier::front() const{
    if (frontier.isEmpty()){
        throw std::underflow_error("Frontier is empty");
    }
    return frontier.front();
}

bool Frontier::isEmpty() const{
    return frontier.isEmpty();
}
int Frontier::size() const{
    return frontier.size();
}
void Frontier::clear(){
    frontier.clear();
}