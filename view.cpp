#include "view.h"
#include "sudoku.h"

/*Render the grid and numbers*/
void Sudoku::Render(){
    SDL_SetRenderDrawColor(renderer,25,25,25,0);
    SDL_RenderClear(renderer);
    Show_grid();
    Show_nums();
    SDL_RenderPresent(renderer);
}

/*Draw grid*/
void Sudoku::Show_grid(){
  Point p1 = Point(0,HAUTEUR - TAILLE_CASE);
  Point p2 = Point(p1.getX(),0);
	while (p1.getX() <= LARGEUR) {	//VERTICALES
  if (p1.getX() == 0 || p1.getX() == 3 * TAILLE_CASE || p1.getX() == 6 * TAILLE_CASE || p1.getX() == 9 * TAILLE_CASE) {
      SDL_SetRenderDrawColor(renderer, 2,150,240,0);
      SDL_RenderDrawLine(renderer,p1.getX(),p1.getY(),p2.getX(),p2.getY());
			p1.getX() = p1.getX() + TAILLE_CASE;
			p2.getX() = p1.getX();
		} else {
           SDL_SetRenderDrawColor(renderer,140,100,136,0);
           SDL_RenderDrawLine(renderer,p1.getX(),p1.getY(),p2.getX(),p2.getY());
			p1.getX() = p1.getX() + TAILLE_CASE;
			p2.getX() = p1.getX();
		}
	}
	Point p3 = Point(0,0);
  Point p4 = Point(LARGEUR, 0);
  while (p3.getY() <= HAUTEUR) {	//HORIZONTALES
      if(p4.getY() == 0 || p4.getY() == 3 * TAILLE_CASE || p4.getY() == 6 * TAILLE_CASE || p4.getY() == 9 * TAILLE_CASE){
        SDL_SetRenderDrawColor(renderer, 2,150,240,0);
        SDL_RenderDrawLine(renderer,p3.getX(),p3.getY(),p4.getX(),p4.getY());
        p3.getY() = p3.getY() + TAILLE_CASE;
  			p4.getY() = p3.getY();
      }
      else {
        SDL_SetRenderDrawColor(renderer,140,100,136,0);
        SDL_RenderDrawLine(renderer,p3.getX(),p3.getY(),p4.getX(),p4.getY());
        p3.getY() = p3.getY() + TAILLE_CASE;
  			p4.getY() = p3.getY();
      }
	}
}


/*Draw numbers*/
void Sudoku::Show_nums(){
 police = TTF_OpenFont("Fonts/04B_20.TTF", 40);
 SDL_Color White = {255, 255, 255};
 SDL_Color Blue = {119,17,187};
 SDL_Color Red = {255,0,0};
 for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      int val = getVal(i,j);
      std::stringstream temp_str;
     temp_str<<val;
      const char* cstr2 = temp_str.str().c_str();
  if(getType(i,j) == MODIFIABLE && coul_type == MODIFIABLE)text = TTF_RenderText_Blended(police,cstr2,Blue);
  else if(getType(i,j) == MODIFIABLE && coul_type == AUTO)text = TTF_RenderText_Blended(police,cstr2, Red);
  else if(getType(i,j) == NON_MODIFIABLE) text = TTF_RenderText_Blended(police,cstr2, White);
  num = SDL_CreateTextureFromSurface(renderer, text);
  SDL_FreeSurface(text);


  pos.x = TAILLE_CASE/3+(TAILLE_CASE*j);
  pos.y = TAILLE_CASE/5+(TAILLE_CASE*i); // x,y
   SDL_QueryTexture(num, NULL, NULL, &pos.w, &pos.h);
   SDL_RenderCopy(renderer, num, NULL, &pos);
   SDL_DestroyTexture(num);

    }
  }
   TTF_CloseFont(police);
}
