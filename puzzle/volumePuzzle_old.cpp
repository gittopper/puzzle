#include <vector>
#include <assert.h>
#include <iostream>
using namespace std;

enum RotType
{
  None,
  RotateX,
  RotateY,
  RotateZ
};

struct ex
{

};

//#define BREAK_ON_LINE(x) if (!(x)) { throw ex();}
//#define BREAK_ON_LINE(x) assert(x);
#define BREAK_ON_LINE(x)


struct IntVector
{
  IntVector(int i = 0, int j = 0, int k = 0)
  {
    vec[0] = i;
    vec[1] = j;
    vec[2] = k;
  }
  int vec[3];

  const int& operator[](int i) const
  {
    return vec[i];
  }

  int& operator[](int i)
  {
    return vec[i];
  }
  IntVector cross(const IntVector v)
  {
    IntVector r;
    r[0] = vec[1] * v.vec[2] - vec[2] * v.vec[1];
    r[1] = vec[2] * v.vec[0] - vec[0] * v.vec[2];
    r[2] = vec[0] * v.vec[1] - vec[1] * v.vec[0];
    return r;
  }
  IntVector& rotate(RotType rotation)
  {
    int x = vec[0];
    int y = vec[1];
    int z = vec[2];

    switch(rotation)
    {
    case RotateX:
      vec[1] = z;
      vec[2] = -y;
      break;
    case RotateY:
      vec[0] = -z;
      vec[2] = x;
      break;
    case RotateZ:
      vec[0] = y;
      vec[1] = -x;
    };
    return *this;
  }
  IntVector operator-(const IntVector& v) const
  {
    return IntVector(vec[0] - v[0], vec[1] - v[1], vec[2] - v[2]);
  }
  bool operator==(const IntVector& v) const
  {
    return vec[0] == v[0] && vec[1] == v[1] && vec[2] == v[2];
  }
  IntVector operator-() const
  {
    return IntVector(-vec[0], -vec[1], -vec[2]);
  }
  IntVector operator+(const IntVector& v) const
  {
    return IntVector(vec[0] + v[0], vec[1] + v[1], vec[2] + v[2]);
  }
  void print() const
  {
    cout << "(" << vec[0] << "," << vec[1] << "," << vec[2] << ")";
  }
};
int dot(const IntVector& v1, const IntVector& v2)
{
  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

ostream& operator << (ostream& os, const IntVector& vec)
{
  vec.print();
  return os;
}

struct Mat
{
  double ar[9];
  inline const double el(int i, int j) const
  {
    return ar[i*3 + j];
  }
  inline double& el(int i, int j)
  {
    return ar[i*3 + j];
  }
  double det()const
  {
    return el(0,0)*el(1,1)*el(2,2)+el(1,0)*el(2,1)*el(0,2)+el(0,1)*el(1,2)*el(2,0) - el(2,0)*el(1,1)*el(0,2)-el(1,0)*el(0,1)*el(2,2)-el(2,1)*el(1,2)*el(0,0);
  }
  void scale(double val)
  {
    for (int i =0; i <9; i++) 
    {
      double r = ar[i] * val;
      ar[i] = r;
      //BREAK_ON_LINE(ar[i] == r);
    }
  }
  Mat(){}
  Mat(IntVector v1,IntVector v2, IntVector v3)
  {
    el(0,0) = v1[0];
    el(1,0) = v1[1];
    el(2,0) = v1[2];

    el(0,1) = v2[0];
    el(1,1) = v2[1];
    el(2,1) = v2[2];

    el(0,2) = v3[0];
    el(1,2) = v3[1];
    el(2,2) = v3[2];
  }
  Mat inverse()
  {
    Mat inv;
    inv.el(0,0) = (el(1,1) * el(2,2) - el(1,2) * el(2,1));
    inv.el(0,1) = (el(0,2) * el(2,1) - el(0,1) * el(2,2));
    inv.el(0,2) = (el(0,1) * el(1,2) - el(0,2) * el(1,1));

    inv.el(1,0) = (el(1,2) * el(2,0) - el(1,0) * el(2,2));
    inv.el(1,1) = (el(0,0) * el(2,2) - el(0,2) * el(2,0));
    inv.el(1,2) = (el(0,2) * el(1,0) - el(0,0) * el(1,2));

    inv.el(2,0) = (el(1,0) * el(2,1) - el(1,1) * el(2,0));
    inv.el(2,1) = (el(0,1) * el(2,0) - el(0,0) * el(2,1));
    inv.el(2,2) = (el(0,0) * el(1,1) - el(0,1) * el(1,0));
    inv.scale(1./det());
    return inv;
  }
  bool operator == (const Mat& m) const
  {
    for (int i=0;i<9;i++)
    {
      if (ar[i] != m.ar[i]) return false;
    }
    return true;
  }
  Mat operator * (const Mat& m) const
  {
    Mat n;
    for (int i=0;i<3;i++)
    {
      for (int j=0;j<3;j++)
      {
        n.el(i,j) = el(i,0) * m.el(0,j) + el(i,1) * m.el(1,j) + el(i,2) * m.el(2,j);
      }
    }
    return n;
  }
};

IntVector operator * (const Mat& m, const IntVector& v)
{
  IntVector o;
  o[0] = int(m.el(0,0) *v[0] + m.el(0,1) *v[1] + m.el(0,2) *v[2]);
  o[1] = int(m.el(1,0) *v[0] + m.el(1,1) *v[1] + m.el(1,2) *v[2]);
  o[2] = int(m.el(2,0) *v[0] + m.el(2,1) *v[1] + m.el(2,2) *v[2]);
  return o;
}

struct VolPart
{
  enum VolType
  {
    Empty,
    Full,
    Angle
  };
  VolType fillInfo;
  IntVector xyz, dir;
  VolPart(VolType t, IntVector coord, IntVector iniDir = IntVector(0,0,0), bool w = false):fillInfo(t),xyz(coord),dir(iniDir),wall(w){}
  bool wall;

  void print() const
  {
    cout<<(fillInfo == Empty ? "Empty" : fillInfo == Full ? "Full" : "Angle");
    cout<<xyz;
    if (fillInfo == Angle) cout<<","<<dir;
  }

  bool operator==(const VolPart& vol) const
  {
    return xyz == vol.xyz && fillInfo == vol.fillInfo && ( fillInfo != Angle || dir == vol.dir); 
  }

  bool hasSide(int dim, int val) const
  {
    if (fillInfo == Empty) return false;
    if (fillInfo == Full) return true;
    BREAK_ON_LINE(!dir[dim] || dir[dim] * dir[dim] == 1);
    return dir[dim] * (1 - 2 * val) >= 0;
  }

  VolPart& operator+=(const VolPart& v)
  {
    BREAK_ON_LINE(xyz == v.xyz);
    if (fillInfo == Empty)
    {
      fillInfo = v.fillInfo;
      dir = v.dir;
      return *this;
    }
    if (fillInfo == Angle && v.fillInfo == Angle && dir == -v.dir)
    {
      fillInfo = Full;
      return *this;
    }
    BREAK_ON_LINE(false);
    return *this;
  }

  VolPart& rotate(RotType rot)
  {
    BREAK_ON_LINE(fillInfo != Empty);
    xyz.rotate(rot);
    if (fillInfo == Angle) dir.rotate(rot);
    return *this;
  }

  VolPart& rotate(const Mat& m)
  {
    xyz = m * xyz;
    if (fillInfo == Angle)  dir = m * dir;
    return *this;
  }

  VolPart& operator-=(const VolPart& another)
  {
    if (fillInfo == Full)
    {
      if (another.fillInfo == Full)
      {
        fillInfo = Empty;
        return *this;
      }
      else if (another.fillInfo == Angle)
      {
        fillInfo = Angle;
        dir = -another.dir;
        return *this;
      }
      else
      {
        BREAK_ON_LINE(false);
      }
    }
    if (fillInfo == Angle)
    {
      if (another.fillInfo == Angle && dir == another.dir)
      {
        fillInfo = Empty;
        return *this;
      }
      else
      {
        BREAK_ON_LINE(false);
      }
    }
    return *this;
  }
  bool couldPlace(const VolPart& another) const
  {
    BREAK_ON_LINE(xyz == another.xyz && another.fillInfo != Empty);
    return fillInfo == Empty
      || fillInfo == Angle && another.fillInfo == Angle && dir == -another.dir
      || fillInfo == Full && another.fillInfo == Empty; 
  }
  bool match(const VolPart& another) const
  {
    return fillInfo != Empty && another.fillInfo != Empty && !wall && !another.wall;
  }
  bool shareOneOfSides(const VolPart& another) const
  {
    BREAK_ON_LINE(dot(xyz - another.xyz, xyz - another.xyz)<=1);

    if (fillInfo == Empty || another.fillInfo == Empty || wall || another.wall) return false;
    if (fillInfo == Full && another.fillInfo == Full) return true;
    if (fillInfo == Angle && another.fillInfo == Full)
    {
      return dot(dir, another.xyz - xyz) < 0;
    }
    if (fillInfo == Full && another.fillInfo == Angle)
    {
      return dot(another.dir, xyz - another.xyz) < 0;
    }
    if (fillInfo == Angle && another.fillInfo == Angle)
    {
      //return true;
      if (xyz == another.xyz)
      {
        if (dir == -another.dir) return true;
      }
      else
      {
        return dot(dir, another.xyz - xyz) < 0 && dot(another.dir, xyz - another.xyz) < 0;
      }
    }
    cout << "problem 3\n";
    BREAK_ON_LINE(false);
    return false;
  }
};


ostream& operator << (ostream& os, const VolPart& v)
{
  v.print();
  return os;
}

struct BBox
{
  BBox():minV(1000,1000,1000),maxV(-1000,-1000,-1000){}
  void merge(const IntVector& v)
  {
    minV[0] = minV[0] > v[0] ? v[0] : minV[0];
    minV[1] = minV[1] > v[1] ? v[1] : minV[1];
    minV[2] = minV[2] > v[2] ? v[2] : minV[2];

    maxV[0] = maxV[0] < v[0] ? v[0] : maxV[0];
    maxV[1] = maxV[1] < v[1] ? v[1] : maxV[1];
    maxV[2] = maxV[2] < v[2] ? v[2] : maxV[2];
  }
  void grow()
  {
    minV = minV - IntVector(1,1,1);
    maxV = maxV + IntVector(1,1,1);
  }
  IntVector minV,maxV;
};

struct PuzzlePart
{
  bool busy;
  int number;

  vector<VolPart> parts;
  PuzzlePart():number(0),busy(false){}
  PuzzlePart(int n):number(n),busy(false){}
  PuzzlePart& rotate(RotType rot)
  {
    for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
    {
      (*it).rotate(rot);
    }
    return *this;
  }
  PuzzlePart& rotate(Mat rot)
  {
    for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
    {
      (*it).rotate(rot);
    }
    return *this;
  }
  void print() const
  {
    cout<<"Part number "<<number<<":"<<endl;
    for (vector<VolPart>::const_iterator it = parts.cbegin(); it != parts.cend(); it++)
    {
      cout<<*it<<endl<<endl;
    }
  }
  bool operator == (const PuzzlePart& part) const
  {
    return parts == part.parts;
  }
  void getBBox(BBox& box) const 
  {
    for (vector<VolPart>::const_iterator it = parts.cbegin(); it != parts.cend(); it++)
    {
      box.merge((*it).xyz);
    }
    return;
  }
  PuzzlePart& shift(const IntVector& shift)
  {
    for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
    {
      (*it).xyz = (*it).xyz + shift;
    }
    return *this;
  }
  Mat getLCS()
  {
    IntVector x = parts[1].xyz - parts[0].xyz;
    IntVector y = parts[2].xyz - parts[0].xyz;
    return Mat(x,y,x.cross(y));
  }

  IntVector getZero()
  {
    return parts[0].xyz;
  }

  PuzzlePart& centralize()
  {
    BBox box;
    getBBox(box);
    shift(-box.minV);
    return *this;
  }
  PuzzlePart copy() const
  {
    return PuzzlePart(*this);
  }
};
ostream& operator << (ostream& os, const PuzzlePart& v)
{
  v.print();
  return os;
}

ostream& operator << (ostream& os, const vector<PuzzlePart>& v)
{
  for(vector<PuzzlePart>::const_iterator it = v.cbegin(); it != v.cend(); it++)
  {
    cout << *it;
  }
  return os;
}


void generatePuzzles(vector<PuzzlePart>& puzzles)
{
  PuzzlePart p1(1);
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,1)));
  p1.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,0),IntVector(1,1,0)));
  p1.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(0,-1,1)));
  puzzles.push_back(p1);

  PuzzlePart p2(2);
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p2.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(1,0,1)));
  p2.parts.push_back(VolPart(VolPart::Angle,IntVector(1,1,0),IntVector(0,1,1)));
  puzzles.push_back(p2);


  PuzzlePart p3(3);
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,1)));
  p3.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(1,0,1)));
  p3.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,0),IntVector(-1,0,-1)));
  puzzles.push_back(p3);


  PuzzlePart p4(4);
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,1)));
  p4.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(0,-1,-1)));
  p4.parts.push_back(VolPart(VolPart::Angle,IntVector(0,2,0),IntVector(-1,1,0)));
  puzzles.push_back(p4);


  PuzzlePart p5(5);
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p5.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(0,1,1)));
  p5.parts.push_back(VolPart(VolPart::Angle,IntVector(0,2,0),IntVector(-1,1,0)));
  puzzles.push_back(p5);


  PuzzlePart p6(6);
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p6.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(1,0,1)));
  p6.parts.push_back(VolPart(VolPart::Angle,IntVector(0,2,0),IntVector(0,1,1)));
  puzzles.push_back(p6);


  PuzzlePart p7(7);
  p7.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p7.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,1)));
  p7.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(0,-1,-1)));
  p7.parts.push_back(VolPart(VolPart::Angle,IntVector(1,1,0),IntVector(0,1,1)));
  puzzles.push_back(p7);


  PuzzlePart p8(8);
  p8.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p8.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p8.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(1,0,1)));
  p8.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,1),IntVector(0,1,1)));
  puzzles.push_back(p8);

}
void generateSomaPuzzles(vector<PuzzlePart>& puzzles)
{
  PuzzlePart p1(1);
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,1)));
  puzzles.push_back(p1);

  PuzzlePart p2(2);
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,1)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  puzzles.push_back(p2);


  PuzzlePart p3(3);
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,1)));
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  puzzles.push_back(p3);


  PuzzlePart p4(4);
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(2,1,0)));
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  puzzles.push_back(p4);


  PuzzlePart p5(5);
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(0,2,0)));
  puzzles.push_back(p5);


  PuzzlePart p6(6);
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(2,0,0)));
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(2,1,0)));
  puzzles.push_back(p6);


  PuzzlePart p7(7);
  p7.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p7.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p7.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  puzzles.push_back(p7);
}

