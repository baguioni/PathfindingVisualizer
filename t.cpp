#include "classes.cpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <queue> 

using namespace std;
void print(int grid[][10]);
/*
U = 0, +1
D = 0, -1
L = -1, 0
R = +1, 0
*/
int main(void){
    int rowO = 2, colO = 5;
    int rowF, colF;
    string dir = "UDLR";
    int grid[5][10] =  {{0,0,0,0,6,0,0,0,0,0},
                        {0,0,0,0,6,0,0,0,0,0},
                        {0,0,0,0,6,1,0,0,0,0},
                        {0,2,0,0,0,0,0,0,0,0},
                        {0,0,0,0,6,0,0,0,0,0}
                        };
    // U D L R
    int dc[] = {-1, +1, 0, 0};
    int dr[] = {0, 0, -1, +1}; 
    queue<int> rowQ, colQ, prevX, prevY, bX, bY;
    rowQ.push(rowO);
    colQ.push(colO);
    bool found = false;
    bool visit[10][10];
    for(int i = 0; i < 10; i++){
        for(int y = 0; y < 10; y++)
            visit[i][y] = false;
    }
    Node prev[50];
    Node back[50];
    visit[rowO][colO] = true;
    int key = 0;
    while(!found){
        print(grid);
        int tempR;
        int tempC;
        for(int i = 0; i < 4; i++){

            tempR = rowQ.front() + dc[i];
            tempC = colQ.front() + dr[i];
            if(tempR >= 0 && tempR < 5 && tempC >= 0 && tempC < 10 && visit[tempR][tempC] == false && grid[tempR][tempC] != 6){
                visit[tempR][tempC] = true;
                back[key].setCoordinate(rowQ.front(),colQ.front());
                prev[key].setCoordinate(tempR,tempC);
                key++;
                if(grid[tempR][tempC] == 2){
                    int b = key-1;
                    int truth = 0;
                    for(int x = 0; x < key; x++){
                        grid[prev[b].getX()][prev[b].getY()] = 8;
                        int temX = back[b].getX();
                        int temY = back[b].getY();
                        for(int z = 0; z < 50 ; z++ ){
                            if(prev[z].getX() == back[b].getX() && prev[z].getY() == back[b].getY()){
                                b = z;
                                break;
                            }                        
                        }
                    }
                    found = true;
                    break;
                }else{
                    rowQ.push(tempR);
                    colQ.push(tempC);
                    grid[tempR][tempC] = 5;
                }
            }
        }
        if(grid[tempR][tempC] != 2){
            colQ.pop();
            rowQ.pop();
        }
    }
    print(grid);

}
void print(int grid[][10]){
    cout <<"\n";
    cout <<"  0 1 2 3 4 5 6 7 8 9\n";
    for(int i = 0; i < 5; i++){
        cout << i <<" ";
        for(int y = 0; y < 10; y++){
            cout << grid[i][y] <<" ";
        }cout <<"\n";
    }cout <<"\n";
}
