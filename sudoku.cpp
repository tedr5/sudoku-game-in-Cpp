#include "sudoku.h"
#include "constants.h"
#include <fstream>
#include <sstream>
#include <vector>

//renderer,0,50,50,100

void Sudoku::Init(const char* title,int width,int height){
    frame = 0;
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
          break;
      case SDLK_s: //Sauvegarde
        SDL_Log("S Pressed");
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
          int x,y;
          SDL_GetMouseState(&x,&y);
          mouse.x = x;
          mouse.y = y;
           Change_square(mouse.x,mouse.y);
          //std::cout<<mouse.x<<" "<<mouse.y<<std::endl;
          break;
      }
    }
 }
}

void Sudoku::Update(){
   frame++;
   //std::cout<< frame << std::endl;

}

void Sudoku::Render(){
    SDL_SetRenderDrawColor(renderer,0,50,50,100);
    SDL_RenderClear(renderer);
    Show_grid();
    Show_nums();
    SDL_RenderPresent(renderer);
}

void Sudoku::Clean(){
 SDL_DestroyWindow(window);
 SDL_DestroyRenderer(renderer);
 SDL_Quit();
 std::cout<<"Sudoku clean"<<std::endl;
 delete this;
}

bool Sudoku::Running(){
    return isRunning;
}

void Sudoku::Show_grid(){
    SDL_SetRenderDrawColor(renderer, 0,204,102,0);
  Point *p1 = new Point(0,HAUTEUR - TAILLE_CASE);
  //cout <<"p1: "<< p1->getX() << " " << p1->getY() <<endl;
  Point *p2 = new Point(p1->getX(),0);
  //cout <<"p2: "<< p2->getX() << " " << p2->getY() <<endl;
	while (p1->getX() <= LARGEUR) {	//VERTICALES
		if (p1->getX() == 0 || p1->getX() == 3 * TAILLE_CASE
		    || p1->getX() == 6 * TAILLE_CASE || p1->getX() == 9 * TAILLE_CASE) {
            SDL_RenderDrawLine(renderer,p1->getX(),p1->getY(),p2->getX(),p2->getY());
			p1->getX() = p1->getX() + TAILLE_CASE;
			p2->getX() = p1->getX();
		} else {
           SDL_RenderDrawLine(renderer,p1->getX(),p1->getY(),p2->getX(),p2->getY());
			p1->getX() = p1->getX() + TAILLE_CASE;
			p2->getX() = p1->getX();
		}
	}
	Point *p3 = new Point(0,0);
    //cout << "p3: "<<p3->getX() << " " << p3->getY() <<endl;
    Point *p4 = new Point(LARGEUR, 0);
    //cout <<"p4: "<< p4->getX() << " " << p4->getY() <<endl;

	while (p3->getY() <= HAUTEUR) {	//HORIZONTALES
		if (p3->getY() == 0 || p3->getY() == 3 * TAILLE_CASE
		    || p3->getY() == 6 * TAILLE_CASE || p3->getY() == 9 * TAILLE_CASE) {
              SDL_RenderDrawLine(renderer,p3->getX(),p3->getY(),p4->getX(),p4->getY());
			p3->getY() = p3->getY() + TAILLE_CASE;
			p4->getY() = p3->getY();
		} else {
             SDL_RenderDrawLine(renderer,p3->getX(),p3->getY(),p4->getX(),p4->getY());
            p3->getY() = p3->getY() + TAILLE_CASE;
			p4->getY() = p3->getY();
		}

	}

}

