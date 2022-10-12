/* -----------------------------------------------------------------------------------------------------------

	[FILE NAME]:	<SERVER.C>

	[AUTHOR(S)]:	<MAHMOUD ALI ABDELHALIM ALI>

	[DATE CREATED]:	<18/8/2022>

	[DESCRIPTION]: <C FILE FOR PAYMENT APPLICATION SERVER>

-------------------------------------------------------------------------------------------------------------*/
/************************************************* INCLUDES **************************************************/
#include<stdio.h>
#include "server.h"
#include"terminal.h"
#include"card.h"
#include<string.h>

/********************************************* GLOBAL VARIABLES **********************************************/

/* Global array of ST_accountsDB_t structure type for the valid accounts data base */
ST_accountsDB_t database_accounts[DB_ACCOUNTS_MAX_NUM] = { {2000.0,  RUNNING, "8989374615436851"},
										   {70000.0, RUNNING, "5807007076043875"},
										   {1000.0,  RUNNING, "9784215845672154"},
										   {975000.0,BLOCKED, "8520247655988112"},
										   {45300.0, RUNNING, "7601559452155364"},
										   {3870.0,  RUNNING, "9745164214657466"},
										   {119200.0,RUNNING, "7347945764576427"},
										   {55700,	 RUNNING, "5146513845121335"},
										   {849000,  BLOCKED, "8464213429154747"},
										   {9800.0,  RUNNING, "1447587532745714"}
};

/* Global array of ST_transaction_t structure type to save transactions */
ST_transaction_t database_transactions[DB_TRANSACTIONS_NUM] = { 0 };

/********************************************* GLOBAL VARIABLES ***********************************************/
/* Global Pointer to save the account address in the accounts DB. */
ST_accountsDB_t* accountAddress_ptr = NULL;

/******************************************* FUNCTIONS DEFINITIONS *******************************************/

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	recieveTransactionData
	[Description]:	This function will take all transaction data and validate its data and save it into
					transactions data base if its approved.
	[in]:			transData Pointer to structure from ST_transactionl_t structure type.
	[out]:			None
	[Return]:		Enumeration member of transaction State (APPROVED,DECLINED_INSUFFECIENT_FUND,
					DECLINED_STOLEN_CARD,INTERNAL_SERVER_ERROR,)
-------------------------------------------------------------------------------------------------------------*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	/* It checks the account details and amount availability */
	for (int i = 0; i < DB_ACCOUNTS_AVAILABE; i++)
	{
		/* In case of the card holder account is valid in server accounts data base */
		if (!(strcmp(transData->cardHolderData.primaryAccountNumber,database_accounts[i].primaryAccountNumber)))
		{
			/* In case of the card holder account balance is less than the transaction amount */
			if ((database_accounts[i].balance) < (transData->terminalData.transAmount))
			{
				return DECLINED_INSUFFECIENT_FUND;
			}
			/* In case of the card holder account state in data base is blocked */
			else if ((database_accounts[i].state) == BLOCKED)
			{
				return DECLINED_STOLEN_CARD;
			}
			/* In case of the transaction can not be saved */
			else if ((saveTransaction(transData)) == SAVING_FAILED)
			{
				return INTERNAL_SERVER_ERROR;
			}
			/* In case of the card holder balance is more than the transaction amount */
			else if ((transData->terminalData.transAmount) <= (database_accounts[i].balance))
			{
				/* update the card holder account balance in data base */
				database_accounts[i].balance -= transData->terminalData.transAmount;
				return APPROVED;
			}
		}
		/* In case of the card holder account is not valid in server accounts data base */
		else
		{
			return FRAUD_CARD;
		}
	}

}

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	isValidAccount
	[Description]:	This function will take card data and validate if the account related to
					this card exists or not.
	[in]:			funcArg1-> cardData Pointer to structure from ST_cardData_t structure type.
	[out]:			funcArg2-> accountRefrence Pointer to structure from ST_accountsDB_t structure type.
	[Return]:		Enumeration member of server State (SERVER_OK,ACCOUNT_NOT_FOUND)
