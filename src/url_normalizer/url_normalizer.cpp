#include "../include/url_normalizer.h"
#include <cctype>


//relative url resolution
std::string URLNormalizer::resolveRelativeURL(
    const std::string& url,
    const std::string& baseURL) const
{
    // Absolute URL
    if (url.find("://") != std::string::npos)
    {
        return url;
    }

    // handle /path
    if (!url.empty() && url.front() == '/'){
        std::size_t schemeEnd = baseURL.find("://");
        if (schemeEnd == std::string::npos){
            return url;
        }
        std::size_t authorityStart = schemeEnd + 3;
        std::size_t authorityEnd =
            baseURL.find('/', authorityStart);
        if (authorityEnd == std::string::npos){
            authorityEnd = baseURL.length();
        }
        return baseURL.substr(0, authorityEnd) + url;
    }

    // handle ./path
    if (url.size() >= 2 && url.substr(0, 2) == "./"){
        std::size_t lastSlash = baseURL.find_last_of('/');
        if (lastSlash == std::string::npos){
            return url.substr(2);
        }
        return baseURL.substr(0, lastSlash + 1) +
            url.substr(2);
    }

    // handle ../path
    // Parent-directory relative URL
    if (url.size() >= 3 && url.substr(0, 3) == "../"){
        std::string resolvedURL = baseURL;
        // Remove the filename from the base URL
        std::size_t lastSlash = resolvedURL.find_last_of('/');
        if (lastSlash != std::string::npos){
            resolvedURL.erase(lastSlash + 1);
        }

        // Find the root of the website (https://example.com/)
        std::size_t schemeEnd = resolvedURL.find("://");
        std::size_t authorityStart = schemeEnd + 3;
        std::size_t authorityEnd =resolvedURL.find('/', authorityStart);
        if (authorityEnd == std::string::npos){
            authorityEnd = resolvedURL.length();
        }
        // Length of "https://example.com/"
        std::size_t rootLength = authorityEnd + 1;
        std::size_t position = 0;
        while (url.compare(position, 3, "../") == 0){
            // Already at website root, can't go higher
            if (resolvedURL.length() <= rootLength){
                break;
            }
            // Remove trailing '/'
            resolvedURL.pop_back();
            // Remove one directory
            std::size_t slash = resolvedURL.find_last_of('/');
            if (slash != std::string::npos){
                resolvedURL.erase(slash + 1);
            }
            position += 3;
        }
        return resolvedURL + url.substr(position);
    }

    // handle plain relative path 
    if (!url.empty() &&
        url.find("://") == std::string::npos &&
        url.front() != '/'){
        std::size_t lastSlash = baseURL.find_last_of('/');
        if (lastSlash == std::string::npos){
            return url;
        }
        return baseURL.substr(0, lastSlash + 1) + url;
    }
        return url;
}

bool URLNormalizer::isFilteredScheme(const std::string& url) const{
    if (url.compare(0, 7, "mailto:") == 0){
        return true;
    }
    if (url.compare(0, 11, "javascript:") == 0){
        return true;
    }
    if (url.compare(0, 5, "data:") == 0){
        return true;
    }
    if (url.compare(0, 4, "tel:") == 0){
        return true;
    }
    return false;
}

bool URLNormalizer::isFilteredResource(const std::string& url) const
{
    if (url.size() >= 4 && url.compare(url.size() - 4, 4, ".css") == 0){
        return true;
    }

    if (url.size() >= 3 && url.compare(url.size() - 3, 3, ".js") == 0){
        return true;
    }

    if (url.size() >= 4 && url.compare(url.size() - 4, 4, ".png") == 0){
        return true;
    }

    if (url.size() >= 4 && url.compare(url.size() - 4, 4, ".jpg") == 0){
        return true;
    }

    if (url.size() >= 5 && url.compare(url.size() - 5, 5, ".jpeg") == 0){
        return true;
    }

    if (url.size() >= 4 && url.compare(url.size() - 4, 4, ".gif") == 0){
        return true;
    }

    if (url.size() >= 4 && url.compare(url.size() - 4, 4, ".svg") == 0){
        return true;
    }
    if (url.size() >= 4 && url.compare(url.size() - 4, 4, ".ico") == 0){
        return true;
    }
    if (url.size() >= 4 && url.compare(url.size() - 4, 4, ".pdf") == 0){
        return true;
    }
    if (url.size() >= 4 && url.compare(url.size() - 4, 4, ".zip") == 0){
        return true;
    }
    return false;
}


