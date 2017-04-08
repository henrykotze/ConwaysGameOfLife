#include <stdlib.h>
#include <stdio.h>

#define CLK 8
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

#define UR 2
#define UG 3
#define UB 4

#define LR 5
#define LG 6
#define LB 7


class cell{
  friend class GRID;
public:
  cell(bool state, int position[2]);
  bool getState()const;
  void setState(bool newState);
  void setNextState(bool next){nextState = next;}
  void mutate(){currentState = nextState;}
  const int* getPos()const;


cell(bool state):currentState(state),nextState(1), pos(NULL){}
cell():currentState(1),nextState(0),pos(NULL){}

cell* operator[](cell* meep){
  return meep;
}

cell& operator=(const cell &copy){
  currentState = copy.currentState;
  nextState = copy.nextState;
  pos = copy.pos;
  return *this;

}




private:
  bool currentState;
  bool nextState;
  int * pos;

};


class GRID{
  public:
    GRID(int row, int col, cell* startP, cell* currP);
    void PopulateGrid();
    void update();

    void PrintGRID();

    void shiftToLife();


    ~GRID(){ //Virtual Method for exiting scope
      free(PosOfEndRows);
      free(PosOfNewRows);
    }

private:
  const int r;
  const int c;
  cell* const startP;
  int NumOfalive;
  const int jumps;
  const int numOfCells;
  cell* cP;
  cell* rowP;

  cell grid;

  //Placeholders for special postions in matrixs
  int* PosOfNewRows;
  int* PosOfEndRows;
  bool isSpecialPosForRows(int pos);
  bool isSpecialPosForCols(int pos);

  void FillUp();
};


int main(int argc, char const *argv[]) {


cell* startPoint = (cell*) malloc(64*38*sizeof(cell));
*startPoint = cell();

int ROW_S = 5;
int COL_S = 5;

  for(int i = 1; i <= ROW_S*COL_S; ++i){    //possible errors for Arduino
        int r = rand()%2;
        *(startPoint + i) = cell(r);
      }

GRID ggrid(ROW_S, COL_S,startPoint,startPoint);
ggrid.PrintGRID();
ggrid.update();
printf("\n");
ggrid.PrintGRID();


ggrid.update();
printf("\n");
ggrid.PrintGRID();


free(startPoint);


  return 0;
}
cell::cell(bool state, int position[2]):
    currentState(state),
    pos(position)
{}

// cell::getState get state
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


GRID::GRID(const int row, const int col, cell* startPointer, cell* currP):
  r(row),
  c(col),
  startP(startPointer),
  NumOfalive(0),
  jumps(col-3),
  numOfCells(row*col),
  cP(startPointer),
  rowP(startP)
{

  FillUp();
  PosOfEndRows = (int*) malloc(r * sizeof(int));
  PosOfNewRows = (int*) malloc(r * sizeof(int));
  int i = 0;

  for(; i<r ;++i){  //possible errors for arduino compilers
    PosOfNewRows[i] = 1 + c*i;
    PosOfEndRows[i] = c*(i+1);
  }
}

bool GRID::isSpecialPosForRows(int pos){
  for(int i = 0; i < r; ++i){ //maybe combine them in one array
    if(*(PosOfNewRows+i) == pos){
      return true;
    }
  }
    return false;
}

bool GRID::isSpecialPosForCols(int pos){
  for(int i = 0; i < r; ++i){
    if(*(PosOfEndRows+i) == pos){
      return true;
    }
  }
  return false;
}


