#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <cmath>

#include "types.h"
#include "position.h"
#include "move.h"
#include "movegen.h"
#include "uci.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

UCI::UCI() {}

void UCI::startCommunication() {
    string input = "";

    while (true) {
        getline(cin, input);

        if (input == "uci") {
            // use uci, only option
            cout << "id name " << ENGINE_NAME << endl;
            cout << "id author " << AUTHOR << endl;

            // send all options that can be set, TODO

            // sent all params and is ready
            cout << "uciok" << endl;

        }
        else if (input == "isready") {
            // are we ready? Guess so.
            cout << "readyok" << endl;
        }

        else if (input == "ucinewgame"){
            // do init.
            pos = Position();
        }

        else if (input.substr(0, 8) == "position") {
            string word;
            std::istringstream iss(input);
            while (iss >> word) {
                if (word == "position")
                    continue;

                else if (word == "fen") {
                    string fen = "";
                    while (iss >> word)
                        fen += word + " ";
                    fen = fen.substr(0,fen.length()-1);
                    // cout << "trying to set fen: " << fen << endl;
                    pos.setFromFEN(fen);
                    break;
                }


                else if (word == "startpos")
                    pos.setFromFEN(STARTING_FEN);

                else if (word == "moves") {
                    while (iss >> word) {
                        if (word.length() >= 4) {
                            Square from, to;
                            from = Square((int)(makeFile(word[0])) + 8*(int)(makeRank(word[1])));
                            to = Square((int)(makeFile(word[2])) + 8*(int)(makeRank(word[3])));
                            pos.doMove(Move(from, to));
                        }
                    }
                }

            }
        }

        else if (input.substr(0,2) == "go") {
            generator = MoveGenerator(pos);
            generator.generateMoves();
            Move bestMove = generator.getRandomMove();
            cout << "info depth 1 score cp -1 time 10 nodes 26 nps 633 pv " << bestMove.str() << endl;
            cout << "bestmove " << bestMove.str() << endl;
        }

        else if (input == "print")
            cout << pos.str() << endl;

        else if (input == "quit")
            break;
    }
}