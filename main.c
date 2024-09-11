#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;
char name[50];
char number[15];
char add[50];

void add_contact()
{
    printf("Enter Contact details below:\n");
    printf("Name:\n");
    scanf("%s", name);
    printf("Contact Number:\n");
    scanf("%s", number);
    printf("Address:\n");
    scanf("%s", add);
    FILE *fptr;
    fptr = fopen("contacts.txt", "a");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fptr, "%s\n%s\n%s\n", name, number, add);
    fclose(fptr);
    printf("Contact added successfully.\n");
}

void search_contact()
{
    char search_name[50];
    printf("Enter the name to search: ");
    scanf("%s", search_name);

    FILE *fptr;
    fptr = fopen("contacts.txt", "r");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    int found = 0;
    while (fscanf(fptr, "%s%s%s", name, number, add) != EOF)
    {
        if (strcmp(name, search_name) == 0)
        {
            printf("Contact found:\nName: %s\nNumber: %s\nAddress: %s\n", name, number, add);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Contact not found.\n");
    }

    fclose(fptr);
}

void edit_contact()
{
    char edit_name[50];
    printf("Enter the name of the contact to edit: ");
    scanf("%s", edit_name);

    FILE *fptr, *temp;
    fptr = fopen("contacts.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fptr == NULL || temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    int found = 0;
    while (fscanf(fptr, "%s%s%s", name, number, add) != EOF)
    {
        if (strcmp(name, edit_name) == 0)
        {
            printf("Enter new details:\n");
            printf("Name: ");
            scanf("%s", name);
            printf("Number: ");
            scanf("%s", number);
            printf("Address: ");
            scanf("%s", add);
            found = 1;
        }
        fprintf(temp, "%s\n%s\n%s\n", name, number, add);
    }

    fclose(fptr);
    fclose(temp);

    if (found)
    {
        remove("contacts.txt");
        rename("temp.txt", "contacts.txt");
        printf("Contact updated successfully.\n");
    }
    else
    {
        remove("temp.txt");
        printf("Contact not found.\n");
    }
}

void del_contact()
{
    char del_name[50];
    printf("Enter the name of the contact to delete: ");
    scanf("%s", del_name);

    FILE *fptr, *temp;
    fptr = fopen("contacts.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fptr == NULL || temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    int found = 0;
    while (fscanf(fptr, "%s%s%s", name, number, add) != EOF)
    {
        if (strcmp(name, del_name) != 0)
        {
            fprintf(temp, "%s\n%s\n%s\n", name, number, add);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(temp);

    if (found)
    {
        remove("contacts.txt");
        rename("temp.txt", "contacts.txt");
        printf("Contact deleted successfully.\n");
    }
    else
    {
        remove("temp.txt");
        printf("Contact not found.\n");
    }
}

void list_contact()
{
    FILE *fptr;
    fptr = fopen("contacts.txt", "r");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("List of contacts:\n");
    while (fscanf(fptr, "%s%s%s", name, number, add) != EOF)
    {
        printf("Name: %s, Number: %s, Address: %s\n", name, number, add);
    }

    fclose(fptr);
}

void exit_program()
{
    printf("Exiting the program. Goodbye!\n");
    exit(0);
}
void duplicate_contact()
{
    printf("No duplicate contacts\n");
}
int main()
{
    while (1)
    {
        printf("\nContact Book\n");
        printf("Select Option:\n1.Add Contact\n2.Search Contact\n3.Edit Contact\n4.Delete Contact\n5.List Contact\n6.Exit\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            add_contact();
            break;
        case 2:
            search_contact();
            break;
        case 3:
            edit_contact();
            break;
        case 4:
            del_contact();
            break;
        case 5:
            list_contact();
            break;
        case 6:
            exit_program();
            break;
        }
    }
    return 0;
}
