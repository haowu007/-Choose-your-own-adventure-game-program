all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
CPPFLAGS=g++ -std=gnu++03  -pedantic -ggdb3 -Werror -Wall
cyoa-step1: cyoa-step1.cpp cyoa.cpp
	 $(CPPFLAGS) -o cyoa-step1 cyoa-step1.cpp

cyoa-step2: cyoa-step2.cpp cyoa.cpp
	$(CPPFLAGS) -o cyoa-step2 cyoa-step2.cpp

cyoa-step3: cyoa-step3.cpp cyoa.cpp
	$(CPPFLAGS) -o cyoa-step3 cyoa-step3.cpp

cyoa-step4: cyoa-step4.cpp cyoa.cpp
	$(CPPFLAGS) -o cyoa-step4 cyoa-step4.cpp


.PHONY: clean
clean:
	rm -f cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4  *.~ *.cpp~ *.hpp~ *.txt~ 