void GRID::update(){
for(int i = 1; i <= numOfCells; ++i){//changes i = 0
  int death = 0;
  int life = 0; //problem
    if(i == 1){   //top left cell
      (startP+1)->getState() ? ++life: ++death; //("%d", life);
      (startP+c)->getState() ? ++life: ++death; //("%d", life);
      (startP+c+1)->getState() ? ++life: ++death; //("%d \n", life);
    }
    else if(i == c){  //top right cell
      (startP+i-1+c)->getState() ? ++life: ++death;
      (startP+i-2+c)->getState() ? ++life: ++death;
      (startP+i-2)->getState() ? ++life: ++death;
    }
    else if(i == c*(r-1)+1){ // bottom left cell
      (startP+i)->getState() ? ++life: ++death;
      (startP+i-1-c)->getState() ? ++life: ++death;
      (startP+i-c)->getState() ? ++life: ++death;
    }
    else if(i == numOfCells){ //bottom right cell
      (startP+i-2)->getState() ? ++life: ++death;
      (startP+i-1-c)->getState() ? ++life: ++death;
      (startP+i-2-c)->getState() ? ++life: ++death;
    }

    else if(isSpecialPosForRows(i)){//left most colomn of Grid
        (startP+i)->getState() ? ++life : ++death;
        (startP+i-c)->getState() ? ++life : ++death;
        (startP+i-c-1)->getState() ? ++life : ++death;
        (startP+i+c)->getState() ? ++life : ++death;
        (startP+i+c-1)->getState() ? ++life : ++death;

    }

    else if(isSpecialPosForCols(i)){
        (startP+i-2)->getState() ? ++life : ++death;
        (startP+i-1+c)->getState() ? ++life : ++death;
        (startP+i-2+c)->getState() ? ++life : ++death;
        (startP+i-1-c)->getState() ? ++life : ++death;
        (startP+i-2-c)->getState() ? ++life : ++death;

    }

    else if(i < c){//top row
      (startP+i)->getState() ? ++life: ++death;
      (startP+i-2)->getState() ? ++life: ++death;
      (startP+i-1+c)->getState() ? ++life: ++death;
      (startP+i+c)->getState() ? ++life: ++death;
      (startP+i+c-2)->getState() ? ++life: ++death;
    }
    else if(i < numOfCells and i > c*(r-1)){//bottom row
      (startP+i)->getState() ? ++life: ++death;
      (startP+i-2)->getState() ? ++life: ++death;
      (startP+i-c)->getState() ? ++life: ++death;
      (startP+i-c-1)->getState() ? ++life: ++death;
      (startP+i-c-2)->getState() ? ++life: ++death;
    }
    else{
        (startP+i)->getState() ? ++life: ++death;
        (startP + i - 2)->getState() ? ++life : ++death;
        (startP + i + c)->getState() ? ++life : ++death;
        (startP + i + c -1)->getState() ? ++life : ++death;
        (startP + i + c -2)->getState() ? ++life : ++death;
        (startP + i - c)->getState() ? ++life : ++death;
        (startP + i - c-1)->getState() ? ++life : ++death;
        (startP + i - c-2)->getState() ? ++life : ++death;
    }
    if(life > 3){
      (startP+i-1)->setNextState(0);
    }
    else if(life < 2){
      (startP+i-1)->setNextState(0);
    }
    else if(life == 3 or life == 2){
      (startP+i-1)->setNextState(1);
    }

    else if(!(startP+i-1)->getState() and life == 3){
      (startP+i-1)->setNextState(1);
    }
  }

  for(int i = 0; i < numOfCells; ++i){
  (startP+i)->mutate();
  }
}

void GRID::PrintGRID(){

  for(int i = 0; i < r*c; ++i){    //possible errors for Arduino
      printf(" %d |", (startP + i)->getState());
      if(isSpecialPosForCols(i+1)) printf("\n");
  }
}

void GRID::FillUp(){ //currently testing
  *startP = cell();
  for(int row = 1; row <= r; ++row){    //possible errors for Arduino
    for(int col = 1; col <= c; ++col){
        *(startP + row*col) = cell();
    }
  }
}



void GRID::shiftToLife(){
  // for(int i = 0; i < numOfCells/2; ++i){
  //   for(int j = 0; j < r/2; j++){
  //     if( (startP+i)->getState() and (startP+i+r/2*c)->getState() ){
  //       PORTD = 0b00001001;
  //     }
  //     else if( (startP+i)->getState() and !(startP+i+r/2*c)->getState() ){
  //       PORTD = 0b00000001;
  //     }
  //     else if( !(startP+i)->getState() and (startP+i+r/2*c)->getState())
  //       PORTB = 0b00001000;
  //     else{
  //       PORTB = 0b00000000;
  //     }
  //     delay(1);
  //
  //     PORTB = 0b00000000;
  //     ++i;
  //     ++j;
  //   }
  //   PORTB = 0b00000100;
  //   PORTB = 0b00000100;
  //   ++DDRC; //increment Row
  // }
}
