#ifndef URL_NORMALIZER_H
#define URL_NORMALIZER_H

#include <string>

class URLNormalizer
{
public:
    std::string normalize(const std::string& url) const;
};

#endif