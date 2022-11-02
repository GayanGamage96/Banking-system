#include <stdio.h>

// declaration of structure
struct accType {
    char bankName[20];
    char bankBranch[20];
    char accHolderName[30];
    int accNumber;
    int pinNumber;
    int availableBalance;
};

void CreateNewAccount();

void Login();

void menu();

void CashDeposit();

void CashWithdrawl();

void AccountInformation();

void deleteAccount();

/* Select the service */

int accountNumber = 0;
int pin = 0;

int main() {
    int option;

    printf("\n======Welcome to Bank of Yours======\n");
    printf("\n ~~~For a bright and light future~~~\n\n");
    //display_options();

    printf("1. Create a new account \n");
    printf("2. Login account \n");
    printf("\n");

    printf("Please enter number 1 to create a new account:");
    printf("Please enter number 2 to login to your account:");

    scanf("%d", &option);
    printf("%d \n", option);

    switch (option) {
        case 1:
            CreateNewAccount();
            break;
        case 2:
            Login();
        default :
            main();

    }

}

void CreateNewAccount() {

    struct accType data;
    printf("\nEnter the your personal details below");
    printf("\n");

    //Enter the personal details;

    printf("\nBank name             : ");
    scanf("%s", &data.bankName);

    printf("\nBank branch            : ");
    scanf("%s", &data.bankBranch);

    printf("\nAccount holder name    : ");
    scanf("%s", &data.accHolderName);

    printf("\nAccount number (1 to 99)          : ");
    scanf("%d", &data.accNumber);

    printf("\nPIN number (1 to 99)              : ");
    scanf("%d", &data.pinNumber);

    printf("\nDeposit cash ");
    scanf("%d", &data.availableBalance);

    FILE *file;
    file = fopen("account.dat", "a");
    fwrite(&data, sizeof(data), 1, file);
    fclose(file);

    printf("\nAccount has been created successfully!!! \n\n");

    main();
}

void Login() {
    int found = 0;
    printf("Enter your account number:\n");
    scanf("%d", &accountNumber);
    printf("Enter your pin number:\n");
    scanf("%d", &pin);


    FILE *file;
    struct accType data;

    file = fopen("account.dat", "r");

    while (fread(&data, sizeof(data), 1, file)) {
        if (accountNumber == data.accNumber) {
            if (pin == data.pinNumber) {
                menu();
                found = 1;
            }
        }
    }
    fclose(file);

    if (found == 0) {
        printf("wrong information\n");
        pin = 0;
        accountNumber = 0;
        main();
    }

}

void menu() {
    int option;

    //display_options();
    printf("\n");
    printf("1. Cash Deposit \n");
    printf("2. Cash withdrawal \n");
    printf("3. Account information \n");
    printf("4. Delete account\n");
    printf("5. Log out \n\n");

    printf("Please select the service you want (1/2/3/4/5):");

    scanf("%d", &option);
    printf("%d \n", option);

    switch (option) {
        case 1:
            CashDeposit();
            break;
        case 2:
            CashWithdrawl();
            break;
        case 3:
            AccountInformation();
            break;
        case 4:
            deleteAccount();
        case 5:
            pin = 0;
            accountNumber = 0;
            main();
        default :
            menu();

    }

}

/* Function to create new account */

// Function to deposit amount in an account

void CashDeposit() {
    FILE *file, *file1;
    int addblance;
    struct accType data;

    file = fopen("account.dat", "r");
    file1 = fopen("tempaccount.dat", "w");


    while (fread(&data, sizeof(data), 1, file)) {
        if (accountNumber == data.accNumber) {
            printf("Enter Amount\n");
            scanf("%d", &addblance);
            data.availableBalance = data.availableBalance + addblance;
            printf("-------------------------------------------------------\n");
            printf("------------------------receipt------------------------\n");
            printf("Account number %d\n", accountNumber);
            printf("Holder name %s\n", data.accHolderName);
            printf("Deposit balance %d\n", addblance);
            printf("New balance %d\n", data.availableBalance);
            printf("-------------------------------------------------------\n");

        }
        fwrite(&data, sizeof(data), 1, file1);
    }
    fclose(file);
    fclose(file1);

    file = fopen("account.dat", "w");
    file1 = fopen("tempaccount.dat", "r");

    while (fread(&data, sizeof(data), 1, file1)) {
        fwrite(&data, sizeof(data), 1, file);
    }

    fclose(file);
    fclose(file1);

    menu();
}

// Function to withdraw amount from an account

void CashWithdrawl() {
    FILE *file, *file1;
    int blance, pin1 = 0;
    struct accType data;

    file = fopen("account.dat", "r");
    file1 = fopen("tempaccount.dat", "w");

    printf("Enter pin number\n");
    scanf("%d", &pin1);

    while (fread(&data, sizeof(data), 1, file)) {
        if (accountNumber == data.accNumber) {
            if (pin1 == data.pinNumber) {
                printf("Enter Amount\n");
                scanf("%d", &blance);
                data.availableBalance = data.availableBalance - blance;
                printf("-------------------------------------------------------\n");
                printf("------------------------receipt------------------------\n");
                printf("Account Number          %d\n", accountNumber);
                printf("Account Holder Name     %s\n", data.accHolderName);
                printf("Withdrawal Amount       %d\n", blance);
                printf("New Balance             %d\n", data.availableBalance);
                printf("-------------------------------------------------------\n");
            }
        }
        fwrite(&data, sizeof(data), 1, file1);
    }
    fclose(file);
    fclose(file1);

    file = fopen("account.dat", "w");
    file1 = fopen("tempaccount.dat", "r");

    while (fread(&data, sizeof(data), 1, file1)) {
        fwrite(&data, sizeof(data), 1, file);
    }

    fclose(file);
    fclose(file1);

    menu();
}

// Displaying account informations

void AccountInformation() {
    FILE *file;
    struct accType data;

    file = fopen("account.dat", "r");

    while (fread(&data, sizeof(data), 1, file)) {
        if (accountNumber == data.accNumber) {
            printf("-------------------------------------------------------\n");
            printf("------------------------receipt------------------------\n");
            printf("Bank Name              %s\n", data.bankName);
            printf("Bank branch Name       %s\n", data.bankBranch);
            printf("Account Holder Name    %s\n", data.accHolderName);
            printf("Account Number         %d\n", data.accNumber);
            printf("Balance Amount         %d\n", data.availableBalance);
            printf("-------------------------------------------------------\n");
        }
    }

    menu();
}


void deleteAccount() {
    FILE *file, *file1;
    int found = 0, pin1 = 0;
    struct accType data;

    file = fopen("account.dat", "r");
    file1 = fopen("tempaccount.dat", "w");

    printf("Enter the pin number\n");
    scanf("%d", &pin1);

    while (fread(&data, sizeof(data), 1, file)) {
        if (accountNumber == data.accNumber) {
            if (pin1 == data.pinNumber) {
                printf("Account has been deleted successfully\n");
                found = 1;
            }
        } else {
            fwrite(&data, sizeof(data), 1, file1);
        }
    }
    fclose(file);
    fclose(file1);

    if (found == 0) {
        printf("wrong information\n");
        pin = 0;
        accountNumber = 0;
        main();
    }

    file = fopen("account.dat", "w");
    file1 = fopen("tempaccount.dat", "r");

    while (fread(&data, sizeof(data), 1, file1)) {
        fwrite(&data, sizeof(data), 1, file);
    }

    fclose(file);
    fclose(file1);

}
