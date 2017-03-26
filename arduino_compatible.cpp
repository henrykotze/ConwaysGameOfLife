#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class cell{
public:
  cell(bool state, int position[2]);
  bool getState()const;
  void setState(bool newState);
  const int* getPos()const;



cell():currentState(1),nextState(0),pos(NULL){}

cell* operator[](cell* meep){
  return meep;
}




private:
  bool currentState;
  bool nextState;
  const int * pos;

};


class GRID{
  public:
    GRID(int row, const int col, cell* startP, cell* currP);
    void PopulateGrid();
    void update();








private:
  int NumOfalive;
  const int r;
  const int c;
  cell* cP;
  cell* const startP;
  cell* rowP;

  cell* grid;

};


int main(int argc, char const *argv[]) {

// Testing basic getters and setters
    int pol[2]={0,0};

    cell meep(0,pol);

    std::cout << meep.getState() << std::endl;

    const int* mp = meep.getPos();

    std::cout << *mp << "   " <<  *(mp+1) << std::endl;
////////////////////////////////////////////////////

cell lol[2];

std::cout << lol[1].getState() << std::endl;


auto lolol = lol;

std::cout << lolol->getState() << std::endl;



  return 0;
}
cell::cell(bool state, int position[2]):
    currentState(state),
    pos(position)
{}

// cell::getState get state of cell
bool cell::getState()const{
  return currentState;
}
// cell::setState set state of cell
void cell::setState(bool newState){
  currentState = newState;
}
//cell::getPos get position of cell
const int* cell::getPos()const{
  return pos;
}


GRID::GRID(int row, int col, cell* startPointer, cell* currP):
  NumOfalive(0),
  r(row),
  c(col),
  cP(startPointer),
  startP(cP),
  rowP(startP)
{
  grid = malloc(cell[r][c]);
}
