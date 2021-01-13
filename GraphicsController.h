#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H
#include <SFML/Graphics/RenderTarget.hpp>
#include "GameLogic.h"

class GraphicsController {
public:
	GraphicsController(sf::RenderTarget &target);
	void Draw();
	void OnMouseClick(int x1, int y1);
private:
	void DrawBoard();
	void DrawText();
	const int bsize;
	GameLogic gamelogic;
	sf::RenderTarget *w;
	
	
	// For input function
	int x, y;
	bool first;
};

#endif

