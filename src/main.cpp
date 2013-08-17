#include "game/game.h"
#include "engine/renderHub.h"

int main(){
	ConsolePlayer player1("Spongebob");
	ConsolePlayer player2("Patrick");
	Board board;

	ConsoleGame g(player1, player2, board);
	g.start();
}
