LDFLAGS=-std=c++11

all: ; g++ $(LDFLAGS) main.cpp GameParser.cpp GameEngine.cpp Player.cpp Board.cpp Berserk.cpp Tracer.cpp Ambusher.cpp Pacifist.cpp Dummy.cpp TestablePlayer.cpp TestableBoard.cpp TestableGameEngine.cpp TestableGameParser.cpp TestableAllStream.cpp -o CengNite
run: ; ./CengNite input.txt
clean: ; rm -rf CengNite;
valgrind: ; valgrind --leak-check=full --error-exitcode=1 ./CengNite input.txt

zipper: ; cat filesToUpload.txt | zip -@ hw4.zip
zipDeleter: ; rm -f hw4.zip

testValgrind: ; make all && make valgrind && echo $?