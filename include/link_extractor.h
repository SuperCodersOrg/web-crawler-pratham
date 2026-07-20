#ifndef LINK_EXTRACTOR_H
#define LINK_EXTRACTOR_H

#include <string>

#include "dynamic_array.h"

class LinkExtractor
{
public:
    DynamicArray <std::string> extractLinks(const std::string& html);
};

#endif