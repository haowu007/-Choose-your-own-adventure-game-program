all: cyoa-step1 cyoa-step2
CPPFLAGS=g++ -std=gnu++03  -pedantic -ggdb3 -Werror -Wall
cyoa-step1: cyoa-step1.cpp
	 $(CPPFLAGS) -o cyoa-step1 cyoa-step1.cpp

cyoa-step2: cyoa-step2.cpp
	$(CPPFLAGS) -o cyoa-step2 cyoa-step2.cpp

.PHONY: clean
clean:
	rm -f cyoa-step1 cyoa-step2  *.~ *.cpp~ *.txt~ 
