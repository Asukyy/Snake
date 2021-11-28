#include <iostream>
#include <cstdlib> // apparition random des pommes (par exemples)
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>

using namespace std;
using namespace sf;

int taille = 20; // taille d'un coté
int width = taille * taille, height = taille * taille;
int num = 3;
int dir = 1;
int i = 1;
bool check = false;
int score = 0;
int message = 0;


struct snake {
    int x, y;
}s[100]; //structure du snake

struct fruit {
    int x, y;
}f; //structure du fruit

void Action()
{
    for (int i = num; i > 0; i--) //boucle inversé
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    if (dir == 0) s[0].y -= 1;
    if (dir == 1) s[0].x += 1;
    if (dir == 2) s[0].y += 1;
    if (dir == 3) s[0].x -= 1;

    if (s[0].x == f.x && s[0].y == f.y) //ajoute une case au s lorsqu'il mange un f
    {
        num++;
        score +=10;
        f.x = rand() % taille;
        f.y = rand() % taille;
        printf("Ton score est de : %d \n", score);

    }

    if (s[0].x < 0) s[0].x = 20; //tp entre les x
    if (s[0].x > taille) s[0].x = 0;

    if (s[0].y < 0) s[0].y = 20; //tp entre les y
    if (s[0].y > taille) s[0].y = 0;
}


int main()
{

    RenderWindow app(sf::VideoMode::VideoMode(width, height), "High Snake", Style::Titlebar);
    app.setFramerateLimit(60);

   Texture background;
   background.loadFromFile("C:/Users/Mathis/source/repos/Snakeap/Snakeap/background.jpg");
   Sprite sprite;
    sprite.setTexture(background);

    Texture food;
    food.loadFromFile("C:/Users/Mathis/source/repos/Snakeap/Snakeap/ap.png");
        Sprite spritef;
    spritef.setTexture(food);

    Texture head;
    head.loadFromFile("C:/Users/Mathis/source/repos/Snakeap/Snakeap/tete.jpg");
        Sprite spriteh;
        spriteh.setTexture(head);

        Texture menu;
        menu.loadFromFile("C:/Users/Mathis/source/repos/Snakeap/Snakeap/space.png");
        Sprite spritem;
        spritem.setTexture(menu);

        Texture gameover;
        gameover.loadFromFile("C:/Users/Mathis/source/repos/Snakeap/Snakeap/f.jpg");
        Sprite spritego;
        spritego.setTexture(gameover);


        while (app.isOpen())
        {
            while (check == false)
            {
                app.clear();
                app.draw(spritem);
                app.display();

                if (Keyboard::isKeyPressed(Keyboard::Enter))

                    check = true;

                if (Keyboard::isKeyPressed(Keyboard::Escape))
                    return EXIT_SUCCESS;
            }


        Music music;
        if (!music.openFromFile("C:/Users/Mathis/source/repos/Snakeap/Snakeap/music.wav"))
        {
             return -1;
        }
        music.play();


        Clock timer;

        f.x = rand() % taille;
        f.y = rand() % taille;

        RectangleShape box(Vector2f(taille, taille));
        box.setFillColor(Color::Green);

        RectangleShape tete(Vector2f(taille, taille));
        tete.setTexture(&head);
        tete.setTextureRect(sf::IntRect(10, 10, 100, 100));

        CircleShape apple(taille / 1.25);
        apple.setTexture(&food);
        apple.setTextureRect(sf::IntRect(10, 10, 100, 100));


        while (app.isOpen())
        {
            Event event;
            while (app.pollEvent(event))
            {
                switch (event.type)
                {
                case Event::KeyReleased:
                    if (event.key.code == Keyboard::Escape)
                        app.close();
                    break;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Up) && dir != 2) dir = 0;
            if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 3) dir = 1;
            if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 0) dir = 2;
            if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 1) dir = 3;

            if (timer.getElapsedTime().asMilliseconds() > 200)
            {
                Action();
                for (int i = 1; i < num; i++)
                {
                    if(s[0].x == s[i].x)
                    {
                        while(s[0].y == s[i].y)
                        {
                            app.clear();
                            app.draw(spritego);
                            app.display();
                            music.stop();
                        }
                    }
                }
                timer.restart();
            }

            app.clear();

            app.draw(spriteh);
            app.draw(spritef);
            app.draw(sprite);

            for (int i = 0; i < num; i++) //Parcourir le num
            {
                box.setPosition(s[i].x * taille, s[i].y * taille);
                app.draw(box);
            }

            tete.setPosition(s[0].x * taille, s[0].y * taille);
            app.draw(tete);

            apple.setPosition(f.x * taille, f.y * taille);

            app.draw(apple);
            {
                while (s[0].x != s[i].x && s[0].y != s[i].y)
                {
                    i++;
                    if (s[0].x == s[i].x)
                    {
                        return (84);
                    }
                }

                if (score >= 50)
                {
                    box.setFillColor(Color(255, 0, 0));
                    tete.setFillColor(Color(250, 127, 0));
                    while (message < 1)
                    {
                        printf("CHUI HIIIIIIIIGH \n");
                        message++;
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
                    if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
                    if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 2;
                    if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 3;

                    if (timer.getElapsedTime().asMilliseconds() > 150)
                    {
                        Action();
                        for (int i = 1; i < num; i++)
                        {
                            if (s[0].x == s[i].x)
                            {
                                while(s[0].y == s[i].y)
                                {
                                    app.clear();
                                    app.draw(spritego);
                                    app.display();
                                    music.stop();
                                }
                            }
                        }
                        timer.restart();

                    }
                }
                if (score >= 100)
                {

                    if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
                    if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
                    if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 2;
                    if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 3;

                    if (timer.getElapsedTime().asMilliseconds() > 150)
                    {
                        Action();
                        for (int i = 1; i < num; i++)
                        {
                            if (s[0].x == s[i].x)
                            {
                                while(s[0].y == s[i].y)
                                {
                                    app.clear();
                                    app.draw(spritego);
                                    app.display();
                                    music.stop();
                                }
                            }
                        }
                        timer.restart();
                    }
                }

                if (score >= 150)
                {

                    if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
                    if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
                    if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 2;
                    if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 3;

                    if (timer.getElapsedTime().asMilliseconds() > 100)
                    {
                        Action();
                        for (int i = 1; i < num; i++)
                        {
                            if (s[0].x == s[i].x)
                            {
                                while(s[0].y == s[i].y)
                                {
                                    app.clear();
                                    app.draw(spritego);
                                    app.display();
                                    music.stop();
                                }
                            }
                        }
                        timer.restart();
                    }
                }

                if (score >= 200)
                {

                    if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
                    if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
                    if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 2;
                    if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 3;

                    if (timer.getElapsedTime().asMilliseconds() > 50)
                    {
                        Action();
                        for (int i = 1; i < num; i++)
                        {
                            if (s[0].x == s[i].x)
                            {
                                while(s[0].y == s[i].y)
                                {
                                    app.clear();
                                    app.draw(spritego);
                                    app.display();
                                    music.stop();
                                }
                            }
                        }
                        timer.restart();
                    }
                }

                if (score >= 250)
                {

                if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
                if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
                if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 2;
                if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 3;

                if (timer.getElapsedTime().asMilliseconds() > 1)
                {
                    Action();
                    for (int i = 1; i < num; i++)
                    {
                        if (s[0].x == s[i].x)
                        {
                            while (s[0].y == s[i].y)
                            {
                                app.clear();
                                app.draw(spritego);
                                app.display();
                                music.stop();
                            }
                        }
                    }
                    timer.restart();
                }
                }

            }
            app.display();
        }
        }

    }
