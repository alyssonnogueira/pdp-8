
PROGRAM = GTK_sample

#
# The INCLUDEDIRS macro contains a list of include directories
# to pass to the compiler so it can find necessary header files.
#
# The LIBDIRS macro contains a list of library directories
# to pass to the linker so it can find necessary libraries.
#
# The LIBS macro contains a list of libraries that the the
# executable must be linked against.
#

INCLUDEDIRS = \
	-I$(ARCENGINEHOME)/include \
	-I/usr/X11R6/include \
        $(shell pkg-config gtk+-3.0 --cflags)


LIBDIRS = \
	-L$(ARCENGINEHOME)/bin \
	-L/usr/X11R6/lib

LIBS = \
	-larcsdk -lgtkctl -laoctl \
	$(shell pkg-config gtk+-3.0 --libs)

#
# The CXXSOURCES macro contains a list of source files.
#
# The CXXOBJECTS macro converts the CXXSOURCES macro into a list
# of object files.
#
# The CXXFLAGS macro contains a list of options to be passed to
# the compiler.  Adding "-g" to this line will cause the compiler
# to add debugging information to the executable.
#
# The CXX macro defines the C++ compiler.
#
# The LDFLAGS macro contains all of the library and library
# directory information to be passed to the linker.
#

CXXSOURCES = main.cpp
CXXOBJECTS = $(CXXSOURCES:.cpp=.o)
CXXFLAGS = -DESRI_UNIX $(INCLUDEDIRS)
CXX = g++

LDFLAGS = $(LIBDIRS) $(LIBS)

#
# Default target: the first target is the default target.
# Just type "make -f Makefile.LinuxGTK" to build it.
#

all: $(PROGRAM)

#
# Link target: automatically builds its object dependencies before
# executing its link command.
#

$(PROGRAM): $(CXXOBJECTS)
	$(CXX) -o $@ $(CXXOBJECTS) $(LDFLAGS)

#
# Object targets: rules that define objects, their dependencies, and
# a list of commands for compilation.
#

GTK_sample.o: main.cpp #GTK_sample.h
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp

#
# Clean target: "make -f Makefile.LinuxGTK clean" to remove unwanted objects and executables.
#

clean:
	$(RM) -f $(CXXOBJECTS) $(PROGRAM)

#
# Run target: "make -f Makefile.LinuxGTK run" to execute the application
#

run:
			./$(PROGRAM)
