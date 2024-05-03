#include "Level1.hpp"
#define LEVEL1_WIDTH 20
#define LEVEL1_HEIGHT 12
#define LEVEL1_ENEMY_COUNT 12
#define LEVEL1_OBJ_COUNT 5

using namespace std;

unsigned int level1_data[] =
{
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 4, 43, 43, 43, 43, 43, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30,
    30, 4, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30,
    30, 30, 43, 43, 43, 43, 30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30,
    30, 30, 43, 43, 43, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 3,
    30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 3,
    30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30,
    30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30, 30, 43, 43, 30,
    30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30, 30, 43, 43, 30,
    30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30
};

void Level1::initialize(int numLives, int pokeballs) {
    
    gameState.nextSceneId = -1;
    
    GLuint mapTextureID = Utility::loadTexture("assets/ruins.png");
    gameState.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 8, 8); // 8 and 8 here are the mapTextureID's spritesheet dimensions
  
    // Initialize Player
    gameState.player = new Entity();
    gameState.player->entityType = PLAYER;
    gameState.player->setPosition(glm::vec3(2, -2, 0));
    gameState.player->setMovement(glm::vec3(0));
    gameState.player->mAcceleration = glm::vec3(0, 0, 0);
    gameState.player->mSpeed = 3.0f;
    gameState.player->collection = pokeballs;
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
    gameState.player->lives = 5; //
    

    gameState.player->width = 0.9;
    gameState.player->height = 0.9;
    
    
    
    gameState.pal = new Entity();
    gameState.pal->entityType = PAL;
    gameState.pal->aiType = WALKER;
    gameState.pal->aiState = WALKING;
    gameState.pal->isPika = true;
    gameState.pal->setPosition(glm::vec3(4.0f, -4.0f, 0.0f));
    gameState.pal->setMovement(glm::vec3(0));
    gameState.pal->mAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    gameState.pal->mSpeed = 3;
    gameState.pal->textureID = Utility::loadTexture("assets/pikachusprite.png");
    
    gameState.pal->characterWalkingAnimations[gameState.pal->LEFT] = new int[4] {4, 5, 6, 7};
    gameState.pal->characterWalkingAnimations[gameState.pal->RIGHT] = new int[4] {8, 9, 10, 11};
    gameState.pal->characterWalkingAnimations[gameState.pal->UP] = new int[4] {12, 13, 14, 15};
    gameState.pal->characterWalkingAnimations[gameState.pal->DOWN] = new int[4] {0, 1, 2, 3};
    
    gameState.pal->indices = gameState.pal->characterWalkingAnimations[gameState.pal->DOWN]; // set indices to an animation up, down, left, or right animation on the spritesheet

    gameState.pal->frames = 4;
    gameState.pal->index = 0;
    gameState.pal->cols = 4;
    gameState.pal->rows = 4;
    gameState.pal->animationTime = 0;
    
    gameState.pal->jumpPower = 3.0f;
    gameState.pal->lives = 3;
    
    gameState.pal->width = 0.9;
    gameState.pal->height = 0.9;
    
//FIRE BALLS
    gameState.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    
    for (int i = 0; i < 9; ++i) {
        gameState.enemies[i].textureID = Utility::loadTexture("assets/fire.png");
        gameState.enemies[i].entityType = ENEMY;
        gameState.enemies[i].isEnemy = true;
        gameState.enemies[i].setMovement(glm::vec3(0));
        gameState.enemies[i].characterWalkingAnimations[gameState.enemies[i].LEFT] = new int[4] {4, 5, 6, 7};
        gameState.enemies[i].characterWalkingAnimations[gameState.enemies[i].RIGHT] = new int[4] {8, 9, 10, 11};
        gameState.enemies[i].characterWalkingAnimations[gameState.enemies[i].UP] = new int[4] {12, 13, 14, 15};
        gameState.enemies[i].characterWalkingAnimations[gameState.enemies[i].DOWN] = new int[4] {0, 1, 2, 3};
        
        gameState.enemies[i].indices = gameState.enemies[i].characterWalkingAnimations[gameState.enemies[i].DOWN]; // set indices to an animation up, down, left, or right animation on the spritesheet

        gameState.enemies[i].frames = 4;
        gameState.enemies[i].index = 0;
        gameState.enemies[i].cols = 4;
        gameState.enemies[i].rows = 1;
        gameState.enemies[i].animationTime = 0;
        gameState.enemies[i].width = 0.7;
        gameState.enemies[i].height = 0.7;
        
//        gameState.enemies[1].aiType = FIRE;
//        gameState.enemies[1].aiState = IDLE;

    //    gameState.enemies[1].jumpPower = 0.0f;
        
    }
    gameState.enemies[0].setPosition(glm::vec3(9.0f, -6.0f, 0.0f));
    gameState.enemies[1].setPosition(glm::vec3(5.0f, -6.0f, 0.0f));
    gameState.enemies[2].setPosition(glm::vec3(9.0f, -2.0f, 0.0f));
    gameState.enemies[3].setPosition(glm::vec3(6.0f, -9.0f, 0.0f));
    gameState.enemies[4].setPosition(glm::vec3(10.0f, -5.0f, 0.0f));
    gameState.enemies[5].setPosition(glm::vec3(13.0f, -10.0f, 0.0f));
    gameState.enemies[6].setPosition(glm::vec3(13.0f, -15.0f, 0.0f));
    gameState.enemies[7].setPosition(glm::vec3(11.0f, -7.0f, 0.0f));
    gameState.enemies[8].setPosition(glm::vec3(7.0f, -9.0f, 0.0f));
    
    
