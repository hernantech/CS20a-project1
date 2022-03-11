//
//  world.h
//  CS20a project1
//
//  Created by testing on 3/11/22.
//

#ifndef world_h
#define world_h
class World;
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


#endif /* world_h */
