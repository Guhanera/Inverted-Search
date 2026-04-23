#include "common.h"

int insert_word(hash_t *arr, char *word, char *file)
{
    // Find index

    int idx;

    if (word[0] >= '0' && word[0] <= '9')   // For digits -> idx = 26
        idx = 26;
    else if (word[0] >= 'A' && word[0] <= 'Z') // Uppercase letter
        idx = word[0] - 'A';
    else if (word[0] >= 'a' && word[0] <= 'z') // Lowercase letter
        idx = word[0] - 'a';
    else                                     // Symbols -> idx = 27
        idx = 27;

    // Create main node
    main_node *new_main = malloc(sizeof(main_node));
    if(!new_main)
    {
        printf("Error allocating memory\n");
        return FAILURE;
    }

    new_main->word = strdup(word);
    new_main->file_count = 1;
    new_main->main_link = NULL;

    // Create sub node
    sub_node *new_sub = malloc(sizeof(sub_node));
    if(!new_sub)
    {
        printf("Error allocating memory\n");
        return FAILURE;
    }

    new_sub->file_name = strdup(file);
    new_sub->word_count = 1;
    new_sub->sub_link = NULL;

    new_main->sub_link = new_sub;

    // If arr link is NULL
    if (arr[idx].main_link == NULL)
    {
        arr[idx].main_link = new_main;
        return SUCCESS;
    }

    main_node *temp = arr[idx].main_link;
    main_node *prev = NULL;

    while (temp)
    {
        prev = temp;
        if (strcmp(temp->word, word) == 0)
        {
            int flag = 0;
            sub_node *sub_temp = temp->sub_link;
            sub_node *sub_prev = NULL;

            while (sub_temp)
            {
                sub_prev = sub_temp;

                // If same word is present within the same file
                if (strcmp(sub_temp->file_name, file) == 0)
                {
                    sub_temp->word_count++;
                    flag = 1;
                    break;
                }
                sub_temp = sub_temp->sub_link;
            }

            // If the same word is present in other file
            if (!flag)
            {
                sub_node *sub_new = malloc(sizeof(sub_node));
                if(!sub_new)
                {
                    printf("Error allocating memory\n");
                    return FAILURE;
                }

                sub_new->file_name = strdup(file);
                sub_new->word_count = 1;
                sub_new->sub_link = NULL;
                temp->file_count++;

                sub_prev->sub_link = sub_new;
            }

            free(new_main->word);
            free(new_main);

            free(new_sub->file_name);
            free(new_sub);

            return SUCCESS;
        }
        temp = temp->main_link;
    }

    prev->main_link = new_main;

    return SUCCESS;
}

int create_database(hash_t *arr, file_node *f_head, file_node *bf_head)
{
    //  If valid file list is empty -> return FAILURE
    if (f_head == NULL)
    {
        printf("\n<--- No files present --->\n");
        return FAILURE;
    }


    file_node *temp = bf_head;

    while (f_head)
    {
        // Check whether file is already present in backup file list
        if(bf_head)
        {
            if(strcmp(bf_head->file_name, f_head->file_name) == 0)
            {
                f_head = f_head->link;
                bf_head = temp;
                continue;
            }
            bf_head = bf_head->link;
        }

        FILE *fp = fopen(f_head->file_name, "r");
        if (fp == NULL)
        {
            fprintf(stderr, "\nFile : \"%s\" not found\n",f_head->file_name);
            f_head = f_head->link;
            continue;
        }

        // Create Database
        char word[500];
        while (fscanf(fp, "%s", word) == 1)
        {
            insert_word(arr, word, f_head->file_name);
        }
        f_head = f_head->link;      //  Move to next valid file
        fclose(fp);

        bf_head = temp;
    }

    return SUCCESS;
}