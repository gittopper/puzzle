#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

class Puzzle55
{
public:
  static const int N = 5;
  vector<vector<int> > puzzles;

  bool table[N][N];
  bool table2[N][N];

  int num;

  bool partIsUsed[8];
  int solution[2 * N - 2][2];

  Puzzle55(vector<vector<int> > puzzleFigures): puzzles(puzzleFigures),num(0)
  {
    for (int i=0;i<N;i++)
    {
      for (int j=0;j<N;j++)
      {
        table[i][j] = 0;
      }
    }
    for (int i=0;i<8;i++)
    {
      partIsUsed[i] = false;
    }
    for (int i=0;i<2 * N - 2;i++)
    {
      solution[i][0] = 0;
      solution[i][1] = 0;
    }
  }

  struct SolutionStep
  {
    SolutionStep(int n, bool r):partNumber(n),revert(r){}
    bool operator == (const SolutionStep& right) const
    {
      return partNumber == right.partNumber && revert == right.revert;
    }
    int partNumber;
    bool revert;
  };
  struct OneSolution
  {
    vector<SolutionStep> sol1,sol2;
  };
  vector<OneSolution> Solutions;

  void getCubeCoordinates(int nthPuzzle, bool revert, int iCube, int &i, int &j)
  {
    int k = puzzles[nthPuzzle][iCube];

    j = k % 5;
    i = (k - j) / 5;
    if (revert)
    {
      i = 1 - i;
      j = 4 - j;
    }
  }

  bool tryToPlace(int nthPuzzle, bool revert, int nthSolutionStep, bool table[N][N])
  {
    nthSolutionStep = nthSolutionStep % (N - 1);
    for(int r = 0; r < 3; r++)
    {
      int i, j;
      getCubeCoordinates(nthPuzzle, revert, r, i, j);
      if (table[nthSolutionStep + i][j]) return false;
    }
    for(int r = 0; r < 3; r++)
    {
      int i, j;
      getCubeCoordinates(nthPuzzle, revert, r, i, j);
      table[nthSolutionStep + i][j] = true;
    }
    return true;
  }

  void undoPuzzle(int nthPuzzle, bool revert, int nthSolutionStep, bool table[N][N])
  {
    nthSolutionStep = nthSolutionStep % (N - 1);
    for(int r = 0; r < 3; r++)
    {
      int i, j;
      getCubeCoordinates(nthPuzzle, revert, r, i, j);
      table[nthSolutionStep + i][j] = false;
    }
  }

  void initTable(bool table1[N][N], bool table2[N][N])
  {
    //initiate second table by imprinting first one
    for(int i = 0;i < N; i++)
    {
      for(int j = 0;j < N; j++)
      {
        int i1 = N - 1 - j;
        int j1 = N - 1 - i;
        table2[i1][j1] = table1[i][j];
      }
    }
  }

  void printFigures()
  {
    for(int i = 0; i < 2*N -2; i++)
    {
      cout<<"figure "<<i<<":"<<endl;
      for(int c2 = N - 1;c2 >= 0; c2--)
      {
        for(int c1 = 0;c1 < 2; c1++)
        {
          bool hasCube = false;
          for(int j = 0;j < 3; j++)
          {
            int k1, k2;
            getCubeCoordinates(i, 0, j, k1, k2);
            hasCube = hasCube || k1 == c1 && k2 == c2;
          }

          cout<<(hasCube?char(219):' ');
          cout<<(c1?'\0':'#');
        }
        cout<<endl;
      }
    }
  }

  bool checkTable(bool table[N][N])
  {
    return true;
    int sumi0 = 0, sumi5 = 0;
    int sumj0 = 0, sumj5 = 0;
    for (int i = 0; i <N; i++)
    {
      sumi0 += table[i][0];
      sumi5 += table[i][4];
      sumj0 += table[0][i];
      sumj5 += table[4][i];
    }
    return !table[2][2] && sumi0 >= 3 && sumi5 >= 3 && sumi0 + sumi5 <=7 && sumi0 + sumi5 + (10 - sumj0 - sumj5) == 13;
  }

