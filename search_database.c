#include "common.h"

int search_database(hash_t *arr, char *search_word)
{
    // Find the index

    int idx;

    if (search_word[0] >= '0' && search_word[0] <= '9')
        idx = 26;
    else if (search_word[0] >= 'A' && search_word[0] <= 'Z')
        idx = search_word[0] - 'A';
    else if (search_word[0] >= 'a' && search_word[0] <= 'z')
        idx = search_word[0] - 'a';
    else
        idx = 27;

    if (arr[idx].main_link)
    {
        main_node *temp = arr[idx].main_link;
        while (temp)
        {
            if (strcmp(temp->word, search_word) == 0) // If word matches
            {
                printf("\nWord : %s\nFile count : %d\n", temp->word, temp->file_count);
                sub_node *sub_temp = temp->sub_link;
                while (sub_temp)   // Traverse through all the sub nodes available
                {
                    printf("\t\tFile name : %s  ------>  Word count : %d\n", sub_temp->file_name, sub_temp->word_count);
                    sub_temp = sub_temp->sub_link;
                }
                printf("\n");

                return SUCCESS;
            }
            temp = temp->main_link;
        }

        return FAILURE;
    }

    return FAILURE;
}