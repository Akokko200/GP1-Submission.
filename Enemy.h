#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
private:
	Sprite m_enemySprite;
	Texture m_enemyTexture;
	float m_enemySpeed;
	bool m_activeEnemy;

public:

	Enemy();
	void EnemySpawn();
	void EnemyReset(int iteration);
	void EnemyMove(float dt);
	void EnemySetActive(bool state);
	float GetEnemyPositionX();
	float GetEnemyPositionY();
	Sprite EnemyGetSprite();
	bool EnemyGetActive();
	float EnemyGetSpeed();
	FloatRect GetCollision();

	
	

};