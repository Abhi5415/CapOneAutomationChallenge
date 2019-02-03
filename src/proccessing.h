#ifndef PROCCESSING
#define PROCCESSING
#include <string>
#include <stack>
using namespace std;

struct Data
{
  int totalLines;
  int singleLines;
  int multiLines;
  int blocks;
  int todo;
};

struct Lang
{
  string singleLine;
  string openMulti;
  string closeMulti;
  int type;
};

bool hasPreceeding(string line, int index);

int checkValidIndex(string line, string commentType);

void countCommentDif(string line, Data &info, stack<int> &comments, Lang lang);

void countCommentSame(string line, Data &info, stack<int> &comments, Lang lang);

void printResults(Data &info);

void identifyLanguage(Lang &lang, string inputFile);

#endif PROCCESSING