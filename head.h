#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
typedef struct{
    _Bool alphabet_case; // a_case
    _Bool time_case; // t_case
    int count_file;//filecount
    int count_dir; //dircount
    char** file_name; //filenames
    int not_found; //notFound
    _Bool error; // errors
}structCases;

structCases options(int argc, char* argv[]);
void reset(structCases* cases);
char** lexo_Sort (int count_file, char** file_name); //lexographicalSort
char** time_Sort (int count_file, char** file_name, char* dirName);//timeSorting
int dir_Content(structCases cases);//dirContents
char* getPath(char* filename, char* dirName, char arr[]);