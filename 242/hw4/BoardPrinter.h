#ifndef HW4_BOARD_PRINTER_H
#define HW4_BOARD_PRINTER_H

// engin : DO NOT MODIFY THIS FILE.

#include <vector>
#include <iostream>

#include "Board.h"

class BoardPrinter {
public:
    /**
     * Prints the given board.
     *
     * @param board Board to print.
     * @param shouldPrintColors If true, paints the board in Terminal.
     */
    static void printBoard(const Board& board, bool shouldPrintColors = true) {
        uint boardSize = board.getSize();

        for(uint y = 0; y < boardSize; y++) {
            for (uint x = 0; x < boardSize; x++) {
                Coordinate coord(x, y);

                Player *playerInCoord = board[coord];

                std::string stringToPrint;

                if(playerInCoord != nullptr && !playerInCoord->isDead()) {
                    // There's an alive player in the coord.

                    stringToPrint = playerInCoord->getBoardID();

                    if(shouldPrintColors)
                        std::cout << Color::Modifier(playerInCoord->getColorID());
                }
                else if (board.isCoordHill(coord)) {
                    // It's the hill.

                    stringToPrint = "HH";

                    if(shouldPrintColors)
                        std::cout << Color::Modifier(Color::HILL);
                }
                else {
                    // Empty.

                    stringToPrint = "--";

                    if(shouldPrintColors)
                        std::cout << Color::Modifier(Color::FG_DEFAULT);
                }

                if(shouldPrintColors && board.isStormInCoord(coord)) {
                    std::cout << Color::Modifier(Color::STORM);
                }

                std::cout << stringToPrint;

                if(shouldPrintColors) {
                    // Reset the colors after print.
                    std::cout << Color::Modifier(Color::FG_DEFAULT);
                    std::cout << Color::Modifier(Color::BG_DEFAULT);
                }
            }

            std::cout << std::endl;
        }
    }
};


#endif //HW4_BOARD_PRINTER_H
