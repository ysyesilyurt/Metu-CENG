#include "TestableGameEngine.h"

#include "GameEngine.h"
#include "BoardPrinter.h"
#include "Tracer.h"
#include "Berserk.h"
#include "Ambusher.h"
#include "Pacifist.h"
#include "Dummy.h"

void TestableGameEngine::runInternal() {
    // Phase 1: Constructing GameEngine

    uint boardSize = 3;

    Player *tracerFirst = new Tracer(0, 0, 0);
    Player *tracerSecond = new Tracer(1, 2, 1);

    std::vector<Player *> *players = new std::vector<Player *>{ tracerFirst, tracerSecond };

    GameEngine engine1 = GameEngine(boardSize, players);

    BoardPrinter::printBoard(engine1.getBoard());
    // 00----
    // --HH01
    // ------

    // Phase 2 : Accessing players

    Player *findTracerFirst = engine1[0];
    Player *findTracerSecond = engine1[1];

    if(findTracerFirst == nullptr || findTracerFirst->getID() != tracerFirst->getID())
        currentGrade -= 1;
    if(findTracerSecond == nullptr || findTracerSecond->getID() != tracerSecond->getID())
        currentGrade -= 1;

    // Phase 3 : takeTurnForPlayer

    Move tracerFirstMove = engine1.takeTurnForPlayer(0);

    // Tracer00(100) moved DOWN.
    if(tracerFirstMove != DOWN)
        currentGrade -= 4;

    BoardPrinter::printBoard(engine1.getBoard());
    // ------
    // 00HH01
    // ------

    Move tracerSecondMove = engine1.takeTurnForPlayer(1);

    // Tracer01(100) moved LEFT.
    if(tracerSecondMove != LEFT)
        currentGrade -= 4;

    BoardPrinter::printBoard(engine1.getBoard());
    // ------
    // 0001--
    // ------

    // Phase 4 : A bit fight

    Move tracerFirstAttack = engine1.takeTurnForPlayer(0);
    // Tracer00(100) ATTACKED Tracer01(100)! (-5)
    if(tracerFirstAttack != ATTACK)
        currentGrade -= 4;

    BoardPrinter::printBoard(engine1.getBoard());

    Move tracerSecondAttack = engine1.takeTurnForPlayer(1);
    // Tracer01(95) ATTACKED Tracer00(100)! (-5)
    if(tracerSecondAttack != ATTACK)
        currentGrade -= 4;

    BoardPrinter::printBoard(engine1.getBoard());

    for(int i = 0; i < 5; i++) // Clearing the path a bit.
        std::cout << std::endl;


    // Phase 5 : A brand new fight, with all players.
    // You may find the summary of this fight as a PDF on CengClass.

    uint newBoardSize = 9;

    Player *berserk1 = new Berserk(0, 0, 1);
    Player *berserk2 = new Berserk(1, 1, 0);

    Player *tracer1 = new Tracer(2, 2, 0);
    Player *tracer2 = new Tracer(3, 0, 2);

    Player *ambusher1 = new Ambusher(4, 4, 3);
    Player *ambusher2 = new Ambusher(5, 3, 4);
    Player *ambusher3 = new Ambusher(6, 5, 4);
    Player *ambusher4 = new Ambusher(7, 4, 5);

    Player *pacifist1 = new Pacifist(8, 7, 8);
    Player *pacifist2 = new Pacifist(9, 8, 7);
    Player *dummyOnHill = new Dummy(10, 4, 4);

    std::vector<Player *> *newPlayers = new std::vector<Player *> { berserk1, berserk2,
                                                                    tracer1, tracer2,
                                                                    ambusher1, ambusher2, ambusher3, ambusher4,
                                                                    pacifist1, pacifist2,
                                                                    dummyOnHill};

    GameEngine engine2 = GameEngine(newBoardSize, newPlayers);

    int infiniteLoopDisengage = 0;

    std::cout << "A brand new game is starting!" << std::endl;

    BoardPrinter::printBoard(engine2.getBoard());

    while(!engine2.isFinished()) {
        if(++infiniteLoopDisengage > 500) {
            // To prevent infinite loop.
            break;
        }

        engine2.takeTurn();

        BoardPrinter::printBoard(engine2.getBoard());
    }

    Player *chickenDinner = engine2.getWinnerPlayer();

    // This is a bit of spoiler, but no one wins!
    // Shame on you, Ambushers!
    if (chickenDinner != nullptr) {
        currentGrade -= 5;
    }
    else {
        std::cout << "No one wins..." << std::endl;
    }

    std::cout << std::endl;
}
