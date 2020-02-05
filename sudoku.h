#ifndef SUDOKU_H
#define SUDOKU_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstring>
#include "constants.h"


class Point{
private:
    int x;
    int y;

public:
       Point();
       Point(int abs,int ord){x = abs; y = ord;}
      ~Point(){std::cout<<"Delete Point"<<std::endl; }
      int &getX(){return x;}
      int &getY(){return y;}
      void setX(int a){x=a;}
      void setY(int o){y=o;}
};

class Sudoku {
private:
   char *name;
   bool isRunning;
   SDL_Window *window;
   SDL_Renderer *renderer;
   SDL_Surface *text;
   TTF_Font *police;
   SDL_Texture* num;
   SDL_Rect pos;
   SDL_Rect mouse;
   int **val;
   int **type;
   int frame;


public:
    Sudoku(){
        val = new int* [N];
   // Create a row for every pointer
   for (int i=0; i<N; i++)
   { // Note : Rows may not be contiguous
      val[i] = new int[N];
      std::memset(val[i], -1, N*sizeof(int));
   }
   type = new int* [N];
// Create a row for every pointer
for (int i=0; i<N; i++)
{ // Note : Rows may not be contiguous
 type[i] = new int[N];
 std::memset(type[i], -1, N*sizeof(int));
}
        std::cout<<"Create Sudoku"<<std::endl;}
  ~Sudoku(){
      for(int i = 0; i < N; ++i) {
              delete[] val[i];
          }
          //Free the array of pointers
          delete[] val;
          for(int i = 0; i < N; ++i) {
                  delete[] type[i];
              }
              //Free the array of pointers
              delete[] type;
  std::cout<<"Sudoku delete"<<std::endl;}
  Sudoku &operator=(const Sudoku &s)
  {
  	//Si le parametre de droite et de gauche sont les memes
  	if(this==&s)
  		return *this;

    for(int i=0;i<N;i++){
       for(int j=0; j<N; j++){
       this->val[i][j] = s.val[i][j];
       this->type[i][j] = s.type[i][j];
       }
   }
  	return *this;
  }
 void setVal(int row,int col,int value){val[row][col] = value;}
 int getVal(int row,int col){return val[row][col];}
  void setType(int row,int col,int value){type[row][col] = value;}
  int getType(int row,int col){return type[row][col];}
  void PrintValue(){
      for (int i=0; i<N; i++)
      {
         for (int j=0; j<N; j++)
            std::cout << val[i][j] << " ";
        std::cout << std::endl;
      }
  }
  void PrintType(){
      for (int i=0; i<N; i++)
      {
         for (int j=0; j<N; j++)
            std::cout << type[i][j] << " ";
        std::cout << std::endl;
      }
  }
 void setName(char* n){name = n;}
  char* getName(){return name;}
  void Init(const char* title,int width,int height);

  void Events();
  void Update();
  void Render();
  void Clean();
  bool Running();
  void Show_grid();//Afficher le quadrillage
  void Show_nums();
  Sudoku& Read_file(char* name);
  int Valid_value(int val, int i, int j);
  Sudoku &Change_square(int i, int j);
  void Write_file();
};
#endif
