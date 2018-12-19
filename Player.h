#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	Texture m_playerTexture;
	Sprite m_player;
	float m_speed;
	bool m_alive;


public:
	Player();
	
	bool PlayerState();

	float GetPositionX();
	float GetPositionY();

	void Move(int direction);
	void SetState(bool state);

	Sprite GetSprite();
	FloatRect GetCollision();


};
