#ifndef _PARSER_H
#define _PARSE_H

typedef enum element_type
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

element *parse_html(char *html_text);
void free_DOM(element *root);
void print_DOM(element *root, int level);

#endif