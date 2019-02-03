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
  // checks for and quotes in the line
  while (line.find("\"", occurence) != string::npos)
  {
    int val = (line.find("\"", occurence));
    quotes.push_back(val);
    occurence = line.find("\"", occurence);
    occurence++;
  }
  occurence = 0;
  int openQuote = 0;

  // checks if the quotes contain any of the commenting symbols
  if (quotes.size() > 0)
  {
    while (line.find(commentType, occurence) != string::npos)
    {
      if (line.find(commentType, occurence) < quotes.at(openQuote) || line.find(commentType, occurence) > quotes.at(openQuote + 1))
      {
        // verifies and returns when the comment symbol is not contained by quotes
        return occurence;
      }
      openQuote += 2;
      if (quotes.size() < openQuote + 2)
        break;

      occurence = line.find(commentType, occurence);
      occurence++;
    }
    // if comment not not found
    return INT_MAX;
  }
  if (line.find(commentType) != string::npos)
  {
    return line.find(commentType);
  }
  else
  {
    // if comment not not found
    return INT_MAX;
  }
}

void countCommentDif(string line, Comments &info, stack<int> &comments, Lang lang)
{
  // Ensures that the logic in this function will operate as expected
  if (line.length() < 0)
  {
    cerr << "Error: Line length too long." << endl;
    exit(0);
  }
  int indexOfMulti = checkValidIndex(line, lang.openMulti);
  int indexOfSingle = checkValidIndex(line, lang.singleLine);
  int indexOfCloseMulti = checkValidIndex(line, lang.closeMulti);

  // Case: for the case when multiline comments start and end on the same line
  if (indexOfMulti < indexOfCloseMulti && indexOfCloseMulti < INT_MAX && indexOfSingle > indexOfMulti)
  {
    info.multiLines++;
    info.blocks++;
  }
  // Case: if a mutliline nullifies a single line
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
  // Case: if a close multiline preceeds a single line
  else if (indexOfCloseMulti < indexOfSingle)
  {
    if (comments.top() == 1)
    {
      comments.pop();
      info.multiLines++;
    }
  }
  // Case: if a multiline comment is still open
  else if (comments.top() == 1)
  {
    info.multiLines++;
    if (checkValidIndex(line, "TODO") < INT_MAX)
      info.todo++;
  }
  // Case: a single line is not contained by a mutliline comment
  else if (indexOfSingle < indexOfMulti && indexOfSingle < indexOfCloseMulti)
  {
    info.singleLines++;
    if (checkValidIndex(line, "TODO") < INT_MAX)
      info.todo++;
  }
}

void countCommentSame(string line, Comments &info, stack<int> &comments, Lang lang)
{
  // Ensures that the logic in this function will operate as expected
  if (line.length() < 0)
  {
    cerr << "Error: Line length too long." << endl;
    exit(0);
  }

  int index = checkValidIndex(line, lang.singleLine);

  // Case: Comment is found
  if (index < INT_MAX)
  {
    // Case: Comment is found after a line that also had a comment
    if (comments.top() == 1)
    {
      comments.push(1);
      info.multiLines++;
      if (checkValidIndex(line, "TODO") < INT_MAX)
        info.todo++;
    }
    // Case: Comment is found with no preceeding comment
    else
    {
      // Case: Comment is found in line with code - does not contribute to mutliline
      if (!hasPreceeding(line, index))
      {
        comments.push(1);
      }
      info.singleLines++;
      if (checkValidIndex(line, "TODO") < INT_MAX)
        info.todo++;
    }
  }
  // Case: No comment is found after a preceeding comment
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
    if (checkValidIndex(line, "TODO") < INT_MAX)
      info.todo++;
  }
}

void printResults(Comments &info)
{
  cout << "Total # of lines: " << info.totalLines << endl;
  cout << "Total # of comment lines: " << info.singleLines + info.multiLines << endl;
  cout << "Total # of single line comments: " << info.singleLines << endl;
  cout << "Total # of comment lines within block comments: " << info.multiLines << endl;
  cout << "Total # of block line comments:" << info.blocks << endl;
  cout << "Total # of TODO’s: " << info.todo << endl;
}