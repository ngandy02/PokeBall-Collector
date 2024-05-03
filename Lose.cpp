#include "Lose.hpp"

void Lose::initialize(int lives, int pokeballs) {
    gameState.nextSceneId = -1;
    
    gameState.player = new Entity();
    gameState.player->entityType = PLAYER;
    gameState.player->setPosition(glm::vec3(0, 0, 0));
    gameState.player->setMovement(glm::vec3(0));
    gameState.player->mAcceleration = glm::vec3(0, -9.81f, 0);
    gameState.player->mSpeed = 3.0f;
    gameState.player->textureID = Utility::loadTexture("assets/pokemontrainer.png");
    
    gameState.player->characterWalkingAnimations[gameState.player->LEFT] = new int[4] {4, 5, 6, 7};
    gameState.player->characterWalkingAnimations[gameState.player->RIGHT] = new int[4] {8, 9, 10, 11};
    gameState.player->characterWalkingAnimations[gameState.player->UP] = new int[4] {12, 13, 14, 15};
    gameState.player->characterWalkingAnimations[gameState.player->DOWN] = new int[4] {0, 1, 2, 3};
    
    gameState.player->indices = gameState.player->characterWalkingAnimations[gameState.player->DOWN]; // set indices to an animation up, down, left, or right animation on the spritesheet
   
    
    gameState.player->frames = 4;
    gameState.player->index = 0;
    gameState.player->cols = 4;
    gameState.player->rows = 4;
    gameState.player->animationTime = 0;
    
    gameState.player->jumpPower = 6.5f;
    gameState.player->lives = lives;
    

        
}
void Lose::update(float deltaTime) {}

void Lose::render(ShaderProgram *program) {
    Utility::drawText(program, Utility::loadTexture("assets/font1.png"), "You Lose! :(", 1, -0.5, glm::vec3(2.15f, -3.5f, 0));
}
