LDFLAGS=-std=c++11

all: ; g++ $(LDFLAGS) main.cpp Koin.cpp Blockchain.cpp Miner.cpp TestableKoin.cpp TestableBlockchain.cpp TestableMiner.cpp TestableAllStream.cpp mersenne.cpp -o CengMiner;
run: ; ./CengMiner
valgrind: ; valgrind --leak-check=full ./CengMiner
clean: ; rm -rf CengMiner;
