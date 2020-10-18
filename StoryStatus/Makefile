CXXFLAGS = -std=c++17

all: storystatus

storystatus: Makefile storystatus.cpp
	g++   ${CXXFLAGS}  storystatus.cpp   -o storystatus -ltinyxml2

clean:
	- rm storystatus