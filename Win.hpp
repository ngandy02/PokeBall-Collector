#include "Scene.hpp"

class Win : public Scene {
public:
    void initialize(int lives, int pokeballs) override;
    void update(float deltaTime) override;
    void render(ShaderProgram *program) override;
};
