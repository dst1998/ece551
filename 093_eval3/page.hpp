#include <fstream>
#include <string>
#include <vector>
class Page {
 private:
  size_t choiceNum;
  bool win;
  bool lose;
  std::vector<std::string> vec;         //all lines from a page
  std::vector<std::string> vecText;     //text part of a page
  std::vector<std::string> vecChoices;  //choices lines of a page
  std::vector<size_t> vecRefer;         // page number of what are referred by this page

 public:
  Page();
  ~Page();
  //Read input file into a vector
  void ReadIn(const char * filename);
  //Parsing the text before and behind '#'
  void ParsePage();
  //Refomat the choice line.
  std ::string RewriteChoice(std::string str, size_t i);
  //print the text of the page.
  void TextPrint();
  //print if win
  void WinPrint();
  //print if lose
  void LosePrint();
  //print choices
  void ChoicesPrint();
  //integrate the methods to read one page
  void ReadOnePage(const char * filename);
  //add pages being referred by this page, if exists.
  void AddRefer(int toAdd);
  //get the value of win(private).
  bool GetWin();
  //get the value of lose(private).
  bool GetLose();
  //get the value of vecRefer(private).
  const std::vector<size_t> GetVecRefer();
  //get the value of vecChoices(private).
  const std::vector<std::string> GetVecChoices();
};
