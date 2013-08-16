#include "game/game.h"

int main(){
	ConsolePlayer player1("Spongebob");
	ConsolePlayer player2("Patrick");
	ConsoleGame g(player1, player2);
	g.start();
}
