#include "../include/seen_store.h"

SeenStore::SeenStore(){}

bool SeenStore::contains(const std::string& url) const{
    return visitedURLs.contains(url);
}

void SeenStore::insert(const std::string& url){
    visitedURLs.insert(url, true);
}

int SeenStore::count() const{
    return visitedURLs.size();
}

bool SeenStore::isEmpty() const{
    return visitedURLs.isEmpty();
}

void SeenStore::clear(){
    visitedURLs.clear();
}
