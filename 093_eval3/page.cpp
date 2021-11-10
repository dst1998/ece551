#include "page.hpp"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Page::Page() : choiceNum(0) {
}
Page::Page(size_t cn) : choiceNum(cn) {
}
//Read input file into a vector
std::vector<std::string> Page::ReadIn(const char * filename) {
  std::ifstream infile(filename);
  if (infile.fail()) {
    std::cerr << "Can't open file:" << filename << std::endl;
    exit(EXIT_FAILURE);
  }
  std::vector<std::string> vec;
  std::string str;
  while (!infile.eof()) {
    std::getline(infile, str);
    vec.push_back(str);
  }
}

//Parsing the text before and behind '#'
void Page::ParsePage(std::vector<std::string> vec) {
  //if no choices,and first line is WIN
  if (vec[0] == "WIN") {
    Page::WinPrint();
  }
  //if no choices,and first line is LOSE
  if (vec[0] == "LOSE") {
    Page::LosePrint();
  }
  //else:have choices in the page
  else {
    //get the number of choices if choices exist on the page.
    for (size_t i = 0; i < vec.size(); i++) {
      if (vec[i] == "#") {
        break;
      }
      else {
        choiceNum += 1;
      }
    }
    //get the choices vector
    std::vector<std::string> vecChoices;
    for (size_t i = 0; i < choiceNum; i++) {
      vecChoices.push_back(vec[i]);
    }
    //reformat the choice vector
    for (size_t i = 0; i < choiceNum; i++) {
      vecChoices[i] = RewriteChoice(vecChoices[i], i);
    }
  }
  //get the text part of the page
  std::vector<std::string> vecText;
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
std::string RewriteChoice(std::string str, size_t i) {
  std::string::size_type pos;  //the position (index) of ":"
  if ((pos = str.find(':')) == str.npos) {
    std::cerr << "Can't find ':' in the choice line." << std::endl;
    exit(EXIT_FAILURE);
  }
  else {
    //substr(a,b):index a included, index b not included.
    if (std::stoi(str.substr(0, pos)) <= 0) {
      std::cerr << "The page number is not a positive integer\n." << std::endl;
      exit(EXIT_FAILURE);
    }
    //if blank or letter exits in the num???????????????????
    //////////////////////////////////////////////////////
    std::string str_out = std::to_string(i + 1);
    str_out += ". ";
    str_out += str.substr(pos);
    return str_out;
  }
}
//print the text of the page.
void Page::TextPrint(std::vector<std::string> & vecText) {
  //////////////////////////////////////////////////////////////
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
void Page::ChoicesPrint(std::vector<std::string> & vecChoices) {
  std::cout << "\n"
            << "What would you like to do?\n"
            << "\n";
  std::cout << "";  ///////////////////////////////////////////////
}