-------------------------------------------------------------------------------------------------------------*/
EN_serverError_t isValidAccount(ST_cardData_t * cardData, ST_accountsDB_t * accountRefrence)
{
	/* It checks the account details and amount availability */
	for (int i = 0; i < DB_ACCOUNTS_AVAILABE; i++)
	{
			/* In case the card holder account is valid in server accounts data base */
		if (!(strcmp(cardData->primaryAccountNumber,database_accounts[i].primaryAccountNumber)))
		{
			accountRefrence = &database_accounts[i];
			accountAddress_ptr = &database_accounts[i];
			return SERVER_OK;
		}
	}
		return ACCOUNT_NOT_FOUND;
}

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	isAmountAvailable
	[Description]:	This function will take terminal data and validate these data and It checks
					if the transaction's amount is available or not.
	[in]:			termData Pointer to structure from ST_terminalData_t structure type.
	[out]:			None.
	[Return]:		Enumeration member of server State (SERVER_OK,LOW_BALANCE)
-------------------------------------------------------------------------------------------------------------*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	/* In case of the card holder account balance is less than the transaction amount */
	if ((accountAddress_ptr->balance) < (termData->transAmount))
	{
		return LOW_BALANCE;
	}
	else
	{
		return SERVER_OK;
	}
}

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	saveTransaction
	[Description]:	This function will store all transaction data in the transactions database.
	[in]:			termData Pointer to structure from ST_terminalData_t structure type.
	[out]:			None.
	[Return]:		Enumeration member of server State (SERVER_OK,LOW_BALANCE)
-------------------------------------------------------------------------------------------------------------*/
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	/* validate of transaction data */
	uint32_t trans_index;
	if(DROPPED_CONNECTION == 0)
	{
		transData->transactionSequenceNumber += 1;

		trans_index = transData->transactionSequenceNumber - 1;

											/* save transaction data */
	/* 1.save the transaction sequence number in the transactions data base */
		database_transactions[trans_index].transactionSequenceNumber = transData->transactionSequenceNumber;

	/* 2. save the card holder data in the transactions data base */
		strcpy(database_transactions[trans_index].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
		strcpy(database_transactions[trans_index].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
		strcpy(database_transactions[trans_index].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);

	/* 3. save the terminal data in the transactions data base */
		database_transactions[trans_index].terminalData.transAmount = transData->terminalData.transAmount;
		strcpy(database_transactions[trans_index].terminalData.transactionDate, transData->terminalData.transactionDate);

	/* 4. save the transaction state in the transactions data base */
		database_transactions[trans_index].transState = transData->transState;

	/* 5. Check if the transaction is already saved successfully */
		if ( (getTransaction(database_transactions[trans_index].transactionSequenceNumber, database_transactions) ) == SERVER_OK )
		{
			return SERVER_OK;
		}
		else
		{
			return SAVING_FAILED;
		}
	}
	else
	{
		return SAVING_FAILED;
	}
}

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	getTransaction
	[Description]:	This function takes the sequence number of a transaction and returns the transaction data
					if found in the transactions DB.
	[in]:			funcArg1-> Integer called transactionSequenceNumber has Sequence number of the transcation.
	[out]:			funcArg2-> termData Pointer to structure from ST_terminalData_t structure type.
	[Return]:		Enumeration member of server State (SERVER_OK,TRANSACTION_NOT_FOUND)
-------------------------------------------------------------------------------------------------------------*/
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	/* Check if the transaction is valid by the given transaction sequence number in the transaction DB */
	for( int i=0 ; i < DB_TRANSACTIONS_NUM ; i++)
	{
		/* In case of the transaction is exist */
		if ( (database_transactions->transactionSequenceNumber) == transactionSequenceNumber)
		{
			/* Return the transaction data if found in the transactions DB */
			transData = &database_transactions[transactionSequenceNumber-1];
			return SERVER_OK;
		}
	}
	/* In case of the transaction is not found. */
	return TRANSACTION_NOT_FOUND;
}
