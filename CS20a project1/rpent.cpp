#include "rpent.h"


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
