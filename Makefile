gppflags = -Wall -c -pthread -std=c++14 -O3

ljusa : main http.o hash.o

main : ljus.cpp ljus.h
	g++ $(gppflags) ljus.cpp -lpistache -lsodium -lyaml-cpp -o main

http.o : ljus/http/LjusHandler.cpp ljus/http/LjusHandler.h
	g++ $(gppflags) ljus/http/LjusHandler.cpp -lpistache -o http.o

hash.o : ljus/hash/Hash.cpp ljus/hash/Hash.h
	g++ $(gppflags) ljus/hash/Hash.cpp -lpistache -lsodium -o hash.o

config.o : ljus/config/Config.cpp ljus.config/Config.h
	g++ $(gppflags) ljus/config/Config.cpp -lyaml-cpp -o config.o
clean:
		rm main http.o hash.o