  bool isReverse(const vector<SolutionStep>& left, const vector<SolutionStep>& right)
  {
    bool eq = true;
    vector<SolutionStep>::const_reverse_iterator j = right.crbegin();
    for(vector<SolutionStep>::const_iterator i = left.cbegin(); i != left.cend(); i++, j++)
    {
      eq = eq && (*i).partNumber == (*j).partNumber && (*i).revert != (*j).revert;
    }
    return eq;
  }

  bool notSaved(OneSolution& sol)
  {
    for(unsigned iSol = 0; iSol < Solutions.size(); iSol++)
    {
      if (
        Solutions[iSol].sol1 == sol.sol1 && sol.sol2 == Solutions[iSol].sol2 
        || Solutions[iSol].sol1 == sol.sol2 && Solutions[iSol].sol2 == sol.sol1 
        || isReverse(Solutions[iSol].sol2, sol.sol2) && isReverse(Solutions[iSol].sol1, sol.sol1) 
        || isReverse(Solutions[iSol].sol1, sol.sol2) && isReverse(Solutions[iSol].sol2, sol.sol1)
        )
        return false;
    }
    return true;
  }

  void tryAddPuzzle(int nthSolutionStep, bool table[N][N])
  {
    if(nthSolutionStep == 2 * N - 2)
    {
      //if (!table[2][2]) return;//no hole at center
      OneSolution sol;
      for (int i = 0; i < N - 1; i++)
      {
        sol.sol1.push_back(SolutionStep(solution[i][0]+1, solution[i][1] != 0));
      }
      for (int i = N - 1; i < 2 * N - 2; i++)
      {
        sol.sol2.push_back(SolutionStep(solution[i][0]+1, solution[i][1] != 0));
      }
      if (notSaved(sol)) 
      {
        Solutions.push_back(sol);
        cout<<"found "<<++num<<" solution:"<<endl;
        for (int i = N - 1; i >= 0; i--)
        {
          for (int j = N - 1; j >= 0; j--)
          {
            cout<<(table2[i][j]?char(219):' ');
          }
          cout<<endl;
        }
        for (unsigned i = 0; i < sol.sol1.size(); i++)
        {
          cout<<sol.sol1[i].partNumber<<","<<(sol.sol1[i].revert ? "1" : "0")<<"  ";
        }
        cout<<"  ";
        for (unsigned i = 0; i < sol.sol2.size(); i++)
        {
          cout<<sol.sol2[i].partNumber<<","<<(sol.sol2[i].revert ? "1" : "0")<<"  ";
        }

        cout<<endl;
      }
      return;
    }
    if (nthSolutionStep == N - 1)
    {
      if (!checkTable(table))
      {
        return;
      }
      initTable(table,table2);
    }
    bool useSecond = nthSolutionStep >= N - 1;
    for(int i = 0; i < 8; i++)
    {
      if (!partIsUsed[i])
      {
        partIsUsed[i] = true;
        solution[nthSolutionStep][0] = i;
        if (tryToPlace(i,false,nthSolutionStep, useSecond ? table2 : table))
        {
          solution[nthSolutionStep][1] = 0;
          tryAddPuzzle(nthSolutionStep + 1, useSecond ? table2 : table);
          undoPuzzle(i,false,nthSolutionStep,useSecond ? table2 : table);
        }
        if (tryToPlace(i,true,nthSolutionStep,useSecond ? table2 : table))
        {
          solution[nthSolutionStep][1] = 1;
          tryAddPuzzle(nthSolutionStep + 1, useSecond ? table2 : table);
          undoPuzzle(i,true,nthSolutionStep,useSecond ? table2 : table);
        }
        partIsUsed[i] = false;
      }
    }
  }
  void solve()
  {
    tryAddPuzzle(0, table);
  }
};
