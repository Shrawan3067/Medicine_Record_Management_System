#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct medicine {
    int id;
    char name[50];
    int quantity;
    int price;
    char date[12];
} m;

FILE *fm;

// Function Prototypes
void displaymedicine();
void addmedicine();
void deletemedicine();
void searchmedicine();
void updateMedicine();

int main() {
    int ch;

    while (1) {
        system("cls");  // Use "clear" for Linux/macOS
        printf("<== MEDICINE RECORD MANAGEMENT SYSTEM ==>\n");
        printf("1. Display Medicine Details\n");
        printf("2. Add New Medicine\n");
        printf("3. Delete Medicine Details\n");
        printf("4. Search a Particular Medicine\n");
        printf("5. Update Medicine Details\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 0:
                exit(0);
            case 1:
                displaymedicine();
                break;
            case 2:
                addmedicine();
                break;
            case 3:
                deletemedicine();
                break;
            case 4:
                searchmedicine();
                break;
            case 5:
                updateMedicine();
                break;
            default:
                printf("Invalid Choice...\n\n");
        }
        printf("\n\nPress Enter to Continue...");
        getchar();
        getchar();
    }

    return 0;
}

void displaymedicine() {
    system("cls");
    printf("<== Medicine List ==>\n\n");
    printf("%-10s %-20s %-10s %-10s\n", "ID", "Name", "Quantity", "Price");
    printf("---------------------------------------------------\n");

    fm = fopen("medicine.txt", "rb");
    if (fm == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&m, sizeof(m), 1, fm) == 1) {
        printf("%-10d %-20s %-10d %-10d\n", m.id, m.name, m.quantity, m.price);
    }

    fclose(fm);
}

void addmedicine() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(m.date, myDate);

    fm = fopen("medicine.txt", "ab");
    if (fm == NULL) {
        printf("Error opening file!");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &m.id);
    
    printf("Enter Medicine Name: ");
    fflush(stdin);
    fgets(m.name, sizeof(m.name), stdin);
    m.name[strcspn(m.name, "\n")] = 0;  // Remove newline character

    printf("Enter Quantity: ");
    scanf("%d", &m.quantity);

    printf("Enter Price: ");
    scanf("%d", &m.price);

    fwrite(&m, sizeof(m), 1, fm);
    fclose(fm);

    printf("\nMedicine Added Successfully.\n");
}

void deletemedicine() {
    int id, found = 0;
    system("cls");
    printf("<== Delete Medicine Details ==>\n\n");
    printf("Enter ID to Delete: ");
    scanf("%d", &id);

    FILE *ft;
    fm = fopen("medicine.txt", "rb");
    if (fm == NULL) {
        printf("No records found!\n");
        return;
    }
    ft = fopen("temp.txt", "wb");

    while (fread(&m, sizeof(m), 1, fm) == 1) {
        if (id == m.id) {
            found = 1;
        } else {
            fwrite(&m, sizeof(m), 1, ft);
        }
    }

    fclose(fm);
    fclose(ft);

    if (found) {
        remove("medicine.txt");
        rename("temp.txt", "medicine.txt");
        printf("\nMedicine Deleted Successfully.\n");
    } else {
        printf("\nRecord Not Found!\n");
    }
}

void searchmedicine() {
    int id, found = 0;
    system("cls");
    printf("<== Search Medicine ==>\n\n");
    printf("Enter Medicine ID to search: ");
    scanf("%d", &id);

    fm = fopen("medicine.txt", "rb");
    if (fm == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&m, sizeof(m), 1, fm) == 1) {
        if (id == m.id) {
            printf("\nMedicine Found:\n");
            printf("ID: %d\n", m.id);
            printf("Name: %s\n", m.name);
            printf("Quantity: %d\n", m.quantity);
            printf("Price: %d\n", m.price);
            found = 1;
            break;
        }
    }

    fclose(fm);
    if (!found) {
        printf("\nMedicine Not Found!\n");
    }
}

void updateMedicine() {
    int id, found = 0;
    system("cls");
    printf("<== Update Medicine Details ==>\n\n");
    printf("Enter Medicine ID to update: ");
    scanf("%d", &id);

    FILE *ft;
    fm = fopen("medicine.txt", "rb");
    if (fm == NULL) {
        printf("No records found!\n");
        return;
    }
    ft = fopen("temp.txt", "wb");

    while (fread(&m, sizeof(m), 1, fm) == 1) {
        if (id == m.id) {
            found = 1;
            printf("Enter New Quantity: ");
            scanf("%d", &m.quantity);
            printf("Enter New Price: ");
            scanf("%d", &m.price);
            printf("\nMedicine Details Updated Successfully.\n");
        }
        fwrite(&m, sizeof(m), 1, ft);
    }

    fclose(fm);
    fclose(ft);

    if (found) {
        remove("medicine.txt");
        rename("temp.txt", "medicine.txt");
    } else {
        printf("\nRecord Not Found!\n");
    }
}
