#include "stdio.h"
#include "head.h"
int dir_Content(structCases cases){
    int i;
    struct stat statStruct;
    char** dirContentfiles = malloc(1000);
    for(i = 0; i<cases.count_file; i++){     //first
        stat(cases.file_name[i],&statStruct);
        if(S_ISDIR(statStruct.st_mode)){
            continue;
        }
        else{
            printf("%s\n\n", cases.file_name[i]);
        }
    }
    int j,k;
    for(i = 0; i<cases.count_file; i++){     //Sec
        stat(cases.file_name[i],&statStruct);
        if(S_ISDIR(statStruct.st_mode)){
            DIR* folder;
            struct dirent *ptr;
            folder = opendir(cases.file_name[i]);
            if(folder == NULL){
                printf("Unable to read directory\n");
            }
            j = 0;
            while((ptr = readdir(folder))!=NULL){   //get the names
                if(!cases.alphabet_case){
                    if(ptr->d_name[0] == '.'){
                        continue;
                    }
                }
                dirContentfiles[j] = ptr->d_name;   
                j++;
            }
            if(cases.time_case){
                time_Sort(j, dirContentfiles,cases.file_name[i]); //sort
            }else{
                lexo_Sort(j, dirContentfiles);
            }
            if(j!=0 && cases.count_dir+cases.not_found>1 ){
                printf("%s:\n", cases.file_name[i]);
            }
            for(k = 0; k<j;k++){
                printf("%s  ", dirContentfiles[k]);
            }
            if(i!= cases.count_file-1){
                printf("\n\n");   
            }
            closedir(folder);
        }
    }
    free(dirContentfiles);
    return 0;
}