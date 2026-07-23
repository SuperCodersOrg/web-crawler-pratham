// #ifndef URL_NORMALIZER_H
// #define URL_NORMALIZER_H

// #include <string>

// class URLNormalizer
// {
// public:
//     std::string normalize(const std::string& url) const;
// };

// #endif


#ifndef URL_NORMALIZER_H
#define URL_NORMALIZER_H

#include <string>

class URLNormalizer{
public:
    std::string normalize(const std::string& url,
                          const std::string& baseURL) const;

private:
    std::string resolveRelativeURL(const std::string& url,
                                   const std::string& baseURL) const;

    bool isFilteredScheme(const std::string& url) const;
    bool isFilteredResource(const std::string& url) const;
};

#endif