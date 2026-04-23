#include "common.h"

int print_database(hash_t *arr)
{
    for(int i=0;i<28;i++)
    {
        if(arr[i].main_link)
        {
            main_node *temp = arr[i].main_link;
            while(temp)
            {
                printf("\nWord : %s\nFile count : %d\n",temp->word,temp->file_count);
                sub_node *sub_temp = temp->sub_link;
                while(sub_temp)
                {
                    printf("\t\tFile name : %s  ------>  Word count : %d\n",sub_temp->file_name,sub_temp->word_count);
                    sub_temp = sub_temp->sub_link;
                }
                printf("\n");
                temp = temp->main_link;
            }
        }
    }

    return SUCCESS;
}