#include "common.h"

/* Save in this form
----------------------------------------------------
|   #index;word;file_count;filename;word_count;#   |
----------------------------------------------------
*/

int save_database(hash_t *arr, char *backup_filename)
{
    char *filename = malloc(strlen(backup_filename));
    int i = 0;

    // Validate .txt extension
    char *str = strchr(backup_filename, '.');
    if (str != NULL && !strcmp(str, ".txt"))
    {
        filename = backup_filename;
    }
    else                // If not create a file with .txt extension with the user provided filename
    {
        while (backup_filename[i] != '.')
        {
            filename[i] = backup_filename[i];
            i++;
        }
        filename[i] = '\0';
        filename = strcat(filename, ".txt");
    }

    // Create a new backup file
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("\n<--- Error creating file --->\n");
        return FAILURE;
    }

    // Encode Magic String
    fprintf(fp,"%s",MAGIC_STRING);

    for (int i = 0; i < 28; i++)
    {
        if (arr[i].main_link)
        {
            main_node *temp = arr[i].main_link;
            while (temp)
            {
                fprintf(fp, "#%d;%s;%d;", i, temp->word, temp->file_count);

                sub_node *sub_temp = temp->sub_link;
                while (sub_temp)
                {
                    fprintf(fp, "%s;%d;", sub_temp->file_name, sub_temp->word_count);
                    sub_temp = sub_temp->sub_link;
                }
                temp = temp->main_link;
                fprintf(fp, "#\n");
            }
        }
    }

    fclose(fp);
    printf("\n<--- Database saved successfully in the name of \"%s\" --->\n",filename);

    return SUCCESS;
}