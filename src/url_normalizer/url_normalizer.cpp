#include "../include/url_normalizer.h"
#include <cctype>

std::string URLNormalizer::normalize(const std::string& url) const
{
    std::string normalizedUrl = url;

    // Trim leading/trailing whitespace
    std::size_t start = normalizedUrl.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
    {
        return "";
    }
    std::size_t end = normalizedUrl.find_last_not_of(" \t\r\n");
    normalizedUrl = normalizedUrl.substr(start, end - start + 1);

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
        std::size_t authorityEnd =
            normalizedUrl.find_first_of("/?", authorityStart);
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