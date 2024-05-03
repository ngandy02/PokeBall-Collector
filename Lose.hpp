#include "Scene.hpp"

class Lose : public Scene {
public:
    void initialize(int lives, int pokeballs) override;
    void update(float deltaTime) override;
    void render(ShaderProgram *program) override;
};