std::string URLNormalizer::normalize(const std::string& url,const std::string& baseURL) const {
std::string normalizedUrl =url;

// Trim leading/trailing whitespace
std::size_t start = normalizedUrl.find_first_not_of(" \t\r\n");
if (start == std::string::npos){
    return "";
}
std::size_t end = normalizedUrl.find_last_not_of(" \t\r\n");
normalizedUrl = normalizedUrl.substr(start, end - start + 1);

std::string normalizedURL = resolveRelativeURL(url, baseURL);


// Remove fragment
std::size_t fragmentPosition = normalizedUrl.find('#');
if (fragmentPosition != std::string::npos)
{
    normalizedUrl.erase(fragmentPosition);
}


// Locate scheme
std::size_t schemeEnd = normalizedUrl.find("://");
if (schemeEnd != std::string::npos)
{
    // Lowercase scheme
    for (std::size_t index = 0; index < schemeEnd; index++)
    {
        normalizedUrl[index] = static_cast<char>(
            std::tolower(static_cast<unsigned char>(normalizedUrl[index])));
    }

    std::size_t authorityStart = schemeEnd + 3;
    // Authority ends at the first '/' or '?' (fragment already stripped)
    std::size_t authorityEnd =
        normalizedUrl.find_first_of("/?", authorityStart);
    if (authorityEnd == std::string::npos)
    {
        authorityEnd = normalizedUrl.length();
    }

    // Skip "user:pass@" if present — only host[:port] should be lowercased
    std::size_t hostStart = authorityStart;
    std::size_t atPosition = normalizedUrl.find('@', authorityStart);
    if (atPosition != std::string::npos && atPosition < authorityEnd)
    {
        hostStart = atPosition + 1;
    }
    
    //lowercase hostname
    for (std::size_t index = hostStart; index < authorityEnd; index++)
    {
        normalizedUrl[index] = static_cast<char>(
            std::tolower(static_cast<unsigned char>(normalizedUrl[index])));
    }
}

normalizedUrl = resolveRelativeURL(normalizedUrl, baseURL);

if (isFilteredScheme(normalizedUrl)){
    return "";
}

if (isFilteredResource(normalizedUrl)){
    return "";
}

// Remove an empty query string, e.g. "...path?" -> "...path"
if (!normalizedUrl.empty() && normalizedUrl.back() == '?')
{
    normalizedUrl.pop_back();
}

// Recompute authority end after the mutation above
schemeEnd = normalizedUrl.find("://");
if (schemeEnd != std::string::npos)
{
    std::size_t authorityStart = schemeEnd + 3;
    std::size_t authorityEnd =normalizedUrl.find_first_of("/?", authorityStart);
    if (authorityEnd == std::string::npos)
    {
        authorityEnd = normalizedUrl.length();
    }

    bool hasQuery =
        normalizedUrl.find('?', authorityEnd) != std::string::npos;

    // Strip a redundant trailing '/' from the path, but only if
    // there's no query string after it, and it isn't the sole
    // "root" slash right after the host (keep http://x.com/ as-is).
    if (!hasQuery && !normalizedUrl.empty() && normalizedUrl.back() == '/' && normalizedUrl.length() - 1 != authorityEnd){
        normalizedUrl.pop_back();
    }
}

return normalizedUrl;

}