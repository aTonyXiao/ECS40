#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

class Word 
{
public:
  string word;
  int value;
public:
  Word();
  Word(const Word &source, map<char, short> &valuemap);
  Word(const string& source);
  Word& operator= (const Word& rhs);
  bool operator < (const Word &rhs) const;
  bool operator == (const Word &rhs) const;
  const void setValue(const map<char, short> &valuemap);
};  // class Flight

bool Word::operator < (const Word &rhs) const
{
  return word.compare(rhs.word) < 0;
}  // operator <

bool Word::operator == (const Word &rhs) const
{
  return word.compare(rhs.word) == 0;
}  // operator <

Word::Word()
{

} // constructor


// const void Word::setValue(const map<char, short> &valuemap)
// {
//   value = 0;

//   for (unsigned i = 0; i < word.size(); i++)
//   {
//     map<char, short>::const_iterator it = valuemap.find(word.at(i));
//     value += it->second;
//   }// for
// }


Word& Word::operator= (const Word& rhs)
{
  word = rhs.word;
  value = rhs.value;
  return *this;
} // operator = 



Word::Word(const string &source)
{
  word = source;
} // constructor


Word::Word(const Word &source, map<char, short> &valuemap)
{
  word = source.word;
  value = 0;

  for (unsigned i = 0; i < word.size(); i++)
  {
    //map<char,int>::iterator it = valuemap.begin();
    map<char, short>::iterator it = valuemap.find(word.at(i));
    value += it->second;
  }// for
} // setword



void insertmap(map<char, short> &valuemap, short values[])
{
  for (int i = 0; i < 26; i++)
    valuemap.insert(pair<char, short> ('a' + i, values[i]));
} // insert the map



void setWordlist(set<Word> &wordList)
{
  ifstream inf("words.txt");
  string line;

  while (inf >> line)
  {
    if (line.size() > 7)   
      continue;

    if (line.at(0) > 'z' || line.at(0) < 'a')
      continue;
   
    // text.push_back(line);
    Word tmp(line);
    wordList.insert(tmp);
  } // while
  // set<Word>::iterator wordit = wordList.begin();

  // for (vector<string>::iterator it = text.begin(); it != text.end(); 
  //     ++it, ++wordit)
  // {
  //   Word tmp(*it);
  //   wordList.insert(tmp);  
  // } // for
} // setWordlist

// void setWordVal(set<Word> &tmpWord, map<char, short> &valuemap)
// {
//   for (set<Word>::iterator it = tmpWord.begin(); it != tmpWord.end(); it++)
//   {
//     (*it).setValue(valuemap);
//   } // for
// } // setWord


void outfunc(set<Word> &tmpWord, string &outstr)
{
  int num = 0;
  set<Word>::iterator wordit;

  if (outstr.size() > 7)
  { 
    cout << " 0 " << outstr << ": No words found.";

    return;
  }// if

  if (tmpWord.size() != 0)
  {
    for (wordit = tmpWord.begin(); wordit != tmpWord.end(); wordit++)
    {
      if (wordit->value > num)
          num = wordit->value;
    } // for get the max value

    if (num < 10)
      cout << " " << num << " " << outstr << ":";
    else //else maxvalue > 10 format
      cout << num << " " << outstr << ":";
      
    for (wordit = tmpWord.begin(); wordit != tmpWord.end(); wordit++)
    {
      if (wordit->value == num)
            cout << " " << wordit->word;
    } // for print the word
  } // if
  else // else
    cout << " 0 " << outstr << ": No words found.";
} // out func


// void run(char** argv, set<Word> &wordList, map<char, short> &valuemap)
// {
//   ifstream inf(argv[1]);
//   string line;
//   set<Word>::iterator it;
//   int num = 0;

//   while (getline(inf, line))
//   {
//     string outstr = line;
//     set<Word> tmpWord;
//     it = tmpWord.begin();
//     set<Word>::iterator wordit;
//     sort(line.begin(), line.end());
//     do
//     {
//       for (unsigned i = 1; i <= line.size(); i++)
//       {  
//         string tmpstr = line.substr(0, i);
//         Word mytmp(tmpstr);
//         wordit = find(wordList.begin(), wordList.end(), mytmp);

//         if (wordit != wordList.end())
//         {
//          Word wrdval(*wordit, valuemap);
//          tmpWord.insert(wrdval);
//          num++;
//         } // if
//       } // for
//     } while (next_permutation(line.begin(), line.end()));
//     num = 0;
//     outfunc(tmpWord, outstr);
//     cout << endl;
//   } // get line
// } // run


void run(char** argv, set<Word> &wordList, map<char, short> &valuemap)
{
  ifstream inf(argv[1]);
  string line;
  set<Word>::iterator it;
  int num = 0;

  while (getline(inf, line))
  {
    string outstr = line;
    set<Word> tmpWord;
    it = tmpWord.begin();
    set<Word>::iterator wordit;
    sort(line.begin(), line.end());
    
    do
    {
      for (unsigned i = 1; i <= line.size(); i++)
      {  
        string tmpstr = line.substr(0, i);
        Word mytmp(tmpstr);
        wordit = wordList.find(mytmp);

        if (wordit != wordList.end())
        {
         Word wrdval(*wordit, valuemap);
         tmpWord.insert(wrdval);
         num++;
        } // if
      } // for
    } while (next_permutation(line.begin(), line.end()));
    num = 0;
    outfunc(tmpWord, outstr);
    cout << endl;
  } // get line
} // run






// void readText(vector<string> &text)
// {
//   ifstream inf("words.txt");
//   string line;

//   while (inf >> line)
//   {
//     if (line.size() > 7)   
//       continue;

//     if (line.at(0) > 'z' || line.at(0) < 'a')
//       continue;
   
//     text.push_back(line);
//   } // while
// } // read text


int main(int argc, char** argv)
{
  short values[] = {1, 3, 3, 2, 1, 4, 2, 4, 2, 8, 
                   5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  map<char, short> valuemap;
  insertmap(valuemap, values);
  set<Word> wordList;
  setWordlist(wordList);
  run(argv, wordList, valuemap);

  return 0;
} // main




