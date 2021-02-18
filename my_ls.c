#include <stdio.h>
#include "head.h"

int main(int argc, char* argv[])
{   
    structCases cases;
    cases = options(argc, argv);
    if(!cases.error){
        dir_Content(cases);
    }
    return 0;
}