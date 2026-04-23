#include "common.h"

int initialise_database(hash_t *arr)
{
    for (int i = 0; i < 28; i++)
    {
        arr[i].index = 0;
        arr[i].main_link = NULL;
    }
    return SUCCESS;
}

int insert_file(file_node **head, char *file)
{
    // Create a new file node
    file_node *new = malloc(sizeof(file_node));
    if(!new)
        return FAILURE;

    new->file_name = file;
    new->link = NULL;

    // If list is empty
    if(*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    file_node *temp = *head;
    while(temp)
    {
        // If file already present
        if(strcmp(file,temp->file_name) == 0)
        {
            free(new);
            return DUPLICATE;
        }
        if(temp->link == NULL)
            break;
        temp = temp->link;
    }

    temp->link = new;

    return SUCCESS;
}

int print_file(file_node *head)
{
    if(head == NULL){
        printf("File list empty\n");
        return SUCCESS;
    }

    while(head){
        printf("|");
        printf("---> %s\n",head->file_name);
        head = head->link;
    }

    return SUCCESS;
}

int validate_input(int argc, char *argv[], file_node **f_head)
{
    if(argc == 1)
    {
        // printf("Invalid arguments\n");
        return SUCCESS;
    }

    for(int i=1;i<argc;i++)
    {
        //  Check whether .txt extension is present in user provided file list and if present, store it in valid file list
        char *str = strchr(argv[i],'.');
        if(str != NULL && strcmp(str,".txt") == 0)
        {
            if(insert_file(f_head,argv[i]) == FAILURE)
            {
                printf("Unable to allocate memory\n");
                return FAILURE;
            }
        }
    }

    //  If valid file list is empty -> return FAILURE
    if(*f_head == NULL)
        return FAILURE;

    printf("\nValid File list : \n|\n");
    print_file(*f_head);
    printf("\n");

    return SUCCESS;

}