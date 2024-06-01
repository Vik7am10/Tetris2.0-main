CXX = g++
CXXFLAGS = -std=c++14 -lX11 -Werror=vla -Wall -L/usr/X11/lib -I/usr/X11/include
OBJECTS = main.o game.o display.o parser.o observer.o subject.o command.o window.o abstractblock.o decoratorblock.o heavyblock.o iblock.o lblock.o jblock.o tblock.o sblock.o oblock.o zblock.o blindboard.o board.o cell.o forceboard.o heavyboard.o level.o level0.o level1.o level2.o level3.o level4.o middleblock.o decoratorboard.o abstractboard.o
EXEC = biquadris

${EXEC}:${OBJECTS}
	${CXX} -g ${OBJECTS} -o ${EXEC} -lX11 -L/usr/X11/lib -I/usr/X11/include

main.o: main.cc game.h

game.o: game.cc game.h display.h parser.h command.h Board.h BlindBoard.h HeavyBoard.h forceboard.h level1.h level2.h abstractboard.h

display.o: display.h display.cc window.h Board.h

parser.o: parser.h parser.cc command.h

observer.o: observer.cc observer.h

subject.o: subject.cc subject.h observer.h

command.o: command.cc command.h

window.o: window.cc window.h

abstractblock.o: abstractblock.cc abstractblock.h Board.h cell.h

decoratorblock.o: decoratorblock.cc decoratorblock.h abstractblock.h Board.h

heavyblock.o: heavyblock.cc heavyblock.h abstractblock.h decoratorblock.h

lblock.o: lblock.cc lblock.h Board.h abstractblock.h

jblock.o: jblock.cc jblock.h Board.h abstractblock.h

iblock.o: iblock.cc iblock.h Board.h abstractblock.h

tblock.o: tblock.cc tblock.h

sblock.o: sblock.cc sblock.h

oblock.o: oblock.cc oblock.h

zblock.o: zblock.cc zblock.h

blindboard.o: BlindBoard.h BlindBoard.cc abstractblock.h Board.h

board.o: Board.h Board.cc cell.h Level.h subject.h abstractblock.h

cell.o: cell.h cell.cc

forceboard.o: forceboard.h forceboard.cc abstractblock.h Board.h

heavyboard.o: HeavyBoard.h HeavyBoard.cc abstractblock.h heavyblock.h Board.h

level.o: Level.h Level.cc sblock.h oblock.h jblock.h lblock.h iblock.h tblock.h zblock.h

level0.o: Level0.h Level0.cc Level1.h Board.h

level1.o: Level0.h Level1.h Level1.cc Level2.h Board.h

level2.o: Level1.h Level2.h Level2.cc Level3.h Board.h

level3.o: Level2.h Level3.h Level3.cc Level4.h Board.h

level4.o: Level3.h Level4.h Level4.cc middleblock.h Board.h

middleblock.o: middleblock.h middleblock.cc Board.h abstractblock.h

abstractboard.o: abstractboard.h abstractboard.cc

decoratorboard.o: decoratorboard.h decoratorboard.cc


clean:
	rm ${OBJECTS} ${EXECS}
