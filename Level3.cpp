#include "LEVEL3.hpp"
#define LEVEL3_WIDTH 20
#define LEVEL3_HEIGHT 12
#define LEVEL3_ENEMY_COUNT 30
#define LEVEL3_OBJ_COUNT 5


using namespace std;


unsigned int LEVEL3_data[] =
{
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
    30, 4, 43, 43, 43, 43, 30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30,
    30, 4, 43, 43, 43, 43, 30,  30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30,
    30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30,
    30, 30, 43, 43, 43, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 3,
    30, 30, 43, 43, 43, 30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 3,
    30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30,
    30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30, 30, 43, 43, 30,
    30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30, 30, 43, 43, 30,
    30, 30, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 30,
    30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30
};

void Level3::initialize(int lives, int pokeballs) {
    
    gameState.nextSceneId = -1;
    
    GLuint mapTextureID = Utility::loadTexture("assets/ruins.png");
    gameState.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, LEVEL3_data, mapTextureID, 1.0f, 8, 8); // 8 and 8 here are the mapTextureID's spritesheet dimensions
  
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
    gameState.player->lives = lives;
    gameState.player->collection = pokeballs;
  
    
    gameState.player->width = 0.9;
    gameState.player->height = 0.9;
    
    
    gameState.pal = new Entity();
    gameState.pal->entityType = PAL;
    gameState.pal->aiType = WALKER;
    gameState.pal->aiState = WALKING;
    gameState.pal->isPika = true;
    gameState.pal->setPosition(glm::vec3( 4.0f, -4.0f, 0.0f));
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
    gameState.enemies = new Entity[LEVEL3_ENEMY_COUNT];
    
    for (int i = 0; i < 24; ++i) {
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
    gameState.enemies[1].setPosition(glm::vec3(5.0f, -7.0f, 0.0f));
    gameState.enemies[2].setPosition(glm::vec3(9.0f, -2.0f, 0.0f));
    gameState.enemies[3].setPosition(glm::vec3(6.0f, -9.0f, 0.0f));
    gameState.enemies[4].setPosition(glm::vec3(10.0f, -5.0f, 0.0f));
    gameState.enemies[5].setPosition(glm::vec3(13.0f, -10.0f, 0.0f));
    gameState.enemies[6].setPosition(glm::vec3(13.0f, -15.0f, 0.0f));
    gameState.enemies[7].setPosition(glm::vec3(11.0f, -7.0f, 0.0f));
    gameState.enemies[8].setPosition(glm::vec3(7.0f, -9.0f, 0.0f));
    gameState.enemies[9].setPosition(glm::vec3(7.0f, -10.0f, 0.0f));
    gameState.enemies[10].setPosition(glm::vec3(16.0f, -4.0f, 0.0f));
    gameState.enemies[11].setPosition(glm::vec3(15.0f, -4.0f, 0.0f));
    gameState.enemies[12].setPosition(glm::vec3(14.0f, -9.0f, 0.0f));
    gameState.enemies[13].setPosition(glm::vec3(13.0f, -9.0f, 0.0f));
    gameState.enemies[14].setPosition(glm::vec3(4.0f, -10.0f, 0.0f));
    gameState.enemies[15].setPosition(glm::vec3(10.0f, -2.0f, 0.0f));
    gameState.enemies[16].setPosition(glm::vec3(15.0f, -9.0f, 0.0f));
    gameState.enemies[17].setPosition(glm::vec3(9.0f, -6.0f, 0.0f));
    gameState.enemies[18].setPosition(glm::vec3(13.0f, -10.0f, 0.0f));
    gameState.enemies[19].setPosition(glm::vec3(16.0f, -7.0f, 0.0f));
    gameState.enemies[20].setPosition(glm::vec3(10.0f, -7.0f, 0.0f));
    gameState.enemies[21].setPosition(glm::vec3(13.0f, -8.0f, 0.0f));
    gameState.enemies[22].setPosition(glm::vec3(13.0f, -7.0f, 0.0f));
    gameState.enemies[23].setPosition(glm::vec3(5.0f, -7.0f, 0.0f));
    
    
    
//POKEBALLS
    


   
    
    
   //enemy pokemon
    gameState.enemies[24].entityType = ENEMY;
    gameState.enemies[24].aiType = WALKER;
    gameState.enemies[24].aiState = WALKING;
    gameState.enemies[24].isChar = true;

    gameState.enemies[24].setPosition(glm::vec3(7.0f, -10.0f, 0.0f));
     gameState.enemies[24].setMovement(glm::vec3(-1, 0, 0));
     gameState.enemies[24].mAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
     gameState.enemies[24].mSpeed = 3;
     gameState.enemies[24].textureID = Utility::loadTexture("assets/darkrai.png");
    
     gameState.enemies[24].characterWalkingAnimations[ gameState.enemies[24].LEFT] = new int[4] {4, 5, 6, 7};
     gameState.enemies[24].characterWalkingAnimations[ gameState.enemies[24].RIGHT] = new int[4] {8, 9, 10, 11};
     gameState.enemies[24].characterWalkingAnimations[ gameState.enemies[24].UP] = new int[4] {12, 13, 14, 15};
     gameState.enemies[24].characterWalkingAnimations[ gameState.enemies[24].DOWN] = new int[4] {0, 1, 2, 3};
    
     gameState.enemies[24].indices =  gameState.enemies[24].characterWalkingAnimations[ gameState.enemies[24].DOWN]; // set indices to an animation up, down, left, or right animation on the spritesheet
   
     gameState.enemies[24].frames = 4;
     gameState.enemies[24].index = 0;
     gameState.enemies[24].cols = 4;
     gameState.enemies[24].rows = 4;
     gameState.enemies[24].animationTime = 0;
    
     gameState.enemies[24].width = 0.9;
     gameState.enemies[24].height = 0.9;
    
    // BULBASAUR/////
    gameState.enemies[25].entityType = ENEMY;
    gameState.enemies[25].aiType = WALKER;
    gameState.enemies[25].aiState = WALKING;
    gameState.enemies[25].isMew = true;

    gameState.enemies[25].setPosition(glm::vec3(16.0f, -4.0f, 0.0f));
     gameState.enemies[25].setMovement(glm::vec3(-1, 0, 0));
     gameState.enemies[25].mAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
     gameState.enemies[25].mSpeed = 3;
     gameState.enemies[25].textureID = Utility::loadTexture("assets/dialgaa.png");
    
     gameState.enemies[25].characterWalkingAnimations[ gameState.enemies[25].LEFT] = new int[4] {4, 5, 6, 7};
     gameState.enemies[25].characterWalkingAnimations[ gameState.enemies[25].RIGHT] = new int[4] {8, 9, 10, 11};
     gameState.enemies[25].characterWalkingAnimations[ gameState.enemies[25].UP] = new int[4] {12, 13, 14, 15};
     gameState.enemies[25].characterWalkingAnimations[ gameState.enemies[25].DOWN] = new int[4] {0, 1, 2, 3};
    
     gameState.enemies[25].indices =  gameState.enemies[25].characterWalkingAnimations[ gameState.enemies[25].DOWN]; // set indices to an animation up, down, left, or right animation on the spritesheet

     gameState.enemies[25].frames = 4;
     gameState.enemies[25].index = 0;
     gameState.enemies[25].cols = 4;
     gameState.enemies[25].rows = 4;
     gameState.enemies[25].animationTime = 0;
    
     gameState.enemies[25].jumpPower = 3.0f;
     gameState.enemies[25].lives = 3;
    
     gameState.enemies[25].width = 0.9;
     gameState.enemies[25].height = 0.9;
    
    //WARTORTLE
    gameState.enemies[26].entityType = ENEMY;
    gameState.enemies[26].aiType = WALKER;
    gameState.enemies[26].aiState = WALKING;
    gameState.enemies[26].isWartortle = true;

    gameState.enemies[26].setPosition(glm::vec3(11.0, -8.0f, 0.0f));
     gameState.enemies[26].setMovement(glm::vec3(-1, 0, 0));
     gameState.enemies[26].mAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
     gameState.enemies[26].mSpeed = 3;
     gameState.enemies[26].textureID = Utility::loadTexture("assets/groudon.png");
    
     gameState.enemies[26].characterWalkingAnimations[ gameState.enemies[26].LEFT] = new int[4] {4, 5, 6, 7};
     gameState.enemies[26].characterWalkingAnimations[ gameState.enemies[26].RIGHT] = new int[4] {8, 9, 10, 11};
     gameState.enemies[26].characterWalkingAnimations[ gameState.enemies[26].UP] = new int[4] {12, 13, 14, 15};
     gameState.enemies[26].characterWalkingAnimations[ gameState.enemies[26].DOWN] = new int[4] {0, 1, 2, 3};
    
     gameState.enemies[26].indices =  gameState.enemies[26].characterWalkingAnimations[ gameState.enemies[26].DOWN]; // set indices to an animation up, down, left, or right animation on the spritesheet

     gameState.enemies[26].frames = 4;
     gameState.enemies[26].index = 0;
     gameState.enemies[26].cols = 4;
     gameState.enemies[26].rows = 4;
     gameState.enemies[26].animationTime = 0;
    
     gameState.enemies[26].jumpPower = 3.0f;
     gameState.enemies[26].lives = 3;
    
     gameState.enemies[26].width = 0.9;
     gameState.enemies[26].height = 0.9;
    
    gameState.enemies[27].entityType = ENEMY;
    gameState.enemies[27].aiType = WALKER;
    gameState.enemies[27].aiState = WALKING;
    gameState.enemies[27].isChar2 = true;

    gameState.enemies[27].setPosition(glm::vec3(16.0f, -4.0f, 0.0f));
     gameState.enemies[27].setMovement(glm::vec3(-1, 0, 0));
     gameState.enemies[27].mAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
     gameState.enemies[27].mSpeed = 3;
     gameState.enemies[27].textureID = Utility::loadTexture("assets/charz.png");
    
     gameState.enemies[27].characterWalkingAnimations[ gameState.enemies[27].LEFT] = new int[4] {4, 5, 6, 7};
     gameState.enemies[27].characterWalkingAnimations[ gameState.enemies[27].RIGHT] = new int[4] {8, 9, 10, 11};
     gameState.enemies[27].characterWalkingAnimations[ gameState.enemies[27].UP] = new int[4] {12, 13, 14, 15};
     gameState.enemies[27].characterWalkingAnimations[ gameState.enemies[27].DOWN] = new int[4] {0, 1, 2, 3};
    
     gameState.enemies[27].indices =  gameState.enemies[27].characterWalkingAnimations[ gameState.enemies[27].DOWN]; // set indices to an animation up, down, left, or right animation on the spritesheet
   
     gameState.enemies[27].frames = 4;
     gameState.enemies[27].index = 0;
     gameState.enemies[27].cols = 4;
     gameState.enemies[27].rows = 4;
     gameState.enemies[27].animationTime = 0;
    
     gameState.enemies[27].width = 0.9;
     gameState.enemies[27].height = 0.9;
    
    gameState.enemies[28].entityType = ENEMY;
    gameState.enemies[28].aiType = WALKER;
    gameState.enemies[28].aiState = WALKING;
    gameState.enemies[28].isChar2 = true;

    gameState.enemies[28].setPosition(glm::vec3(16.0f, -4.0f, 0.0f));
     gameState.enemies[28].setMovement(glm::vec3(-1, 0, 0));
     gameState.enemies[28].mAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
     gameState.enemies[28].mSpeed = 3;
     gameState.enemies[28].textureID = Utility::loadTexture("assets/charz.png");
    
     gameState.enemies[28].characterWalkingAnimations[ gameState.enemies[28].LEFT] = new int[4] {4, 5, 6, 7};
     gameState.enemies[28].characterWalkingAnimations[ gameState.enemies[28].RIGHT] = new int[4] {8, 9, 10, 11};
     gameState.enemies[28].characterWalkingAnimations[ gameState.enemies[28].UP] = new int[4] {12, 13, 14, 15};
     gameState.enemies[28].characterWalkingAnimations[ gameState.enemies[28].DOWN] = new int[4] {0, 1, 2, 3};
    
     gameState.enemies[28].indices =  gameState.enemies[28].characterWalkingAnimations[ gameState.enemies[28].DOWN]; // set indices to an animation up, down, left, or right animation on the spritesheet
   
     gameState.enemies[28].frames = 4;
     gameState.enemies[28].index = 0;
     gameState.enemies[28].cols = 4;
     gameState.enemies[28].rows = 4;
     gameState.enemies[28].animationTime = 0;
    
     gameState.enemies[28].width = 0.9;
     gameState.enemies[28].height = 0.9;
    
    
//POKEBALLS//////
    gameState.objects = new Entity[LEVEL3_OBJ_COUNT];

    for (int i = 0; i < LEVEL3_OBJ_COUNT; ++i){
        gameState.objects[i].entityType = OBJECT;
        gameState.objects[i].isCollected = false;
        gameState.objects[i].setMovement(glm::vec3(0, 0, 0));
        gameState.objects[i].textureID = Utility::loadTexture("assets/pokeball.png");
        gameState.objects[i].width = 0.9;
        gameState.objects[i].height = 0.9;
    }
    gameState.objects[0].setPosition(glm::vec3(5.0f, -10.0f, 0.0f));
    gameState.objects[1].setPosition(glm::vec3(8.0f, -6.0f, 0.0f));
    gameState.objects[2].setPosition(glm::vec3(14.0f, -10.0f, 0.0f));
    gameState.objects[3].setPosition(glm::vec3(16.0f, -3.0f, 0.0f));
    gameState.objects[4].setPosition(glm::vec3(10.0f, -9.0f, 0.0f));


    
        


}
void Level3::update(float deltaTime) {
    gameState.player->update(deltaTime, gameState.player, gameState.enemies, LEVEL3_ENEMY_COUNT, gameState.map);
    gameState.pal->update(deltaTime, gameState.pal, gameState.player, LEVEL3_ENEMY_COUNT, gameState.map);
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; ++i) {
        gameState.enemies[i].update(deltaTime, gameState.player, gameState.enemies, LEVEL3_ENEMY_COUNT, gameState.map);
    }
    for (int i = 0; i < LEVEL3_OBJ_COUNT; ++i){
        gameState.objects[i].update(deltaTime, &(gameState.objects[i]), gameState.player, LEVEL3_OBJ_COUNT, gameState.map);
    }
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; ++i) {
        if (gameState.enemies[i].hitsBottom){
            gameState.enemies[i].jump = true;
        }
    }
    if (gameState.player->lives == 0) {
        gameState.nextSceneId = 5;
    }
    
    // change this so that player walks to doorway to go to next level
    if (((gameState.player->getPosition().x >= 18) && ((-8 <= gameState.player->getPosition().y) && (gameState.player->getPosition().y <= -5))) && ((gameState.pal->getPosition().x >= 18) && ((-8 <= gameState.pal->getPosition().y) && (gameState.pal->getPosition().y <= -5)))) {
        gameState.nextSceneId = 4;
    }
  
    if (!(gameState.player->isAlive)) {
        gameState.player->lives -= 1;
        gameState.player->setPosition(glm::vec3(2, -2, 0));
        gameState.pal->setPosition(gameState.player->getPosition());
        gameState.player->isAlive = true;
    }
    
}
void Level3::render(ShaderProgram *program) {
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
      
        for(int i = 0; i < LEVEL3_OBJ_COUNT; ++i){
            gameState.objects[i].render(program);
        }
        
        for (int i = 0; i < LEVEL3_ENEMY_COUNT; ++i) {
            gameState.enemies[i].render(program);
        }
    }
}

