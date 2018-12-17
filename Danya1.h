class enemy {
public:
    bool enemyMove;
    bool enemyLive;
    int lives;
    Image image;
    Texture texture;
    Sprite enemysprite;
    
    enemy(float X, float Y){
        image.loadFromFile("bones.png");
        texture.loadFromImage(image);
        enemysprite.setTexture(texture);
        enemysprite.setTextureRect(IntRect(48, 128, 48, 64));
        enemysprite.setPosition(X, Y);
    }
};

class enemy2 {
public:
    bool enemyMove;
    bool enemyLive;
    int lives;
    Image image;
    Texture texture;
    Sprite enemysprite;
    
    enemy2(float X, float Y){
        image.loadFromFile("ghost.png");
        texture.loadFromImage(image);
        enemysprite.setTexture(texture);
        enemysprite.setTextureRect(IntRect(64, 48, 64, 64));
        enemysprite.setPosition(X, Y);
    }
};

class enemy3 {
public:
    bool enemyLive;
    int lives;
    Image image;
    Texture texture;
    Sprite enemysprite;
    
    enemy3(float X, float Y){
        image.loadFromFile("ghost.png");
        texture.loadFromImage(image);
        enemysprite.setTexture(texture);
        enemysprite.setTextureRect(IntRect(64*16, 16, 128, 128));
        enemysprite.setPosition(X, Y);
    }
};