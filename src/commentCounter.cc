#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include "proccessing.h"

bool hasPreceeding(string line, int index)
{
  if (index == 0)
    return false;
  index--;
  while (index != 0)
  {
    if (line[index] != ' ')
      return true;

    index--;
  }
  return false;
}

int checkValidIndex(string line, string commentType)
{
  vector<int> quotes;
  int occurence = 0;

  while (line.find("\"", occurence) != string::npos)
  {
    int val = (line.find("\"", occurence));
    quotes.push_back(val);
    occurence = line.find("\"", occurence);
    occurence++;
  }
  occurence = 0;
  int openQuote = 0;

  if (quotes.size() > 0)
  {
    while (line.find(commentType, occurence) != string::npos)
    {
      if (line.find(commentType, occurence) < quotes.at(openQuote) || line.find(commentType, occurence) > quotes.at(openQuote + 1))
      {
        return occurence;
      }
      openQuote += 2;
      if (quotes.size() < openQuote + 2)
        break;

      occurence = line.find(commentType, occurence);
      occurence++;
    }
    return INT_MAX;
  }
  if (line.find(commentType) != string::npos)
  {
    return line.find(commentType);
  }
  else
  {
    return INT_MAX;
  }
}

void countCommentDif(string line, Data &info, stack<int> &comments, Lang lang)
{
  if (line.length() < 0)
  {
    cerr << "Error: Line length too long." << endl;
    exit(0);
  }
  int indexOfMulti = checkValidIndex(line, lang.openMulti);
  int indexOfSingle = checkValidIndex(line, lang.singleLine);
  int indexOfCloseMulti = checkValidIndex(line, lang.closeMulti);

  if (indexOfMulti < indexOfCloseMulti && indexOfCloseMulti < INT_MAX && indexOfSingle > indexOfMulti)
  {
    info.multiLines++;
    info.blocks++;
  }

  else if (indexOfMulti < indexOfSingle)
  {
    if (comments.top() != 1)
    {
      comments.push(1);
      info.blocks++;
      if (checkValidIndex(line, "TODO") < INT_MAX)
        info.todo++;
    }
    info.multiLines++;
  }

  else if (indexOfCloseMulti < indexOfSingle)
  {
    if (comments.top() == 1)
    {
      comments.pop();
      info.multiLines++;
    }
  }

  else if (comments.top() == 1)
  {
    info.multiLines++;
    if (checkValidIndex(line, "TODO") < INT_MAX)
      info.todo++;
  }
  //
  else if (indexOfSingle < indexOfMulti && indexOfSingle < indexOfCloseMulti)
  {
    info.singleLines++;
    if (checkValidIndex(line, "TODO") < INT_MAX)
      info.todo++;
  }

  else
  {
    return;
  }
}

void countCommentSame(string line, Data &info, stack<int> &comments, Lang lang)
{
  if (line.length() < 0)
  {
    cerr << "Error: Line length too long." << endl;
    exit(0);
  }
  int index = checkValidIndex(line, lang.singleLine);

  if (index < INT_MAX)
  {
    if (comments.top() == 1)
    {
      comments.push(1);
      info.multiLines++;
      return;
    }
    else
    {
      if (!hasPreceeding(line, index))
      {
        comments.push(1);
      }
      info.singleLines++;
    }
  }
  else if (comments.top() == 1)
  {
    comments.pop();
    if (comments.top() == 1)
    {
      info.multiLines++;
      info.singleLines--;
      info.blocks++;
    }
    comments.push(0);
  }
}

void printResults(Data &info)
{
  cout << "Total # of lines: " << info.totalLines << endl;
  cout << "Total # of comment lines: " << info.singleLines + info.multiLines << endl;
  cout << "Total # of single line comments: " << info.singleLines << endl;
  cout << "Total # of comment lines within block comments: " << info.multiLines << endl;
  cout << "Total # of block line comments:" << info.blocks << endl;
  cout << "Total # of TODO’s: " << info.todo << endl;
}