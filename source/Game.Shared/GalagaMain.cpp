#include <iostream>
#include <algorithm>
#include "SpriteTextureLoading.h"
#include "PlayerProjectile.h"
#include "Spaceship.h"
#include "Enemy.h"
#include "WaveSpawner.h"
#include <cstdlib>
#include "EnemyBullet.h"
#include "pch.h"

namespace GalagaPort
{

}
/*
SpriteTextureLoading textureLoader; //An object of the SpriteTextureLoading class that holds onto textures used in the program
Spaceship shipSprite;

PlayerProjectile currentProjectile[2] = {}; //Holds player projectile objects to maintain reference
EnemyBullet enemyShots[4];

int enemyPosition = 0; //Specifies the wave to be spawned next in line
int yScroll = 0; //
float yScrollCounter = 5.0f;
sf::Time timeOfHit = sf::Time();
float hitCooldown = 2.0;

sf::Time enemyLastShot = sf::Time();
sf::Time playerLastShot = sf::Time();
float enemyShootCooldown = 0.8f;
float playerShootCooldown = 0.4f;
float explosionTime = 0.5f;

bool markedForDelete = false;

int enemyCounter = 0;
WaveSpawner* enemyManager = new WaveSpawner(textureLoader.redEnemy, textureLoader.greenEnemy, textureLoader.yellowEnemy);

sf::RenderWindow window(sf::VideoMode(700, 700), "NOT a Galaga clone");
bool gameStart = false;

bool gameWin = false;

void GameLoop(); //The main loop for the game
void GameStart(); //The start screen for the game
void GameWin(); //The win state for the game
void GameLoss(); //The loss screen for the game
void InitializeStates();//Basic state initialization

int main()
{
    if (markedForDelete)
    {
        delete enemyManager;
    }
    else
    {
        InitializeStates();
        GameStart();
        GameLoop();
    }
}

void InitializeStates() //Sets basic states for necessary objects
{
    enemyManager->SetPatrol(); //Initializes enemy waves and other behavior

    shipSprite.setTexture(textureLoader.ship);

    window.draw(textureLoader.startSprite);
    window.display();
}

void GameLoop() //The basic game loop itself
{
    sf::Clock clock; //Keep track of time in the game by seconds for timing and wave spawning
    sf::Time timePassed;

    for (int  l = 0; l < sizeof(shipSprite.lives) / sizeof(sf::Sprite); l++) //Starts by initializing the player live icons so they know how many times they can be hit before death
    {
        shipSprite.lives[l].setPosition(sf::Vector2f(l * 40.0f + 8, 665));
        shipSprite.lives[l].setTexture(textureLoader.ship);
    }

    while (window.isOpen() && gameStart && shipSprite.life > 0 && !gameWin) //Continue as long as the player hasn't closed the window
    {
        timePassed = clock.getElapsedTime();
        if (enemyPosition < 5) //Spawns all enemy waves at target times based on seconds spent in game
        {
            (*enemyManager).CheckClock(enemyPosition, timePassed.asSeconds());
        }

        if (timeOfHit.asSeconds() > 0.01f) //Checks if hurt cooldown time is up for ship. This is used to change it from the "hurt" state back to the normal state again.
        {
            if ((timePassed.asSeconds() - timeOfHit.asSeconds()) >= hitCooldown)
            {
                timeOfHit = sf::Time();
                shipSprite.isHurt = false;
                shipSprite.setTexture(textureLoader.ship);
            }
        }

        if (yScroll + 4 <= 1500 && yScrollCounter <= 0) //This is used to scroll the background by shifting the y coordinate used in the texture
        {
            yScrollCounter = 5;
            yScroll += 4;
            textureLoader.background.loadFromFile("Assets\\Images\\SpaceBackgroundLoopable.png", sf::IntRect(0, yScroll, 700, 700));
        }

        else if (yScrollCounter <= 0) //This resets the yscrollcounter variable and yscroll variables so the texture loops again.
        {
            yScrollCounter = 5;
            yScroll = 0;
            textureLoader.background.loadFromFile("Assets\\Images\\SpaceBackgroundLoopable.png", sf::IntRect(0, yScroll, 0, 0));
        }
        yScrollCounter -= 0.1f;

        sf::Event event;

        while (window.pollEvent(event)) //Check for user input that has effect on game
        {
            if (event.type == sf::Event::Closed) //Checks for closing of window
            {
                delete(enemyManager);
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A && (shipSprite.shipX - 16 - shipSprite.changeAmt >= 0)) //Checks if we should move the ship left
                {
                    shipSprite.shipX -= shipSprite.changeAmt;
                    shipSprite.collisionBox.setPosition(shipSprite.getPosition());
                }
                if (event.key.code == sf::Keyboard::D && (700 - 32 - shipSprite.changeAmt >= shipSprite.shipX)) //Check if we should move the ship right
                {
                    shipSprite.shipX += shipSprite.changeAmt;
                    shipSprite.collisionBox.setPosition(shipSprite.getPosition());
                }

                if (event.key.code == sf::Keyboard::Space) //Instantiate new missile if there are empty spaces for it
                {
                    if (playerShootCooldown <= (timePassed.asSeconds() - playerLastShot.asSeconds()) || playerLastShot.asSeconds() == 0)
                    {
                        shipSprite.NewMissile(shipSprite, currentProjectile, window, textureLoader.missile);
                        playerLastShot = timePassed;
                        textureLoader.shootSound.play();
                    }
                }
            }
        }

        if (enemyShootCooldown <= (timePassed.asSeconds() - enemyLastShot.asSeconds()) || enemyLastShot.asSeconds() == 0) //Checks if there are currently less than 4 missiles onscreen, allowing instantiation of a new one if so. Only allowed if enemyshotcooldown has been surpassed or met
        {
            int index = 0;
            if (!(*enemyManager).enemyMissileActive[0])
            {
                index = 0;
            }
            if (!(*enemyManager).enemyMissileActive[1])
            {
                index = 1;
            }
            if (!(*enemyManager).enemyMissileActive[2])
            {
                index = 2;
            }
            if (!(*enemyManager).enemyMissileActive[3])
            {
                index = 3;
            }
            (*enemyManager).shootNextBullet(index, enemyPosition, timePassed, enemyShots[index], enemyLastShot);
        }

        for (int i = 0; i < sizeof(shipSprite.missileActive); i++) //Goes through missiles to see if  any have collided with  enemy
        {
            if (shipSprite.missileActive[i])
            {
                currentProjectile[i].setTexture(textureLoader.missile);
                (*enemyManager).CheckForCollision(currentProjectile[i], textureLoader.currentScoreNumber, shipSprite.missileActive, i, timePassed);
            }
        }

        for (int i = 0; i < sizeof((*enemyManager).enemyMissileActive); i++) //Goes through missiles to see if  any have collided with enemy
        {
            if ((*enemyManager).enemyMissileActive[i])
            {
                if (enemyShots[i].posY >= 700)
                {
                    (*enemyManager).enemyMissileActive[i] = false;
                }
                else
                {
                    enemyShots[i].setTexture(textureLoader.missile);
                    enemyShots[i].Fly();
                    if (shipSprite.CheckForCollision(enemyShots[i]))
                    {
                        if (timeOfHit.asSeconds() == 0)
                        {
                            textureLoader.deathSound.play();
                            timeOfHit = timePassed;
                            shipSprite.setTexture(textureLoader.hurtShip);
                        }
                    }
                }
            }
        }

        //Draw everything that's necessary for screen
        window.draw(textureLoader.backgroundSprite); //Draw background

        shipSprite.setPosition(shipSprite.shipX, shipSprite.shipY); //Sets and draws ship
        window.draw(shipSprite);

        shipSprite.DrawMissiles(shipSprite, currentProjectile, window);//Sets and draws missiles

        window.draw(textureLoader.score); //Draws the score and sets it appropriately
        textureLoader.currentScore.setString(std::to_string(textureLoader.currentScoreNumber));
        window.draw(textureLoader.currentScore);

        for (int i = 0; i < sizeof((*enemyManager).enemyMissileActive); i++) //Goes through missiles to see if  any have collided with 
        {
            if ((*enemyManager).enemyMissileActive[i])
            {
                window.draw(enemyShots[i]);
            }
        }

        for (int l = 0; l < shipSprite.life; l++)
        {
            window.draw(shipSprite.lives[l]);
        }
        (*enemyManager).SwitchState(enemyCounter);
        (*enemyManager).DrawAllEnemies(enemyPosition, &window, timePassed.asSeconds()); //Draws all enemies on screen

        gameWin = true;

        for (int i = 0; i < 8; i++)
        {
            if ((*enemyManager).wave1[i].isAlive) //Checks to see if any enemies in wave 1 are alive to see if win state is reached
            {
                gameWin = false;
            }
            if ((*enemyManager).wave1[i].isExploding) //Checks to see if any enemies in wave 1 are exploading and sets sprite accordingly
            {
                (*enemyManager).wave1[i].explosionUpdate(explosionTime, timePassed, textureLoader.explosion);
            }

        }
        for (int i = 0; i < 8; i++)
        {
            if ((*enemyManager).wave2[i].isAlive) //Checks to see if any enemies in wave 2 are alive to see if win state is reached
            {
                gameWin = false;
            }
            if ((*enemyManager).wave2[i].isExploding) //Checks to see if any enemies in wave 2 are exploading and sets sprite accordingly
            {
                (*enemyManager).wave2[i].explosionUpdate(explosionTime, timePassed, textureLoader.explosion);
            }
        }
        for (int i = 0; i < 8; i++)
        {
            if ((*enemyManager).wave3[i].isAlive) //Checks to see if any enemies in wave 3 are alive to see if win state is reached
            {
                gameWin = false;
            }
            if ((*enemyManager).wave3[i].isExploding) //Checks to see if any enemies in wave 3 are exploading and sets sprite accordingly
            {
                (*enemyManager).wave3[i].explosionUpdate(explosionTime, timePassed, textureLoader.explosion);
            }
        }
        for (int i = 0; i < 8; i++)
        {
            if ((*enemyManager).wave4[i].isAlive) //Checks to see if any enemies in wave 4 are alive to see if win state is reached
            {
                gameWin = false;
            }
            if ((*enemyManager).wave4[i].isExploding) //Checks to see if any enemies in wave 4 are exploading and sets sprite accordingly
            {
                (*enemyManager).wave4[i].explosionUpdate(explosionTime, timePassed, textureLoader.explosion);
            }
        }
        for (int i = 0; i < 8; i++)
        {
            if ((*enemyManager).wave5[i].isAlive) //Checks to see if any enemies in wave 5 are alive to see if win state is reached
            {
                gameWin = false;
            }
            if ((*enemyManager).wave5[i].isExploding) //Checks to see if any enemies in wave 5 are exploading and sets sprite accordingly
            {
                (*enemyManager).wave5[i].explosionUpdate(explosionTime, timePassed, textureLoader.explosion);
            }
        }
        window.display(); //Ends frame
        enemyCounter++; //Changes enemy counter to see if next idle sprite should be switched to
    }
    if (shipSprite.life <= 0)
    {
        GameLoss();
    }
    else if (gameWin)
    {
        GameWin();
    }
}

void GameLoss()
{
    sf::Event event;
    textureLoader.lossSound.play();

    window.draw(textureLoader.backgroundSprite);
    window.draw(textureLoader.score);
    window.draw(textureLoader.currentScore);
    window.draw(textureLoader.lossMessage);
    window.display();

    while (window.isOpen() && shipSprite.life <= 0 && !markedForDelete)
    {
        while (window.pollEvent(event)) //Check for user input to restart game
        {

            if (event.type == sf::Event::Closed) //Checks for closing of window
            {
                markedForDelete = true; //Properly deletes the wave spawner's occupied memory
                main();
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter) //Resets game state to replay game if enter is pressed
                {
                    timeOfHit = sf::Time();
                    shipSprite = (*new Spaceship);
                    enemyManager = new WaveSpawner(textureLoader.redEnemy, textureLoader.greenEnemy, textureLoader.yellowEnemy);
                    enemyPosition = 0;
                    enemyLastShot = sf::Time();
                    for (int i = 0; i < sizeof(currentProjectile) / sizeof(PlayerProjectile); i++)
                    {
                        currentProjectile[i].posY = 0;
                    }
                    playerLastShot = sf::Time();
                    textureLoader.currentScoreNumber = 0;
                    InitializeStates();
                    GameLoop();
                }
            }
            window.draw(textureLoader.backgroundSprite);
            window.draw(textureLoader.score);
            window.draw(textureLoader.currentScore);
            window.draw(textureLoader.lossMessage);
            window.display();
        }
    }
}

void GameWin()
{
    sf::Event event;

    textureLoader.winSound.play();

    window.draw(textureLoader.backgroundSprite);
    window.draw(textureLoader.score); //Draws the score
    window.draw(textureLoader.currentScore); //Draws the score
    window.draw(textureLoader.winMessage); //Writes the win message
    window.display();

    while (window.isOpen() && gameWin && !markedForDelete)
    {
        while (window.pollEvent(event)) //Check for user input that has effect on game
        {
            if (event.type == sf::Event::Closed) //Checks for closing of window
            {
                markedForDelete = true; //Properly deletes the wave spawner's occupied memory
                main();
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter) //Resets game state to replay game if enter is pressed
                {
                    gameWin = false;
                    timeOfHit = sf::Time();
                    shipSprite = (*new Spaceship);
                    enemyManager = new WaveSpawner(textureLoader.redEnemy, textureLoader.greenEnemy, textureLoader.yellowEnemy);
                    enemyPosition = 0;
                    enemyLastShot = sf::Time();
                    for (int i = 0; i < sizeof(currentProjectile) / sizeof(PlayerProjectile); i++)
                    {
                        currentProjectile[i].posY = 0;
                    }
                    playerLastShot = sf::Time();
                    textureLoader.currentScoreNumber = 0;
                    InitializeStates();
                    GameLoop();
                }
            }
        }
    }
}

void GameStart()
{
    textureLoader.startSound.play();

    while (window.isOpen() && !gameStart && !markedForDelete) //Waits until player presses enter to begin game
    {
        sf::Event event;
        while (window.pollEvent(event)) //Check for Window close event
        {
            if (event.type == sf::Event::Closed)
            {
                markedForDelete = true; //Properly deletes the wave spawner's occupied memory
                main();
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    gameStart = true;
                }
            }
        }
    }
}
*/