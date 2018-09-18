#include <iostream>
#include <vector>
#include <fstream>

bool allFull(std::vector<std::vector<int> > v){
  int i, j;
  for(i=0; i<3; i++)
  {
    for(j=0; j<3; j++){
      if(v[i][j] == 0 ) break;
    }
  }
  if(i == 3 && j == 3) return true;
  else return false;
}

bool end(std::vector<std::vector<int> > v){
  if(v[1][1] == v[0][0] && v[1][1] == v[2][2] && v[1][1] != 0) return true;
  else if(v[1][1] == v[0][1] && v[1][1] == v[2][1] && v[1][1] != 0) return true;
  else if(v[1][1] == v[0][2] && v[1][1] == v[2][0] && v[1][1] != 0) return true;
  else if(v[1][1] == v[1][0] && v[1][1] == v[1][2] && v[1][1] != 0) return true;
  else if(v[0][0] == v[0][1] && v[0][0] == v[0][2] && v[0][0] != 0) return true;
  else if(v[0][0] == v[1][0] && v[0][0] == v[2][0] && v[0][0] != 0) return true;
  else if(v[2][2] == v[2][1] && v[2][2] == v[2][0] && v[2][2] != 0) return true;
  else if(v[2][2] == v[1][2] && v[2][2] == v[0][2] && v[2][2] != 0) return true;
  else if(allFull(v)) return true;
  else return false;
}

void inBang(std::vector<std::vector<int> > v){
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      std::cout << v[i][j] << " ";
    }
    std::cout << std::endl;
  }
  for(int i=0; i<10; i++){std::cout << std::endl;}
}

void simpleAI(std::vector<std::vector<int> > &v, int first, int aiNumber){
  int luotDi=0;
  std::cout << aiNumber <<  '\n';
  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
      if(v[i][j] == 0){
        v[i][j] = first;
        if(end(v)){
          v[i][j] = aiNumber;
          luotDi++;
          break;
        }
        else v[i][j] = 0;
        }
      }
      if(luotDi == 1) break;
    }
    for(int i=0; i<3; i++)
    {
      if(luotDi == 1) break;
      for(int j=0; j<3; j++)
      {
        if(v[i][j] == 0){
          v[i][j] = aiNumber;
          luotDi++;
          if(!end(v)){
            luotDi--;
             v[i][j] = 0;
          }
          else break;
          }
        }
      }
      for(int i=0; i<3; i++)
      {
        if(luotDi == 1) break;
        for(int j=0; j<3; j++){
          if(v[i][j] == 0) {
            v[i][j] = aiNumber;
            luotDi++;
            break;
          }
        }
      }
}

void aiFirstMove(std::vector<std::vector<int> > v, int turn)
{
  v[1][1] = turn;
}

int main()
{
  std::vector<int> v1(3);
  std::vector<std::vector<int> > v2(3,v1);
  std::ofstream ghiFile;
  ghiFile.open("tictac.dat");
  int x, y, mode;
  int turn = 1;
  int luot = 1;
  int aiNumber;
  std::cout << "An 1 de choi 1 minh, 2 de choi 2 nguoi: " << std::endl;
  std::cin >> mode;
  if(mode == 2){
    while(!end(v2))
    {
      std::cin >> x >> y;
      v2[x-1][y-1] = turn;
      inBang(v2);
      ghiFile << turn << x << y << std::endl;
      if(turn == 1) turn++;
      else turn--;
    }
  }
  else {
    std::cout << "An 1 de di truoc, 2 de di sau" << std::endl;
    int first;
    std::cin >> first;
    if(first == 1) aiNumber = 2;
    else aiNumber = 1;
    while (!end(v2)){
      if(first == 2 && luot == 1) {
        v2[1][1] = turn;
        luot++;
      }
      else if(turn == first ) {
        std::cin >> x >> y;
        v2[x-1][y-1] = turn;
      }
      else if(turn == aiNumber) simpleAI(v2,first, aiNumber);
      inBang(v2);
      if(turn == 1) turn++;
      else turn--;
      }
      //inBang(v2);
    }
  ghiFile.close();
  if(turn == 1 && !allFull(v2)) std::cout << "player " << 2 << "thang";
  else if(turn == 2 && !allFull(v2)) std::cout << "player " << 1 << "thang" ;
  return 0;
}
