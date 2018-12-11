#include <SFML/Graphics.hpp>
#include <iostream>
#include "core.hpp"
#include <list>

using namespace sf;
using namespace std;

class platform {
public:
    float x, y, w, h;
    Image image;
    Texture texture;//���� ��������
    Sprite platformsprite;//���� ������
    
    platform(float X, float Y){  //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
        image.loadFromFile("Resources\platform.jpg");
        texture.loadFromImage(image);//���������� ���� ����������� � ��������
        platformsprite.setTexture(texture);//�������� ������ ���������
        x = X; y = Y;//���������� ��������� �������
        platformsprite.setTextureRect(IntRect(0, 0, 256, 64));
        platformsprite.setPosition(x,y);
    }
};

int main()
{
    bool on_ground = false;
    bool stopPlatform = false;
    bool stopPlatform2 = false;
    bool heroJump = false;
    bool platformMove = true;
    bool onMovingPlatform = false;
    bool createNewPlatform = false;

    RenderWindow window(sf::VideoMode(800, 600), "EASY GAME ");
    
    Texture poisontexture;
    poisontexture.loadFromFile("Resources\poison.png");
    
    Sprite poisonsprite;
    poisonsprite.setTexture(poisontexture);
    poisonsprite.setTextureRect(IntRect(0,0,1279,64));
    poisonsprite.setPosition(0, 1216);
    
    Texture herotexture;
    herotexture.loadFromFile("Resources\hero2.png");
    
    Sprite herosprite;
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(IntRect(32, 128, 64, 128));
    herosprite.setPosition(592, 1280-128-64);
    
    startGame(herosprite.getPosition().x, herosprite.getPosition().y);
    platform p1(512, 1280-64);
    pushPlatformIntoMatrix(p1.platformsprite.getPosition().x, p1.platformsprite.getPosition().y);
    platform p2(0, 1280-128);
    pushPlatformIntoMatrix(p2.platformsprite.getPosition().x, p2.platformsprite.getPosition().y);
    platform p3(1280-256, 1280-192);
    pushPlatformIntoMatrix(p3.platformsprite.getPosition().x, p3.platformsprite.getPosition().y);
    platform p4(0, 1280-192-64);
    pushPlatformIntoMatrix(p4.platformsprite.getPosition().x, p4.platformsprite.getPosition().y);
    
    float CurrentFrame = 0;  //������ ������� ����
    Clock clock;
    
    while (window.isOpen())
    {
        
        if (on_ground && (herosprite.getPosition().y < 1280-64-128)){
            onMovingPlatform = true;
        } else {
            onMovingPlatform = false;
        }
        
        on_ground = onGround();
        //        std::cout << on_ground;
        
        if (gameOver() == 2) {
            window.close();
        }
        
        if (gameOver() == 1) {
            herosprite.setPosition(592, 1280-128-64);
            changeHeroPosition(herosprite.getPosition().x, herosprite.getPosition().y);
            on_ground = true;
        }
        
        
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        
        ///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
        
        if ((Keyboard::isKeyPressed(Keyboard::Left))) { //���� ������ ������� ������� �����
            //            CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
            //            if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
            //            herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
            herosprite.move(-0.2*time, 0);
            changeHeroPosition(herosprite.getPosition().x, herosprite.getPosition().y);
        }
        
        if ((Keyboard::isKeyPressed(Keyboard::Right))) {
//                        CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
//                        if (CurrentFrame > 4) CurrentFrame -= 4; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
//                        herosprite.setTextureRect(IntRect(32 * int(CurrentFrame), 128, 64, 128)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
            
            herosprite.move(0.2*time, 0);//���������� ���� �������� ��������� ������
            changeHeroPosition(herosprite.getPosition().x, herosprite.getPosition().y);
            
        }
        
        if ((Keyboard::isKeyPressed(Keyboard::Space)) ) {
            
            if (((p1.platformsprite.getPosition().y - herosprite.getPosition().y) < 1024)){
                herosprite.move(0, -0.6*time);
                heroJump = true;
            }
            changeHeroPosition(herosprite.getPosition().x, herosprite.getPosition().y);
            
        }
        // �������� � ��������� ���������
        
        if (p2.platformsprite.getPosition().x >= 1280-256)
            platformMove = false;
        if (p2.platformsprite.getPosition().x <= 0)
            platformMove = true;
        if (!stopPlatform){
            if (platformMove){
                p2.platformsprite.move (0.2*time, 0);
                if ((p2.platformsprite.getPosition().x >= p1.platformsprite.getPosition().x) && onMovingPlatform){
                    stopPlatform = true;
                }
            }
            else {
                p2.platformsprite.move (-0.2*time, 0);
                if ((p2.platformsprite.getPosition().x <= p1.platformsprite.getPosition().x) && onMovingPlatform){
                    stopPlatform = true;
                }
            }
            pushPlatformIntoMatrix(p2.platformsprite.getPosition().x, p2.platformsprite.getPosition().y);
        }
        
        // �������� ������ ���������
        
        if (stopPlatform){
            if (p3.platformsprite.getPosition().x >= 1280-256)
                platformMove = false;
            if (p3.platformsprite.getPosition().x <= 0)
                platformMove = true;
            if (!stopPlatform2){
                if (platformMove){
                    p3.platformsprite.move (0.2*time, 0);
                    if ((p3.platformsprite.getPosition().x >= p2.platformsprite.getPosition().x) && onMovingPlatform){
                        stopPlatform2 = true;
                    }
                }
                else {
                    p3.platformsprite.move (-0.2*time, 0);
                    if ((p3.platformsprite.getPosition().x <= p2.platformsprite.getPosition().x) && onMovingPlatform){
                        stopPlatform2 = true;
                        }
                    }
                pushPlatformIntoMatrix(p3.platformsprite.getPosition().x, p3.platformsprite.getPosition().y);
            }
        }
        if (!on_ground && (p1.platformsprite.getPosition().y - herosprite.getPosition().y) < 1024){
            herosprite.move(0, 0.3*time);
            changeHeroPosition(herosprite.getPosition().x, herosprite.getPosition().y);
        }
        
        // �������� ��������� � ����������
        
        if (onMovingPlatform){
            if (!stopPlatform){
                if (platformMove){
                    herosprite.move(0.2*time, 0);
                    changeHeroPosition(herosprite.getPosition().x, herosprite.getPosition().y);
                } else {
                    herosprite.move(-0.2*time, 0);
                    changeHeroPosition(herosprite.getPosition().x, herosprite.getPosition().y);
                }
            }
        }
        
        window.clear();
        window.draw(poisonsprite);
        window.draw(herosprite);
        window.draw(p1.platformsprite);
        window.draw(p2.platformsprite);
        if (stopPlatform)
            window.draw(p3.platformsprite);
        if (stopPlatform2)
            window.draw(p4.platformsprite);
        window.display();
    }
    
    return 0;
}