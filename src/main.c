#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/utils.h"
#include "../include/parser.h"

/*

The goal is to write some code which can represent a tree of DOM text nodes and elements

To achieve this, we will want to create a struct which can aptly represent an element.

*/

int main(int argc, char **argv)
{
    /*

    We already have the element tree through which we can create this structure. Now we need a way to process the tags.
    I think the way to go will be evaluating the string we take in byte by byte, checking for <. Then we get the tag by
    just taking in the string until we get to the >. Then we create an element for it.

    We need to keep track of the current parent we are inside and popping out of parents when we reach a closing tag etc.

    Accounting for inline tags which overlap will be interesting, but we will not consider it for now
    Example: <em>This <strong>is a</em> paragraph</strong>.

    */

    if (argc != 2)
        err_n_die("requires one argument for an html file");

    int htmlfd;

    if ((htmlfd = open(argv[1], O_RDONLY)) == -1)
        err_n_die("failed to open %s", argv[1]);

    char *html_text = read_file(htmlfd);

    element *root = parse_html(html_text);

    print_DOM(root, 0);

    free(html_text);
    free_DOM(root);
    return EXIT_SUCCESS;
}