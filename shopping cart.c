#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "users_info.txt"
#define CART_FILENAME "cart_data.txt"

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void saveCartToFile() {
    FILE *cartFile = fopen(CART_FILENAME, "w");
    if (cartFile == NULL) {
        printf("Error: Unable to save the cart to the file.\n");
        return;
    }

    fprintf(cartFile, "Item Name\tQuantity\tPrice\n");
    fprintf(cartFile, "---------------------------------\n");
    fprintf(cartFile, "Item 1\t2\t10.50\n");
    fprintf(cartFile, "Item 2\t1\t5.75\n");

    fclose(cartFile);
    printf("Cart data saved successfully!\n");
}

struct Cart_Item {
    char name[50];
    int quantity;
    float price;
};

int menu() {
    int choice;
    printf("\nQUICKCART Menu -->\n");
    printf("1. Add Item\n");
    printf("2. Remove Item\n");
    printf("3. View Cart\n");
    printf("4. Checkout\n");
    printf("5. Save\n");
    printf("6. Exit\n\n");

    printf("Enter your choice (enter the number): ");
    scanf("%d", &choice);   
    return choice;
}

int main() {
    int reg, j, i = 0, found = 0, cartcount = 0;
    char itemName[50];
    float totalPrice = 0;
    FILE *filePtr;
    struct Cart_Item cart[10];

    printSpaces(41);
    printf("Welcome \n");

    printSpaces(43);
    printf("To\n");

    printSpaces(40);
    printf("QUICKCART\n");

    printSpaces(32);
    printf("Fast and efficient shopping\n\n");

    printSpaces(32);
    printf("Fast and efficient shopping\n\n");
    printf("=======================================================================================================\n");
    
    printf("         ****     *    * ******* ******  *     *           ******      *       *****   *******  \n");
    printf("        *    *    *    *    *    *       *   *             *          ***      *    *     *    \n");
    printf("       *      *   *    *    *    *       * *               *         *    *    *   *      *    \n ");
    printf("     *        *  *    *    *    *       *  *              *        ********   * *        *    \n  ");
    printf("     *    * *   *    *    *    *       *   *             *       *        *  * *        *    \n ");
    printf("       *    *    *    *    *    *       *    *            *       *        *  *   *      *   \n ");
    printf("        ****  *  ****** ******* ******  *     *           ******  *        *  *    *     *     \n\n");
   
    printf("=======================================================================================================\n\n\n");

    printf("Are you already registered? (Yes = 1 / No = 0): ");
    scanf("%d", &reg);

    if (reg == 0) {
        char email[25], password[20], name[50], address[60], bank[15];
        int bankNum, otp;

        filePtr = fopen(FILENAME, "a");
        if (filePtr == NULL) {
            printf("Error: Unable to open the file.\n");
            return 1;
        }

        printf("Input your Email: ");
        scanf("%s", email);
        printf("Input your Password: ");
        scanf("%s", password);
        printf("Input your Name: ");
        scanf("%s", name);
        printf("Input your Address: ");
        scanf("%s", address);
        printf("Input your Bank Name: ");
        scanf("%s", bank);
        printf("Input your Bank Number: ");
        scanf("%d", &bankNum);
        printf("Input your OTP number: ");
        scanf("%d", &otp);

        fprintf(filePtr, "%s\n%s\n%s\n%s\n%s\n%d\n%d\n", email, password, name, address, bank, bankNum, otp);
        fclose(filePtr);
        printf("Registration successful! Your details have been saved.\n");
    } else if (reg == 1) {
        char email[25], password[20], fileEmail[25], filePassword[20];
        int found = 0, attempts = 0;

        filePtr = fopen(FILENAME, "r");
        if (filePtr == NULL) {
            printf("Error: No registered users found. Please register first.\n");
            return 1;
        }

        while (attempts < 4) {
            printf("Enter your Email: ");
            scanf("%s", email);
            printf("Enter your Password: ");
            scanf("%s", password);

            rewind(filePtr);
            while (fscanf(filePtr, "%s %s", fileEmail, filePassword) != EOF) {
                if (strcmp(email, fileEmail) == 0 && strcmp(password, filePassword) == 0) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                printf("Login successful! Welcome back.\n");
                fclose(filePtr);

                while (1) {
                    int choice = menu();

                    switch (choice) {
                        case 1:
                            if (cartcount < 10) {
                                printf("Enter item name: ");
                                scanf("%s", cart[cartcount].name);
                                printf("Enter item quantity: ");
                                scanf("%d", &cart[cartcount].quantity);
                                printf("Enter item price: ");
                                scanf("%f", &cart[cartcount].price);

                                cartcount++;
                                printf("Item added successfully.\n");
                            } else {
                                printf("Cart is full.\n");
                            }
                            break;

                        case 2:
                            if (cartcount == 0) {
                                printf("Your cart is empty. Nothing to remove.\n");
                                break;
                            }

                            printf("Enter the name of the item to remove: ");
                            scanf("%s", itemName);

                            found = 0;
                            for (i = 0; i < cartcount; i++) {
                                if (strcmp(cart[i].name, itemName) == 0) {
                                    for (j = i; j < cartcount - 1; j++) {
                                        cart[j] = cart[j + 1];
                                    }
                                    cartcount--;
                                    printf("Item '%s' removed from the cart.\n", itemName);
                                    found = 1;
                                    break;
                                }
                            }

                            if (!found) {
                                printf("Item '%s' not found in the cart.\n", itemName);
                            }
                            break;

                        case 3:
                            if (cartcount == 0) {
                                printf("Your cart is empty.\n");
                            } else {
                                printf("Your Cart:\n");
                                printf("Item Name\tQuantity\tPrice\n");
                                printf("---------------------------------\n");
                                for (i = 0; i < cartcount; i++) {
                                    printf("%s\t\t%d\t\t%.2f\n", cart[i].name, cart[i].quantity, cart[i].price);
                                }
                            }
                            break;

                        case 4:
                            if (cartcount == 0) {
                                printf("Your cart is empty.\n");
                            } else {
                                printf("Your Order Summary:\n");
                                printf("Item Name\tQuantity\tPrice\n");
                                printf("---------------------------------\n");

                                totalPrice = 0;
                                for (i = 0; i < cartcount; i++) {
                                    printf("%s\t\t%d\t\t%.2f\n", cart[i].name, cart[i].quantity, cart[i].price);
                                    totalPrice += cart[i].quantity * cart[i].price;
                                }

                                printf("---------------------------------\n");
                                printf("Total Price: %.2f\n", totalPrice);

                                printf("Proceeding with the payment...\n");
                                printf("Payment successful! Thank you for shopping with QUICKCART.\n\n");

                                saveCartToFile();
                            }
                            break;

                        case 5:
                            saveCartToFile();
                            break;

                        case 6:
                            printf("Thank you for using QUICKCART! Goodbye.\n");
                            return 0;

                        default:
                            printf("Invalid choice! Please try again.\n\n");
                    }
                }
            }
            attempts++;
            printf("Incorrect email or password. Attempts left: %d\n", 3 - attempts);
        }

        fclose(filePtr);
    }
    return 0;
}
