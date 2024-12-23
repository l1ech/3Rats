#include <memory>
#include <string>

#include "Acteur.h"
#include "Player.h"
#include "Enemy.h"
#include "Player_Computer.h"

class ActeurFactory {
public:
    static std::unique_ptr<Acteur> createActeur(const std::string& type) {
        if (type == "Player") {
            return std::make_unique<Player>();
        } else if (type == "Enemy") {
            return std::make_unique<Enemy>();
        } else if (type == "Player_Computer") {
            return std::make_unique<Player_Computer>();
        }
        return nullptr;
    }
};