void generatePuzzles2(vector<PuzzlePart>& puzzles)
{
  PuzzlePart p1(1);
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p1.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,0),IntVector(0,1,-1)));
  puzzles.push_back(p1);

  PuzzlePart p2(2);
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,1)));
  p2.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,1),IntVector(-1,0,1)));
  puzzles.push_back(p2);


  PuzzlePart p3(3);
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,1)));
  p3.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,0),IntVector(1,1,0)));
  p3.parts.push_back(VolPart(VolPart::Angle,IntVector(1,0,1),IntVector(1,0,-1)));
  puzzles.push_back(p3);
}
typedef vector<vector<vector<VolPart> > > BOX;


ostream& operator << (ostream& os, const BOX& v)
{
  int dimX = v.size();
  int dimY = v[0].size();
  int dimZ = v[0][0].size();
  for(int x = dimX - 1; x >= 0; x--)
  {
    for(int z = dimZ - 1; z >= 0; z--)
    {
      for(int y = 0; y <= dimY - 1; y++)
      {
        VolPart::VolType t = v[x][y][z].fillInfo;
        char s = t == VolPart::Empty ? ' ' : t == VolPart::Full ? 178 : 176;
        //cout << v[i][j][k];
        cout << s;
      }
      cout << endl;
    }
      cout << endl << endl;
  }
  return os;
}

