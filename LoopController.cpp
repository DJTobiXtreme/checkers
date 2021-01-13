#include "LoopController.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
using namespace std;

LoopController::LoopController(): m_w(sf::VideoMode(1600,1800),"Chekers") ,graphicscontroller(m_w){
	
}


void LoopController::Start ( ) {
	m_w.setFramerateLimit(60);

	
	sf::Event e;
	while (m_w.isOpen()){
		
		while(m_w.pollEvent(e)){
			if (e.type == sf::Event::Closed){
				m_w.close();
			}
			if (e.type == sf::Event::MouseButtonPressed){
				graphicscontroller.OnMouseClick(e.mouseButton.x/200, e.mouseButton.y/200);
			}
			
		}
		
		m_w.clear(sf::Color::White);
		graphicscontroller.Draw();
		m_w.display();
	} 
}

