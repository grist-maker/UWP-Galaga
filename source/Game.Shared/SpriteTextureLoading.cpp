#include "SpriteTextureLoading.h"
#include "pch.h"
/*
SpriteTextureLoading::SpriteTextureLoading()
{
    //Loads in sprites for the animation on all 3 enemies
    greenEnemy1.loadFromFile("Assets\\Images\\GalagaEnemyGreen1.png");
    greenEnemy2.loadFromFile("Assets\\Images\\GalagaEnemyGreen2.png");
    redEnemy1.loadFromFile("Assets\\Images\\GalagaEnemyRed1.png");
    redEnemy2.loadFromFile("Assets\\Images\\GalagaEnemyRed2.png");
    yellowEnemy1.loadFromFile("Assets\\Images\\GalagaEnemyYellow1.png");
    yellowEnemy2.loadFromFile("Assets\\Images\\GalagaEnemyYellow2.png");

    redEnemy[0] = redEnemy1;
    redEnemy[1] = redEnemy2;
    greenEnemy[0] = greenEnemy1;
    greenEnemy[1] = greenEnemy2;
    yellowEnemy[0] = yellowEnemy1;
    yellowEnemy[1] = yellowEnemy2;

    //Loads in backgrounds for the game
    startScreen.loadFromFile("Assets\\Images\\StartScreen.png", sf::IntRect(0, 0, 700, 700));
    background.loadFromFile("Assets\\Images\\SpaceBackgroundLoopable.png", sf::IntRect(0, 0, 700, 700));
    startSprite.setTexture(startScreen);
    backgroundSprite.setTexture(background);

    //Loads in missile and ship sprites
    ship.loadFromFile("Assets\\Images\\GalagaShip.png");
    missile.loadFromFile("Assets\\Images\\PlayerProjectile.png");
    hurtShip.loadFromFile("Assets\\Images\\GalagaShipHurt.png");

    //Loads in explosion sprites for animation
    explosion[0].loadFromFile("Assets\\Images\\Explosion1.png");
    explosion[1].loadFromFile("Assets\\Images\\Explosion2.png");
    explosion[2].loadFromFile("Assets\\Images\\Explosion3.png");
    explosion[3].loadFromFile("Assets\\Images\\Explosion4.png");
    explosion[4].loadFromFile("Assets\\Images\\Explosion5.png");
    explosion[5].loadFromFile("Assets\\Images\\Explosion6.png");

    //Loads in font and assigns necessary assets for score display
    galagaFont.loadFromFile("Assets\\Font\\GalagaFont.ttf");
    score.setFont(galagaFont);
    score.setString("High Score");
    score.setCharacterSize(20);
    score.setFillColor(sf::Color::Red);
    score.setPosition(sf::Vector2f(250, 0));

    currentScore.setFont(galagaFont);
    currentScore.setString(std::to_string(currentScoreNumber));
    currentScore.setCharacterSize(20);
    currentScore.setFillColor(sf::Color::White);
    currentScore.setPosition(sf::Vector2f(300, 30));

    //Loads in loss screen data
    lossMessage.setFont(galagaFont);
    lossMessage.setString("You Lose!");
    lossMessage.setCharacterSize(60);
    lossMessage.setFillColor(sf::Color::White);
    lossMessage.setPosition(sf::Vector2f(100, 350));

    //Loads in win screen data
    winMessage.setFont(galagaFont);
    winMessage.setString("You Win!");
    winMessage.setCharacterSize(60);
    winMessage.setFillColor(sf::Color::White);
    winMessage.setPosition(sf::Vector2f(100, 350));

    //Loads necessary sound effects from Assets folder
    shootBuffer.loadFromFile("Assets\\Audio\\PlayerShot.ogg");
    deathBuffer.loadFromFile("Assets\\Audio\\PlayerDeath.ogg");
    startBuffer.loadFromFile("Assets\\Audio\\GalagaStartScreen.ogg");
    winBuffer.loadFromFile("Assets\\Audio\\WinScreen.ogg");
    loseBuffer.loadFromFile("Assets\\Audio\\LossScreen.ogg");

    shootSound.setBuffer(shootBuffer);
    deathSound.setBuffer(deathBuffer);
    startSound.setBuffer(startBuffer);
    winSound.setBuffer(winBuffer);
    lossSound.setBuffer(loseBuffer);
}*/