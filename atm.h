#pragma once
#define MAX 100
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
struct Account {            //account with 7 members
	char bank_name[MAX];    // name of bank
	char id[MAX];           // id since our id more than 32.000 we are using strings
	char fist_name[MAX];    // holder's first name
	char last_name[MAX];    // holder's last name
	int password;           // password
	int account_number;     // holder's account number with 8 digits
	int balance;            // holder's amount in its account
};
typedef struct Account Account; // every time we don't need to use our Account variable with its
								//key word struct so we are just naming it

typedef struct {
	int count;
	Account* buffer;
}ATM;// same as above naming ATM while creation and use it without struct key word and 
	 // this struct keep number of elements and pointer to the struct, it means
	 // we can create the arrays of structures

	 /********************* 5 MAIN FUNCTIONS FOR OUR ATM ********************/
ATM* Create_Atm();               // CREATE ATM
void withdrawal(ATM*);          // WITHDRAWAL FUNCTION
void deposit(ATM*);            // DEPOSIT FUNCTION
void balance_check(ATM*);     // CHECK_BALANCE FUNCTION
void transfer(ATM*);         // TRANSFER FUNCTION
void transaction_history(); // CHECK_TRANS_HISTORY

							/******************* 5 SUBFUNCTIONS FOR OUR ATM **********************/
void put_back(ATM* atm);
static bool search_ID(ATM* atm, char* id, int* x);
static bool search_Bank(ATM* atm, int* account_num, int* x);
static void balance_receipt(ATM* atm, int* x);
static void transfer_receipt(ATM* atm, int* position1, int* position2, int* amount);