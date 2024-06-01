#include <iostream>
#include <string>
#include "game.h"
using namespace std;

int main(int argc, char** argv) {
    istream &in = cin;
    ostream &out = cout;

    Game g{out};
    
    // CLI
    for (int i = 0; i < argc; i++) {
        string s = argv[i];
        if (s == "-text") {
            g.setTextOnly(true);
        } else if (s == "-seed") {
            string seed;
            try {
                seed = argv[i+1];
                g.setSeed(seed);
            } catch(...) {
                out << "no seed provided";
            }
        } else if (s == "-scriptfile1") {
            string filepath;
            try {
                filepath = argv[i+1];
                g.setSFO(filepath);
            } catch(...) {
                out << "no scriptfile provided";
            }
        } else if (s == "-scriptfile2") {
            string filepath;
            try {
                filepath = argv[i+1];
                g.setSFT(filepath);
            } catch(...) {
                out << "no scriptfile provided";
            }
        } else if (s == "-startlevel") {
            string n;
            try {
                n = argv[i+1];
                g.setStartLevel(n);
            } catch(...) {
                out << "no level integer provided";
            }
        }
    }
    g.play(in);
}