void initBox(BOX& volume,int dimX,int dimY,int dimZ)
{
  for (int x = 0; x <= dimX + 1; x++)
  {
    volume.push_back(vector<vector<VolPart> >());
    for (int y = 0; y <= dimY + 1; y++)
    {
      volume[x].push_back(vector<VolPart>());
      for (int z = 0; z <= dimZ + 1; z++)
      {
        bool isWall = !(x % (dimX + 1)) || !(y % (dimY + 1)) || !(z % (dimZ + 1));
        volume[x][y].push_back(VolPart(isWall ? VolPart::Full : VolPart::Empty,IntVector(x,y,z),IntVector(0,0,0),isWall));
      }
    }
  }
}

struct Solver
{
  int dimX, dimY, dimZ;
  vector<PuzzlePart> solution;
  BOX box;
  int numPlaced;
  vector<PuzzlePart> puzzles;
  int progress;
  int maxSol;
//  Solver():numPlaced(0),progress(0),maxSol(0),dimX(3),dimY(4),dimZ(2)
  Solver():numPlaced(0),progress(0),maxSol(0),dimX(3),dimY(3),dimZ(3)
  {
    initBox(box,dimX,dimY,dimZ);
//    generatePuzzles(puzzles);
    generateSomaPuzzles(puzzles);
    cout << puzzles;
  }
  void remove(const PuzzlePart& part)
  {
    for(unsigned i = 0; i < part.parts.size(); i++)
    {
      const VolPart& vol = part.parts[i];
      box[vol.xyz[0]][vol.xyz[1]][vol.xyz[2]] -= vol;
    }
    numPlaced--;
  }
  void place(const PuzzlePart& part, BOX& b)
  {
    for(unsigned i = 0; i < part.parts.size(); i++)
    {
      const VolPart& vol = part.parts[i];
      b[vol.xyz[0]][vol.xyz[1]][vol.xyz[2]] += vol;
    }
    numPlaced++;
    return;
  }
  bool couldPlace(const PuzzlePart& part, bool& matched)
  {
    matched = false;
    for(unsigned i = 0; i < part.parts.size(); i++)
    {
      const VolPart& vol = part.parts[i];
      if (!box[vol.xyz[0]][vol.xyz[1]][vol.xyz[2]].couldPlace(vol)) return false;

      if (matched) continue;
      matched = matched || box[vol.xyz[0]][vol.xyz[1]][vol.xyz[2]].shareOneOfSides(vol);

      matched = matched || box[vol.xyz[0]-1][vol.xyz[1]][vol.xyz[2]].shareOneOfSides(vol);
      matched = matched || box[vol.xyz[0]+1][vol.xyz[1]][vol.xyz[2]].shareOneOfSides(vol);
      if (matched) continue;

      matched = matched || box[vol.xyz[0]][vol.xyz[1]-1][vol.xyz[2]].shareOneOfSides(vol);
      matched = matched || box[vol.xyz[0]][vol.xyz[1]+1][vol.xyz[2]].shareOneOfSides(vol);
      if (matched) continue;

      matched = matched || box[vol.xyz[0]][vol.xyz[1]][vol.xyz[2]-1].shareOneOfSides(vol);
      matched = matched || box[vol.xyz[0]][vol.xyz[1]][vol.xyz[2]+1].shareOneOfSides(vol);
    }
    return true;
  }
  bool isSqueezed(const VolPart& vol) const
  {
    if (vol.fillInfo != VolPart::Angle) return false;
    BREAK_ON_LINE(!vol.dir[0] || !vol.dir[1] || !vol.dir[2]);
    int n = 0;
    if (vol.dir[0] != 0)
    {
      const VolPart& nVol = box[vol.xyz[0]+vol.dir[0]][vol.xyz[1]][vol.xyz[2]];
      if (nVol.fillInfo == VolPart::Full)
      {
        n++;
      }
      else if (nVol.fillInfo == VolPart::Angle)
      {
        if (vol.dir[0] * nVol.dir[0] >= 0)
        {
          n++;
        }
      }
    }
    if (vol.dir[1] != 0)
    {
      const VolPart& nVol = box[vol.xyz[0]][vol.xyz[1]+vol.dir[1]][vol.xyz[2]];
      if (nVol.fillInfo == VolPart::Full)
      {
        n++;
      }
      else if (nVol.fillInfo == VolPart::Angle)
      {
        if (vol.dir[1] * nVol.dir[1] >= 0)
        {
          n++;
        }
      }
    }
    if (vol.dir[2] != 0)
    {
      const VolPart& nVol = box[vol.xyz[0]][vol.xyz[1]][vol.xyz[2]+vol.dir[2]];
      if (nVol.fillInfo == VolPart::Full)
      {
        n++;
      }
      else if (nVol.fillInfo == VolPart::Angle)
      {
        if (vol.dir[2] * nVol.dir[2] >= 0)
        {
          n++;
        }
      }
    }
    return n>1;
  }
  bool isSqueezedV2(const VolPart& vol) const
  {
    if (vol.fillInfo != VolPart::Angle) return false;

    BREAK_ON_LINE(dot(vol.dir,vol.dir) == 2);
    int n = 0;
    if (vol.dir[0] > 0)
    {
      const VolPart& nVol = box[vol.xyz[0]+1][vol.xyz[1]][vol.xyz[2]];
      if (nVol.fillInfo == VolPart::Full)
      {
        n++;
      }
      else if (nVol.hasSide(0,0)) n++;
    }
    if (vol.dir[0] < 0)
    {
      const VolPart& nVol = box[vol.xyz[0]-1][vol.xyz[1]][vol.xyz[2]];
      if (nVol.fillInfo == VolPart::Full || nVol.hasSide(0,1))
      {
        n++;
      }
    }

    if (vol.dir[1] > 0)
    {
      const VolPart& nVol = box[vol.xyz[0]][vol.xyz[1]+1][vol.xyz[2]];
      if (nVol.fillInfo == VolPart::Full || nVol.hasSide(1,0))
      {
        n++;
      }
    }
    if (vol.dir[1] < 0)
    {
      const VolPart& nVol = box[vol.xyz[0]][vol.xyz[1]-1][vol.xyz[2]];
      if (nVol.fillInfo == VolPart::Full || nVol.hasSide(1,1))
      {
        n++;
      }
    }

    if (vol.dir[2] > 0)
    {
      const VolPart& nVol = box[vol.xyz[0]][vol.xyz[1]][vol.xyz[2]+1];
      if (nVol.fillInfo == VolPart::Full || nVol.hasSide(2,0))
      {
        n++;
      }
    }
    if (vol.dir[2] < 0)
    {
      const VolPart& nVol = box[vol.xyz[0]][vol.xyz[1]][vol.xyz[2]-1];
      if (nVol.fillInfo == VolPart::Full || nVol.hasSide(2,1))
      {
        n++;
      }
    }

    return n > 1;
  }
  bool hasSqueezed(const PuzzlePart& part) const
  {
    BBox bbox;
    part.getBBox(bbox);
    bbox.grow();

    for(int x = bbox.minV[0]; x <= bbox.maxV[0];x++)
    {
      for(int y = bbox.minV[1]; y <= bbox.maxV[1];y++)
      {
        for(int z = bbox.minV[2]; z <= bbox.maxV[2];z++)
        {

//          if (isSqueezed(box[x][y][z])) return true;
          BREAK_ON_LINE(isSqueezed(box[x][y][z]) == isSqueezedV2(box[x][y][z]));
          if (isSqueezedV2(box[x][y][z])) return true;
        }
      }
    }
    return false;
  }
  bool tryToPlace(const PuzzlePart& part)
  {
    bool matched;
    if (!couldPlace(part,matched))
    {
      return false;
    }
    if (numPlaced && !matched)
    {
      return false;
    }
    place(part,box);
    if (hasSqueezed(part))
    {
      remove(part);
      return false;
    }
    return true;
  }
  bool checkHalf(const VolPart& vol) const
  {
    int x = vol.xyz[0];
    int y = vol.xyz[1];
    int z = vol.xyz[2];
    return 
      box[x-1][y][z].fillInfo == VolPart::Angle && box[x-1][y][z].dir[0]>0 ||
      box[x+1][y][z].fillInfo == VolPart::Angle && box[x+1][y][z].dir[0]<0 ||
      box[x][y-1][z].fillInfo == VolPart::Angle && box[x][y-1][z].dir[1]>0 ||
      box[x][y+1][z].fillInfo == VolPart::Angle && box[x][y+1][z].dir[1]<0 ||
      box[x][y][z-1].fillInfo == VolPart::Angle && box[x][y][z-1].dir[2]>0 ||
      box[x][y][z+1].fillInfo == VolPart::Angle && box[x][y][z+1].dir[2]<0;
  }
  bool hasTwoEmpty() const
  {
    for (int x = 1; x <= dimX; x++)
    {
      for (int y = 1; y <= dimY; y++)
      {
        for (int z = 1; z <= dimZ; z++)
        {
          if(box[x][y][z].fillInfo == VolPart::Empty && checkHalf(box[x][y][z]) &&(
            box[x+1][y][z].fillInfo == VolPart::Empty && checkHalf(box[x+1][y][z]) ||
            box[x][y+1][z].fillInfo == VolPart::Empty && checkHalf(box[x][y+1][z]) ||
            box[x][y][z+1].fillInfo == VolPart::Empty && checkHalf(box[x][y][z+1])
            ))
            return true;
        }
      }
    }
    return false;
  }
  vector<vector<PuzzlePart> > solutions;

