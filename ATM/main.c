#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void user_mode(int* mode){
    printf("Press 1 to deposit and 2 to withdraw\n>>>");
    scanf("%d", mode);

    if(*mode != 1 && *mode != 2){
        printf("Invalid mode");
        exit(1);
    }
}

void deposit(int *bal){
    int to_deposit;
    printf("Deposite mode selected.\nCurrent balance is $%d.\nEnter the amount to deposit.\n>>>$", *bal);
    scanf("%d", &to_deposit);
    *bal += to_deposit;
    printf("$%d succesfully deposited. You new balance is $%d.\n", to_deposit, *bal);
}

void withdraw(int *bal){
    int to_withdraw;
    printf("Withdrawal mode selected.\nCurrent balance is $%d.\nEnter the amount to deposit.\n>>>$", *bal);
    scanf("%d", &to_withdraw);

    while(to_withdraw>*bal){
        printf("Please enter an amount lower that $%d.\n>>>$", *bal);
        scanf("%d", &to_withdraw);
    }

    *bal -= to_withdraw;
    printf("$%d succesfully withdrawed. You new balance is $%d.\n", to_withdraw, *bal);
    
}
int main(){

    //initialize the balance of the user
    FILE *balance_file;
    balance_file = fopen("balance.txt", "r");
    int bal;
    fscanf(balance_file, "%d", &bal);
    fclose(balance_file);

    int mode;
    //greet the user and get their mode
    printf("Welcome to your ATM. Your current balance is $%d. Would you like to deposit or withdraw money?\n", bal);
    char confirm;
    do{
        user_mode(&mode);
        if(mode ==1){
            deposit(&bal);
            balance_file = fopen("balance.txt", "w");
            fprintf(balance_file, "%d", bal);
            fclose(balance_file);
        }
        else{
            withdraw(&bal);
            balance_file = fopen("balance.txt", "w");
            fprintf(balance_file, "%d", bal);
            fclose(balance_file);
        }
        printf("Do you want to access the ATM again?\nType y for yes.\n>>>");
        scanf(" %c", &confirm);
    } while(tolower(confirm) == 'y');

    return 0;
}
