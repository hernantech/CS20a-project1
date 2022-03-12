//
//  world.cpp
//  CS20a project1
//
//  Created by Alex Hernandez on 3/11/22.
//

#include <stdio.h>
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
