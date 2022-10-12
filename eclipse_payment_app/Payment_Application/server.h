/* -----------------------------------------------------------------------------------------------------------

	[FILE NAME]:	<SERVER.H>

	[AUTHOR(S)]:	<MAHMOUD ALI ABDELHALIM ALI>

	[DATE CREATED]:	<18/8/2022>

	[DESCRIPTION]: <HEADER FILE FOR PAYMENT APPLICATION SERVER>

-------------------------------------------------------------------------------------------------------------*/
/********************************************* HEADER FILE GAURD *********************************************/
#ifndef SERVER_H
#define SERVER_H
/************************************************ INCLUDES ***************************************************/
#include "std_types.h"
#include "common_macros.h"
#include "card.h"
#include "terminal.h"

/*********************************************** DEFINITIONS *************************************************/
#define DB_ACCOUNTS_MAX_NUM		255
#define DB_ACCOUNTS_AVAILABE	10
#define DB_TRANSACTIONS_NUM		255
#define DROPPED_CONNECTION		0

/********************************************* ENUMERATIONS **************************************************/
/*-------------------------------------------------------------------------------------------------------------
 	[Enumeration Name]: EN_transState_t
	[Enumeration Description]: This enumeration for transaction errors
	[Enumeration Members]:
		1. APPROVED -> 0
		2. DECLINED_INSUFFECIENT_FUND -> 1
		3. DECLINED_STOLEN_CARD -> 2
		4. FRAUD_CARD -> 3
		5. INTERNAL_SERVER_ERROR -> 4
-------------------------------------------------------------------------------------------------------------*/
typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

/*-------------------------------------------------------------------------------------------------------------
	[Enumeration Name]: EN_serverError_t
	[Enumeration Description]: This enumeration for server errors
	[Enumeration Members]:
		1. SERVER_OK -> 0
		2. SAVING_FAILED -> 1
		3. TRANSACTION_NOT_FOUND -> 2
		4. ACCOUNT_NOT_FOUND -> 3
		5. LOW_BALANCE -> 4
		6. BLOCKED_ACCOUNT -> 5
-------------------------------------------------------------------------------------------------------------*/
typedef enum EN_serverError_t
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

/*-------------------------------------------------------------------------------------------------------------
 	[Enumeration Name]:			EN_accountState_t
	[Enumeration Description]:	This enumeration for Account states
	[Enumeration Members]:
		1. RUNNING -> 0
		2. BLOCKED -> 1
-------------------------------------------------------------------------------------------------------------*/
typedef enum EN_accountState_t
{
	 RUNNING, BLOCKED
}EN_accountState_t;
/*********************************************** STRUCTURES **************************************************/
/*-------------------------------------------------------------------------------------------------------------
	[Structure Name]: ST_transaction_t
	[Structure Description]: This structure for maintaining information transaction Data
	[Structure Members]:
		1. structure variable from card data type that has a card holder data
		2. structure variable from card data type that has a terminal data
		3. Enumeration variable from transaction state type that has a transaction state
		4. float variable that has a transaction sequence number
-------------------------------------------------------------------------------------------------------------*/
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

/*-------------------------------------------------------------------------------------------------------------
	[Structure Name]: ST_accountsDB_t
	[Structure Description]: This structure for maintaining accounts Data Base
	[Structure Members]:
		1. float varibale that has an account balance
		2. Enumeration varibale from account state type that has an account state
		3. string of 20 numbers that has a primary account number
-------------------------------------------------------------------------------------------------------------*/
typedef struct ST_accountsDB_t
{
	float32_t balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

/******************************************** Functions Prototypes *******************************************/

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	recieveTransactionData
	[Description]:	This function will take all transaction data and validate its data and save it into
					transactions data base if its approved.
	[in]:			transData Pointer to structure from ST_transactionl_t structure type.
	[out]:			None
	[Return]:		Enumeration member of transaction State (APPROVED,DECLINED_INSUFFECIENT_FUND,
					DECLINED_STOLEN_CARD,INTERNAL_SERVER_ERROR,)
-------------------------------------------------------------------------------------------------------------*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData);

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	isValidAccount
	[Description]:	This function will take card data and validate if the account related to
					this card exists or not.
	[in]:			funcArg1-> cardData Pointer to structure from ST_cardData_t structure type.
	[out]:			funcArg2-> accountRefrence Pointer to structure from ST_accountsDB_t structure type.
	[Return]:		Enumeration member of server State (SERVER_OK,ACCOUNT_NOT_FOUND)
-------------------------------------------------------------------------------------------------------------*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	isAmountAvailable
	[Description]:	This function will take terminal data and validate these data and It checks
					if the transaction's amount is available or not.
	[in]:			termData Pointer to structure from ST_terminalData_t structure type.
	[out]:			None.
	[Return]:		Enumeration member of server State (SERVER_OK,LOW_BALANCE)
-------------------------------------------------------------------------------------------------------------*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	saveTransaction
	[Description]:	This function will store all transaction data in the transactions database.
	[in]:			termData Pointer to structure from ST_terminalData_t structure type.
	[out]:			None.
	[Return]:		Enumeration member of server State (SERVER_OK,LOW_BALANCE)
-------------------------------------------------------------------------------------------------------------*/
EN_serverError_t saveTransaction(ST_transaction_t* transData);

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	getTransaction
	[Description]:	This function takes the sequence number of a transaction and returns the transaction data
					if found in the transactions DB.
	[in]:			funcArg1-> Integer called transactionSequenceNumber has Sequence number of the transcation.
	[out]:			funcArg2-> termData Pointer to structure from ST_terminalData_t structure type.
	[Return]:		Enumeration member of server State (SERVER_OK,TRANSACTION_NOT_FOUND)
-------------------------------------------------------------------------------------------------------------*/
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);

#endif
