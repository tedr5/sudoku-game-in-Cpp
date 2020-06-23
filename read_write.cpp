#include <fstream>
#include <string>
#include "sudoku.h"
#include <vector>
#include <filesystem>
#include <iterator>
#include <regex>

std::vector<std::filesystem::directory_entry> find_files(
  std::filesystem::path const& path,
  std::string_view regex)
  {
    std::vector<std::filesystem::directory_entry> result;
    std::cout<<regex.data()<<std::endl;
    std::regex rx(regex.data());

    std::copy_if(
      std::filesystem::recursive_directory_iterator(path),
      std::filesystem::recursive_directory_iterator(),
      std::back_inserter(result),
      [&rx](std::filesystem::directory_entry const& entry){
        return std::filesystem::is_regular_file(entry.path()) &&
        std::regex_match(entry.path().filename().string(),rx);
      });
      return result;
  }


void read_directory(const std::string& name,const char* nb1)
{   std::filesystem::path const& p(name);
    std::string str(nb1);
    std::cout<<str<<std::endl;
    auto pattern = R"(PLAY[)" + str + R"(].sudoku.save[0-1000])";
    auto result = find_files(p,pattern);
    for(auto const& entry: result)
    {
     std::cout<< "ITERATE" << std::endl;
      /*int pos = str3.find("e");
      str3 = str3.substr(pos+1);*/
      std::cout<< entry.path().string() << std::endl;
    }
}
char Sudoku::getChar(int val){
   switch (val) {
     case 0: return '.'; break;
     case 1: return '1'; break;
     case 2: return '2'; break;
     case 3: return '3'; break;
     case 4: return '4'; break;
     case 5: return '5'; break;
     case 6: return '6'; break;
     case 7: return '7'; break;
     case 8: return '8'; break;
     case 9: return '9'; break;
   }
   return ' ';
}


/*Read file game */
Sudoku &Sudoku::Read_file(const char* name){
    std::ifstream fichier(name);
    char charlu;
    if(fichier.is_open()){
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
 return *this;
}


/*Sudoku save*/
void Sudoku::Write_file(){
  read_directory(".","1");
 std::string gamename =  (std::string) getName();
 std::string tmp = ".save";
 std::string savenum = tmp.append( std::to_string(save_num));
 std::string savename = gamename.append(savenum);

 std::ofstream fichier(savename);
 char num,typedelimiter;
 if(fichier.is_open()){
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
     int val = getVal(i,j);
     int square_type = getType(i,j);
     if(square_type == MODIFIABLE && val != 0){
       typedelimiter = '*';
       fichier << typedelimiter;
     }
     num = getChar(val);
     fichier << num;
     } fichier << '\n';
  }
 }
 fichier.close();
}