void Sudoku::Show_nums(){
police = TTF_OpenFont("Fonts/04B_20.TTF", 40);
SDL_Color White = {255, 255, 255};
for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      int val = getVal(i,j);
      std::stringstream temp_str;
     temp_str<<val;
      const char* cstr2 = temp_str.str().c_str();
  text = TTF_RenderText_Blended(police,cstr2, White);
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

Sudoku &Sudoku::Read_file(char* name){
    std::ifstream fichier(name);
    char charlu;
    if(!fichier.eof()){
      for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    fichier.get(charlu);
            if (charlu == '.') {
                    this->setVal(i,j,0);
                    this->setType(i,j,MODIFIABLE);
					}
					else if (charlu == '1') {
                    this->setVal(i,j,1);
                    this->setType(i,j,NON_MODIFIABLE);
					}
					else if (charlu == '2') {
                    this->setVal(i,j,2);
                    this->setType(i,j,NON_MODIFIABLE);
					}
					else if (charlu == '3') {
                         this->setVal(i,j,3);
                         this->setType(i,j,NON_MODIFIABLE);
					}
					else if (charlu == '4') {
                        this->setVal(i,j,4);
                        this->setType(i,j,NON_MODIFIABLE);
					}
					else if (charlu == '5') {
                         this->setVal(i,j,5);
                         this->setType(i,j,NON_MODIFIABLE);
					}
					else if (charlu == '6') {
                       this->setVal(i,j,6);
                       this->setType(i,j,NON_MODIFIABLE);
					}
					else if (charlu == '7') {
                       this->setVal(i,j,7);
                       this->setType(i,j,NON_MODIFIABLE);
					}
					else if (charlu == '8') {
                        this->setVal(i,j,8);
                        this->setType(i,j,NON_MODIFIABLE);
					}
					else if (charlu == '9') {
                        this->setVal(i,j,9);
                        this->setType(i,j,NON_MODIFIABLE);
					}
					//eviter d'avancer dans les colonnes du tableau quand retour à la ligne lu
					else if (charlu == '\n') {
						j = j - 1;
					}

					else if (charlu == '*') {
                     // lire caractere suivant
                        fichier.get(charlu);
                        if (charlu == '.') {
                                this->setVal(i,j,0);
                                this->setType(i,j,MODIFIABLE);
            					}
            					else if (charlu == '1') {
                                this->setVal(i,j,1);
                                this->setType(i,j,NON_MODIFIABLE);
            					}
            					else if (charlu == '2') {
                                this->setVal(i,j,2);
                                this->setType(i,j,NON_MODIFIABLE);
            					}
            					else if (charlu == '3') {
                                     this->setVal(i,j,3);
                                     this->setType(i,j,NON_MODIFIABLE);
            					}
            					else if (charlu == '4') {
                                    this->setVal(i,j,4);
                                    this->setType(i,j,NON_MODIFIABLE);
            					}
            					else if (charlu == '5') {
                                     this->setVal(i,j,5);
                                     this->setType(i,j,NON_MODIFIABLE);
            					}
            					else if (charlu == '6') {
                                   this->setVal(i,j,6);
                                   this->setType(i,j,NON_MODIFIABLE);
            					}
            					else if (charlu == '7') {
                                   this->setVal(i,j,7);
                                   this->setType(i,j,NON_MODIFIABLE);
            					}
            					else if (charlu == '8') {
                                    this->setVal(i,j,8);
                                    this->setType(i,j,NON_MODIFIABLE);
            					}
            					else if (charlu == '9') {
                                    this->setVal(i,j,9);
                                    this->setType(i,j,NON_MODIFIABLE);
            					}
            					//éviter d'avancer dans les colonnes du tableau quand retour à la ligne lu
            					else if (charlu == '\n') {
            						j = j - 1;
            					}
                         }
                  }
            }
     }
       fichier.close();
      /* PrintValue();
       std::cout<<std::endl;
       PrintType();
     */
return *this;
}

int Sudoku::Valid_value(int val, int i, int j)
{
	int x, y;
	int lg = line(j), col = column(i);
	int regionL = areaL(lg), regionC = areaC(col);
	for (x = 0; x < N; x++) {
		if (x != col) {
			if (this->val[lg][x] == val) {
				return 0;
			}
		}
	}

	for (x = 0; x < N; x++) {
		if (x != lg) {
			if (this->val[x][col] == val) {
				return 0;
			}
		}
	}
	for (x = regionL; x < regionL + 3; x++) {
		for (y = regionC; y < regionC + 3; y++) {
			if ((x != lg) && (y != col)) {
				if (this->val[x][y] == val) {
					return 0;
				}
			}
		}
	}
	return 1;
}

Sudoku &Sudoku::Change_square(int i, int j)	//Modifier contenu de la case,si case de travail
{

	int lg = line(j), col = column(i);
    std::cout<<"Ligne:"<<lg<<" "<<"Colonne:"<<col<<std::endl;
	int x, n;
    std::vector<int> possible(10,0);
	int cpt = 0;

	if (type[lg][col] == MODIFIABLE) {
		// SI LA VALEUR X EST POSSIBLE ALORS ON MET 1
		for (x = 0; x < 10; x++) {
			if (Valid_value(x, i, j)) {
				possible[x] = 1;
				cpt++;
			}
		}
		int courant = getVal(lg,col);
		for (n = 0; n < 10; n++) {
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
	std::cout<<"SORTIE DE Change_square\n";
	return *this;
}

void Sudoku::Write_file(){

}
