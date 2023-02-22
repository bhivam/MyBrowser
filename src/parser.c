#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../include/parser.h"

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

char *type2str(element_type tag_type)
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
    else if (tag_type == ROOT)
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
        print_DOM(root->elements[j], level + 1);
}