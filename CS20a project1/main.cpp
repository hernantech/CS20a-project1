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

class World;

class Life {
public:

	int getCol() const; // const member functions cannot modify member variables.
	int getRow() const;
	int getHeight() const;
	int getWidth() const;
	char getFigure(int r, int c) const;

protected:
	int m_col;
	int m_row;
	int m_height;
	int m_width;
	char **m_sprite;
	World *m_world;
};

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

class World {
public:
	// Constructor/destructor
	World();
	~World();

	void print() const;

	bool init(Life *life);
	void update();
private:

	void clearScreen() const;
	char nextState(char state, char row, char col, bool toggle) const;

	// The rules of Conway's Game of Life requires each cell to
	// examine it's neighbors.  So, we have to check the entire world
	// first before we change it.  We can use two copies of the world,
	// one to check the current state (current day) then another to generate
	// the next state(for the next day). We can toggle between them each
	// step, to avoid having to copy between worlds each step (day) of the game.
	char **m_grid_1;
	char **m_grid_2;
	bool m_toggle;


};


///////////////////////////////////////////////////////////////////////////
// Life Implemention
///////////////////////////////////////////////////////////////////////////

int Life::getCol() const {
	return m_col;
}
int Life::getRow() const {
	return m_row;
}
int Life::getHeight() const {
	return m_height;
}
int Life::getWidth() const {
	return m_width;
}
char Life::getFigure(int r, int c) const {
	return m_sprite[r][c];
}

///////////////////////////////////////////////////////////////////////////
// RPent Implemention
///////////////////////////////////////////////////////////////////////////

RPent::RPent(int r, int c) {

	m_col = c;
	m_row = r;
	m_height = RPENT_SIZE;
	m_width = RPENT_SIZE;

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
	m_sprite[2][1] = DEAD;
	m_sprite[2][2] = DEAD;
}

RPent::~RPent() {
	for (int i = 0; i < m_height; i++) {
		delete[] m_sprite[i];
	}
	delete[] m_sprite;
}
///////////////////////////////////////////////////////////////////////////
// Glider Implemention
///////////////////////////////////////////////////////////////////////////

Glider::Glider(int r, int c) {
	m_col = c;
	m_row = r;
	m_height = GLIDER_SIZE;
	m_width = GLIDER_SIZE;

	// Allocate space for figure
	m_sprite = new char*[m_height];
	for (int i = 0; i < m_height; i++) {
		m_sprite[i] = new char[m_width];
	}

	// Initialize figure
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			m_sprite[i][j] = DEAD;
		}
	}
	m_sprite[0][1] = ALIVE;
	m_sprite[1][2] = ALIVE;
	m_sprite[2][0] = ALIVE;
	m_sprite[2][1] = ALIVE;
	m_sprite[2][2] = ALIVE;
}

Glider::~Glider() {
	for (int i = 0; i < m_height; i++) {
		delete[] m_sprite[i];
	}
	delete[] m_sprite;
}

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
// World Implemention
///////////////////////////////////////////////////////////////////////////

World::World()
{
	m_toggle = true;

	m_grid_1 = new char*[WORLD_ROWS];
	m_grid_2 = new char*[WORLD_ROWS];

	for (char i = 0; i < WORLD_ROWS; i++) {
		m_grid_1[i] = new char[WORLD_COLS];
		m_grid_2[i] = new char[WORLD_COLS];
	}

	for (char i = 0; i < WORLD_ROWS; i++) {
		for (char j = 0; j < WORLD_COLS; j++) {
			m_grid_1[i][j] = DEAD;
		}
	}

}

World::~World() {
	for (char i = 0; i < WORLD_ROWS; i++) {
		delete[] m_grid_1[i];
		delete[] m_grid_2[i];
	}
	delete[] m_grid_1;
	delete[] m_grid_2;

}

void World::print() const {
	clearScreen();
	if (m_toggle) {
		for (char i = 0; i < WORLD_ROWS; i++) {
			for (char j = 0; j < WORLD_COLS; j++) {
				std::cout << m_grid_1[i][j];
			}
			std::cout << std::endl;
		}
	}
	else {
		for (char i = 0; i < WORLD_ROWS; i++) {
			for (char j = 0; j < WORLD_COLS; j++) {
				std::cout << m_grid_2[i][j];
			}
			std::cout << std::endl;
		}
	}
	for (char i = 0; i < WORLD_COLS; i++) {
		std::cout << '=';
	}
	std::cout << std::endl;
}

void World::update() {
	if (m_toggle) {
		for (char i = 0; i < WORLD_ROWS; i++) {
			for (char j = 0; j < WORLD_COLS; j++) {
				m_grid_2[i][j] =
					nextState(m_grid_1[i][j], i, j, m_toggle);
			}
		}
		m_toggle = !m_toggle;
	}
	else {
		for (char i = 0; i < WORLD_ROWS; i++) {
			for (char j = 0; j < WORLD_COLS; j++) {
				m_grid_1[i][j] =
					nextState(m_grid_2[i][j], i, j, m_toggle);
			}
		}
		m_toggle = !m_toggle;
	}
}

char World::nextState(char state, char row, char col, bool toggle) const {
	int yCoord = row;
	int xCoord = col;
	char neighbors = 0;
	if (toggle) {
		for (char i = yCoord - 1; i <= yCoord + 1; i++) {
			for (char j = xCoord - 1; j <= xCoord + 1; j++) {
				if (i == yCoord && j == xCoord) {
					continue;
				}
				if (i > -1 && i < WORLD_ROWS && j > -1 && j < WORLD_COLS) {
					if (m_grid_1[i][j] == ALIVE) {
						neighbors++;
					}
				}
			}
		}
	}
	else {
		for (char i = yCoord - 1; i <= yCoord + 1; i++) {
			for (char j = xCoord - 1; j <= xCoord + 1; j++) {
				if (i == yCoord && j == xCoord) {
					continue;
				}
				if (i > -1 && i < WORLD_ROWS && j > -1 && j < WORLD_COLS) {
					if (m_grid_2[i][j] == ALIVE) {
						neighbors++;
					}
				}
			}
		}
	}
	if (state == ALIVE) {
		return (neighbors > 1 && neighbors < 4) ? ALIVE : DEAD;
	}
	else {
		return (neighbors == 3) ? ALIVE : DEAD;
	}
}

bool World::init(Life *life) {

	if (life == nullptr) {
		std::cout << "Cannot add nullptr life" << std::endl;
		return false;
	}

	for (char i = life->getRow(); i - life->getRow() < life->getHeight(); i++) {
		for (char j = life->getCol(); j - life->getCol() < life->getWidth(); j++) {
			if (i < WORLD_ROWS && j < WORLD_COLS) {
				m_grid_1[i][j] =
					life->getFigure(i - life->getRow(), j - life->getCol());
			}
		}
	}
	return true;
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
