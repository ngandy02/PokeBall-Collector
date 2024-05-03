#include "Scene.hpp"

class Level2 : public Scene {
public:
    void initialize(int lives, int pokeballs) override;
    void update(float deltaTime) override;
    void render(ShaderProgram *program) override;
};
