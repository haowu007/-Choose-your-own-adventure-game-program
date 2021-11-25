//This is the source file for step4
#include "cyoa.cpp"
int main(int argc, char ** argv) {
  if (argc != 2) {  //error handling
    std::cerr << "Usage: please enter one directory name!\n";
    exit(EXIT_FAILURE);
  }
  int flag_has_win = 0;  //this indicates if we have found at least one path to WIN
  std::map<size_t, std::vector<size_t> > adj_map;
  std::set<size_t> win_pages_set;
  size_t num_page = examine_whole_story(argv[1], adj_map, win_pages_set);

  std::vector<size_t> visited_vector(num_page - 1, 0);
  std::stack<std::pair<size_t, std::vector<std::pair<size_t, size_t> > > >
      page_stack;  //first=page second=vector<<parent_page,parent_choice>>
  //Now we are ready to do DFS for the given adj_map
  std::vector<std::pair<size_t, size_t> > path_vector;
  std::pair<size_t, std::vector<std::pair<size_t, size_t> > > p(1, path_vector);
  page_stack.push(p);
  visited_vector[1] = 1;
  while (!page_stack.empty()) {
    size_t cur_page = page_stack.top().first;
    std::vector<std::pair<size_t, size_t> > cur_path_vec = page_stack.top().second;

    page_stack.pop();
    //if current page is a Win page
    // print the current path vector
    // cannot mark it as visited (we could go to a win page more than once through different paths!)
    if (win_pages_set.count(cur_page) > 0) {  //it is a win page!!
      cur_path_vec.push_back(std::pair<size_t, size_t>(cur_page, 0));
      printPath(cur_path_vec);
      flag_has_win = 1;
    }
    else {  //it is not a win page
      std::vector<size_t> cur_neighbour = adj_map[cur_page];
      for (size_t i = 0; i < cur_neighbour.size(); i++) {
        size_t neigh_page = cur_neighbour[i];
        if (visited_vector[neigh_page] == 0) {  //avoid cycle!!
          std::vector<std::pair<size_t, size_t> > new_path_vec = cur_path_vec;
          new_path_vec.push_back(std::pair<size_t, size_t>(cur_page, i + 1));
          std::pair<size_t, std::vector<std::pair<size_t, size_t> > > pp(neigh_page,
                                                                         new_path_vec);
          page_stack.push(pp);
          visited_vector[neigh_page] = 1;
        }
      }
    }
  }
  if (flag_has_win == 0) {
    std::cout << "This story is unwinnable!" << std::endl;
  }
  return EXIT_SUCCESS;
}
