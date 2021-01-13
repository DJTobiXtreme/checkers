#include "GraphicsController.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
using namespace std;
using namespace sf;

GraphicsController::GraphicsController(sf::RenderTarget &target) : w(&target), bsize(200), first(true){

}


void GraphicsController::DrawBoard () {
	for(int i=0;i<8;i++) { 
		for(int j=0;j<8;j++) { 
			switch(gamelogic.getInfo(i,j)){
			case 1:{
				CircleShape p1normal(bsize/2,bsize);
				p1normal.setFillColor(Color::Green);
				p1normal.setPosition(i*bsize,j*bsize);
				w->draw(p1normal);
				break;
			};
			case 2:{
				CircleShape p2normal(bsize/2,bsize);
				p2normal.setFillColor(Color::Yellow);
				p2normal.setPosition(i*bsize,j*bsize);
				w->draw(p2normal);
				break;
			};
			case 3:{
				CircleShape p1normal(bsize/2,bsize);
				p1normal.setFillColor(Color::Blue);
				p1normal.setPosition(i*bsize,j*bsize);
				w->draw(p1normal);
				break;
			};
			case 4:{
				CircleShape p1normal(bsize/2,bsize);
				p1normal.setFillColor(Color::Red);
				p1normal.setPosition(i*bsize,j*bsize);
				w->draw(p1normal);
				break;
			};
			case 9:{
				RectangleShape invalid(Vector2f(bsize,bsize));
				invalid.setFillColor(Color::Black);
				invalid.setPosition(i*bsize,j*bsize);
				w->draw(invalid);
				break;
			};	
			}
		}
	}
}

void GraphicsController::DrawText ( ) {
	Font font;
	font.loadFromFile("Roboto.ttf");
	string s = "Player: "+to_string(gamelogic.getCurrentPlayer())+ " " + gamelogic.getLastMessage();
	
	Text text;
	text.setFont(font);
	text.setString(s);
	text.setCharacterSize(50); // in pixels, not points!
	text.setFillColor(Color::Red);
	text.setPosition(0,1600);
	text.setStyle(Text::Bold | Text::Underlined);
	w->draw(text);
	
	s = "Player 1 score: " + to_string(gamelogic.getScore1()) + " " + "Player 2 score: " + to_string(gamelogic.getScore2());
	text.setPosition(0,1650);
	text.setString(s);
	text.setColor(Color::Blue);
	w->draw(text);
}

void GraphicsController::Draw ( ) {
	DrawBoard();
	DrawText();
}

void GraphicsController::OnMouseClick (int x1, int y1) {
	if (first){
		x = x1; y=y1;
		first = !first;
		std::cout<<x1<<" "<<y1<<std::endl;
	} else {
		gamelogic.input(x,y,x1,y1);
		first = !first;
	}
}


