#include <iostream>
#include <vector>
#include <map>
#include <bitset>
///////////////////////////////////////CELL/////////////////////////////////

class cell{
  friend class matrix;
  private:

    std::pair<int, int> pos;
    bool status;


  public:
    cell(int x, int y, bool stat);
    cell(int x, int y);


    std::pair<int, int> getPos();
    bool getStatus();

    void changeStatus(bool stat);
    cell(){} //someone needs to explains this to me
    cell& operator=(cell &&);


    // void LoadCells(stream& bitmap); //nead object type
};

cell& cell::operator=(cell &&rRef){
  if(this != &rRef){
    status = rRef.status;
    pos = rRef.pos;
  }
return *this;
}

cell::cell(int x, int y, bool stat){
  pos.first = x;
  pos.second = y;
  status = stat;
}

cell::cell(int x, int y){
  pos.first = x;
  pos.second = y;
  status = rand()%2;


}


std::pair<int,int> cell::getPos(){
  return pos;
}

bool cell::getStatus(){
  return status;
}

void cell::changeStatus(bool stat){
  status = stat;
}





/////////////////////////////////////MATRIX/////////////////////////////////////////

class matrix{
  private:
    int rows;
    int cols;
    std::vector<cell> gameOfLife;
    std::map< std::pair<int,int>, cell > life;
    int population = 0;
  public:
    matrix(int r, int c);

    void update();
    void rowBytes(int r, std::bitset<64> &data);

    void printMatrix();

    void populate();




};

matrix::matrix(int r, int c){
  rows = r;
  cols = c;

  for(int iter = 0; iter < r; iter++){
    for(int i = 0; i < c; i++){
      life[std::pair<int,int>(iter,i)] = cell(iter,i);
    }
  }
}

void matrix::printMatrix(){
  for(int x = 0; x < rows; x++){
    for(int y = 0; y < cols; y++){
      std::cout << life[std::pair<int,int>(x,y)].getStatus() << std::flush;
    }
    std::cout << std::endl;
  }
}

void matrix::update(){

  for(int r = 0; r <= rows; r++){
    for(int c = 0; c <= cols; c++){
      int alive = 0;
      int dead = 0;
      if(c == 0 and r < rows and r != rows -1){
          life[std::pair<int,int>(r+1,c)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r,c+1)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r+1,c+1)].getStatus()? ++alive : ++dead;
      }
      else if(r == 0 and c < cols){
          life[std::pair<int,int>(r+1,c)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r,c+1)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r+1,c+1)].getStatus()? ++alive : ++dead;
          life[std::pair<int,int>(r,c-1)].getStatus()? ++alive : ++dead;
          life[std::pair<int,int>(r-1,c-1)].getStatus()? ++alive : ++dead;
      }
      else if(c == cols-1 and r >= 0 and r < rows-1){
          life[std::pair<int,int>(r+1,c)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r-1,c)].getStatus()? ++alive : ++dead;
          life[std::pair<int,int>(r-1,c-1)].getStatus()? ++alive : ++dead;

      }
      else if(r == rows-1 and c >= 0 and c < cols){
          life[std::pair<int,int>(r,c+1)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r-1,c)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r-1,c+1)].getStatus()? ++alive : ++dead;
      }
      else if(r == rows -1 and c == cols - 1){
          life[std::pair<int,int>(r-1,c)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r,c-1)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r-1,c-1)].getStatus()?++alive: ++dead;
      }

      else{
          life[std::pair<int,int>(r+1,c)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r+1,c+1)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r+1,c-1)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r-1,c)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r-1,c+1)].getStatus()? ++alive:++dead;
          life[std::pair<int,int>(r-1,c-1)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r,c+1)].getStatus()? ++alive: ++dead;
          life[std::pair<int,int>(r,c-1)].getStatus()? ++alive: ++dead;
      }
      if( alive < 2){
          life[std::pair<int,int>(r,c)].changeStatus(0);
          --population;

      }
      else if(alive > 3){
          life[std::pair<int,int>(r,c)].changeStatus(0);
          --population;
      }

      if(!life[std::pair<int,int>(r,c)].getStatus()){
          if(alive == 3){
              life[std::pair<int,int>(r,c)].changeStatus(1);
              ++population;
          }
        }
      }
    }
  }

void matrix::populate(){
  for(int r = 0; r < rows; ++r){
    for(int c = 0; c < cols; ++c){
      life[std::pair<int,int>(r,c)].changeStatus(rand()%2);
    }
  }
}


void matrix::rowBytes(int r, std::bitset<64> &data){
  for(int col = 0; col< 64; ++col){
    data[63-col] = life[std::pair<int,int>(r,col)].getStatus();
  }
}








/////////////////////////////////////MAIN///////////////////////////////////
int main(int argc, char const *argv[]){

  matrix meep(32,64);
  meep.printMatrix();

  std::bitset<64> mep(0);
  auto &meepmeep = mep;


  meep.rowBytes(31, meepmeep);


  std::cout << "\n" << std::endl;
  std::cout << mep.to_string() << std::endl;




  return 0;
}
