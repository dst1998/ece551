#include "page.hpp"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Page::Page() : choiceNum(0), win(false), lose(false) {
}
Page::Page(size_t cn) : choiceNum(cn), win(false), lose(false) {
}
Page::~Page() {
}
//Read input file into a vector
void Page::ReadIn(const char * filename) {
  std::ifstream infile(filename);
  if (infile.fail()) {
    std::cerr << "Can't open file: " << filename << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string str;
  while (!infile.eof()) {
    std::getline(infile, str);
    vec.push_back(str);
  }
  /*for (size_t i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << std::endl;
    }*/
}

//Parsing the text before and behind '#'
void Page::ParsePage() {
  //if no choices,and first line is WIN
  if (vec[0].compare("WIN") == 0) {
    win = true;
  }
  //if no choices,and first line is LOSE
  else if (vec[0].compare("LOSE") == 0) {
    lose = true;
  }
  //if have choices in the page
  else {
    //get the number of choices if choices exist on the page.
    for (size_t i = 0; i < vec.size(); i++) {
      if (vec[i][0] == '#') {
        break;
      }
      else {
        choiceNum += 1;
      }
    }
    //get the choices vector
    for (size_t i = 0; i < choiceNum; i++) {
      vecChoices.push_back(vec[i]);
    }
    //reformat the choice vector
    for (size_t i = 0; i < choiceNum; i++) {
      vecChoices[i] = RewriteChoice(vecChoices[i], i);
    }
  }
  //get the text part of the page
  size_t TextStartNum;  //the row that text starts.
  if (choiceNum == 0) {
    TextStartNum = 2;
  }
  else {
    TextStartNum = choiceNum + 1;
  }
  for (size_t i = TextStartNum; i < vec.size(); i++) {
    vecText.push_back(vec[i]);
  }
}
//reformat the choice line
std::string Page::RewriteChoice(std::string str, size_t i) {
  std::string::size_type pos;  //the position (index) of ":"
  if ((pos = str.find(':')) == str.npos) {
    std::cerr << "Can't find ':' in the choice line." << std::endl;
    exit(EXIT_FAILURE);
  }
  else {
    //substr(a,b):index a included, index b not included.
    int index;
    std::stringstream ssnum;
    /*std::cout
        << str.substr(0, pos)
        << std::endl; */ ////////////////////////////////////////////////////////////////
    ssnum << str.substr(0, pos);  //put string into sstream
    ssnum >> index;
    /*std::cout << "index=" << index
      << std::endl; */ //////////////////////////////////////////////////
    //if what before ":"change turn into a int, exit.
    /*if (!ssnum.good()) {
      ssnum.clear();
      std::cerr << "Not a valid integer!\n";
      exit(EXIT_FAILURE);
      }*/
    //if int index is not strictly larger than 0, exit.
    if (index <= 0) {
      std::cerr << "The page number is not a positive integer\n." << std::endl;
      exit(EXIT_FAILURE);
    }
    //if blank or letter exits in the num???????????????????
    //////////////////////////////////////////////////////
    std::stringstream ssout;
    ssout << i + 1 << ". " << str.substr(pos + 1);
    return ssout.str();
  }
}
//print the text of the page.
void Page::TextPrint() {
  for (size_t i = 0; i < vecText.size(); i++) {
    std::cout << vecText[i] << std::endl;
  }
}
//print if win
void Page::WinPrint() {
  std::cout << "Congratulations! You have won. Hooray!\n";
}
//print if lose
void Page::LosePrint() {
  std::cout << "Sorry, you have lost. Better luck next time!\n";
}
//print choices
void Page::ChoicesPrint() {
  std::cout << "\n"
            << "What would you like to do?\n"
            << "\n";
  for (size_t i = 0; i < vecChoices.size(); i++) {
    std::cout << vecChoices[i] << std::endl;
  }
}
void Page::ReadOnePage(const char * filename) {
  ReadIn(filename);
  ParsePage();
  TextPrint();
  //if no choices,and first line is WIN
  if (win == true) {
    WinPrint();
  }
  //if no choices,and first line is LOSE
  if (lose == true) {
    LosePrint();
  }
  //else:have choices in the page
  else {
    ChoicesPrint();
  }
}
