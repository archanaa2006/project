#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CUSTOMERS 100

// Define a structure to store customer reservation details
struct Reservation {
    int customerID;
    char name[50];
    int roomNumber;
    int daysBooked;
    float totalAmount;
};

// Function to calculate the total amount based on days booked and a fixed rate
float calculateAmount(int days) {
    float rate = 100.0;  // Per day room rate
    return days * rate;
}

// Function to add a new reservation
void addReservation(struct Reservation customers[], int *count) {
    if (*count >= MAX_CUSTOMERS) {
        printf("No more rooms available!\n");
        return;
    }

    printf("Enter Customer ID: ");
    scanf("%d", &customers[*count].customerID);
    getchar();  // Consume the newline character
    printf("Enter Customer Name: ");
    fgets(customers[*count].name, 50, stdin);
    customers[*count].name[strcspn(customers[*count].name, "\n")] = '\0';  // Remove newline
    printf("Enter Room Number: ");
    scanf("%d", &customers[*count].roomNumber);
    printf("Enter Number of Days: ");
    scanf("%d", &customers[*count].daysBooked);

    // Calculate the total amount for the stay
    customers[*count].totalAmount = calculateAmount(customers[*count].daysBooked);

    printf("\nReservation added successfully!\n\n");
    (*count)++;
}

// Function to display all reservations
void displayReservations(struct Reservation customers[], int count) {
    if (count == 0) {
        printf("No reservations to display.\n\n");
        return;
    }

    printf("\nAll Reservations:\n");
    printf("Customer ID | Name                    | Room No. | Days | Amount\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-12d | %-22s | %-8d | %-4d | %.2f\n",
            customers[i].customerID, customers[i].name, customers[i].roomNumber,
            customers[i].daysBooked, customers[i].totalAmount);
    }
    printf("\n");
}

// Function to search for a reservation by customer ID
void searchByID(struct Reservation customers[], int count, int searchID) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (customers[i].customerID == searchID) {
            printf("\nReservation Found:\n");
            printf("Customer ID: %d | Name: %s | Room No: %d | Days: %d | Amount: %.2f\n\n",
                customers[i].customerID, customers[i].name, customers[i].roomNumber,
                customers[i].daysBooked, customers[i].totalAmount);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nNo reservation found with ID: %d\n\n", searchID);
    }
}

// Function to search for a reservation by customer name
void searchByName(struct Reservation customers[], int count, char searchName[]) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcasecmp(customers[i].name, searchName) == 0) {
            printf("\nReservation Found:\n");
            printf("Customer ID: %d | Name: %s | Room No: %d | Days: %d | Amount: %.2f\n\n",
                customers[i].customerID, customers[i].name, customers[i].roomNumber,
                customers[i].daysBooked, customers[i].totalAmount);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nNo reservation found with Name: %s\n\n", searchName);
    }
}

// Function to modify an existing reservation
void modifyReservation(struct Reservation customers[], int count, int customerID) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (customers[i].customerID == customerID) {
            printf("\nReservation Found for ID %d:\n", customerID);
            printf("Current Room No: %d, Current Days: %d, Current Amount: %.2f\n",
                customers[i].roomNumber, customers[i].daysBooked, customers[i].totalAmount);

            printf("\nEnter New Room Number: ");
            scanf("%d", &customers[i].roomNumber);
            printf("Enter New Number of Days: ");
            scanf("%d", &customers[i].daysBooked);

            // Recalculate total amount
            customers[i].totalAmount = calculateAmount(customers[i].daysBooked);

            printf("\nReservation updated successfully!\n\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\nNo reservation found with ID: %d\n\n", customerID);
    }
}

// Function to delete a reservation by customer ID
void deleteReservation(struct Reservation customers[], int *count, int customerID) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (customers[i].customerID == customerID) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                customers[j] = customers[j + 1];  // Shift records to the left
            }
            (*count)--;  // Decrease the reservation count
            printf("\nReservation for ID %d deleted successfully!\n\n", customerID);
            break;
        }
    }
    if (!found) {
        printf("\nNo reservation found with ID: %d\n\n", customerID);
    }
}

int main() {
    struct Reservation customers[MAX_CUSTOMERS];  // Array to store customer reservations
    int count = 0;  // Total number of reservations
    int choice, customerID;
    char searchName[50];

    while (1) {
        printf("Hotel Reservation System\n");
        printf("1. Add Reservation\n");
        printf("2. Display All Reservations\n");
        printf("3. Search Reservation by ID\n");
        printf("4. Search Reservation by Name\n");
        printf("5. Modify Reservation\n");
        printf("6. Delete Reservation\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addReservation(customers, &count);
                break;
            case 2:
                displayReservations(customers, count);
                break;
            case 3:
                printf("Enter Customer ID to search: ");
                scanf("%d", &customerID);
                searchByID(customers, count, customerID);
                break;
            case 4:
                getchar();  // Consume the newline character
                printf("Enter Customer Name to search: ");
                fgets(searchName, sizeof(searchName), stdin);
                searchName[strcspn(searchName, "\n")] = '\0';  // Remove newline
                searchByName(customers, count, searchName);
                break;
            case 5:
                printf("Enter Customer ID to modify: ");
                scanf("%d", &customerID);
                modifyReservation(customers, count, customerID);
                break;
            case 6:
                printf("Enter Customer ID to delete: ");
                scanf("%d", &customerID);
                deleteReservation(customers, &count, customerID);
                break;
            case 7:
                printf("Exiting the system...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n\n");
        }
    }

    return 0;
}