  vector<PuzzlePart> getOrdered(const vector<PuzzlePart >& sol)
  {
    vector<PuzzlePart> ordered;
    for(unsigned i = 1; i<=puzzles.size();i++)
    {
      for(unsigned j = 0; j<sol.size();j++)
      {
        if (sol[j].number == i) ordered.push_back(sol[j]);
      }
    }
    return ordered;
  }

  bool verifyAlgorithm()
  {
    BOX tt;
    initBox(tt,dimX,dimY,dimZ);
    int n = numPlaced;
    for(unsigned i =0; i < solution.size(); i++)
    {
      place(solution[i],tt);
    }
    numPlaced = n;
    return tt == box;
  }

  bool newSolution()
  {
    vector<PuzzlePart> sol = getOrdered(solution);

    for(unsigned iSol = 0; iSol < solutions.size(); iSol ++)
    {
      if (solutions[iSol].size() != sol.size() && sol.size()) continue;

      vector<PuzzlePart>& prevSol = solutions[iSol];
      for(unsigned i=0;i<prevSol.size();i++)
      {
        if (prevSol[i].number != sol[i].number) continue;
      }

      Mat rot1 = prevSol[0].getLCS();
      Mat rot2 = sol[0].getLCS();

      Mat res = rot2 * rot1.inverse();
      IntVector prevShift = -prevSol[0].getZero();
      IntVector shift = sol[0].getZero();

      bool theSame = true;

      for(unsigned i=0;i<sol.size();i++)
      {
        PuzzlePart p = prevSol[i];
        
        p.shift(prevShift).rotate(res).shift(shift);
        theSame = theSame && p == sol[i];
        if (!theSame) break;
      }

      if (theSame)
      {
        return false;
      }
    }
    solutions.push_back(sol);
    return true;
  }
  void drawSolution(const vector<PuzzlePart>& s) const
  {
    for (unsigned i = 0; i < s.size(); i++)
    {
      cout << ( i > 0 ? "," : "") << s[i].number;
    }
    cout << endl << box;
  }
  bool tryToShow()
  {
    maxSol = numPlaced;
    if (newSolution())
    {
      cout << "Solution number " << solutions.size() << ":"<< endl;
      cout << "Number of figures is " << numPlaced << ":"<< endl;
      cout << solutions[solutions.size()-1] << endl;
      drawSolution(solutions[solutions.size()-1]);
      return true;
    }
    return false;
  }

