#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>


#include "game.h"
#include "game.h"
#include "world.h"
#include "world.h"
#include "life.h"
#include "life.h"
#include "rpent.h"
#include "rpent.h"
#include "glider.h"
#include "glider.h"
#include "globals.h"
#include "globals.h"




///////////////////////////////////////////////////////////////////////////
// Type Definitions
///////////////////////////////////////////////////////////////////////////



class RPent : public Life {
public:

	// Constructor/destructor
	RPent(int r, int c);
	~RPent();
};
class Glider : public Life {
public:
	// Constructor/destructor
	Glider(int r, int c);
	~Glider();
};

class Tub : public Life {
public:
	// Constructor/destructor
	Tub(int r, int c);
	~Tub();
};




///////////////////////////////////////////////////////////////////////////
// Tub Implemention
///////////////////////////////////////////////////////////////////////////

Tub::Tub(int r, int c) {

	m_col = c;
	m_row = r;
	m_height = TUB_SIZE;
	m_width = TUB_SIZE;

	//Allocate space for figure
	m_sprite = new char*[m_height];
	for (int i = 0; i < m_height; i++) {
		m_sprite[i] = new char[m_width];
	}

	//Initialize figure
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			m_sprite[i][j] = ALIVE;
		}
	}
	m_sprite[0][0] = DEAD;
	m_sprite[0][2] = DEAD;
	m_sprite[1][1] = DEAD;
	m_sprite[2][0] = DEAD;
	m_sprite[2][2] = DEAD;
}

Tub::~Tub() {
	for (int i = 0; i < m_height; i++) {
		delete[] m_sprite[i];
	}
	delete[] m_sprite;
}





///////////////////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////////////////

int main() {

	Life **population = new Life*[3];

	population[0] = new Glider(4, 4);
	population[1] = new RPent(14, 14);
	population[2] = new Tub(2, 15);
	int numLife = 3;

	// Create the game
	Game g(population, numLife);

	// Run the game
	g.gameLoop();

	// Report
	g.report();

	// Clean up
	delete population[0];
	delete population[1];
	delete population[2];
	delete[] population;

}







/////////////////////////////////////////// START \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// WARNING: Do NOT modify any code found below this warning.  Note that moving code is not
// the same thing as modifying code.  Modifying code changes the behavior, moving code does not.
// Modifying also includes breaking apart the preproccesor directives; do not assume code is
// written specifically for your platform alone.



// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  // DO NOT BREAK APART THE CONTROL MACROS
//  Microsoft Visual C++
#include <windows.h>

void World::clearScreen() const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD upperLeft = { 0, 0 };
	DWORD dwCharsWritten;
	FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
		&dwCharsWritten);
	SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // DO NOT BREAK APART THE CONTROL MACROS
// not Microsoft Visual C++, so assume UNIX interface
#include <iostream>
#include <cstring>
#include <cstdlib>

void World::clearScreen() const {  // will just write a newline in an Xcode output window

	static const char* term = getenv("TERM");
	if (term == nullptr || strcmp(term, "dumb") == 0)
		std::cout << std::endl;
	else {
		static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
		std::cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << std::flush;
	}
}

#endif // DO NOT BREAK APART THE CONTROL MACROS

//////////////////////////////////////////// END \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
