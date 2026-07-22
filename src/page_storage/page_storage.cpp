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

//read
std::string PageStorage::readPage(const PageInfo& pageInfo) const{
    std::ifstream inFile(storageLocation + "/" + pageInfo.storageKey);
    if (!inFile){
        throw std::runtime_error("Unable to open page file.");
    }

    std::string line;
    std::string html;
    // Skip metadata
    while (std::getline(inFile, line)){
        if (line == "-----HTML-----"){
            break;
        }
    }

    // Read HTML content
    while (std::getline(inFile, line)){
        html+=line+'\n';
    }
    inFile.close();

    return html;
}

//store page
void PageStorage::storePage(const std::string& url,const std::string& html,int depth){
    if (hasPage(url)){
        return;
    }
    PageInfo pageInfo;
    pageInfo.url = url;
    pageInfo.depth = depth;
    pageInfo.storageKey = generateStorageKey(nextPageID);
    writePage(pageInfo, html);
    urlToPageID.insert(url, nextPageID);
    pages.push(pageInfo);
    nextPageID++;
}

// get page
std::string PageStorage::getPage(const std::string& url) const{
    if (!hasPage(url)){
        throw std::runtime_error("Page not found.");
    }
    int pageID = urlToPageID.get(url);
    return readPage(pages[pageID]);
}

//has page
bool PageStorage::hasPage(const std::string& url) const{
    return urlToPageID.contains(url);
}

//url by id
std::string PageStorage::getURLByID(int pageID) const{
    if (pageID <= 0 || pageID >= nextPageID){
        throw std::out_of_range("Invalid Page ID.");
    }
    return pages[pageID].url;
}

//pagecount 
int PageStorage::pageCount() const{
    return nextPageID - 1;
}

//
void PageStorage::clear(){
    try{
    std::filesystem::remove_all(storageLocation);
    std::filesystem::create_directories(storageLocation);
    }
    catch(const std::filesystem::filesystem_error& e){
        throw std::runtime_error(e.what());
    }

    urlToPageID.clear();

    pages.clear();

    PageInfo dummyPage;
    pages.push(dummyPage);

    nextPageID = 1;
}