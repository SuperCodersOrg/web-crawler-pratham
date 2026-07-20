#include "../include/link_extractor.h"

DynamicArray<std::string> LinkExtractor::extractLinks(const std::string& html){
    DynamicArray<std::string> extractedLinks;
    const std::string pattern = "href=";
    std::size_t currentPosition = 0;
    while (true){
        std::size_t hrefPosition =
            html.find(pattern, currentPosition);

        if (hrefPosition == std::string::npos){
            break;
        }

        std::size_t quotePosition =hrefPosition + pattern.size();

        // Prevent out-of-bounds access
        if (quotePosition >= html.size()){
            break;
        }

        char quoteCharacter = html[quotePosition];
        if (quoteCharacter != '"' &&quoteCharacter != '\''){
            currentPosition = quotePosition + 1;
            continue;
        }
        std::size_t closingQuote =html.find(quoteCharacter, quotePosition + 1);
        if (closingQuote == std::string::npos){
            break;
        }
        std::string extractedURL =html.substr(quotePosition + 1,closingQuote - quotePosition - 1);

        if (!extractedURL.empty()){
            extractedLinks.push(extractedURL);
        }
        currentPosition = closingQuote + 1;
    }
    return extractedLinks;
}