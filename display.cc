#include "window.h"
#include "display.h"
#include <iostream>
#include <iomanip>
#include <memory>
using namespace std;

DisplayAscii::DisplayAscii(ostream &out) : out{out} {}
DisplayUI::DisplayUI() : wptr{make_unique<Xwindow>(BOX_WIDTH,BOX_HEIGHT)} {}
DisplayT::~DisplayT() {}

void DisplayAscii::draw(unique_ptr<AbstractBoard> &b1, unique_ptr<AbstractBoard> &b2) {
    if (b1->gameOver()) {
        out << "Player 2 Wins! Game Over.";
        return;
    } else if (b2->gameOver()) {
        out << "Player 1 Wins! Game Over.";
        return;
    }
    int p1Score = b1->getScore();
    int p1HighScore = b1->getHighScore();
    int p1Level = b1->getLevel();
    vector<vector<char>> p1NextBlock = b1->displayNextBlock();
    vector<vector<char>> p1Display = b1->display();

    int p2Score = b2->getScore();
    int p2HighScore = b2->getHighScore();
    int p2Level = b2->getLevel();
    vector<vector<char>> p2NextBlock = b2->displayNextBlock();
    vector<vector<char>> p2Display = b2->display();
    

    const string SPACING = "      ";
    const int BUFFER = 3;
    out << "Level:" << setw(5) << p1Level << SPACING << "Level:" << setw(5) << p2Level << endl;
    out << "HS:" << setw(8) << p1HighScore << SPACING << "HS:" << setw(8) << p2HighScore << endl;
    out << "Score:" << setw(5) << p1Score << SPACING << "Score:" << setw(5) << p2Score << endl;
    out << "-----------" << SPACING << "-----------" << endl;
    for (int i = 0; i < BUFFER; i++) {
        out << endl;
    }


    for (int i = 0; i < p1Display.size(); i++) {
        for (int j = 0; j < p1Display[i].size(); j++) {
            out << p1Display[i][j];
        }
        out << SPACING;
        for (int j = 0; j < p2Display[i].size(); j++) {
            out << p2Display[i][j];
        }
        out << endl;
    }
    out << "-----------" << SPACING << "-----------" << endl;


    out << "Next      :" << SPACING << "Next:      " << endl;
    for (int i = 0; i < p1NextBlock.size(); i++) {
        for (int j = 0; j < p1NextBlock[i].size(); j++) {
            out << p1NextBlock[i][j];
        }
        out << SPACING;
        for (int j = 0; j < p2NextBlock[i].size(); j++) {
            out << p2NextBlock[i][j];
        }
        out << endl;
    }


}


