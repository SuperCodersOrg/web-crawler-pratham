#ifndef PAGE_STORAGE_H
#define PAGE_STORAGE_H

#include <string>
#include "dynamic_array.h"
#include "hash_map.h"

class PageStorage{
private:
    struct PageInfo{
        std::string url;
        int depth;
        std::string storageKey;
    };
    HashMap<std::string, int> urlToPageID;
    DynamicArray<PageInfo> pages;

    std::string storageLocation;
    int nextPageID;
    std::string generateStorageKey(int pageID) const;
    void writePage(const PageInfo& pageInfo,const std::string& html) const;
    std::string readPage(const PageInfo& pageInfo) const;

public:
    explicit PageStorage(const std::string& storageLocation = "storage");
    void storePage(const std::string& url,
                   const std::string& html,
                   int depth);

    std::string getPage(const std::string& url) const;
    bool hasPage(const std::string& url) const;
    std::string getURLByID(int pageID) const;
    int pageCount() const;
    void clear();
};

#endif