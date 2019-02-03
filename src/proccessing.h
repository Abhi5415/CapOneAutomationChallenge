#ifndef PROCCESSING
#define PROCCESSING
#include <string>
#include <stack>
using namespace std;

struct Comments
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

// @summary: checks if a given index has any preceeding characters in a string
// @params: line_ line to be checked
// @params: index_ before to be checked
// @return: whether a character exists before index
bool hasPreceeding(string line, int index);

// @summary: checks for the first valid instance of a string not in quotes
// @params: line_ line to be checked
// @params: commentType_ string to check for
// @return: the starting index of where that string is found
int checkValidIndex(string line, string commentType);

// @summary: updates the number of comments for languages with mutli and single line comments
// @params: line_ line to be checked
// @params: &info_ Comments struct to be updated
// @params: &comments_ comments stack with previous comment data
// @params: lang_ language and commenting data
void countCommentDif(string line, Comments &info, stack<int> &comments, Lang lang);

// @summary: updates the number of comments for languages with only single line comments
// @params: line_ line to be checked
// @params: &info_ Comments struct to be updated
// @params: &comments_ comments stack with previous comment data
// @params: lang_ language and commenting data
void countCommentSame(string line, Comments &info, stack<int> &comments, const Lang lang);

// @summary: prints comment data in the desired format
// @params: &info_ Comments struct to be used
void printResults(Comments &info);

// @summary: identifies language and sets up commenting strings in the Lang obj
// @params: &lang_ language data to be updated
// @params: inputFile_ file name used for its extension
void identifyLanguage(Lang &lang, const string inputFile);

#endif PROCCESSING