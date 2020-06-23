#include "view.h"
#include "sudoku.h"
#include "constants.h"
#include <vector>
#include <cmath>


//renderer,0,50,50,100
/*Initialize the sudoku game grid*/
void Sudoku::Init(const char* title,int width,int height){
     save_num = 1;
     coul_type = MODIFIABLE;
     setName(title);
     Read_file(title);
   if(SDL_Init(SDL_INIT_VIDEO) == 0){
   window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,SDL_WINDOW_OPENGL);
      if(window){
         std::cout<< "Create window Successfull"<< std::endl;
         isRunning = true;
         renderer = SDL_CreateRenderer(window, -1,0);
        if(TTF_Init() == -1){
            std::cout << "Error TTF Init" << std::endl;
            exit(EXIT_FAILURE);
        }atexit(TTF_Quit);
     }
   }
   else {
       isRunning = false;
   }
}
/* Handle keyboard or mouse events*/
void Sudoku::Events(){
   SDL_Event event;
  while(SDL_PollEvent(&event)) {
   switch(event.type){
   case SDL_QUIT:
       isRunning = false;
       SDL_Log("Exit with cross");
     break;
   case SDL_KEYDOWN:
     switch (event.key.keysym.sym)
      {
      case SDLK_u: //Undo
          SDL_Log("U Pressed");
          break;
      case SDLK_v: //Resoudre auto
        SDL_Log("V Pressed");
        Auto_solve();
        break;
      case SDLK_s: //Sauvegarde
        SDL_Log("S Pressed");
        Write_file();
          break;
      case SDLK_q: //Quitter
         SDL_Log("Q Pressed");
          isRunning = false;
          break;
      }
     case SDL_MOUSEBUTTONDOWN: //Clic souris
      switch (event.button.button)
      {
      case SDL_BUTTON_LEFT:
          SDL_Log("LEFT Clic");
          int mouse_x,mouse_y;
          SDL_GetMouseState(&mouse_x,&mouse_y);
          Change_square(mouse_x,mouse_y);
          break;
      }
    }
 }
}
/*Destroy all components and quit properly*/
void Sudoku::Clean(){
 SDL_DestroyWindow(window);
 SDL_DestroyRenderer(renderer);
 SDL_Quit();
 std::cout<<"Sudoku clean"<<std::endl;
 delete this;
}
/*Know if game is running*/
bool Sudoku::Running(){
    return isRunning;
}


bool Sudoku::Next_square(int *row,int *col){
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      if(val[i][j] ==  0){
        *row = i;
        *col = j;
        return false;
      }
    }
  }
  return true;
}

bool Sudoku::Completed(){
   for(int i=0; i<N; i++){
     for(int j=0; j<N; j++){
       if(val[i][j] == 0)
        return false;
     }
   }
  return true;
}

/*Get only valid values when interacting with grid empty square*/
bool Sudoku::Valid_value(int i, int j,int v, int MODE)
{
	int x, y;
        int lg,col;
        int regionL,regionC;
	if(MODE == AUTO){
         lg = i;        col = j;
  }
  else if(MODE == MODIFIABLE){
         lg = line(j);         col = column(i);
	}
          regionL = areaL(lg);  regionC = areaC(col);

	for (x = 0; x < N; x++) {
		if (x != col && val[lg][x] == v)
		return false;
  }

  for (x = 0; x < N; x++) {
		if (x != lg && val[x][col] == v)
		return false;
	}

	for (x = regionL; x < regionL + 3; x++) {
	     for (y = regionC; y < regionC + 3; y++) {
	      	if ((x != lg) && (y != col) && val[x][y] == v)
		        return false;
	     }
	}
	return true;
}

bool Sudoku::Auto_solve(){
  int row,col;
  //TO DO: ajouter undo tout les mouvements joueurs avant resoudre
  coul_type = AUTO;
 if(Completed()){
  std::cout<<"FINISHED SUDOKU!"<<std::endl;
  return true;
 }
 else{
  Next_square(&row,&col);
 }

     for(int num=1; num<=9; num++){
       if(Valid_value(row,col,num,AUTO) && type[row][col] == MODIFIABLE){
         val[row][col] = num;
         if(Auto_solve())return true;
         val[row][col] = 0;
        }
     }

    return false;
}

/*Change value of square*/
Sudoku &Sudoku::Change_square(int i, int j)
{
  save_num++;
  int lg = line(j), col = column(i);
    std::vector<int> possible(10,0);
	int cpt = 0;
	if (type[lg][col] == MODIFIABLE) {
		// SI LA VALEUR X EST POSSIBLE ALORS ON MET 1
		for(int x = 0; x < 10; x++) {
			if (Valid_value(i, j, x, MODIFIABLE)) {
				possible[x] = 1;
				cpt++;
			}
		}
		int courant = getVal(lg,col);
		for (int n = 0; n < 10; n++) {
			courant = courant + 1;

			if (courant == 10 || val[lg][col] == IMPOSSIBLE) {
				courant = 0;
			     val[lg][col] = 0;
				return *this;
			} else if (possible[courant] == 1) {
				val[lg][col] = courant;
				return *this;
			} else if (cpt == 0) {
				val[lg][col] = IMPOSSIBLE;
				return *this;
			}
		}
	}
	return *this;
}
