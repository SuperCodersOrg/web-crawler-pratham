#include "../include/fetcher.h"

#include <curl/curl.h>
#include <string>
#include <chrono>
#include <thread>

static size_t writeCallback(void* contents,size_t size,size_t nmemb,void* userp){
    std::string* html = static_cast<std::string*>(userp);
    html->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

Fetcher::Fetcher()
    : requestDelay(1){}

void Fetcher::setRequestDelay(int seconds){
    if (seconds < 1){
        requestDelay = 1;
    }
    else{
        requestDelay = seconds;
    }
}



