//This is the source file for the whole assignment
//Most functions are implemented here
#include "cyoa.hpp"  //for class Page

#include <cstdlib>
#include <fstream>   //for open/close the input files
#include <iostream>  //for std::cout
#include <map>       //for std::map
#include <sstream>   //for std::stringstream
#include <stack>     //for std::stack
#include <string>    //for std::string
#include <vector>    //for std::vector

void Page::print_page() {
  std::vector<std::string>::const_iterator it;
  for (it = actual_text_vec.begin(); it != actual_text_vec.end(); ++it) {
    std::cout << *it << std::endl;
  }
  std::cout << std::endl;  //print a blank line
  if (result_flag == 1) {  //The output corresponding to "Win"
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }
  else if (result_flag == 2) {  //The output corresponding to "Lose"
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
  else {  //The output corresponding to "Continue reading"
    std::cout << "What would you like to do?" << std::endl;
    std::cout << std::endl;  //print another blank line
    int i = 1;
    for (it = navi_choice_vec.begin(); it != navi_choice_vec.end(); ++it) {
      std::cout << " " << i++ << ". " << *it << std::endl;
    }
  }
}

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

bool parseOneChoice(Page & page,
                    std::string & cur,
                    std::map<size_t, std::vector<size_t> > & adj_map,
                    size_t page_num) {
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
  // pages_set.insert(atoi(page_num_str.c_str()));
  adj_map[page_num].push_back(atoi(page_num_str.c_str()));
  return true;
}

int ParsePage(Page & page,
              const char * filename,
              std::map<size_t, std::vector<size_t> > & adj_map,
              size_t page_num) {
  std::fstream Myfile;
  Myfile.open(filename, std::ifstream::in);
  if (Myfile.fail() == true) {  //Error handling
    //  std::cerr << "Open file failed!\n";
    return -1;  //This file does not exist;
  }
  int found_textlabel_flag = 0;  //If 1, we have seen the "#" line
  std::string cur;               //the line we are currently reading in
  std::getline(Myfile, cur);     //FIRST PART: Navigation Section-->first line
  if (cur == "WIN") {
    page.result_flag = 1;  //The User wins
    std::vector<size_t> vec;
    adj_map[page_num] = vec;
  }
  else if (cur == "LOSE") {
    page.result_flag = 2;  //The User loses
    std::vector<size_t> vec;
    adj_map[page_num] = vec;
  }
  else {
    page.result_flag = 3;  //The User shall continue reading
    if (parseOneChoice(page, cur, adj_map, page_num) == false) {
      std::cerr << "No first choice found!!\n";
      exit(EXIT_FAILURE);
    }
    while (std::getline(Myfile, cur)) {  //Parse the choices

      if (cur[0] == '#') {
        found_textlabel_flag = 1;
        break;  //Ready to parse next section
      }
      if (parseOneChoice(page, cur, adj_map, page_num) == false) {  //ERROR HANDLING
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
  if (page.result_flag == 3) {  //Not win or lose page
    return 1;
  }
  else {
    return (page.result_flag == 1) ? 2 : 3;  //if win, return 2; if lose, return 3
  }
}

int examine_whole_story(char * directory,
                        std::map<size_t, std::vector<size_t> > & adj_map) {
  std::string directory_name(directory);
  std::string prefix = directory_name;
  std::string page1_name = prefix += "/page1.txt";
  //std::set<size_t> pages_set;
  Page page;
  //  std::cout << "current page name:" << page1_name.c_str() << std::endl;
  int contain_win = 0;
  int contain_lose = 0;
  int flag_valid_page = ParsePage(page, page1_name.c_str(), adj_map, 1);
  if (flag_valid_page == 2) {
    contain_win++;
  }
  if (flag_valid_page == 3) {
    contain_lose++;
  }
  if (flag_valid_page == -1) {  //error handling
    std::cerr << "Page1 not found!!\n";
    exit(EXIT_FAILURE);
  }
  size_t num_page = 2;

  while (flag_valid_page != -1) {
    Page page;
    std::string prefix = directory_name;
    std::string cur_page_name = prefix += "/page";  //"story1/page"
    std::stringstream cur_pagenum;
    cur_pagenum << num_page;
    cur_page_name += cur_pagenum.str();  //"storyt1/page3"
    cur_page_name += ".txt";             //"story1/page3.txt"

    flag_valid_page = ParsePage(page, cur_page_name.c_str(), adj_map, num_page);
    if (flag_valid_page == 2) {
      contain_win++;
    }
    if (flag_valid_page == 3) {
      contain_lose++;
    }
    num_page++;
  }

  std::map<size_t, std::vector<size_t> >::reverse_iterator rever_it = adj_map.rbegin();
  if (rever_it->first >= num_page) {  //error handling
    std::cerr << "Page choice went out of valid range!!\n";
    exit(EXIT_FAILURE);
  }
  //output all the choices in map
  /*  for (std::map<size_t, std::vector<size_t> >::iterator it = adj_map.begin();
       it != adj_map.end();
       it++) {
    std::cout << it->first << std::endl;
  }
  */
  if (adj_map.count(1) > 0) {  //map contains page number "1"
    if (adj_map.size() != num_page - 2) {
      std::cerr << "At least one page is unreachable!\n";
      std::cout << "MAP SIZE:" << adj_map.size() << std::endl;
      std::cout << "wanted size:" << num_page - 3 << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  else {  //page 1 is not in our map

    if (adj_map.size() != num_page - 3) {
      std::cerr << "At least one page is unreachable!\n";

      exit(EXIT_FAILURE);
    }
  }
  if (contain_win == 0 || contain_lose == 0) {
    std::cerr << "Missing win or lose page!\n";
    exit(EXIT_SUCCESS);
  }
  return num_page;
}
void ReadaStory(char * directory_name, size_t num_page) {
  std::string nextpage = "1";  //We start reading from page1.
  std::string users_choice;
  size_t users_num = 0;
  int flag_valid_page = 0;
  std::map<size_t, std::vector<size_t> > pages_MAP;
  while (1) {
    Page page;
    std::string prefix = directory_name;
    std::string cur_page_name = prefix += "/page";  //"story1/page"
    cur_page_name += nextpage;                      //"storyt1/page3"
    cur_page_name += ".txt";                        //"story1/page3.txt"
    flag_valid_page = ParsePage(page, cur_page_name.c_str(), pages_MAP, 0);
    page.print_page();
    //   std::cout << "********************************" << std::endl;
    if (flag_valid_page == 2 || flag_valid_page == 3) {
      return;  //we have finished the story!
    }
    else {
      int validflag = 0;
      while (validflag == 0) {
        std::cin >> users_choice;
        users_num = (size_t)atoi(users_choice.c_str());
        if (!isPositiveNum(users_choice) || users_num > num_page - 2) {
          std::cout << "That is not a valid choice, please try again" << std::endl;
        }
        else {  //if the choice is in current page's permitted choice?
          size_t valid_size = page.navi_PageNum_vec.size();
          if (users_num <= valid_size) {
            validflag = 1;
          }
          if (validflag == 0) {
            std::cout << "That is not a valid choice, please try again" << std::endl;
          }
        }
      }
    }
    nextpage = page.navi_PageNum_vec[users_num - 1];
  }
}
