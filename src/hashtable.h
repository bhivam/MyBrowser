#ifndef _HASHTABLE_H
#define _HASHTABLE_H

typedef struct htable
{
    char **vstr_table;
    int *vint_table;
} htable;

typedef enum table_type
{
    STRING_VALUE,
    INT_VALUE
} table_type;

int put(char *val, htable *hash_table);
int put(int val, htable *hash_table);

char *get(int key, htable *hash_table);
int get(char *key, htable *hash_table);

void free_table(htable *hashtable);
htable *malloc_table(table_type type);

#endif