  void solve()
  {
    BREAK_ON_LINE(verifyAlgorithm());
//     if (maxSol<numPlaced && (numPlaced < puzzles.size() - 1) || numPlaced == puzzles.size() - 1 && hasTwoEmpty())
//     {
//       tryToShow();
//     }
    if (numPlaced == puzzles.size())
    {
      tryToShow();
      return;
    }
    for(unsigned iPuzzle = 0; iPuzzle <puzzles.size(); iPuzzle ++)
    {
      if (puzzles[iPuzzle].busy) continue;

      if (false && numPlaced == 1 && progress< 1003 ) 
      {
        cout <<++progress<<endl;
        return;
      }
      puzzles[iPuzzle].busy = true;

      PuzzlePart part = puzzles[iPuzzle];
      for (int i = 0; i < 6; i++)
      {
        if (i < 4)
        {
          part.rotate(RotateY);
        }
        else if (i == 4)
        {
          part.rotate(RotateX);
        }else
        {
          part.rotate(RotateX);
          part.rotate(RotateX);
        }
        PuzzlePart part2 = part;
        for (int j = 0; j < 4; j++)
        {
          part2.rotate(RotateZ).centralize();
          BBox boundaries;
          part2.getBBox(boundaries);
          int xmax = dimX - boundaries.maxV[0];
          int ymax = dimY - boundaries.maxV[1];
          int zmax = dimZ - boundaries.maxV[2];

          if (xmax < 1 || ymax < 1 || zmax < 1 ) continue;
          
          if (numPlaced == 0)
          {
            xmax = xmax / 2 + 1;
            ymax = ymax / 2 + 1;
            zmax = zmax / 2 + 1;
          }
          

          for(int x = 1; x <= xmax;x++)
          {
            for(int y = 1; y <= ymax;y++)
            {
              for(int z = 1; z <= zmax;z++)
              {
                PuzzlePart part3 = part2;
                part3.shift(IntVector(x,y,z));
                if (tryToPlace(part3))
                {
                  solution.push_back(part3);
                  solve();
                  remove(part3);
                  solution.pop_back();
                }
              }
            }
          }
        }
      }
      puzzles[iPuzzle].busy = false;
      if (numPlaced == 0) return; //first figure only once should be checked
      if (numPlaced == 1) 
      {
        cout <<++progress<<endl;
      }
    }
  }
};

