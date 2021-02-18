#include "head.h"
#include <stdio.h>
void reset(structCases* cases){ 
    cases->alphabet_case = 0;
    cases->time_case = 0;
    cases->count_file = 1;
    cases->count_dir = 1;
    cases->file_name = malloc(sizeof(char*));
    cases->file_name[0] = ".";
    cases->error = 0;
    cases->not_found = 0;
}
structCases options(int argc, char* argv[]){
    struct stat statStruct;
    structCases cases;
    reset(&cases);
    int i, statReturn,errorCount = 0, countfile = 0, count_dir = 0;
    for(i = 1; i<argc; i++){
        // find option
        if (argv[i][0] == '-'){    
            switch (argv[i][1]){
                case 'a':
                    cases.alphabet_case = 1;
                    break;
                case 't':
                    cases.time_case = 1;
                    break;
                default:
                    printf("my_ls: invalid option -- '%c'\n", argv[i][1]);
                    // last operation if doesn't correct
                    cases.error = 1;   
                    break;
            }
        }else{      // find file_name
            statReturn = stat(argv[i], &statStruct); 
            if(statReturn!=0){
                errorCount++;
                printf("my_ls: cannot access '%s': No such file or directory\n", argv[i]);
            }else{
                if (countfile == 0){
                    free(cases.file_name);
                    cases.file_name = malloc(sizeof(char*)* (argc-1));
                }
                if(S_ISDIR(statStruct.st_mode)){    //count files
                    count_dir++;
                }
                cases.file_name[countfile++] = argv[i];
            }
        }
    }
    cases.not_found=errorCount;
    if(countfile == 0 && errorCount!=0){    
        cases.error = 1;   
    }
    if(cases.error){
        free(cases.file_name);
    }
    if(countfile>1){    
        if(cases.time_case){
            time_Sort(countfile, cases.file_name, ".");  
        }else{
            lexo_Sort(countfile,cases.file_name);
        }
        cases.count_file = countfile;
        cases.count_dir =count_dir;
    }
    return cases;   
}
int stringCompare(char* a, char*b){
    for(int i = 0; *a!='\0'|| *b!= '\0';i++, *a++, *b++){
        if(*a < *b ){
            return 1;
        }
        if(*a>*b){
            return 2;
        }
    }
    return 0;
}
int my_strlen(char* arr){
    int i;
    for(i = 0; arr[i]!= '\0';i++){

    }
    return i;
}

char* getPath(char* filename, char* dirName, char arr[]){  
    int i = 0;
    for(int j = 0; dirName[j]!= '\0'; j++){
        arr[i++] = dirName[j];
    }
    arr[i++] = '/';
    for(int j = 0;filename[j]!='\0';j++){
        arr[i++] = filename[j];
    }
    arr[i] = '\0';
    return &arr[0];
}
void swap(char** xp, char** yp) 
{
    char* temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
char** lexo_Sort (int count_file, char** file_name){     //sort by ASCII 

    int i,j,min_idx;
    for(i = 0; i < count_file - 1; i++){
        min_idx = i;
        for (j = i+1; j < count_file; j++){
            if (stringCompare(file_name[j], file_name[min_idx])==1)
                min_idx = j; 
        }
            
        // printf("%s - %s\n", file_name[i], file_name[min_idx]);
        swap(&file_name[min_idx], &file_name[i]);
    }
    return file_name;
}

char** time_Sort (int count_file, char** file_name, char* dirName){    
    struct stat statStruct1;    
    struct stat statStruct2;
    _Bool isSorted = 0;
    char arr[100];
    int i, j, k, l;
    char* temp;
    
    for(i = 0; i < count_file -1;i++){
        isSorted = 1;
        for(j = 0; j<count_file -1; j++){
            temp = getPath(file_name[j], dirName, arr);
            k = stat(temp, &statStruct1);   
            temp = getPath(file_name[j+1], dirName, arr);
            l = stat(temp, &statStruct2);
            if(statStruct1.st_mtim.tv_sec<statStruct2.st_mtim.tv_sec){
                swap(&file_name[j], &file_name[j+1]); 

            }

            else if(statStruct1.st_mtim.tv_sec==statStruct2.st_mtim.tv_sec){
                if(statStruct1.st_mtim.tv_nsec<statStruct2.st_mtim.tv_nsec){
                    swap(&file_name[j], &file_name[j+1]); 

                }
            else if(statStruct1.st_mtim.tv_nsec==statStruct2.st_mtim.tv_nsec){
                if(stringCompare(file_name[j], file_name[j+1])==2){
                    swap(&file_name[j], &file_name[j+1]); 
                }
            }
            }
        }
    }
    return file_name;
}