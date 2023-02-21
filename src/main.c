#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../include/utils.h"

#define BUFFER_SIZE 4096

/*

The goal is to write some code which can represent a tree of DOM text nodes and elements

To achieve this, we will want to create a struct which can aptly represent an element.

*/

typedef enum
{
    DIV,
    P,
    HTML,
    HEAD,
    TITLE,
    BODY,
    ROOT,
    nulltype
} element_type;

typedef struct element
{
    // We want the element type, and a list of elements.
    element_type type;
    struct element **elements;
    struct element *parent;
    int num_elements;
    char *text;
} element;

char *read_file(int fd)
{
    char read_buffer[BUFFER_SIZE];
    memset(read_buffer, 0, BUFFER_SIZE);

    char *file_text = malloc(sizeof(char));

    int bytes_read = 0;
    int current_size = 0;

    while ((bytes_read = read(fd, read_buffer, BUFFER_SIZE - 1)) > 0)
    {
        // increase the size of file_text by the number of bytes read
        file_text = realloc(file_text, sizeof(char) * (current_size + bytes_read));
        // move the text from the buffer to the newly allocated space in file text
        memmove(file_text + current_size, read_buffer, bytes_read);
        // increase the size of file text by the number of bytes read into the buffer
        current_size = current_size + bytes_read;

        // setting the entries of read_buffer to zero to avoid any errors
        memset(read_buffer, 0, BUFFER_SIZE);
    }

    // adding another character and setting it to the terminating character to indicate the end of the string.
    file_text = realloc(file_text, sizeof(char) * (current_size + 1));
    file_text[current_size] = 0;
    return file_text;
}

// TODO replace this with a hashmap implementation (NO DEPENDENCIES)
element_type str2type(char *tag_text)
{
    if (strcmp(tag_text, "p") == 0)
        return P;
    else if (strcmp(tag_text, "div") == 0)
        return DIV;
    else if (strcmp(tag_text, "html") == 0)
        return HTML;
    else if (strcmp(tag_text, "head") == 0)
        return HEAD;
    else if (strcmp(tag_text, "title") == 0)
        return TITLE;
    else if (strcmp(tag_text, "body") == 0)
        return BODY;
    else
        return nulltype;
}

char *type2str (element_type tag_type)
{
    if (tag_type == P)
        return "p";
    else if (tag_type == DIV)
        return "div";
    else if (tag_type == HEAD)
        return "head";
    else if (tag_type == BODY)
        return "body";
    else if (tag_type == HTML)
        return "html";
    else if (tag_type == TITLE)
        return "title";
    else if(tag_type == ROOT)
        return "root";
    return "unkown";
}

element_type get_tag(char *html_text)
{
    int tag_len;
    for (tag_len = 0; html_text[tag_len] != '>'; tag_len++)
        continue;

    char *tag_text = malloc(sizeof(char) * tag_len + 1);
    memmove(tag_text, html_text, tag_len);
    tag_text[tag_len] = 0;

    element_type tag_type = str2type(tag_text);

    free(tag_text);
    return tag_type;
}

element *parse_html(char *html_text)
{
    element *root = malloc(sizeof(element));
    root->type = ROOT;
    root->elements = NULL;
    root->num_elements = 0;
    root->parent = NULL;
    root->text = NULL;

    int text_size = strlen(html_text);

    element *parent = root;

    for (int i = 0; i < text_size; i++)
    {
        switch (html_text[i])
        {
        case ' ':
        case '\n':
            continue;
        case '<':
        {
            if (html_text[i + 1] == '/')
                break;

            // go through and get the tag now. to be added to parent. switch this to be parent until it is knocked off.
            parent->num_elements++;
            parent->elements = realloc(parent->elements, sizeof(element *) * parent->num_elements);


            element *new_element = malloc(sizeof(element));
            new_element->type = get_tag(html_text + i + 1);
            new_element->elements = NULL;
            new_element->num_elements = 0;
            new_element->parent = parent;
            new_element->text = NULL;

            parent->elements[parent->num_elements - 1] = new_element;

            parent = new_element;

            break;
        }
        case '/':
            // when we enounter a closing tag, we will change the parent to be the parent of the current parent
            parent = parent->parent;
            break;
        default: // this is where normal text will end up.
            break;
        }
    }

    return root;
}

void free_DOM(element *root)
{
    if (root->num_elements == 0)
    {
        if (root->text != NULL)
            free(root->text);
        free(root);
        return;
    }
    for (int i = 0; i < root->num_elements; i++)
    {
        free_DOM(root->elements[i]);
    }
    free(root->elements);
    if (root->text != NULL)
        free(root->text);

    free(root);
}

void print_DOM(element *root, int level)
{
    for (int i = 0; i < level; i++)
        printf("|");
    printf("%s\n", type2str(root->type));

    for (int j = 0; j < root->num_elements; j++)
        print_DOM(root->elements[j], level+1);
}

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