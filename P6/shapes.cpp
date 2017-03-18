#include <iostream>
using namespace std;

class Shape
{
public:
  friend void operator <<(ostream& os, const Shape &rhs);
  virtual void write(ostream& os) const = 0;
}; // shape class

void operator << (ostream& os, const Shape &rhs)
{
  rhs.write(os);
}//<<

class IntersectingLines: public Shape
{
public:
  void write(ostream& os) const;
}; // Intersectoing line

void IntersectingLines::write(ostream& os) const
{
 cout << "    /\\" << endl;
 cout << "   /  \\" << endl;
 cout << "  /    \\" << endl;
 cout << " /      \\" << endl;
 cout << "/        \\" << endl;
 // cout << os;  
} // inter


class BaseLine: public Shape
{
public:
  void write(ostream& os) const;
}; // BaseLine

void BaseLine::write(ostream& os) const
{
  cout << "----------" << endl;
  // cout << os;
} // base

class ParallelLines: public Shape
{
public:
  // friend ostream& <<(ostream& os, Shape &rhs);
  void write(ostream& os) const;
}; // parallel line

void ParallelLines::write(ostream& os) const
{
  cout << "|        |" << endl;
  cout << "|        |" << endl;
  cout << "|        |" << endl;
  // cout << os;
} // para



class BlankLines: public Shape
{
public:
  // friend ostream& <<(ostream& os, Shape &rhs);
  void write(ostream &os) const;
}; // blank line

void BlankLines::write(ostream& os) const
{
  cout << "\n\n";
} // blank

class Circle: public Shape
{
public:
  // friend ostream& <<(ostream& os, Shape &rhs);
  void write(ostream &os) const;
}; // circle

void Circle::write(ostream& os) const
{
  cout << "    *" << endl;
  cout << "  *   *" << endl;
  cout << "   * *" << endl;
  // cout << os;
} // write



int main()
{
  Shape* shapes[9];
  shapes[0] = new IntersectingLines();
  shapes[1] = new BaseLine();
  shapes[2] = new ParallelLines();
  shapes[3] = new BaseLine();
  shapes[5] = new Circle();
  shapes[6] = new IntersectingLines();
  shapes[7] = new BaseLine();
  shapes[8] = new IntersectingLines();
  shapes[4] = new BlankLines();

  for (int i = 0; i < 9; i++)
  {
    cout << *shapes[i];
  }// delete [] shapes;
  
  return 0;
} // main