//POKEBALLS
    


   
    
    
   //enemy pokemon
    gameState.enemies[9].entityType = ENEMY;
    gameState.enemies[9].aiType = WALKER;
    gameState.enemies[9].aiState = WALKING;
    gameState.enemies[9].isChar = true;

    gameState.enemies[9].setPosition(glm::vec3(7.0f, -10.0f, 0.0f));
     gameState.enemies[9].setMovement(glm::vec3(-1, 0, 0));
     gameState.enemies[9].mAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
     gameState.enemies[9].mSpeed = 3;
     gameState.enemies[9].textureID = Utility::loadTexture("assets/charz.png");
    
     gameState.enemies[9].characterWalkingAnimations[ gameState.enemies[9].LEFT] = new int[4] {4, 5, 6, 7};
     gameState.enemies[9].characterWalkingAnimations[ gameState.enemies[9].RIGHT] = new int[4] {8, 9, 10, 11};
     gameState.enemies[9].characterWalkingAnimations[ gameState.enemies[9].UP] = new int[4] {12, 13, 14, 15};
     gameState.enemies[9].characterWalkingAnimations[ gameState.enemies[9].DOWN] = new int[4] {0, 1, 2, 3};
    
     gameState.enemies[9].indices =  gameState.enemies[9].characterWalkingAnimations[ gameState.enemies[9].DOWN]; // set indices to an animation up, down, left, or right animation on the spritesheet
   
     gameState.enemies[9].frames = 4;
     gameState.enemies[9].index = 0;
     gameState.enemies[9].cols = 4;
     gameState.enemies[9].rows = 4;
     gameState.enemies[9].animationTime = 0;
    
     gameState.enemies[9].width = 0.9;
     gameState.enemies[9].height = 0.9;
    
    // BULBASAUR/////
    gameState.enemies[10].entityType = ENEMY;
    gameState.enemies[10].aiType = WALKER;
    gameState.enemies[10].aiState = WALKING;
    gameState.enemies[10].isBulb = true;

    gameState.enemies[10].setPosition(glm::vec3(12.0f, -4.0f, 0.0f));
     gameState.enemies[10].setMovement(glm::vec3(-1, 0, 0));
     gameState.enemies[10].mAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
     gameState.enemies[10].mSpeed = 3;
     gameState.enemies[10].textureID = Utility::loadTexture("assets/bulbasaur.png");
    
     gameState.enemies[10].characterWalkingAnimations[ gameState.enemies[10].LEFT] = new int[4] {4, 5, 6, 7};
     gameState.enemies[10].characterWalkingAnimations[ gameState.enemies[10].RIGHT] = new int[4] {8, 9, 10, 11};
     gameState.enemies[10].characterWalkingAnimations[ gameState.enemies[10].UP] = new int[4] {12, 13, 14, 15};
     gameState.enemies[10].characterWalkingAnimations[ gameState.enemies[10].DOWN] = new int[4] {0, 1, 2, 3};
    
     gameState.enemies[10].indices =  gameState.enemies[10].characterWalkingAnimations[ gameState.enemies[10].DOWN]; // set indices to an animation up, down, left, or right animation on the spritesheet

     gameState.enemies[10].frames = 4;
     gameState.enemies[10].index = 0;
     gameState.enemies[10].cols = 4;
     gameState.enemies[10].rows = 4;
     gameState.enemies[10].animationTime = 0;
    
     gameState.enemies[10].jumpPower = 3.0f;
     gameState.enemies[10].lives = 3;
    
     gameState.enemies[10].width = 0.9;
     gameState.enemies[10].height = 0.9;
    
    //WARTORTLE
    gameState.enemies[11].entityType = ENEMY;
    gameState.enemies[11].aiType = WALKER;
    gameState.enemies[11].aiState = WALKING;
    gameState.enemies[11].isWartortle = true;

    gameState.enemies[11].setPosition(glm::vec3(10.0, -8.0f, 0.0f));
     gameState.enemies[11].setMovement(glm::vec3(-1, 0, 0));
     gameState.enemies[11].mAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
     gameState.enemies[11].mSpeed = 3;
     gameState.enemies[11].textureID = Utility::loadTexture("assets/wartortle.png");
    
     gameState.enemies[11].characterWalkingAnimations[ gameState.enemies[11].LEFT] = new int[4] {4, 5, 6, 7};
     gameState.enemies[11].characterWalkingAnimations[ gameState.enemies[11].RIGHT] = new int[4] {8, 9, 10, 11};
     gameState.enemies[11].characterWalkingAnimations[ gameState.enemies[11].UP] = new int[4] {12, 13, 14, 15};
     gameState.enemies[11].characterWalkingAnimations[ gameState.enemies[11].DOWN] = new int[4] {0, 1, 2, 3};
    
     gameState.enemies[11].indices =  gameState.enemies[11].characterWalkingAnimations[ gameState.enemies[11].DOWN]; // set indices to an animation up, down, left, or right animation on the spritesheet

     gameState.enemies[11].frames = 4;
     gameState.enemies[11].index = 0;
     gameState.enemies[11].cols = 4;
     gameState.enemies[11].rows = 4;
     gameState.enemies[11].animationTime = 0;
    
     gameState.enemies[11].jumpPower = 3.0f;
     gameState.enemies[11].lives = 3;
    
     gameState.enemies[11].width = 0.9;
     gameState.enemies[11].height = 0.9;
    
    
