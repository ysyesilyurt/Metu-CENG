Testing MyStack
-----------------------------
g++ main_MyStack.cpp -o MyStack

./MyStack
./MyStack > main_MyStack.out 
valgrind ./MyStack

Testing LinkedList
----------------------
g++ main_LinkedList.cpp -o LinkedList
./LinkedList
./LinkedList > main_LinkedList.out
valgrind ./LinkedList

Testing Playlist
-----------------------
g++ main_Playlist.cpp Playlist.cpp Entry.cpp HistoryRecord.cpp -o Playlist
./Playlist
./Playlist > main_Playlist.out
valgrind ./Playlist