void DisplayUI::draw(unique_ptr<AbstractBoard> &b1, unique_ptr<AbstractBoard> &b2) {



    int p1Score = b1->getScore();
    int p1HighScore = b1->getHighScore();
    int p1Level = b1->getLevel();
    vector<vector<char>> p1NextBlock = b1->displayNextBlock();
    vector<vector<char>> p1Display = b1->display();

    int p2Score = b2->getScore();
    int p2HighScore = b2->getHighScore();
    int p2Level = b2->getLevel();
    vector<vector<char>> p2NextBlock = b2->displayNextBlock();
    vector<vector<char>> p2Display = b2->display();

    // don't draw if gameOver
    if (b1->gameOver()) {
        wptr->drawString(X_INDENT,70 + Y_INDENT + 3 * LINE_SPACING + p1Display.size() * CELL_SIZE + 2 * DIV_HEIGHT + p1NextBlock.size() * CELL_SIZE + 100,"Player 2 Wins! Game Over.");
        return;
    } else if (b2->gameOver()) {
        wptr->drawString(X_INDENT + SECOND,70 + Y_INDENT + 3 * LINE_SPACING + p2Display.size() * CELL_SIZE + 2 * DIV_HEIGHT + p2NextBlock.size() * CELL_SIZE + 100,"Player 2 Wins! Game Over.");
        return;
    }

    wptr.reset(new Xwindow{BOX_WIDTH, BOX_HEIGHT});
    Xwindow &w = *wptr;


    // p1Level
    w.drawString(X_INDENT,Y_INDENT, "Level:");
    w.drawString(X_INDENT + LINE_TAB - CHAR_SIZE * to_string(p1Level).length(),Y_INDENT, to_string(p1Level));
    // p1HighScore
    w.drawString(X_INDENT,Y_INDENT + LINE_SPACING, "Highscore:");
    w.drawString(X_INDENT + LINE_TAB - CHAR_SIZE * to_string(p1HighScore).length(),Y_INDENT + LINE_SPACING, to_string(p1HighScore));
    // p1Score
    w.drawString(X_INDENT, Y_INDENT + 2 * LINE_SPACING, "Score:");
    w.drawString(X_INDENT + LINE_TAB - CHAR_SIZE * to_string(p1Score).length(),Y_INDENT + 2 * LINE_SPACING, to_string(p1Score));
    // p1Divider
    w.fillRectangle(X_INDENT,Y_INDENT + 3 * LINE_SPACING, DIV_WIDTH,DIV_HEIGHT,Xwindow::Black);

    // p2Level
    w.drawString(X_INDENT + SECOND,Y_INDENT, "Level:");
    w.drawString(X_INDENT + SECOND + LINE_TAB - CHAR_SIZE * to_string(p2Level).length(),Y_INDENT, to_string(p2Level));
    // p2HighScore
    w.drawString(X_INDENT + SECOND,Y_INDENT + LINE_SPACING, "Highscore:");
    w.drawString(X_INDENT + SECOND + LINE_TAB - CHAR_SIZE * to_string(p2HighScore).length(),Y_INDENT + LINE_SPACING, to_string(p2HighScore));
    // p2Score
    w.drawString(X_INDENT + SECOND, Y_INDENT + 2 * LINE_SPACING, "Score:");
    w.drawString(X_INDENT + SECOND + LINE_TAB - CHAR_SIZE * to_string(p2Score).length(),Y_INDENT + 2 * LINE_SPACING, to_string(p2Score));
    // p2Divider
    w.fillRectangle(X_INDENT + SECOND,Y_INDENT + 3 * LINE_SPACING, DIV_WIDTH,DIV_HEIGHT,Xwindow::Black);

    // Draw line by line board 1 and board 2
    for (int i = 0; i < p1Display.size(); i++) {
        for (int j = 0; j < p1Display[i].size(); j++) {
            auto colour = Xwindow::Red; 
            switch (p1Display[i][j]) { // What colour?
                case 'i':
                    colour = Xwindow::Cyan;
                    break;
                case 'j':
                    colour = Xwindow::Blue;
                    break;
                case 'l':
                    colour = Xwindow::Orange;
                    break;
                case 'o':
                    colour = Xwindow::Yellow;
                    break;
                case 's':
                    colour = Xwindow::Green;
                    break;
                case 'z':
                    colour = Xwindow::Red;
                    break;
                case 't':
                    colour = Xwindow::Magenta;
                    break;
                default:
                    colour = Xwindow::Black;
                    break;
            }
            w.fillRectangle(X_INDENT + j * CELL_SIZE,Y_INDENT + 3 * LINE_SPACING + DIV_HEIGHT + i * CELL_SIZE ,CELL_SIZE,CELL_SIZE, colour);
        }
        for (int j = 0; j < p2Display[i].size(); j++) {
            auto colour = Xwindow::Black; 
            switch (p2Display[i][j]) { // What colour?
                case 'i':
                    colour = Xwindow::Cyan;
                    break;
                case 'j':
                    colour = Xwindow::Blue;
                    break;
                case 'l':
                    colour = Xwindow::Orange;
                    break;
                case 'o':
                    colour = Xwindow::Yellow;
                    break;
                case 's':
                    colour = Xwindow::Green;
                    break;
                case 'z':
                    colour = Xwindow::Red;
                    break;
                case 't':
                    colour = Xwindow::Magenta;
                    break;
                default:
                    colour = Xwindow::Black;
                    break;
            }
            w.fillRectangle(X_INDENT + SECOND + j * CELL_SIZE,Y_INDENT + 3 * LINE_SPACING + DIV_HEIGHT + i * CELL_SIZE ,CELL_SIZE,CELL_SIZE, colour);
        }
    }
    
    // p1Divider
    w.fillRectangle(X_INDENT,Y_INDENT + 3 * LINE_SPACING + DIV_HEIGHT + p1Display.size() * CELL_SIZE,DIV_WIDTH,DIV_HEIGHT,Xwindow::Black);
    // p2Divider
    w.fillRectangle(X_INDENT + SECOND,Y_INDENT + 3 * LINE_SPACING + DIV_HEIGHT + p2Display.size() * CELL_SIZE,DIV_WIDTH,DIV_HEIGHT,Xwindow::Black);
    // p1Next
    w.drawString(X_INDENT,Y_INDENT + 3 * LINE_SPACING + p1Display.size() * CELL_SIZE + 2 * DIV_HEIGHT + 50, "Next:");
    // p2Next
    w.drawString(X_INDENT + SECOND,Y_INDENT + 3 * LINE_SPACING + p2Display.size() * CELL_SIZE + 2 * DIV_HEIGHT + 50, "Next:");

    
    for (int i = 0; i < p1NextBlock.size(); i++) {
        for (int j = 0; j < p1NextBlock[i].size(); j++) {
            auto colour = Xwindow::Black; 
            switch (p1NextBlock[i][j]) { // What colour?
                case 'i':
                    colour = Xwindow::Cyan;
                    break;
                case 'j':
                    colour = Xwindow::Blue;
                    break;
                case 'l':
                    colour = Xwindow::Orange;
                    break;
                case 'o':
                    colour = Xwindow::Yellow;
                    break;
                case 's':
                    colour = Xwindow::Green;
                    break;
                case 'z':
                    colour = Xwindow::Red;
                    break;
                case 't':
                    colour = Xwindow::Magenta;
                    break;
                default:
                    colour = Xwindow::Black;
                    break;
            }
            w.fillRectangle(X_INDENT + j * CELL_SIZE,70+Y_INDENT + 3 * LINE_SPACING + p1Display.size() * CELL_SIZE + 2 * DIV_HEIGHT + i * CELL_SIZE,CELL_SIZE,CELL_SIZE, colour);
        }
        for (int j = 0; j < p2NextBlock[i].size(); j++) {
            auto colour = Xwindow::Black; 
            switch (p2NextBlock[i][j]) { // What colour?
                case 'i':
                    colour = Xwindow::Cyan;
                    break;
                case 'j':
                    colour = Xwindow::Blue;
                    break;
                case 'l':
                    colour = Xwindow::Orange;
                    break;
                case 'o':
                    colour = Xwindow::Yellow;
                    break;
                case 's':
                    colour = Xwindow::Green;
                    break;
                case 'z':
                    colour = Xwindow::Red;
                    break;
                case 't':
                    colour = Xwindow::Magenta;
                    break;
                default:
                    colour = Xwindow::Black;
                    break;
            }
            w.fillRectangle(X_INDENT + SECOND + j * CELL_SIZE,70 + Y_INDENT + 3 * LINE_SPACING + p2Display.size() * CELL_SIZE + 2 * DIV_HEIGHT + i * CELL_SIZE,CELL_SIZE,CELL_SIZE, colour);
        }
    }

}
