#include <complex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

struct PasswordEntry
{
    char username[100];
    char website[100];
    char password[100];
};

void encrypt_decrypt(char *text, char key);
void setup_master_password();
int check_master_password();
void add_password(struct PasswordEntry **passwords, int *count, int *capacity);
void delete_password(struct PasswordEntry **passwords, int *count);
void view_passwords(struct PasswordEntry *passwords, int count);
void save_passwords(struct PasswordEntry *passwords, int count);
void load_passwords(struct PasswordEntry **passwords, int *count, int *capacity);

int main()
{
    int password_result = check_master_password();
    struct PasswordEntry *password = NULL;
    int password_count = 0;
    int capacity = 2;
    int choice = 0;

    password = malloc(capacity * sizeof(struct PasswordEntry));
    if(password == NULL)
    {
        printf("Memory Allocation Failed\n");
        return 1;
    }

    FILE *test_file = fopen("master_password.txt", "r");

    if(test_file == NULL)
    {
        setup_master_password();
    }
    else
    {
        fclose(test_file);
    }

    if(password_result == 0)
    {
        printf("Access denied!\n");
        return 1;
    }

    printf("✅ Access granted!\n");

    do
    {
        printf("===== PASSWORD MANAGER =====\n");
        printf("1. Add password\n");
        printf("2. View password\n");
        printf("3. Delet password\n");
        printf("4. Save password to file\n");
        printf("5. Load password from file\n");
        printf("6. Exit\n");
        printf("===============================\n");
        printf("Enter youre choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                add_password(&password, &password_count, &capacity);
                break;
            case 2:
                view_passwords(password, password_count);
                break;
            case 3:
                delete_password(&password, &password_count);
                break;
            case 4:
                save_passwords(password, password_count);
                break;
            case 5:
                load_passwords(&password, &password_count, &capacity);
                break;
            case 6:
                printf("GOOD BYE!!\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }

    }while(choice != 6);

    return 0;
}

void encrypt_decrypt(char *text, char key)
{
    for(int i = 0; text[i] != '\0'; i++)
    {
        text[i] = text[i] ^ key;
    }
}

void setup_master_password()
{
    char master_password[100] = "";
    char key = 'K';

    printf("Enter the master password: ");
    fgets(master_password, sizeof(master_password), stdin);
    master_password[strcspn(master_password, "\n")] = '\0';

    FILE *file = fopen("master_password.txt", "w");

    encrypt_decrypt(master_password, key);
    
    if(file == NULL)
    {
        printf("Seting up master password has Failed\n");
        return;
    }

    fprintf(file, "%s", master_password);
    fclose(file);

    printf("✅ Master password created!\n");
}

int check_master_password()
{
    char enter_password[100] = "";
    char saved_password[100] = "";
    char key = 'K';

    FILE *file = fopen("master_password.txt", "r");

    if(file == NULL)
    {
        printf("Master password is not set yet!!\n");
        return 0;
    }

    fgets(saved_password, sizeof(saved_password), file);
    saved_password[strcspn(saved_password, "\n")] = '\0';
    fclose(file);

    encrypt_decrypt(saved_password, key);

    printf("Enter the Master password: ");
    fgets(enter_password, sizeof(enter_password), stdin);
    enter_password[strcspn(enter_password, "\n")] = '\0';

    if(strcmp(saved_password, enter_password) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void add_password(struct PasswordEntry **passwords, int *count, int *capacity)
{
    char website[100] = "";
    char password[100] = "";
    char username[100] = "";
    char key = 'K';

    if(*count == *capacity)
    {
        *capacity *= 2;

        struct PasswordEntry *temp = realloc(*passwords, *capacity * sizeof(struct PasswordEntry));
        
        if(temp == NULL)
        {
            printf("Memory Allocation Failed\n");
            return;
        }
        *passwords = temp;
    }

    printf("Enter the website name: ");
    fgets(website, sizeof(website), stdin);
    website[strcspn(website, "\n")] = '\0';

    printf("Enter the passwords: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    printf("Enter the username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    encrypt_decrypt(password, key);

    strcpy((*passwords)[*count].website, website);
    strcpy((*passwords)[*count].username, username);
    strcpy((*passwords)[*count].password, password);
 
    (*count)++;
    printf("✅ Password added!\n");
}

void view_passwords(struct PasswordEntry *passwords, int count)
{
    char key = 'K';

    if(count == 0)
    {
        printf("There is now password saved yet!!\n");
        return;
    }
    for(int i = 0; i < count; i++)
    {
        encrypt_decrypt(passwords[i].password, key); 
        printf("\nWebsite: %s\n", passwords[i].website);
        printf("Username: %s\n", passwords[i].username);
        printf("Password: %s\n", passwords[i].password);
        printf("------------------------\n");

        encrypt_decrypt(passwords[i].password, key);
    }
}

void delete_password(struct PasswordEntry **passwords, int *count)
{
    if (*count == 0) {
        printf("No passwords saved yet!\n");
        return;
    }

    int delete_choice = 0;

    printf("\nDelete by:\n");
    printf("1. Website name\n");
    printf("2. Number\n");
    printf("3. Cancel\n");
    printf("Enter: ");
    scanf("%d", &delete_choice);
    getchar();

    if (delete_choice == 1) //delete by the website name
    {
        char website_to_delete[100] = "";
        int found_index = -1;

        printf("\nSaved websites:\n");
        for (int i = 0; i < *count; i++)
        {
            printf("%d. %s\n", i + 1, (*passwords)[i].website);
        }
        
        printf("\nEnter website name to delete: ");
        fgets(website_to_delete, sizeof(website_to_delete), stdin);
        website_to_delete[strcspn(website_to_delete, "\n")] = '\0';

        for(int i = 0; i < *count; i++)
        {
            if (strcmp((*passwords)[i].website, website_to_delete) == 0)
            {
                found_index = i;
                break;
            }
        }

        if(found_index != -1)
        {
            for (int i = found_index; i < *count - 1; i++)
            {
                (*passwords)[i] = (*passwords)[i + 1];
            }
            
            (*count)--;
            printf("✅ Password deleted!\n");
        }
        
        else
        {
            printf("❌ Website not found!\n");
        }
    }

    else if(delete_choice == 2) 
    {
        int number = 0;

        printf("\nSaved websites:\n");
        for(int i = 0; i < *count; i++)
        {
            printf("%d. %s\n", i + 1, (*passwords)[i].website);
        }
        
        printf("Enter number to delete: ");
        scanf("%d", &number);
        getchar();

        if (number < 1 || number > *count)
        {
            printf("❌ Invalid number!\n");
            return;
        }
        
        for (int i = number - 1; i < *count - 1; i++)
        {
            (*passwords)[i] = (*passwords)[i + 1];
        }

        (*count)--;
        printf("✅ Password deleted!\n");
    }

    else
    {
        printf("Cancelled\n");
        return;
    }
}

void save_passwords(struct PasswordEntry *passwords, int count)
{
    FILE *file = fopen("saved_passwords.txt", "w");

    if(file == NULL)
    {
        printf("There is no password saved yet!!\n");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        fprintf(file, "%s|%s|%s",
                passwords[i].website,
                passwords[i].username,
                passwords[i].password);
    }

    fclose(file);
    printf("✅ %d passwords saved!\n", count);
}

void load_passwords(struct PasswordEntry **passwords, int *count, int *capacity)
{
     FILE *file = fopen("saved_passwords.txt", "r");
    
    if (file == NULL)
    {
        printf("There is no file saved yet\n");
        return; 
    }
    
    char line[512];
    
    while(fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        
        if (*count == *capacity)
        {
            *capacity *= 2;
            struct PasswordEntry *temp = realloc(*passwords, *capacity * sizeof(struct PasswordEntry));
            if (temp == NULL) {
                printf("Memory allocation failed!\n");
                fclose(file);
                return;
            }
            *passwords = temp;
        }
        char *token = strtok(line, "|");
        if(token == NULL) continue;
        strcpy((*passwords)[*count].website, token);

        token = strtok(NULL, "|");
        if(token == NULL) continue;
        strcpy((*passwords)[*count].username, token);

        token = strtok(NULL, "|");
        if(token == NULL) continue;
        strcpy((*passwords)[*count].password, token);

        (*count)++;
    }
    fclose(file);
    
    if (*count > 0)
    {
        printf("✅ %d passwords loaded!\n", *count);
    }
}
