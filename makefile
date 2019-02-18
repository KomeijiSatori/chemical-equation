target : main.o substance.o fraction.o utils.o helper.o format.o
		g++ -g -o main main.o substance.o fraction.o utils.o helper.o format.o

substance.o : substance.cpp substance.h
		g++ -g -c substance.cpp

utils.o : utils.cpp utils.h
		g++ -g -c utils.cpp

fraction.o : fraction.cpp fraction.h
		g++ -g -c fraction.cpp

helper.o : helper.cpp helper.h fraction.h substance.h
		g++ -g -c helper.cpp

format.o : format.cpp format.h substance.h
		g++ -g -c format.cpp

main.o : main.cpp substance.o
		g++ -g -c main.cpp

clean :
		rm main.o substance.o utils.o fraction.o helper.o format.o
