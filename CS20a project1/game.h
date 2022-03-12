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



///////////////////////////////////////////////////////////////////////////
// Game Implemention
///////////////////////////////////////////////////////////////////////////

Game::Game(Life **life, int numLife) {

	m_steps = 0;
	m_automate = false;
	m_world = new World();

	if (life != nullptr) {
		for (int i = 0; i < numLife; i++) {
			if (life[i] != nullptr) {
				bool success = m_world->init(life[i]);
				if (!success) {
					std::cout << "Failed to add life to the world" << std::endl;
				}
			}

		}
	}

}
Game::~Game() {
	delete m_world;
}

void Game::gameLoop() {
	while (true) {
		m_world->print();

		if (!m_automate) {
			std::cout << "command (<space> to step, <a> to automate, <q> to quit): ";

			std::string action;
			std::getline(std::cin, action);

			switch (action[0])
			{

			default:
				std::cout << '\a' << std::endl;  // beep
				continue;
			case 'q':
				std::cout << "Quitting Game." << std::endl;
				return;
			case 's':

				continue;
			case ' ':

				break;
			case 'a':
				m_automate = true;
				break;

			}
		}
		else {
			if (m_steps >= MAX_STEPS) {
				std::cout << "Reached max steps, quitting." << std::endl;
				return;
			}
			delay(300);
		}
		m_steps++;
		m_world->update();
	}
}

void Game::report() {
	std::string msg = "Hello World!"; // Replace Hello World with your answer.
	std::cout << msg << std::endl;
}


void Game::delay(int ms) const{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}



#endif /* game_h */
