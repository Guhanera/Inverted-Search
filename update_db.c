#include "common.h"

int update_database(file_node **bf_head, file_node *f_head, hash_t *arr, char *backup_filename)
{
    // Validate .txt extension
    char *str = strchr(backup_filename, '.');

    if (str != NULL && !strcmp(str, ".txt"))
    {
        // Open the backup file in READ mode
        FILE *fp = fopen(backup_filename, "r");
        if (fp == NULL)
        {
            printf("File doesn't exist\n");
            return FAILURE;
        }

        // Validate Magic String
        char m_str[4];
        if (fread(m_str, 1, 3, fp) != 3)
        {
            printf("Error reading magic string\n");
            return FAILURE;
        }
        m_str[3] = '\0';
        if (strcmp(m_str, MAGIC_STRING) != 0)
        {
            printf("Magic String mismatch\n");
            fclose(fp);
            return FAILURE;
        }

        int idx;
        char word[50];
        int file_count;

        while ((fscanf(fp, "#%d;%[^;];%d;", &idx, word, &file_count)) == 3)
        {
            // Create a main node
            main_node *new = malloc(sizeof(main_node));
            if (!new)
            {
                printf("Error allocating memory\n");
                return FAILURE;
            }

            new->word = strdup(word);
            new->file_count = 0;
            new->main_link = NULL;
            new->sub_link = NULL;

            sub_node *prev = NULL;

            if (arr[idx].main_link == NULL)
            {
                arr[idx].main_link = new;
            }
            else
            {
                main_node *temp = arr[idx].main_link;
                main_node *main_prev = NULL;
                int word_found = 0;

                while (temp)
                {
                    // Check whether the word is already present or not in the Database
                    if (strcmp(temp->word, word) == 0)
                    {
                        word_found = 1;
                        break;
                    }
                    main_prev = temp;
                    temp = temp->main_link;
                }

                // If the word is present traverse to the final sub link
                if (word_found)
                {
                    free(new);

                    sub_node *cur = temp->sub_link;

                    if (cur)
                    {
                        while (cur->sub_link)
                        {
                            cur = cur->sub_link;
                        }
                        prev = cur;
                    }
                    else
                    {
                        prev = NULL;
                    }

                    new = temp;
                }
                else  // If word is not present link the previous main link with currently created new main node
                {
                    main_prev->main_link = new;
                }
            }

            char file_name[50];
            int word_count;

            while ((fscanf(fp, "%[^;];%d;", file_name, &word_count)) == 2)
            {
                // Insert the file in backup file list
                if (insert_file(bf_head, strdup(file_name)) == FAILURE)
                {
                    printf("Unable to allocate memory\n");
                    return FAILURE;
                }

                // Check whether the file is already present in the Database
                file_node *temp = f_head;
                int found = 0;

                while (temp)
                {
                    if (strcmp(temp->file_name, file_name) == 0)
                    {
                        found = 1;
                        break;
                    }
                    temp = temp->link;
                }

                if (found)
                {
                    char ch = fgetc(fp);
                    if (ch == '#') // Indicates the end of line or end of one word
                    {
                        fseek(fp,1,SEEK_CUR);
                        break;
                    }
                    else // safer than fseek
                    {
                        ungetc(ch, fp);
                    }
                    continue;
                }

                // Create sub node
                sub_node *sub_new = malloc(sizeof(sub_node));
                if (!sub_new)
                {
                    printf("Error allocating memory\n");
                    return FAILURE;
                }

                sub_new->file_name = strdup(file_name);
                sub_new->word_count = word_count;
                sub_new->sub_link = NULL;

                if (prev) // Link the previous sub node with current sub node
                {
                    prev->sub_link = sub_new;
                }
                else // Link the first sub node with main node
                {
                    new->sub_link = sub_new;
                }

                prev = sub_new; // Store the previous sub node

                new->file_count++;

                char ch = fgetc(fp);
                if (ch == '#') // Indicates the end of line or end of one word
                {
                    fseek(fp,1,SEEK_CUR);
                    break;
                }
                else
                {
                    ungetc(ch, fp);
                }
            }
        }

        fclose(fp);

        printf("\n<--- Database updated successfully --->\n");
        return SUCCESS;
    }

    return FAILURE;
}