void makeTests(Solver& solver)
{
  BREAK_ON_LINE(IntVector(0,0,1).rotate(RotateX) == IntVector(0,1,0));
  BREAK_ON_LINE(IntVector(0,0,1).rotate(RotateX).rotate(RotateX) == IntVector(0,0,-1));

  BREAK_ON_LINE(IntVector(1,0,0).rotate(RotateY) == IntVector(0,0,1));
  BREAK_ON_LINE(IntVector(1,0,0).rotate(RotateY).rotate(RotateY) == IntVector(-1,0,0));

  BREAK_ON_LINE(IntVector(0,1,0).rotate(RotateZ) == IntVector(1,0,0));
  BREAK_ON_LINE(IntVector(0,1,0).rotate(RotateZ).rotate(RotateZ) == IntVector(0,-1,0));


  PuzzlePart part = solver.puzzles[0];
  part.rotate(RotateX);
  part.centralize();

  PuzzlePart p1(1);
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,1)));
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p1.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,0),IntVector(1,0,-1)));
  p1.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,1),IntVector(0,1,1)));

  bool areEqual = part == p1;
  BREAK_ON_LINE(areEqual);

  Mat m(IntVector(0,-1,0),IntVector(0,0,1),IntVector(1,0,0));
  Mat r = m * m.inverse();
  Mat e(IntVector(1,0,0),IntVector(0,1,0),IntVector(0,0,1));
  BREAK_ON_LINE(r == e);
  IntVector v = e * IntVector(-1,1,2);
  BREAK_ON_LINE(v == IntVector(-1,1,2));
}

void solvePuzzle()
{
  Solver solver;

  //makeTests(solver);

  solver.solve();

  cout << "Press any key to exit..."<<flush;
  cin.get();
}