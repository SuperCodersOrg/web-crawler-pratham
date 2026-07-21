**date:21st july**

duration: 100 minutes

goal: implement link_extractor.h and link_extractor.cpp

what i tried: 
i started by designing the link extractor as a stateless component whose only responsibility is extracting hyperlinks from the html content of a webpage. i kept the interface minimal by exposing only the extractLinks() method that returns a DynamicArray of extracted urls without storing any internal state. during implementation i used simple string searching with std::string::find() to locate href= attributes, identified the opening and closing quotation marks, extracted the url using substr() and stored each valid hyperlink inside the dynamic array. 

problem: 
the main challenge was what to use for link extraction algorithm like kmp ,regex ,or simple string matching , so i researched and found out that kmp would not be suitable as i have to match only "href" the five characters so building a table for kmp search would only be time taking ans consume memory and same goes for regex i dont need such advance matching algos so i decided to go with find and substr using strings.
another challenge was figuring out how to correctly extract only the url portion from an html anchor tag without using a dedicated html parser. i had to carefully calculate the positions of the opening and closing quotation marks so that substr() returned only the hyperlink.

outcome:

implemented the first version of link_extractor.h and link_extractor.cpp using simple pattern matching with find() and substr(), verified extraction of multiple hyperlinks from html pages, handled basic malformed input safely and kept the component stateless so it integrates cleanly with the url normalizer and other crawler modules.

commit references:

- **c738f07** (origin/main) implemented link extractor (search of href anchor tag and extract link)


**date: 21st july**

duration: 60 minutes

goal: design and implement the first version of url_normalizer.h and url_normalizer.cpp

what i tried:
i started by understanding why url normalization is required in a crawler and identified the most common cases that could lead to duplicate page visits. based on the project context, i designed the url normalizer as a stateless component with a single normalize() function that accepts a url and returns its normalized form. i first implemented normalization of the scheme and hostname by converting them to lowercase while ensuring that the path and query portions of the url remained unchanged. i also kept the implementation independent from the crawler so that it can be reused wherever url normalization is required.

problem:
the biggest challenge was deciding exactly which parts of a url should be converted to lowercase. initially i considered converting the complete url, but after studying the structure of urls i realized that only the scheme and hostname are case-insensitive, whereas the path and query may be treated differently by web servers. understanding these boundaries was important to avoid modifying urls incorrectly.

outcome:

implemented the initial version of url_normalizer.h and url_normalizer.cpp with support for lowercasing the scheme and hostname while keeping the implementation modular for adding more normalization rules later.

commit references:
- **4dd79ac** web crawler: created url_normalizer.h
- **eebc588** url_normalizer: method for removing trailing and leading whitespaces plus remove fragments


**date: 21st july**

duration: 120 minutes

goal: extend the url normalizer with additional normalization rules

what i tried:
after completing the basic implementation, i extended the normalizer to handle the most common duplicate url cases mentioned in the project documentation. i added logic to trim leading and trailing whitespace, remove url fragments, eliminate empty query strings and remove redundant trailing slashes while preserving the root slash after the hostname. while implementing these rules, i carefully arranged the order of normalization so that each transformation worked correctly with the next one and verified the behavior on different url examples.

problem:
the main difficulty was handling the interaction between empty query strings and trailing slashes. removing one before the other could lead to different results in certain cases, so i spent time reasoning through different url formats before deciding the order of execution. i also had to ensure that the trailing slash removal did not accidentally modify the root path of a website.

```cpp
example:
    https://example.com/page?/
here 
    https://example.com/page?/
                            ^^
                        Query = "/"

i did ,remove last slash only and only iff,
if (!normalizedUrl.empty() &&
    normalizedUrl.back() == '/' &&
    normalizedUrl.length() - 1 != hostEnd){
    normalizedUrl.pop_back();
}

```
outcome:
completed the first version of the url normalizer with support for trimming whitespace, removing fragments, converting the scheme and hostname to lowercase, removing empty query strings and removing redundant trailing slashes. the implementation now covers the normalization cases required for the current version of the crawler while keeping more advanced normalization rules for future iterations.

commit references:
- **eb1d6ab** url_normalizer :implemented scheme and hostname lowercase conversion
- **eebc588** url_normalizer: method for removing trailing and leading whitespaces plus remove fragments
