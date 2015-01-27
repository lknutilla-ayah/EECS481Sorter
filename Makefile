PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

# GENERIC END
PROG = team
OBJS = main.o


# Compile flags
LFLAGS = -std=c++11 -Wall -pedantic -Wvla
CFLAGS = -c $(LFLAGS)

# By default, release build
all: release

# Different build states
debug: LFLAGS += -g
release: LFLAGS += -O3

# <NOT GENERIC>
PROG = team
OBJS = main.o preferences.o groups.o
# </NOT GENERIC>

# Compile
debug: $(PROG)
release: $(PROG)

# Compile program
$(PROG): $(OBJS)
	g++ $(LFLAGS) $(OBJS) -o $(PROG)

clean:
	rm -rf *.o *~ team

# Generic end

# Object files
main.o: main.cpp 
	g++ $(CFLAGS) main.cpp

preferences.o: main.cpp preferences.h preferences.cpp
	g++ $(CFLAGS) preferences.cpp

groups.o: main.cpp preferences.cpp groups.h groups.cpp
	g++ $(CFLAGS) groups.cpp


