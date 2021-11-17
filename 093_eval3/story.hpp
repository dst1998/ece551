#include <vector>

#include "page.hpp"
class Story {
 private:
  int win;
  int lose;
  size_t pageNum;
  std::vector<int> BeReferencedVec;
  std::vector<Page> vecPages;

 public:
  //default constructor
  Story();
  // get the number of total pages and initialize the BeReferencedVec.
  void GetPageNum(char * directory);
  //check errors of one page, exit if have any error.
  void CheckOnePage(const char * filename);
  //check all pages of the story.
  void CheckPages(char * directory);
  //read whole story after checking.
  void ReadStory();
};
