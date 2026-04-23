#ifndef INV_H
#define INV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1
#define DUPLICATE 2

#define MAGIC_STRING "@23" // 3 byte Magic String

extern int empty;

typedef struct sub_node
{
    char *file_name;
    int word_count;
    struct sub_node *sub_link;
} sub_node;

typedef struct main_node
{
    char *word;
    int file_count;
    sub_node *sub_link;
    struct main_node *main_link;
} main_node;

typedef struct hash_t
{
    int index;
    main_node *main_link;
} hash_t;

typedef struct file_node
{
    char *file_name;
    struct file_node *link;
} file_node;

int initialise_database(hash_t *arr);

int validate_input(int argc, char *argv[], file_node **f_head);
int insert_file(file_node **head, char *file);
int print_file(file_node *head);


int create_database(hash_t *arr, file_node *f_head, file_node *bf_head);
int insert_word(hash_t *arr, char *word, char *file);

int search_database(hash_t *arr, char *search_word);

int save_database(hash_t *arr, char *backup_filename);

int update_database(file_node **bf_head, file_node *f_head, hash_t *arr, char *backup_filename);

int print_database(hash_t *arr);

#endif