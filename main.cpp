#include "sudoku.h"


int main(int argc,char *argv[]) {
   Sudoku *sudoku = new Sudoku();
  sudoku->Init(argv[1],HAUTEUR,LARGEUR);
   const int FPS = 30;
   const int frameDelay = 1000 / FPS;
   Uint32 frameStart;
   int frameTime;
  while(sudoku->Running()){
      frameStart = SDL_GetTicks();
      sudoku->Events();
      sudoku->Render();
      frameTime = SDL_GetTicks() - frameStart;

     if(frameDelay > frameTime){
          SDL_Delay(frameDelay - frameTime);
      }
  }
 sudoku->Clean();
  return 0;
}
