#include "game/game.h"

int main(){
	ConsolePlayer player1("Spongebob");
	ConsolePlayer player2("Patrick");
	DebugGame g(player1, player2);
	g.start();
}
