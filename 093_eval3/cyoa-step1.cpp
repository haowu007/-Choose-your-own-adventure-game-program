//This is the source file for step1
#include <cstdlib>
#include <fstream>   //for open/close the input files
#include <iostream>  //for std::cout
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

  void printThepage() {}
};
bool isPositiveNum(std::string & s) {
  size_t len = s.length();
  for (size_t i = 0; i < len; ++i) {
    if (i == 0 && s[i] == '0') {
      return false;
    }
    if (s[i] < '0' or s[i] > '9') {
      return false;
    }
  }
  return true;
}

bool parseOneChoice(Page & page, std::string & cur) {
  size_t colon_pos = cur.find(":");
  if (colon_pos == std::string::npos) {  //error handling
    std::cerr << "No colon found in this choice!\n";
    return false;
  }
  std::string page_num_str = cur.substr(0, colon_pos);
  std::string choice_str = cur.substr(colon_pos + 1);
  if (isPositiveNum(page_num_str) == false) {
    std::cerr << "Invalid Page Number for this choice!!\n";
    return false;
  }
  page.navi_PageNum_vec.push_back(page_num_str);
  page.navi_choice_vec.push_back(choice_str);
  return true;
}

void ParsePage(Page & page, char * filename) {
  std::fstream Myfile;
  Myfile.open(filename, std::ifstream::in);
  if (Myfile.fail() == true) {  //Error handling
    std::cerr << "Open file failed!\n";
    exit(EXIT_FAILURE);
  }
  int found_textlabel_flag = 0;  //If 1, we have seen the "#" line
  std::string cur;               //the line we are currently reading in
  std::getline(Myfile, cur);     //FIRST PART: Navigation Section-->first line
  if (cur == "WIN") {
    page.result_flag = 1;  //The User wins
  }
  else if (cur == "LOSE") {
    page.result_flag = 2;  //The User loses
  }
  else {
    page.result_flag = 3;  //The User shall continue reading
    if (parseOneChoice(page, cur) == false) {
      std::cerr << "No first choice found!!\n";
      exit(EXIT_FAILURE);
    }
    while (std::getline(Myfile, cur)) {  //Parse the choices

      if (cur[0] == '#') {
        found_textlabel_flag = 1;
        break;  //Ready to parse next section
      }
      if (parseOneChoice(page, cur) == false) {  //ERROR HANDLING
        std::cerr << "Invalid choice in Navigation Section!\n";
        exit(EXIT_FAILURE);
      }
    }
  }
  if (found_textlabel_flag == 0) {
    std::getline(Myfile, cur);
    if (cur[0] != '#') {
      std::cerr << "No '#' line found! Invalid format!\n";
      exit(EXIT_FAILURE);
    }
  }

  //If we reach this line of code, we have read past the # line
  while (std::getline(Myfile, cur)) {
    page.actual_text_vec.push_back(cur);
  }
  //remember to close!!
}

void print_page(Page & page) {
  std::vector<std::string>::const_iterator it;
  for (it = page.actual_text_vec.begin(); it != page.actual_text_vec.end(); ++it) {
    std::cout << *it << std::endl;
  }
  std::cout << std::endl;       //print a blank line
  if (page.result_flag == 1) {  //The output corresponding to "Win"
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }
  else if (page.result_flag == 2) {  //The output corresponding to "Lose"
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
  else {  //The output corresponding to "Continue reading"
    std::cout << "What would you like to do?" << std::endl;
    std::cout << std::endl;  //print another blank line
    int i = 1;
    for (it = page.navi_choice_vec.begin(); it != page.navi_choice_vec.end(); ++it) {
      std::cout << " " << i++ << ". " << *it << std::endl;
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {  //Error handling
    std::cerr << "Usage: Please enter one file name!\n";
    exit(EXIT_FAILURE);
  }

  Page page;
  ParsePage(page, argv[1]);
  print_page(page);
  return EXIT_SUCCESS;
}
