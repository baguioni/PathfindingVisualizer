#include "SFML/Graphics.hpp"
#include <unistd.h>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "classes.cpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <queue> 

int main(void){

    float gridSizeF = 20.0f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    sf::RenderWindow window(sf::VideoMode(500, 500), "Shortest-Path", sf::Style::Close);

    sf::Vector2i mouseWindow;
    sf::Vector2f mouseView;
    sf::Vector2u mouseGrid;
    sf::Vector2i clickPos;
    
    const int height = 100;
    const int width = 100;

    // Object that selects a grid
    sf::RectangleShape cursor(sf::Vector2f(gridSizeF,gridSizeF));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineThickness(1.0f);
    cursor.setOutlineColor(sf::Color::Red);

    std::vector<std::vector<sf::RectangleShape> > tileMap;
    tileMap.resize(width, std::vector<sf::RectangleShape>());
    for(int x = 0; x < width; x++){
        tileMap[x].resize(width,sf::RectangleShape());
        for(int y = 0; y < height; y++){
            tileMap[x][y].setSize(sf::Vector2f(gridSizeF,gridSizeF));
            tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
            tileMap[x][y].setOutlineThickness(1.0f);
            tileMap[x][y].setOutlineColor(sf::Color::Black);
        }
    }

    nodeType select = START;
    Node start;
    Node end;
    std::vector<Node> frontier;
    std::vector<Node> neighbor;
    int endCount = 0, startCount = 0, starting = 0;
    while (window.isOpen()){
        // Mouse position
        mouseWindow = sf::Mouse::getPosition(window);
        mouseView = window.mapPixelToCoords(mouseWindow);
        if(mouseView.x >= 0.f)
            mouseGrid.x = mouseView.x / gridSizeU;
        if(mouseView.y >= 0.f)
            mouseGrid.y = mouseView.y / gridSizeU;

        // Cursor
        // Snaps cursor to a grid
        cursor.setPosition(mouseGrid.x * gridSizeF, mouseGrid.y * gridSizeF);

        sf::Event ev;

        while(window.pollEvent(ev)){
            switch(ev.type){ 
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            } 

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                select = START;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                select = END;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                startCount = 0;
                endCount = 0;
                starting = 0;
                for(int x = 0; x < width; x++){
                    for(int y = 0; y < height; y++)
                        tileMap[x][y].setFillColor(sf::Color::White);
                }
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
                starting = 1;
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(select == START && !startCount){
                    tileMap[mouseGrid.x][mouseGrid.y].setFillColor(sf::Color::Blue);
                    start.setCoordinate(mouseGrid.x,mouseGrid.y);
                    startCount = 1;
                }else if(select == END && !endCount){
                    tileMap[mouseGrid.x][mouseGrid.y].setFillColor(sf::Color::Red);
                    end.setCoordinate(mouseGrid.x,mouseGrid.y); 
                    endCount = 1;
                }
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                tileMap[mouseGrid.x][mouseGrid.y].setFillColor(sf::Color::Black);
        }

        if(startCount == 1 && endCount == 1 && starting == 1){
            int dc[] = {-1, +1, 0, 0};
            int dr[] = {0, 0, -1, +1}; 
            std::queue<int> rowQ, colQ;
            rowQ.push(start.getX());
            colQ.push(start.getY());
            bool found = false;
            bool visit[height][width];
            for(int i = 0; i < 100; i++){
                for(int y = 0; y < 100; y++)
                    visit[i][y] = false;}
            Node prev[10000];
            Node back[10000];
            visit[start.getX()][start.getY()] = true;
            int key;
            while(!found){
                int tempR;
                int tempC;
                for(int i = 0; i < 4; i++){
                    tempR = rowQ.front() + dc[i];
                    tempC = colQ.front() + dr[i];
                    if(tempR >= 0 && tempR < height && tempC >= 0 && tempC < width && visit[tempR][tempC] == false && tileMap[tempR][tempC].getFillColor() != sf::Color::Black){
                        
                        visit[tempR][tempC] = true;
                        back[key].setCoordinate(rowQ.front(),colQ.front());
                        prev[key].setCoordinate(tempR,tempC);
                        key++;
                        if(tileMap[tempR][tempC].getFillColor() == sf::Color::Red){
                            int b = key-1;
                            int truth = 0;
                            for(int x = 0; x < key; x++){
                                if(start.getX() ==  prev[b].getX() && start.getY() == prev[b].getY()){
                                    break;
                                }
                                tileMap[prev[b].getX()][prev[b].getY()].setFillColor(sf::Color::Yellow);
                                tileMap[end.getX()][end.getY()].setFillColor(sf::Color::Red);
                                int temX = back[b].getX();
                                int temY = back[b].getY();
                                for(int z = 0; z < sizeof(back)/sizeof(back[0]) ; z++ ){
                                    if(prev[z].getX() == back[b].getX() && prev[z].getY() == back[b].getY()){
                                        b = z;
                                        break;
                                    }                        
                                }
                            }
                            starting = 0;
                            found = true;
                            break;
                        }else{
                            rowQ.push(tempR);
                            colQ.push(tempC);
                            tileMap[tempR][tempC].setFillColor(sf::Color::Green);
                            window.clear();
                            for(int x = 0; x < width; x++){
                                for(int y = 0; y < height; y++)
                                    window.draw(tileMap[x][y]);
                            }
                            window.display();
                        }
                    }
                }
                if(tileMap[tempR][tempC].getFillColor() != sf::Color::Red){
                    colQ.pop();
                    rowQ.pop();
                }
            }
        }
        window.clear();
        for(int x = 0; x < width; x++){
            for(int y = 0; y < height; y++)
                window.draw(tileMap[x][y]);
        }
        window.draw(cursor);    
        window.display();
    }
}

//g++ main.cpp -o t -lsfml-graphics -lsfml-window -lsfml-system

