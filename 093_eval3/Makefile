CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
cyoa-step1: cyoa-step1.cpp page.hpp page.cpp
	g++ $(CPPFLAGS) -o cyoa-step1 cyoa-step1.cpp page.hpp page.cpp
cyoa-step2: cyoa-step2.cpp story.hpp story.cpp page.hpp page.cpp
	g++ $(CPPFLAGS) -o cyoa-step2 cyoa-step2.cpp story.hpp story.cpp page.hpp page.cpp
cyoa-step3: cyoa-step3.cpp story.hpp story.cpp page.hpp page.cpp
	g++ $(CPPFLAGS) -o cyoa-step3 cyoa-step3.cpp story.hpp story.cpp page.hpp page.cpp
cyoa-step4: cyoa-step4.cpp story.hpp story.cpp page.hpp page.cpp
	g++ $(CPPFLAGS) -o cyoa-step4 cyoa-step4.cpp story.hpp story.cpp page.hpp page.cpp
