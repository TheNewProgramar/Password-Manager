
char website_to_delete[100] = "";
printf("\nEnter website name to delete: ");
fgets(website_to_delete, sizeof(website_to_delete), stdin);
website_to_delete[strcspn(website_to_delete, "\n")] = '\0';
