#include "pch.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include "Enemy.h"
#include "Player.h"

using namespace sf;

int main()
{
	//States
	int gameState = 0;

	//Technicalities
	VideoMode vm(1280, 640);
	RenderWindow window(vm, "Poopity Scoop", Style::Default);
	Clock clock;
	bool pause = true;
	bool canPause = true;
	bool levelsetupdone = false;

	
	
	//Background Stuff.
	Texture textureBackground;
	textureBackground.loadFromFile("Graphics/Background.png");
	Sprite spriteBackground;
	Sprite spriteBackground2;
	spriteBackground.setTexture(textureBackground); spriteBackground2.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);
	spriteBackground2.setPosition(0, -640);
	bool BackgroundToggle = true;
	float backgroundMoveSpeed = 500.0f;
	
	Texture endBackgroundTexture;
	Sprite endBackground;
	endBackgroundTexture.loadFromFile("Graphics/Background2.png");
	endBackground.setTexture(endBackgroundTexture);
	endBackground.setPosition(0, 0);

	Texture mainmenuTextureBackground;
	mainmenuTextureBackground.loadFromFile("Graphics/Background3.png");
	Sprite menubackground;
	menubackground.setTexture(mainmenuTextureBackground);
	menubackground.setPosition(0, 0);


	
	//Initializing Player Class.
	Player player;

	//Initializing Enemy Class Array.
	Enemy enemy[5];


	//Score
	float scoreInt = 0.0f;
	float tempscore = 0;
	float finalscore = 0.0f;
	Font font;
	font.loadFromFile("Font/8bitTxt.ttf");
	Text scoreText;
	scoreText.setCharacterSize(75);
	scoreText.setFillColor(Color::Red);
	scoreText.setOutlineColor(Color::Black);
	scoreText.setOutlineThickness(1);
	scoreText.setFont(font);
	scoreText.setPosition(500, 0);

	Text reminder;
	reminder.setCharacterSize(36);
	reminder.setFont(font);
	reminder.setFillColor(Color::Black);
	reminder.setOutlineColor(Color::White);
	reminder.setOutlineThickness(1);
	reminder.setPosition(120, 600);
	reminder.setString("Press enter to play. Arrows to move left and right.");

	Text gameover;
	gameover.setCharacterSize(112);
	gameover.setFont(font);
	gameover.setFillColor(Color::Black);
	gameover.setOutlineColor(Color::White);
	gameover.setOutlineThickness(1);
	gameover.setPosition(320, 0);
	gameover.setString("Game Over!");

	Text newhighscore;
	newhighscore.setCharacterSize(56);
	newhighscore.setFont(font);
	newhighscore.setFillColor(Color::White);
	newhighscore.setOutlineColor(Color::Black);
	newhighscore.setOutlineThickness(1);
	newhighscore.setPosition(120, 120);
	newhighscore.setString("Congrats! That's a new high score!");

	Text highscore;
	int tempint;
	highscore.setCharacterSize(56);
	highscore.setFont(font);
	highscore.setFillColor(Color::White);
	highscore.setOutlineColor(Color::Black);
	highscore.setOutlineThickness(1);
	highscore.setPosition(320, 200);
	highscore.setString("The high score is: ###");

	Text yourscore;
	yourscore.setCharacterSize(56);
	yourscore.setFont(font);
	yourscore.setFillColor(Color::White);
	yourscore.setOutlineColor(Color::Black);
	yourscore.setOutlineThickness(1);
	yourscore.setPosition(310, 300);
	yourscore.setString("Your score is: ####");

	Text title;
	title.setCharacterSize(112);
	title.setFont(font);
	title.setFillColor(Color::Black);
	title.setOutlineColor(Color::White);
	title.setOutlineThickness(3);
	title.setPosition(280, 0);
	title.setString("X-Treme Cars");

	Text pressEnter;
	pressEnter.setCharacterSize(70);
	pressEnter.setFont(font);
	pressEnter.setFillColor(Color::Black);
	pressEnter.setOutlineColor(Color::White);
	pressEnter.setOutlineThickness(1);
	pressEnter.setPosition(300, 340);
	pressEnter.setString("Press Enter To Play!");

	Text retry;
	retry.setCharacterSize(70);
	retry.setFont(font);
	retry.setFillColor(Color::Black);
	retry.setOutlineColor(Color::White);
	retry.setOutlineThickness(1);
	retry.setPosition(270, 400);
	retry.setString("Press Enter To Retry!");


	
	//Sound
	SoundBuffer levelMusicBuffer;
	levelMusicBuffer.loadFromFile("Sounds/GGGBit.wav");
	Sound levelMusic;
	levelMusic.setBuffer(levelMusicBuffer);
	levelMusic.setLoop(true);
	
	SoundBuffer mainMusicBuffer;
	mainMusicBuffer.loadFromFile("Sounds/Vu8bit.wav");
	Sound mainMusic;
	mainMusic.setBuffer(mainMusicBuffer);
	mainMusic.setLoop(true);
	mainMusic.play();
	
	SoundBuffer crashBuffer;
	crashBuffer.loadFromFile("Sounds/Crash.wav");
	Sound crash;
	crash.setBuffer(crashBuffer);
	
    
	//Main Loop
	while (window.isOpen())
	{
		while (window.hasFocus()) {
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			Time dt = clock.restart(); //Setting up delta time.
			if (gameState == 0)
			{
				bool setupdone = false;
				if (!setupdone)
				{
					window.setMouseCursorVisible(true);
					setupdone = true;
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					mainMusic.stop();
					window.setMouseCursorVisible(false);
					gameState = 1;
				}

				window.clear();
				window.draw(menubackground);
				window.draw(title);
				window.draw(pressEnter);
				window.display();
			}
			if (gameState == 1)
			{

				
				if (!levelsetupdone)
				{
					player.SetState(true);
					for(int i=0;i<5;i++)
					{
						enemy[i].EnemyReset(i);
					}
					tempscore = 0;
					levelsetupdone = true;
				}

				//Player Input.	
				if (canPause)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						if (pause)
						{
							pause = false;
							canPause = false;
							levelMusic.play();
						}
						else
						{
							pause = true;
							canPause = false;
							levelMusic.pause();
						}
					}
				}
				if (!Keyboard::isKeyPressed(Keyboard::Enter))
				{
					canPause = true;
				}


				//Updating the scene.
				if (!pause && player.PlayerState()) {

					//Score
					tempscore += 1 * dt.asSeconds();
					scoreInt = tempscore;
					floor(scoreInt);


					//Moving the player
					if (Keyboard::isKeyPressed(Keyboard::Right))
					{
						if (player.GetPositionX() < 900)
						{
							player.Move(1);
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						if (player.GetPositionX() > 290)
						{
							player.Move(-1);
						}
					}

					for (int i = 0; i < 5; i++)
					{
						if (enemy[i].EnemyGetActive() == false)
						{
							enemy[i].EnemyReset(i);
							break;
						}
						else
						{
							float temp = dt.asSeconds();
							enemy[i].EnemyMove(temp);
							if (enemy[i].GetEnemyPositionY() > 900)
							{
								enemy[i].EnemySetActive(false);
							}
						}
					}


					spriteBackground.setPosition(spriteBackground.getPosition().x, spriteBackground.getPosition().y + backgroundMoveSpeed * dt.asSeconds());
					spriteBackground2.setPosition(spriteBackground2.getPosition().x, spriteBackground2.getPosition().y + backgroundMoveSpeed * dt.asSeconds());
					if (spriteBackground.getPosition().y > 640)
					{

						spriteBackground.setPosition(0, -640);



					}
					if (spriteBackground2.getPosition().y > 640)
					{
						spriteBackground2.setPosition(0, -640);

					}


				}
				// Collisions
				for (int i = 0; i < 5; i++)
				{
					if (enemy[i].GetCollision().intersects(player.GetCollision()))
					{
						enemy[i].EnemyReset(i);
						player.SetState(false);
						finalscore = scoreInt;
						levelMusic.stop();
						crash.play();
						gameState = 2;
					}
				}



				std::stringstream scoreStream;
				scoreStream << "Score: " << scoreInt;
				scoreText.setString(scoreStream.str());
				//Drawing the scene.
				window.clear();
				window.draw(spriteBackground);
				window.draw(spriteBackground2);
				if (player.PlayerState()) { window.draw(player.GetSprite()); }
				for (int i = 0; i < 5; i++) { window.draw(enemy[i].EnemyGetSprite()); }
				if (pause) { window.draw(reminder); };
				window.draw(scoreText);
				window.display();

			}
			if (gameState == 2)
			{
				bool setupdone = false;
				if (!setupdone)
				{
					window.setMouseCursorVisible(true);
					setupdone = true;
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					levelsetupdone = false;
					gameState = 1;
				}

				//Reading the High score stored in the gamedata folder and storing it's content in the tempint created at the begining of the file for manipulating scores.
				std::ifstream inputFile("gamedata/highscore.txt");
				if (inputFile.is_open())
				{
					inputFile >> tempint;
					inputFile.close();
				}


				window.clear();
				window.draw(endBackground);
				window.draw(gameover);
				//if your score > previous high score. Print this. Then update and save new high score.
				if (tempint < finalscore)
				{
					window.draw(newhighscore);

					std::ofstream outputFile("gamedata/highscore.txt");
					outputFile.clear();
					outputFile << finalscore;
					outputFile.close();
				}
				//the scores:
				std::stringstream yourscorestream;
				yourscorestream << "Your score is: " << finalscore;
				yourscore.setString(yourscorestream.str());
				window.draw(yourscore);
				std::stringstream highscorestream;
				highscorestream << "The Highscore is: " << tempint;
				highscore.setString(highscorestream.str());
				window.draw(highscore);
				window.draw(retry);
				window.display();
			}

		}
	}

	return 0;
}

