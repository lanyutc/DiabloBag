CC = g++
FLAGS  = -Wall -g -MMD 


SRCS    = $(wildcard *.cpp)
BINS    = test

all: $(BINS)


$(BINS): $(SRCS:.cpp=.o)
	$(CC)  $(FLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(FLAGS) $(DDEFINE) $(INCLUDE) -c -o $@ $<
	@-mv -f $*.d .dep.$@

clean:
	@-rm -f *.o *.oxx *.po *.so *.d .dep.* $(BINS)

-include /dev/null $(wildcard .dep.*)
