#include "common.h"

/*

<--- INVERTED SEARCH --->

-> Name : Guhan Era
-> Roll.no : 25036B_36
-> Start date : 02.04.2026
-> End date : 10.04.2026
-> Description :
    *   This project implements an inverted index-based search system to enable fast text searching
        across multiple documents. It consists of two main phases: Indexing and Querying.
    *   In the indexing phase, input files are processed to extract words and store them along with file
        details using data structures like linked lists or hashing. This information is saved as a database file.
    *   In the querying phase, user input is searched against the indexed data to quickly identify and
        display the most relevant files based on word matches.
    *   The project follows a structured flow where input files are first validated and stored in a linked list and a
        hash table is then initialized to efficiently store indexed words.
    *   Using a menu-driven approach, the user can create the database by indexing words from files, display the
        stored data, search for specific words, save the database to a file, and update it when needed.
    *   The system uses hashing along with linked lists to ensure fast and efficient storage and retrieval
        of data.
*/

int main(int argc, char *argv[])
{
    hash_t arr[28];
    file_node *f_head = NULL;           // Valid file list
    file_node *bf_head = NULL;          // Backup files list

    if (validate_input(argc, argv, &f_head) == FAILURE)
    {
        printf("\n<--- Invalid arguments --->\n\n");
        return FAILURE;
    }

    initialise_database(arr);

    int option;
    printf("\n1. Create Database\n2. Display Database\n3. Search Database\n4. Save Database\n5. Update Database\n0. Exit");

    int create_flag = 0;
    int update_flag = 0;

    while (1)
    {
        printf("\nEnter your option : ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            //   Check whether Database already exist
            if(create_flag)
            {
                printf("\n<--- Database already exist --->\n");
                break;
            }
            if (create_database(arr, f_head, bf_head) == FAILURE)
            {
                printf("\n<--- Error creating database --->\n");
                return FAILURE;
            }
            create_flag = 1;
            printf("\n<---- Database created successfully ---->\n");

            break;

        case 2:
            //  Check whether the database is empty

            if(!create_flag && !update_flag)
            {
                printf("\n<--- No Database present --->\n");
                break;
            }
            print_database(arr);

            break;

        case 3:
            //  Check whether the database is empty

            if(!create_flag && !update_flag)
            {
                printf("\n<--- No Database present --->\n");
                break;
            }

            char search_word[100];
            printf("Enter the word to search :\n");
            scanf("%s", search_word);

            if (search_database(arr, search_word) == FAILURE)
            {
                printf("<--- Word not found --->\n");
            }

            break;

        case 4:
            //  Check whether the database is empty

            if(!create_flag && !update_flag)
            {
                printf("\n<--- No Database present --->\n");
                break;
            }

            char backup_filename[50];
            printf("Enter the backup filename: ");
            scanf("%s", backup_filename);

            if (save_database(arr, backup_filename) == FAILURE)
            {
                printf("<--- Error saving Database --->\n");
                return FAILURE;
            }

            break;

        case 5:
            if(update_flag)
            {
                printf("\n<--- Database already updated --->\n");
                break;
            }

            printf("Enter the backup filename: ");
            scanf("%s", backup_filename);

            file_node *head = f_head;

            if(!create_flag)
                head = NULL;

            if (!update_flag && update_database(&bf_head, head, arr, backup_filename) == FAILURE)
            {
                printf("<--- Error updating Database --->\n");
                return FAILURE;
            }
            update_flag = 1;

            printf("\nBackup file list : \n");
            print_file(bf_head);

            break;

        case 0:
            return SUCCESS;

            break;

        default:
            printf("><------- Invalid Input -------><\n");
            getchar();
        }
    }
}