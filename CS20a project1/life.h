//
//  life.h
//  CS20a project1
//
//  Created by Alex Hernandez on 3/11/22.
//

#ifndef life_h
#define life_h


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


#endif /* life_h */
