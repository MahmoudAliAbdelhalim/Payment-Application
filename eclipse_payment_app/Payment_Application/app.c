/* -----------------------------------------------------------------------------------------------------------

	[FILE NAME]:	<APP.C>

	[AUTHOR(S)]:	<MAHMOUD ALI ABDELHALIM ALI>

	[DATE CREATED]:	<18/8/2022>

	[DESCRIPTION]: <C FILE FOR PAYMENT APPLICATION >

-------------------------------------------------------------------------------------------------------------*/
/************************************************* INCLUDES **************************************************/
#include<stdio.h>
#include "server.h"
#include"terminal.h"
#include"card.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
/********************************************* GLOBAL VARIABLES ***********************************************/
/* Global Structure variable from card data structure type to store card data */
ST_cardData_t clientCardData;

/* Global Structure variable from terminal data structure type to store terminal data */
ST_terminalData_t transTermData;

/* Global Structure variable from transaction structure type to store transaction data */
ST_transaction_t transactionData;

/* Global Integer variable from transaction structure type to store the transaction sequence number */
uint32_t SEQ_NUM;

/* Global Pointer variable to structure from transaction structure type */
ST_transaction_t* transPtr;

/* Global Pointer to save the account address in the accounts DB. */
ST_accountsDB_t* cardAccountAddress = NULL;
/******************************************* FUNCTIONS DEFINITIONS ********************************************/
/*------------------------------------------------------------------------------------------------------------
	[Function Name]:appStart
	[Description]:	This function is responsible for start the application
	[in]:			Void
	[out]:			None
	[Return]:		Void
-------------------------------------------------------------------------------------------------------------*/
void appStart(void)
{
	/****************************** Getting the card holder data from the card *******************************/
				/* a. Get the card name from the client*/
				getCardHolderName(&clientCardData);
				/* b. Get the card expiry date from the client*/
				getCardExpiryDate(&clientCardData);
				/* c. Get the card primary account number from the client */
				getCardPAN(&clientCardData);

				/******************** Getting the terminal data of the transaction from the terminal *********************/
				/* a. Get Transaction Date from the terminal and store it into transTermData structure */
				getTransactionDate(&transTermData);

				/************************************ 1. Expired card user story *****************************************/
				if ((isCardExpired(&clientCardData, &transTermData)) == EXPIRED_CARD)
				{
					printf("\nDeclined, Expired Card!");
					return;
				}

				/**************************************** Card is not expired ********************************************/
				else
				{
					/* b. Set the maximum amount for withdrawal */
					setMaxAmount(&transTermData);
					/* c. Get the transaction amount from the terminal and store it into transTermData structure */
					getTransactionAmount(&transTermData);

					/**************************** 2. Exceed the maximum amount user story ********************************/
					if ( (isBelowMaxAmount(&transTermData)) == EXCEED_MAX_AMOUNT)
					{
						printf("\nDeclined, Amount Exceeding Limit!");
						return;
					}
					/************************** Transaction amount is below the maximum amount ***************************/
					else
					{
						/********************************* 3. Invalid card user story ************************************/
						if( (isValidAccount(&clientCardData, cardAccountAddress)) == ACCOUNT_NOT_FOUND)
						{
							printf("\nDeclined, Invalid Account!");
							return;
						}
						/************************************ Card account is valid **************************************/
						else
						{
							/**************************** 4. Insufficient fund user story ********************************/
							if ( (isAmountAvailable(&transTermData)) == LOW_BALANCE)
							{
								printf("\nDeclined, Insufficient funds!");
								return;
							}
							/**************************** 5. Transaction approved user story *****************************/
							else
							{
								/* Receive the transaction data and store it into transactionData structure and update account balance */
								recieveTransactionData(&transactionData);
								/* Save the transaction data into the server transactions DB */
								saveTransaction(&transactionData);
								printf("\nTransaction Approved.");
								return ;
							}
						}
					}
				}
}
/********************************************* MAIN FUNCTION ***********************************************/
int main()
{
	setbuf(stdout,NULL);
	while(1)
	{
		/* a.Start new transaction process */
			appStart();
	}
	return 0;
}
