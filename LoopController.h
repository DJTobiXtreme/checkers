#ifndef LOOPCONTROLLER_H
#define LOOPCONTROLLER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "GraphicsController.h"

class LoopController {
public:
	LoopController();
	void Start();
private:
	sf::RenderWindow m_w;
	GraphicsController graphicscontroller;
};

#endif

