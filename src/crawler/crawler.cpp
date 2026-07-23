#include "../include/crawler.h"

#include <iostream>

Crawler::Crawler(int maxDepth, int maxPages): maxDepth(maxDepth),maxPages(maxPages),pagesCrawled(0){}

void Crawler::crawl(const std::string& seedUrl){
    frontier.enqueue(seedUrl, 0);

    while (!frontier.isEmpty() && pagesCrawled < maxPages){
        FrontierItem current = frontier.dequeue();


        // for test 
        std::cout << "\nProcessing: "
          << current.url
          << " Depth: "
          << current.depth
          << std::endl;



        std::string normalizedURL =
            urlNormalizer.normalize(current.url,current.url);

        // 
        std::cout << "Normalized URL: "
          << normalizedURL
          << std::endl;



        if (seenStore.contains(normalizedURL)){
            std::cout << "Already visited\n";
            continue;
        }


        seenStore.insert(normalizedURL);

        std::cout << "Fetching..." << std::endl;

        std::string html =
            fetcher.fetch(normalizedURL);

        std::cout << "Downloaded "
          << html.size()
          << " bytes\n";



        if (html.empty()){
             std::cout << "Fetch failed\n";
            continue;
        }

        pageStorage.storePage(
            normalizedURL,
            html,
            current.depth
        );
        std::cout << "Stored page\n";

        pagesCrawled++;

        std::cout << "Pages crawled = "
          << pagesCrawled
          << std::endl;
          
        DynamicArray<std::string> links =
            linkExtractor.extractLinks(html);

        std::cout << "Links found: "
          << links.size()
          << std::endl;


        for (int i = 0; i < links.size(); i++){
            std::string normalizedLink =
                urlNormalizer.normalize(links[i],normalizedURL);

            if (normalizedLink.empty()){
                continue;
            }

            std::cout << "Found -> "
                    << normalizedLink
                    << std::endl;

            if (!seenStore.contains(normalizedLink) && current.depth + 1 <= maxDepth){
                frontier.enqueue(normalizedLink,current.depth + 1);
                std::cout << "Queued\n";
            }
        }
    }
}