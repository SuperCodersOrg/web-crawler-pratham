#include "../include/page_storage.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

//constructor
PageStorage::PageStorage(const std::string& storageLocation) : storageLocation(storageLocation), nextPageID(1){
    std::filesystem ::create_directories(storageLocation);

    PageInfo dummyPage;
    pages.push(dummyPage);
}

std::string PageStorage::generateStorageKey(int pageID) const{
    return "page_" + std::to_string(pageID) + ".html";
}

//write
void PageStorage::writePage(const PageInfo& pageInfo,const std::string& html) const{
    std::ofstream outFile(storageLocation + "/" + pageInfo.storageKey);
    if (!outFile){
        throw std::runtime_error("Unable to create page file.");
    }
    outFile << "URL: " << pageInfo.url << '\n';
    outFile << "Depth: " << pageInfo.depth << '\n';
    outFile << '\n';
    outFile << "-----HTML-----" << '\n';
    outFile << html;

    outFile.close();
}

