//This is the source file for step3
#include "cyoa.cpp"
int main(int argc, char ** argv) {
  if (argc != 2) {  //error handling
    std::cerr << "Usage: please enter one directory name!\n";
    exit(EXIT_FAILURE);
  }
  std::map<size_t, std::vector<size_t> > adj_map;
  size_t num_page = examine_whole_story(argv[1], adj_map);
  /*
  for (std::map<size_t, std::vector<size_t> >::iterator it = adj_map.begin();
       it != adj_map.end();
       it++) {
    std::cout << "For page " << it->first << ":\n";
    for (std::vector<size_t>::iterator it2 = it->second.begin(); it2 != it->second.end(); 
         it2++) {
      std::cout << "    page" << *it2 << " " << std::endl;
    }
  }
  */
  std::vector<size_t> depth_vector(
      num_page - 1, 0);  //because the returned num_page is 2+the real pages number
  std::vector<size_t> visited_vector(num_page - 1, 0);
  std::stack<std::pair<size_t, size_t> > page_stack;  //first=page second=depth
  //Now we are ready to do DFS for the given adj_map
  std::pair<size_t, size_t> p(1, 0);
  page_stack.push(p);
  while (!page_stack.empty()) {
    size_t cur_page = page_stack.top().first;
    size_t cur_depth = page_stack.top().second;
    page_stack.pop();
    std::vector<size_t> cur_neighbour = adj_map[cur_page];
    for (std::vector<size_t>::iterator it = cur_neighbour.begin();
         it != cur_neighbour.end();
         it++) {
      if (depth_vector[*it] == 0 || depth_vector[*it] > 1 + cur_depth) {
        depth_vector[*it] = cur_depth + 1;  //renew the current depth
      }
      if (visited_vector[*it] == 0) {
        std::pair<size_t, size_t> pp(*it, 1 + cur_depth);
        page_stack.push(pp);
        visited_vector[*it] = 1;
      }
    }
  }

  for (size_t i = 1; i < depth_vector.size(); i++) {
    std::cout << "Page " << i;
    if (depth_vector[i] == 0 && i != 1) {
      std::cout << " is not reachable" << std::endl;
    }
    else {
      std::cout << ":" << depth_vector[i] << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
