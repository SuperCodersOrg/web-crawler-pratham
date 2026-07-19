#ifndef FETCHER_H
#define FETCHER_H

#include <string>

class Fetcher
{
private:
    int requestDelay;

public:
    Fetcher();
    
    std::string fetch(const std::string& url);

    void setRequestDelay(int seconds = 1);
};

#endif