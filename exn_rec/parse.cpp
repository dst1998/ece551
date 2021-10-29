#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef std::pair<std::string, std::vector<std::string> > item_t;

//my exception class to handle terrible input
class invalid_input : public std::exception {
  const char * err_msg;

 public:
  invalid_input(const std::string msg) : err_msg(msg.c_str()) {}
  invalid_input(const char * msg) : err_msg(msg) {}
  virtual const char * what() const throw() { return err_msg; }
};

// prints each key and associated values
void printItems(const std::vector<item_t> & items) {
  for (std::vector<item_t>::const_iterator it = items.begin(); it != items.end(); ++it) {
    std::cout << "key = " << it->first << "\n  values = ";
    std::string delim = "";
    for (std::vector<std::string>::const_iterator it2 = it->second.begin();
         it2 != it->second.end();
         ++it2) {
      std::cout << delim << *it2;
      delim = "; ";
    }
    std::cout << std::endl;
  }
}

// for each line in file, parse to key and assoc values
item_t parseLine(const std::string & line) {
  item_t ans;
  std::size_t delim = line.find(":");
  ////////////////////////////////////////
  if (delim == std::string::npos) {                 //if no colon is found
    throw invalid_input("No colon found in line");  // no new
  }
  std::string key = line.substr(0, delim);  // name is from beg to colon
  ans.first = key;
  std::size_t end;
  // get vals, which are comma-separated
  while ((end = line.find(",", delim + 1)) != std::string::npos) {
    //if ...
    std::string val = line.substr(delim + 2, end - delim - 2);
    ans.second.push_back(val);
    delim = end;
  }
  // rest of line is last val
  std::string val = line.substr(delim + 1);
  if (val != "") {
    ans.second.push_back(val.substr(1));
  }
  return ans;
}

// reads one file
std::vector<item_t> itemsFromFile(std::ifstream & f) {
  std::vector<item_t> ans;
  std::string line;
  while (std::getline(f, line)) {
    try {
      item_t item = parseLine(line);
      ans.push_back(item);
    }
    catch (invalid_input & exc) {
      std::cerr << "Caught a bad input.\n" << exc.what() << "\n";
    }
  }
  return ans;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage: filename\n";
    return EXIT_FAILURE;
  }
  std::ifstream ifs(argv[1]);
  if (!ifs.is_open()) {
    std::cerr << "File could not be opened\n";
    return EXIT_FAILURE;
  }
  std::vector<item_t> items = itemsFromFile(ifs);
  ifs.close();
  printItems(items);
  return EXIT_SUCCESS;
}
