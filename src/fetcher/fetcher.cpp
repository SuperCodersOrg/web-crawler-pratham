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

std::string Fetcher::fetch(const std::string& url){
    std::this_thread::sleep_for(std::chrono::seconds(requestDelay));
    CURL* curl = curl_easy_init();
    if (curl == nullptr){
        return "";
    }
    std::string html;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

    curl_easy_setopt(curl,CURLOPT_USERAGENT,"WebCrawler/1.0");

    CURLcode result = curl_easy_perform(curl);

    curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&httpStatusCode);
    curl_easy_cleanup(curl);
    if (result != CURLE_OK){
        return "";
    }
    if (httpStatusCode != 200){
        return "";
    }

    if (html.empty()){
        return "";
    }
    return html;
}


