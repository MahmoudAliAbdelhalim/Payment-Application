/* -----------------------------------------------------------------------------------------------------------

	[FILE NAME]:	<TERMINAL.C>

	[AUTHOR(S)]:	<MAHMOUD ALI ABDELHALIM ALI>

	[DATE CREATED]:	<18/8/2022>

	[DESCRIPTION]: <C FILE FOR PAYMENT APPLICATION TERMINAL>

-------------------------------------------------------------------------------------------------------------*/
/************************************************* INCLUDES **************************************************/
#include<stdio.h>
#include"terminal.h"
#include"card.h"
#include<string.h>
#include<stdlib.h>
/******************************************* FUNCTIONS DEFINITIONS *******************************************/
/*------------------------------------------------------------------------------------------------------------
	[Function Name]:getTransactionDate
	[Description]:	This function is responsible for getting transaction date from user and store it into
					transactionDate string member of terminal data structure.
	[Arguments]
	[in]:			Pointer to structure from ST_terminalData_t structure type.
	[out]:			None
	[Return]:		Enumeration member of terminal State (TERMINAL_OK,WRONG_DATE)
-------------------------------------------------------------------------------------------------------------*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("\nEnter transaction date: ");
	scanf("%s", termData->transactionDate);
	/* If the transaction date is NULL or less than 10 characters */
	if (termData->transactionDate == NULL)
	{
		return WRONG_DATE;
	}
	if(strlen(termData->transactionDate) < 8)
	{
		return WRONG_DATE;
	}
	/* If the transaction date has a wrong format */
	else if ( (termData->transactionDate[2] != '/') && (termData->transactionDate[5] != '/'))
	{
		return WRONG_DATE;
	}
	else
	{
		return TERMINAL_OK;
	}
}

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:isCardExpired
	[Description]:	This function is responsible for comparing the card expiry date with the transaction date.
	[Arguments]
	[in]:			funcArgType1 cardData Pointer:
					indicates to pointer to structure from ST_cardData_t structure type.
	[in]:			funcArgType2 termData Pointer:
					indicates to pointer to structure from ST_terminalData_t structure type.
	[out]:			None
	[Return]:		Enumeration member of terminal State (TERMINAL_OK,EXPIRED_CARD)
-------------------------------------------------------------------------------------------------------------*/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	/* declaration of 4 variables to store card expiry date*/
	uint8_t card_exp_years_tens = cardData->cardExpirationDate[3];
	uint8_t card_exp_years_ones = cardData->cardExpirationDate[4];
	uint8_t card_exp_months_tens = cardData->cardExpirationDate[0];
	uint8_t card_exp_months_ones = cardData->cardExpirationDate[1];

	/* declaration of 4 variables to store transaction date*/
	uint8_t trans_years_tens = termData->transactionDate[8];
	uint8_t trans_years_ones = termData->transactionDate[9];
	uint8_t trans_months_tens = termData->transactionDate[3];
	uint8_t trans_months_ones = termData->transactionDate[4];

	/* check card expiry years's tens */
	/* in case of tens of years of card expiry date more than tens of years of transaction date */
	if (card_exp_years_tens < trans_years_tens)
	{
		return EXPIRED_CARD;
	}

	/* in case of tens of years of both are equal */
	else if (card_exp_years_tens == trans_years_tens)
	{
		/* check card expiry years's ones*/
		/* in case of ones of years of card expiry date is more than ones of years of transaction date */
		if (card_exp_years_ones < trans_years_ones)
		{
			return EXPIRED_CARD;
		}

		/* in case of ones of years of both are equal */
		else if (card_exp_years_ones == trans_years_ones)
		{
			/*check card expiry months's tens*/
			/* in case of tens of months of card expiry date more than tens of months of transaction date */
			if (card_exp_months_tens < trans_months_tens)
			{
				return EXPIRED_CARD;
			}
			/* in case of tens of months of both are equal */
			else if (card_exp_months_tens == trans_months_tens)
			{
				/*check card expiry months's ones*/
				/* in case of ones of months of card expiry date is more than ones of months of transaction date */
				if (card_exp_months_ones < trans_months_ones)
				{
					return EXPIRED_CARD;
				}
				/* in case of ones of months of both are equal */
				else if (card_exp_months_ones == trans_months_ones)
				{
					return EXPIRED_CARD;
				}
				/* in case of ones of months of card expiry date is less than ones of months of transaction date */
				else
				{
					return TERMINAL_OK;
				}
			}
			/* in case of tens of months of card expiry date is less than tens of months of transaction date */
			else
			{
				return TERMINAL_OK;
			}
		}
		/* in case of years of months of card expiry date is less than ones of years of transaction date */
		else
		{
			return TERMINAL_OK;
		}
	}
	/* in case of tens of years of card expiry date is less than tens of years of transaction date */
	else
	{
		return TERMINAL_OK;
	}
}

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	getTransactionAmount
	[Description]:	This function is responsible for getting transaction amount from user and store it into
					transAmount string member of terminal data structure.
	[Arguments]
	[in]:			termData Pointer to structure from ST_terminalData_t structure type.
	[out]:			None
	[Return]:		Enumeration member of terminal State (TERMINAL_OK,INVALID_AMOUNT)
-------------------------------------------------------------------------------------------------------------*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("\nEnter transaction amount: ");
	scanf("%f", &termData->transAmount);

	/* If the transaction amount is less than or equal to 0 */
	if (termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:isBelowMaxAmount
	[Description]:	This function is responsible for comparing the transaction amount with the terminal max amount.
	[Arguments]
	[in]:			termData Pointer to structure from ST_terminalData_t structure type.
	[out]:			None
	[Return]:		Enumeration member of terminal State (TERMINAL_OK,EXCEED_MAX_AMOUNT)
-------------------------------------------------------------------------------------------------------------*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	/* If the transaction amount is larger than the terminal max amount */
	if ((termData->transAmount) > (termData->maxTransAmount))
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	setMaxAmount
	[Description]:	This function is responsible for setting the maximum allowed amount into transAmount
					string member of terminal data structure.
	[Arguments]
	[in]:			termData Pointer to structure from ST_terminalData_t structure type.
	[out]:			None
	[Return]:		Enumeration member of terminal State (TERMINAL_OK,INVALID_MAX_AMOUNT )
-------------------------------------------------------------------------------------------------------------*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("\nEnter maximum amount allowed: ");
	scanf("%f", &termData->maxTransAmount);
	/* If transaction max amount less than or equal to 0 */
	if (termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}
