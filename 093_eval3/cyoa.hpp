#include <cstdlib>
#include <fstream>   //for open/close the input files
#include <iostream>  //for std::cout
#include <set>       //for std::set
#include <sstream>   //for std::stringstream
#include <string>    //for std::string
#include <vector>    //for std::vector
class Page {
 public:
  std::vector<std::string>
      navi_PageNum_vec;  //Each element in our vector stores exactly one NAVIGATION line(before the colon) on the given page
  std::vector<std::string>
      navi_choice_vec;  //Each elemnet in this vector stores the content after the colon in a navigation line
  std::vector<std::string> actual_text_vec;  //The text of this given page
  int result_flag;                           //1 for Win, 2 for lose, 3 for continue

  void print_page();
};
