#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iterator>
using namespace std;


void doInsert(vector<string> &source, ifstream& inf)
{
  string tmp;
  inf >> tmp;
  int line = atoi(tmp.c_str());
  inf >> tmp;
  int position = atoi(tmp.c_str());
  string leftpart;
  getline(inf, leftpart, '\n');
  leftpart = leftpart.substr(1, leftpart.size());
  vector<string>::iterator it = source.begin() + line;
  (*it).insert(position, leftpart);
}// doInsert


void doReplace(vector<string> &source, ifstream& inf)
{
  string tmp;
  inf >> tmp;
  int line = atoi(tmp.c_str());
  inf >> tmp;
  int start = atoi(tmp.c_str());
  inf >> tmp;
  int end = atoi(tmp.c_str());
  string leftpart;
  getline(inf, leftpart, '\n');
  leftpart = leftpart.substr(1, leftpart.size());
  vector<string>::iterator it = source.begin() + line;
  (*it).replace(start, end - start, leftpart);
} // doReplace

void doFind(vector<string> &source, ifstream& inf)
{
  int i = 0;
  std::vector<int> linenum;
  string leftpart;
  getline(inf, leftpart, '\n');
  leftpart = leftpart.substr(1, leftpart.size());

  for (vector<string>::iterator it = source.begin(); 
       it != source.end(); ++it, ++i)
  {
    std::size_t found = (*it).find(leftpart);

    if (found!=std::string::npos)
    {
      linenum.push_back(i);
    } // if
  } // for

  cout << leftpart << " ";

  for (vector<int>::iterator i = linenum.begin(); i != linenum.end(); i++)
  {
    cout << *i << " ";
  } // output

  cout << endl;
} // doFind

void doDelete(vector<string> &source, ifstream& inf)
{
  string tmp;
  inf >> tmp;
  int start = atoi(tmp.c_str());
  inf >> tmp;
  int end = atoi(tmp.c_str());
  source.erase(source.begin() + start, source.begin() + end + 1);
} // doDelete

void doErase(vector<string> &source, ifstream& inf)
{
  string leftpart;
  int i = 0;
  getline(inf, leftpart, '\n');
  leftpart = leftpart.substr(1, leftpart.size());

  for (vector<string>::iterator it = source.begin(); it != source.end(); ++it)
  {
    std::size_t found = (*it).find(leftpart);

    while (found!=std::string::npos)
    {
      // int i = (*it).compare(leftpart);
      (*it).replace(found, leftpart.size(), "");
      found = (*it).find(leftpart, found);
    }// tranversing the string
  }// tarversing all string in vector

  for (vector<string>::iterator it = source.begin(); 
       it != source.end() - 1; ++it, ++i)
  {
    if ((*it).size() == 0)
    {
      source.erase(source.begin() + i, source.begin() + i + 1);
      --it;
      --i;
    }//delete the empty line
  }//for
} // doErase

void doCopy(vector<string> &source, ifstream& inf)
{
  string tmp;
  inf >> tmp;
  int start = atoi(tmp.c_str());
  inf >> tmp;
  int end = atoi(tmp.c_str());
  inf >> tmp;
  int desti = atoi(tmp.c_str());
  source.insert(source.begin() + desti, source.begin() + start, 
                source.begin() + end + 1);
} // doCopy

void doMove(vector<string> &source, ifstream& inf)
{
  string tmp;
  inf >> tmp;
  int start = atoi(tmp.c_str());
  inf >> tmp;
  int end = atoi(tmp.c_str());
  inf >> tmp;
  int desti = atoi(tmp.c_str());
  std::vector<string> temp(source.begin() + start, 
                           source.begin() + end + 1);
  source.erase(source.begin() + start, 
               source.begin() + end + 1);

  if (desti != 0)
    source.insert(source.begin() + desti - 1,
                  temp.begin(), temp.end());
  else // else insert 0
    source.insert(source.begin() + desti,
                  temp.begin(), temp.end());
} // doMove

void modified(vector<string> &source, char **argv)
{
  char command;
  ifstream inf(argv[2]);

  while (inf >> command) //inf at end
  {
    switch(command)
      {
        case 'I': doInsert(source, inf); break;
        case 'R': doReplace(source, inf); break;
        case 'F': doFind(source, inf); break;
        case 'D': doDelete(source, inf); break;
        case 'E': doErase(source, inf); break;
        case 'C': doCopy(source, inf); break;
        case 'M': doMove(source, inf); break;
      }// switch
  }  // while
}// modified


void savefile(vector<string> &source, char ** argv)
{
  ofstream of(argv[3]);

  for (vector<string>::iterator it = source.begin(); 
       it != source.end(); ++it)
  {
    of << (*it) << endl;
  } // for
} // save file




int main(int argc, char** argv)
{
  std::vector<string> source;
  string line;
  ifstream inf(argv[1]);

  while (getline(inf, line, '\n'))
  {
    source.push_back(line);
  }  // while
  
  modified(source, argv);
  savefile(source, argv);

  return 0;
}// main fun

