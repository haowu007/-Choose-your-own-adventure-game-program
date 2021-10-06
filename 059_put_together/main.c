#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //  printf("%s is the file we are trying to count\n", filename);
  counts_t * c = createCounts();
  FILE * f = fopen(filename, "r");
  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;
  //  printf("****** Our Kv table has %d pairs in it!*******\n ", kvPairs->length);
  while ((len = getline(&line, &sz, f)) >= 0) {
    // printf("%s was the key we just read in\n", line);
    line[len - 1] = '\0';  // turn "APPLE\n" into "APPLE"
    char * value = lookupValue(kvPairs, line);

    //  printf("%s was the value we just found for %s\n", value, line);
    addCount(c, value);
    free(line);
    line = NULL;
    sz = 0;
  }
  free(
      line);  // the last time we read yet read in length 0, there was also memory allocated!!!

  if (fclose(f) != 0) {
    fprintf(stderr, "falied when closing %s\n!", filename);
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv_table = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv_table);
    //compute the output file name from argv[i] (call this outName)
    char * outname = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outname, "w");
    if (f == NULL) {
      fprintf(stderr, "falied when opening %s \n!", argv[i]);
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "filed when closing %s \n!", argv[i]);
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    freeCounts(c);
    free(outname);
  }
  //free the memory for kv
  freeKVs(kv_table);
  return EXIT_SUCCESS;
}
