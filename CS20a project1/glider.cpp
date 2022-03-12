#include "glider.h"



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