//POKEBALLS//////
    gameState.objects = new Entity[LEVEL1_OBJ_COUNT];

    for (int i = 0; i < LEVEL1_OBJ_COUNT; ++i){
        gameState.objects[i].entityType = OBJECT;
        gameState.objects[i].isCollected = false;
        gameState.objects[i].setMovement(glm::vec3(0, 0, 0));
        gameState.objects[i].textureID = Utility::loadTexture("assets/pokeball.png");
        gameState.objects[i].width = 0.9;
        gameState.objects[i].height = 0.9;
    }
    gameState.objects[0].setPosition(glm::vec3(2.0f, -5.0f, 0.0f));
    gameState.objects[1].setPosition(glm::vec3(7.0f, -8.0f, 0.0f));
    gameState.objects[2].setPosition(glm::vec3(12.0f, -3.0f, 0.0f));
    gameState.objects[3].setPosition(glm::vec3(11.0f, -9.0f, 0.0f));
    gameState.objects[4].setPosition(glm::vec3(9.0f, -7.0f, 0.0f));


    
        

}




void Level1::update(float deltaTime) { // deltatime is 0.016667f
    gameState.player->update(deltaTime, gameState.player, gameState.enemies, LEVEL1_ENEMY_COUNT, gameState.map);
    gameState.pal->update(deltaTime, gameState.pal, gameState.player, LEVEL1_ENEMY_COUNT, gameState.map);
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; ++i) {
        gameState.enemies[i].update(deltaTime, gameState.player, gameState.enemies, LEVEL1_ENEMY_COUNT, gameState.map);
    }
    for (int i = 0; i < LEVEL1_OBJ_COUNT; ++i){
        gameState.objects[i].update(deltaTime, &(gameState.objects[i]), gameState.player, LEVEL1_OBJ_COUNT, gameState.map);
    }
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; ++i) {
        if (gameState.enemies[i].hitsBottom){
            gameState.enemies[i].jump = true;
        }
    }
    if (gameState.player->lives == 0) {
        gameState.nextSceneId = 5;
    }
    
    // change this so that player walks to doorway to go to next level
    if (((gameState.player->getPosition().x >= 18) && ((-8 <= gameState.player->getPosition().y) && (gameState.player->getPosition().y <= -5)) && ((gameState.pal->getPosition().x >= 18) && ((-8 <= gameState.pal->getPosition().y) && (gameState.pal->getPosition().y <= -5))))) {
        gameState.nextSceneId = 2;
    }
   
    
    if (!(gameState.player->isAlive)) {
        gameState.player->lives -= 1;
        gameState.player->setPosition(glm::vec3(2, -2, 0));
        gameState.pal->setPosition(gameState.player->getPosition());
        gameState.player->isAlive = true;
    }
    
}
void Level1::render(ShaderProgram *program) {
    if (gameState.paused == true){
        Utility::drawText(program, Utility::loadTexture("assets/font1.png"), "PAUSED", 1.0f, -0.1f, glm::vec3(2, -1, 0));
        Utility::drawText(program, Utility::loadTexture("assets/font1.png"), "Press S to resume", 1.0f, -0.1f, glm::vec3(6, -3, 0));
    }
    else{
        Utility::drawText(program, Utility::loadTexture("assets/font1.png"), "Lives:" + to_string(gameState.player->lives), 1.0f, -0.1f, glm::vec3(1, -1, 0));
        Utility::drawText(program, Utility::loadTexture("assets/font1.png"), "Next LVL->", 1.0f, -0.1f, glm::vec3(6, -3, 0));
        
        gameState.map->render(program);
        gameState.player->render(program);
        gameState.pal->render(program);
      
        for(int i = 0; i < LEVEL1_OBJ_COUNT; ++i){
            gameState.objects[i].render(program);
        }
        
        for (int i = 0; i < LEVEL1_ENEMY_COUNT; ++i) {
            gameState.enemies[i].render(program);
        }
    }
}
