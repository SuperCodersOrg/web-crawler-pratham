#ifndef CRAWLER_H
#define CRAWLER_H

#include <string>

#include "frontier.h"
#include "seen_store.h"
#include "page_storage.h"
#include "fetcher.h"
#include "link_extractor.h"
#include "url_normalizer.h"

class Crawler{
private:
    Frontier frontier;
    SeenStore seenStore;
    PageStorage pageStorage;

    Fetcher fetcher;
    LinkExtractor linkExtractor;
    URLNormalizer urlNormalizer;

    int maxDepth;
    int maxPages;
    int pagesCrawled;

public:
    Crawler(int maxDepth = 2, int maxPages = 100);
    void crawl(const std::string& seedUrl);
};

#endif