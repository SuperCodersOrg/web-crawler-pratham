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

    
}