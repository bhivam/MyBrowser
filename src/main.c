#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/utils.h"

#define BUFFER_SIZE 4096

/*

The goal is to write some code which can represent a tree of DOM text nodes and elements

To achieve this, we will want to create a struct which can aptly represent an element. 

*/


typedef enum
{
    DIV, P, HTML, HEAD, TITLE, BODY
} element_type;

typedef struct element
{
    // We want the element type, and a list of elements.
    element_type type;
    struct element *elements;
} element;


int main(int argc, char **argv)
{
    
    if (argc != 2)
        err_n_die("requires one argument for an html file");

    int htmlfd;

    if ((htmlfd = open(argv[1], O_RDONLY)) == -1)
        err_n_die("failed to open %s", argv[1]);

    
    

    return EXIT_SUCCESS;
}