**date:18th july**

duration:60 minutes

goal: git repo setup, configure cmake, install and initialize libcurl

what i tried: since this was the start of the crawler project, i first created a separate git repository and organized the initial folder structure for the project. after that i wrote the initial CMakeLists.txt file and configured the build system so that future crawler components could be compiled easily. then i installed libcurl and integrated it with cmake. finally i wrote a small test program to verify that libcurl was properly initialized and was able to download a webpage successfully before proceeding with the implementation.

problem: initially cmake was unable to locate the curl library because either the development package was not installed correctly or the required paths were not available during configuration. i also had to understand how cmake discovers external libraries and how to correctly link them with the executable.

outcome:

successfully created the git repository, configured the project using cmake, installed libcurl, linked it with the project, and verified that the development environment was ready for implementing the crawler.

pratham@PC-Niklaus:/mnt/n/cq/Project 2/web-crawler-pratham$ pkg-config --modversion libcurl
8.5.0

pratham@PC-Niklaus:/mnt/n/cq/Project 2/web-crawler-pratham/build$ ./webcrawler
libcurl initialized successfully!

- commit reference for git and cmake setup- **baddb9f** configured cmake, setup git repo ,install and initialize libcurl
- commit reference for adding collection loberary as submodule- **624be1e** added collection library as submodule




**date:18th july**

duration:120 minutes

goal: complete the design proposal for web crawler

what i tried: before writing the proposal i spent time understanding how a crawler actually works by reading the project handbook and context document. instead of directly writing the proposal, i first identified the major components such as crawler, frontier, fetcher, seen url store, page storage, link extractor and url normalizer and understood the responsibility of each one. after that i designed the public apis, internal representations, memory diagrams, complexity analysis and design decisions.

problem: the biggest challenge was deciding the responsibility boundaries between different components. for example i had to decide whether url normalization should be performed by the crawler itself or by a separate url normalizer component, and whether the fetcher should only download html or also perform parsing. similarly i had to decide how page storage should be organized so that it remains compatible with future projects like the indexer.

outcome:
completed the first version of the web crawler design proposal including component architecture, public apis, complexity analysis, memory diagrams and the design decisions .

- commit reference-**69817b0** first version of design proposal for web crawler

**date:18t july**

duration:90 minutes

goal: implement fetcher.h and fetcher.cpp

what i tried: i started by designing the fetcher as an independent component whose only responsibility is downloading the html content of a webpage. i kept the interface minimal by exposing only the fetch() method and a configurable request delay while hiding all libcurl specific implementation details inside fetcher.cpp. during implementation i initialized libcurl, configured the required curl options, implemented the callback function to collect the downloaded html into a string . i also kept the implementation open for future extension so that if dynamic page rendering or browser automation is required later, only the internal implementation of the fetcher needs to change without affecting the crawler.

problem: the main difficulty was understanding libcurl's callback mechanism because the downloaded data does not come back directly as a string. instead it arrives in small chunks through a write callback, so i had to understand how to append each chunk correctly into a single html string. i also had to handle different failure cases such as invalid urls, server errors and connection failures by returning an empty string so that the crawler can decide how to proceed.

outcome:

implemented the first version of fetcher.h and fetcher.cpp using libcurl, verified html downloading on sample webpages and kept the fetcher modular enough for future enhancements without changing the crawler interface.

commit references:
**f290e1b** (HEAD -> main) web crawler: fetcher.cpp -> fetch() method implementation plus error handling
**9f605ed** web crawler: fetcher.cpp -> writeCallback() & setRequestDelay()
**4e0b73b** web crawler: wrote fetcher.h
