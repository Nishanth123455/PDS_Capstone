

#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define loanInterest 7.5
#define fixedDepositInterest 5.0


struct details {
  char name[30];
  int acc_number;
  int balance;
  int loan_amount;
  time_t loan_start_time;
  int months;
  float monthlyAmount;
  int fixed_deposit_amount;
  time_t fixed_deposit_start_time;
};

void createAccount(struct details *account, int *accountNumber) {
    printf("Selected account creation\n");
    if (*accountNumber < 30) {
        printf("Press ENTER \n");

        getchar();

        printf("Enter Name: ");
        fgets(account[*accountNumber].name, sizeof(account[*accountNumber].name), stdin);
        account[*accountNumber].name[strcspn(account[*accountNumber].name, "\n")] = '\0';
        account[*accountNumber].acc_number = 12705478 + *accountNumber;
        account[*accountNumber].balance = 0;
        account[*accountNumber].loan_amount = 0; 
        account[*accountNumber].fixed_deposit_amount = 0;
        printf("Account created with Account Number: %d\n", account[*accountNumber].acc_number);
        (*accountNumber)++;
    } else {
        printf("Cannot create more accounts. Limit reached.\n");
    }


    printf("Press any key to continue ");
    _getch();
    printf("Thank you");

}

void accountInquiry(const struct details *account, int accountNumber, int targetAccountNumber) {
    int found = 0;
    for (int i = 0; i < accountNumber; i++) {
        if (account[i].acc_number == targetAccountNumber) {
            printf("Account Number: %d\n", account[i].acc_number);
            printf("Name: %s\n", account[i].name);
            printf("Balance: %d\n", account[i].balance);
            printf("Loan amount: %d\n", account[i].loan_amount);
            printf("Fixed Deposit Balance: %d\n", account[i].fixed_deposit_amount);
            
             

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found.\n");
    }
    printf("Press any key continue\n ");
    _getch();
    printf("Thank you");
}

void savingsAccountDeposit(struct details *account, int accountNumber, int targetAccountNumber) {
    int depositAmount;
    int found = 0;
    for (int i = 0; i < accountNumber; i++) {
        if (account[i].acc_number == targetAccountNumber) {
            printf("Selected savings account deposit\n");
            printf("Enter the deposit amount: ");
            scanf("%d", &depositAmount);
            account[i].balance += depositAmount;
            printf("Deposited %d into the savings account. New balance: %d\n", depositAmount, account[i].balance);
            found = 1;
         
        }
    }

    if (!found) {
        printf("Account not found or deposit not processed.\n");
    }

    printf("Press any key continue\n ");
    _getch();
    printf("Thank you");
    return;
}

void savingsAccountWithdraw(struct details *account, int accountNumber, int targetAccountNumber) {
    int withdrawAmount;
    int found = 0;
    for (int i = 0; i < accountNumber; i++) {
        if (account[i].acc_number == targetAccountNumber) {
            found = 1;
            printf("Selected savings account withdrawal\n");
            printf("Enter the withdrawal amount: ");
            scanf("%d", &withdrawAmount);
            if (withdrawAmount <= account[i].balance) {
                account[i].balance -= withdrawAmount;
                printf("Withdrawn %d from the savings account. New balance: %d\n", withdrawAmount, account[i].balance);
            } else {
                printf("Insufficient balance in the savings account.\n");
            }
           
        }
    }

    if (!found) {
        printf("Account not found or withdrawal not processed.\n");
        
    }

    printf("Press any key to continue ");
    _getch();+
    printf("Thank you");
    return;
}

void openFixedDeposit(struct details *account, int accountNumber, int targetAccountNumber, int depositAmount) {
    int found = 0;
    for (int i = 0; i < accountNumber; i++) {
        if (account[i].acc_number == targetAccountNumber) {
            found = 1;
            printf("Selected open fixed deposit\n");

            if (depositAmount <= 0) {
                printf("Invalid deposit amount. Please enter a positive amount.\n");
                return;
            }

            account[i].fixed_deposit_amount = depositAmount;
            time(&account[i].fixed_deposit_start_time);

            printf("Fixed deposit of %d opened and added to the account.\n", depositAmount);

            
        }
    }

    if (!found) {
        printf("Account not found or deposit not processed.\n");
        
    }
    printf("Press any key to continue ");
    _getch();
    printf("Thank you");
    return;
}

void withdrawFixedDeposit(struct details *account, int accountNumber, int targetAccountNumber) {
    int found = 0;
    for (int i = 0; i < accountNumber; i++) {
        if (account[i].acc_number == targetAccountNumber) {
            found = 1;
            printf("Selected withdraw fixed deposit\n");

            if (account[i].fixed_deposit_amount <= 0) {
                printf("No active fixed deposit found.\n");
                return;
            }

            time_t currentTime;
            time(&currentTime);
            double elapsedMonths = difftime(currentTime, account[i].fixed_deposit_start_time) / (30.44 * 24 * 60 * 60); // Approximate days in a month
            double interest = (account[i].fixed_deposit_amount * fixedDepositInterest * elapsedMonths) / 12;

            
            account[i].balance += account[i].fixed_deposit_amount + (int)interest;
            account[i].fixed_deposit_amount = 0;

            printf("Fixed deposit withdrawn. Added %d interest and principal amount to the account balance. New balance: %d\n", (int)interest, account[i].balance);

            
        }
    }

    if (!found) {
        printf("Account not found or deposit not processed.\n");
        
    }

    
    printf("Press any key to continue ");
    _getch();
    printf("Thank you");
    return;
}

void applyLoan(struct details *account, int accountNumber, int targetAccountNumber){
    int loanAmount;

    int found = 0;

    for (int i = 0; i < accountNumber; i++) {
        if (account[i].acc_number == targetAccountNumber) {
            found = 1;
            printf("Selected apply for loan\n");
            printf("Enter the loan amount: ");
            scanf("%d", &loanAmount);
            printf("Enter time period in months: ");
            scanf("%i", &account[i].months);
            

            if (loanAmount <= 0) {
                printf("Invalid loan amount. Please enter a positive amount.\n");
                return;
            }

            account[i].loan_amount = loanAmount + (loanAmount * 7.5 * account[i].months)/1200;
            account[i].monthlyAmount = account[i].loan_amount/12;


            time(&account[i].loan_start_time); 

            printf("Loan of %d applied and added to the account\nTotal loan amount: %d\n Monthly payment: %f", loanAmount, account[i].loan_amount, account[i].monthlyAmount);

            
        }
    }

    if (!found) {
        printf("Account not found or loan not processed.\n");
        
    }

    printf("Press any key to continue ");
    _getch();
    printf("Thank you");
    return;

}

void monthlyRepayment(struct details *account, int accountNumber, int targetAccountNumber) {
    int found = 0;
    for (int i = 0; i < accountNumber; i++) {
        if (account[i].acc_number == targetAccountNumber) {
            found = 1;
            printf("Selected monthly loan repayment\n");

            if (account[i].loan_amount <= 0) {
                printf("No outstanding loans to repay.\n");
                return;
            }

            time_t currentTime;
            time(&currentTime);
            double elapsedMonths = difftime(currentTime, account[i].loan_start_time) / (30 * 24 * 60 * 60); 

            if (elapsedMonths >= 1) {
               
                float monthlyRepaymentAmount = account[i].monthlyAmount;
                account[i].balance -= monthlyRepaymentAmount;

                printf("Monthly loan repayment applied to the account. New balance: %d\n", account[i].balance);

                time(&account[i].loan_start_time);
            } else {
                printf("You can only make monthly repayments after the first month of the loan.\n");
            }

            
        }
    }

    if (!found) {
        printf("Account not found or loan repayment not processed.\n");
        
    }

    printf("Press any key to continue ");
    _getch();
    printf("Thank you");
    return;
}


int main() {
    struct details det[30];

    int acn = 0;
    int choice = 1;
    int maxChoice = 9;
    char key;


    while (1) {
        system("cls");

        printf("=== Banking System Main Menu ===(Press w and s to scroll up and down and k to select)\n");
        for (int i = 1; i <= maxChoice; i++) {
            if (i == choice) {
                printf("-> ");
            } else {
                printf("   ");
            }
            switch (i) {
                case 1:
                    printf("1. Create New Account\n");
                    break;
                case 2:
                    printf("2. Deposit Funds\n");
                    break;
                case 3:
                    printf("3. Withdraw Funds\n");
                    break;
                case 4:
                    printf("4. Open Fixed Deposit\n");
                    break;
                case 5:
                    printf("5. Deposit/Withdraw Fixed Deposit\n");
                    break;
                case 6:
                    printf("6. Apply for Loan\n");
                    break;
                case 7:
                    printf("7. Monthly Loan Repayment\n");
                    break;
                case 8:
                    printf("8. Account Inquiry\n");
                    break;
                case 9:
                    printf("9. Exit\n");
                    break;
            }
        }

        key = getch();

        switch (key) {
            case 'w':
                if (choice > 1) {
                    choice--;
                }
                break;
            case 's':
                if (choice < maxChoice) {
                    choice++;
                }
                break;
            case 'k':
                switch (choice) {
                    case 1:
                        createAccount(det, &acn);
                        break;
                    case 2:
                        printf("Deposit selected.\n");
                        int targetAccountNumber2;
                        printf("Enter the Account Number for the deposit: ");
                        scanf("%d", &targetAccountNumber2);
                        savingsAccountDeposit(det, acn, targetAccountNumber2);
                        break;
                    case 3:
                        printf("Withdrawal selected.\n");
                        printf("Savings Account Withdrawal selected.\n");
                        int withdrawAccountNumber;
                        printf("Enter the Account Number for the withdrawal: ");
                        scanf("%d", &withdrawAccountNumber);
                        savingsAccountWithdraw(det, acn, withdrawAccountNumber);
                        break;
                    case 4:
                        printf("Open Fixed Deposit selected\n");
                        int targetAccountNumber4;
                        printf("Enter the Account Number for opening a fixed deposit: ");
                        scanf("%d", &targetAccountNumber4);

                        int depositAmount;

                        printf("Enter the deposit amount for the fixed deposit: ");
                        scanf("%d", &depositAmount);
                        openFixedDeposit(det, acn, targetAccountNumber4, depositAmount);
                        
                        break;

                    case 5:
                        printf("Selected Open/Withdraw Fixed Deposit\n");
                        int targetAccountNumber5;
                        printf("Enter the Account Number: ");
                        scanf("%d", &targetAccountNumber5);
                        printf("Enter the deposit amount (0 to withdraw fixed deposit): ");
                        scanf("%d", &depositAmount);
                        if (depositAmount > 0) {
                            openFixedDeposit(det, acn, targetAccountNumber5, depositAmount);
                        } else {
                            withdrawFixedDeposit(det, acn, targetAccountNumber5);
                        }
                        break;

                    case 6:
                        printf("Apply for Loan selected.\n");
                        int targetAccountNumber6;
                        printf("Enter the Account Number to apply for a loan: ");
                        scanf("%d", &targetAccountNumber6);
                        applyLoan(det, acn, targetAccountNumber6);
                        break;
                    case 7:
                        printf("Monthly Loan Repayment selected.\n");
                        int targetAccountNumber7;
                        printf("Enter the Account Number for loan repayment: ");
                        scanf("%d", &targetAccountNumber7);
                        monthlyRepayment(det, acn, targetAccountNumber7);
                        break;    
                    case 8:
                        printf("Account Inquiry selected.\n");
                        int targetAccountNumber8;
                        printf("Enter the Account Number to inquire: ");
                        scanf("%d", &targetAccountNumber8);
                        accountInquiry(det, acn, targetAccountNumber8);
                        break;
                    case 9:
                        printf("Exiting the program. Goodbye!\n");
                        return 0;
                }
                break;
        }
    }

    return 0;
}
