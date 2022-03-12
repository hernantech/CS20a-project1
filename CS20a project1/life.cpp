#include "life.h"

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
