all: storyteller

storyteller: storyteller.cpp View.o
	g++ -DBOOST_SIGNALS_NO_DEPRECATION_WARNING -o $@ storyteller.cpp View.o -lwthttp -lwt -lboost_signals

View.o: View.cpp View.h
	g++ -DBOOST_SIGNALS_NO_DEPRECATION_WARNING -c View.cpp

clean:
	- rm storyteller
	- rm *.o


run-local: storyteller
	./storyteller  --docroot . --http-address 0.0.0.0 --http-port 9090
