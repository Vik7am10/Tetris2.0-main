#include "game.h"
#include "command.h"
#include "display.h"
#include "Board.h"
#include "BlindBoard.h"
#include "HeavyBoard.h"
#include "ForceBoard.h"
#include "abstractboard.h"
#include <iostream>
#include <memory>
#include <fstream>
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level0.h"

using namespace std;



Game::Game(ostream &out) :  out{out}, da{make_unique<DisplayAscii>(out)}, du{make_unique<DisplayUI>()},textOnly{false},
                            p{Parser()}, t{P1} {
    unique_ptr<Level> level1 = make_unique<Level0>();
    unique_ptr<Level> level2 = make_unique<Level0>();
    std::unique_ptr<ifstream> file1 = make_unique<ifstream>("sequence1.txt");
    std::unique_ptr<ifstream> file2 = make_unique<ifstream>("sequence2.txt");
    level1->block_file = std::move(file1);
    level2->block_file = std::move(file2);

    b1 = make_unique<Board>(std::move(level1));
    b2 = make_unique<Board>(std::move(level2));
}


void Game::setTextOnly(bool b) {
    textOnly = b;
}


void Game::setSeed(string s) {
    int seed = p.getInt(s);
    b1->setSeed(seed);
    b2->setSeed(seed);
}

void Game::setSFO(string filepath) {
    b1->setFile(filepath);
}

void Game::setSFT(string filepath) {
    b2->setFile(filepath);
}

void Game::setStartLevel(string s) {
    int n = p.getInt(s);
    for (int i = 1; i < n; i++) {
        b1->levelUp();
        b2->levelUp();
    }
}


void Game::notify(istream &in) {
    // whose turn is it?
    // prompt for special move
    string s;
    Command c;
    out << "What special move?";
    while (in >> s) {
        c = p.sparse(s);
        if (c.getType() == "invalid") {
            out << "invalid command. try again." << endl;
        } else {
            break;
        }
    }
    if (t == P1) {
        if (c.getType() == "blind") {
            b2 = make_unique<BlindBoard>(move(b2));
        } else if (c.getType() == "force") {
            char c;
            in >> c;
            b2 = make_unique<ForceBoard>(move(b2), c);
        } else if (c.getType() == "heavy") {
            b2 = make_unique<HeavyBoard>(move(b2));
        }
    } else if (t == P2) {
        if (c.getType() == "blind") {
            b1 = make_unique<BlindBoard>(move(b1));
        } else if (c.getType() == "force") {
            char c;
            in >> c;
            b1 = make_unique<ForceBoard>(move(b1), c);
        } else if (c.getType() == "heavy") {
            b1 = make_unique<HeavyBoard>(move(b1));
        }
    }
}



void Game::play(istream &in) {
    string s;
    Command c;

    da->draw(b1, b2); // ASCII   

    if (!textOnly) {
        du->draw(b1,b2); // UI
    }

    while (in >> s) {
        // Get Command
        c = p.parse(s);
        // Which board are we talking about?
        unique_ptr<AbstractBoard> *pubptr; // pointer to a unique_ptr<Board>
        if (t == P1) {
            pubptr = &b1;
        } else if (t == P2) {
            pubptr = &b2;
        }


        // INVALID ARG
        if (c.getType() == "invalid") {
            out << "invalid command. try again." << endl;
            continue;
        }



        // NON-REPEATED ARG        
        if (c.getType() == "restart") {
            b1.reset(nullptr);
            b2.reset(nullptr);
            t = P1;
            continue;
        } else if (c.getType() == "random") {
            (*pubptr)->restoreRandom();
            continue;
        } else if (c.getType() == "norandom") {
            string filepath;
            in >> filepath;
            (*pubptr)->setNoRandom(filepath);
            continue;
        }


        // REPEATED ARG
        for (int i = 0; i < c.getTimes(); i++) {
            da->draw(b1, b2); // ASCII   

            if (!textOnly) {
                du->draw(b1,b2); // UI
            }
            // SEQUENCE
            if (c.getType() == "sequence") {
                string filepath;
                in >> filepath;
                fstream file{filepath};
                play(file);
                continue;
            }


            // LEVEL UP/DOWN
            if (c.getType() == "levelup") {
                (*pubptr)->levelUp();
                continue;
            } else if (c.getType() == "leveldown") {
                (*pubptr)->levelDown();
                continue;
            }


            // I,J,L,O,Z,S,T
            if (c.getType().length() == 1) {
                (*pubptr)->forceNextBlock(c.getType()[0]);
                continue;
            }


            // MOVE (Board::move(string) can accept and handle)
            if ((*pubptr)->move(c.getType())) notify(in);
            if (c.getType() == "drop") {
                if (t == P1) {
                    t = P2;
                    if (t == P1) {
                        pubptr = &b1;
                    } else if (t == P2) {
                        pubptr = &b2;
                    }
                    if (!b1->gameOver()) {
                        out << "Player 2's Turn" << endl;
                    }
                } else if (t == P2) {
                    t = P1;
                    if (t == P1) {
                        pubptr = &b1;
                    } else if (t == P2) {
                        pubptr = &b2;
                    }
                    if (!b2->gameOver()) {
                        out << "Player 1's Turn" << endl;
                    }
                }
                
            }
        }

        da->draw(b1,b2); // ASCII
        if (!textOnly) {
            du->draw(b1,b2); // UI
        } 
        if (b1->gameOver() || b2->gameOver()) {
            char c;
            in >> c;
            return;
        }
    }
}
