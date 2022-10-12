/* -----------------------------------------------------------------------------------------------------------

	[FILE NAME]:	<CARD.C>

	[AUTHOR(S)]:	<MAHMOUD ALI ABDELHALIM ALI>

	[DATE CREATED]:	<18/8/2022>

	[DESCRIPTION]: <C FILE FOR PAYMENT APPLICATION CARD>

-------------------------------------------------------------------------------------------------------------*/
/************************************************* INCLUDES **************************************************/
#include<stdio.h>
#include"card.h"
#include<string.h>

/******************************************* FUNCTIONS DEFINITIONS *******************************************/

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:getCardHolderName
	[Description]:	This function is responsible for getting card holder name from user and store it into
					cardHolderName string member of card data structure.
	[Arguments]
	[in]:			cardData Pointer to structure from ST_cardData structure type.
	[out]:			None
	[Return]:		Enumeration member of Card State
-------------------------------------------------------------------------------------------------------------*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("\nEnter card holder name: ");
	scanf("%s", cardData->cardHolderName);
	/* If Card holder name is NULL*/
	if (cardData->cardHolderName == NULL)
	{
		return WRONG_NAME;
	}
	/* If Card holder name is less than 20 characters or more than 24 */
	else if ((strlen(cardData->cardHolderName) < 20) || (strlen(cardData->cardHolderName) > 24))
	{
		return WRONG_NAME;
	}
	else
	{
		return CARD_OK;
	}
}

/*------------------------------------------------------------------------------------------------------------
	[Function Name] :	getCardExpiryDate
	[Description] :		This funtion is responsible for getting card expiry date from userand store it into
						cardExpirationDate string member of card data structure.
	[Arguments]
	[in] :				cardData Pointer to structure from ST_cardData structure type.
	[out] :				None
	[Return] :			Enumeration member of Card State(CARD_OK or WRONG_EXP_DATE)
------------------------------------------------------------------------------------------------------------ - */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("\nEnter card expiry date as MM/YY : ");
	scanf("%s", cardData->cardExpirationDate);

	/* If the card expiry date is NULL or not equal 5 characters */
	if (cardData->cardExpirationDate == NULL || strlen(cardData->cardExpirationDate) != 5)
	{
		return WRONG_EXP_DATE;
	}
	/* If the card expiry date has a wrong format */
	else if (cardData->cardExpirationDate[2] != '/')
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		return CARD_OK;
	}
}

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	getCardPAN
	[Description]:	This function is responsible for getting card primary account number from user and store it
					into primaryAccountNumber string member of card data structure.
	[Arguments]
	[in]:			cardData Pointer to structure from ST_cardData structure type.
	[out]:			None
	[Return]:		Enumeration member of Card State (CARD_OK or WRONG_PAN)
-------------------------------------------------------------------------------------------------------------*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("\nEnter card primary account number : ");
	scanf("%s", cardData->primaryAccountNumber);
	/* If the PAN is NULL */
	if (cardData->primaryAccountNumber == NULL)
	{
		return WRONG_PAN;
	}
	/* If the PAN is less than 16 or more than 19 characters*/
	else if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
	{
		return WRONG_PAN;
	}
	else
	{
		return CARD_OK;
	}

}
