**date:22nd july**

duration: 45 minutes

goal: implement seen_Store.h and seen_store.cpp

what i tried: 
seen store is for storing whether we have seen a particular url or not so there was not much to implement in this section , i just had to use my hash_map from project 1 and that was it i made a data structure named visitedUrls which stores true for urls that are visited .

problem: 
None

outcome:

implemented the first version of seen_store.h and seen_store.cpp

commit references:

- **ca0f817** web crawler: implemented seen_store.cpp directly using hash_map from project 1
- **7df5210** web crawler: added seen_store.



**date: 22nd july**

duration: 50 min

goal: writing page_storage.h with private helper and public api.

problem: the main challenge was keeping the design extensible for future projects(like if i shift to database ) . Designing the api in a way that hides implementation details such as filenames and file paths so that the underlying storage mechanism can later be replaced with a database without changing the external interface.

what i did:
designed the page storage component as an abstraction over the physical storage mechanism whose responsibility is storing and retrieving crawled webpages while hiding all file handling details from the rest of the crawler. i defined a minimal public api with methods for storing pages, retrieving html by url, checking page existence, retrieving urls by page id and counting stored pages. to keep the implementation extensible i also introduced private helper methods such as generateStorageKey(), writePage() and readPage() so that the storage backend can be changed later without affecting the public interface 

outcome:
completed the first version of page_storage.h with a clean public api helper methods for storage operations and an internal design that separates storage implementation from crawler logic while remaining flexible for future extensions.

commit reference:
- **acfb491** web crawler: page storage - wrote page_storage.h with private helper functions and public api


**date: 22nd july**

duration: 120 min

goal: writing page_storage.cpp with methods and private helpers like write_page ,read_page,store_page,get page,haspage,urlbyId and page count

problem:
the main challenge was deciding which data structure should manage the page metadata efficiently. initially i considered using only a DynamicArray to store all page information as i was already using it store the url based on PageID, but that meant every lookup by url would require a linear search through the entire array, making getPage() and hasPage() inefficient as the number of stored pages grows.

what i did:
after comparing the trade-offs, i decided to combine both data structures instead of relying on just one. i used a HashMap to map urls to page ids, providing constant time lookup for crawler operations, and a DynamicArray to store page metadata sequentially by page id, allowing direct access for future indexer traversal. this hybrid approach eliminated linear searches while avoiding unnecessary duplication and satisfied both the crawler's current requirements and the future needs of project 03.

outcome:
successfully implemented page storage.h using file system for the current version .

commit reference:
- **54640ed** page_storage : implemented Clear() for PageStorage
- **044f48f** page_storage : implemented store_page, getPage,hasPage, UrlById and pageCount
- **eafe5ca** page_storage.cpp : implemented read page
- **fce5ec6** page_storage.cpp: constrcutor & write page method



