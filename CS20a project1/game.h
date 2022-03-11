//
//  game.h
//  CS20a project1
//
//  Created by testing on 3/11/22.
//

#ifndef game_h
#define game_h
class Life;
class World;

class Game {
public:
	// Constructor/destructor
	Game(Life **life, int numLife);
	~Game();
	void report();
	
	void gameLoop();
private:
	void delay(int ms) const;
	World * m_world;
	int m_steps;
	bool m_automate;
};



#endif /* game_h */
