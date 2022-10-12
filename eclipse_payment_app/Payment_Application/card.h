/* -----------------------------------------------------------------------------------------------------------

	[FILE NAME]:	<CARD.H>

	[AUTHOR(S)]:	<MAHMOUD ALI ABDELHALIM ALI>

	[DATE CREATED]:	<18/8/2022>

	[DESCRIPTION]: <HEADER FILE FOR PAYMENT APPLICATION CARD>

-------------------------------------------------------------------------------------------------------------*/
/********************************************* HEADER FILE GAURD *********************************************/
#ifndef CARD_H
#define CARD_H
/************************************************* INCLUDES **************************************************/
#include "std_types.h"
#include "common_macros.h"
/************************************************ STRUCTURES ************************************************/
/*-------------------------------------------------------------------------------------------------------------
	[Structure Name]: ST_cardData_t
	[Structure Description]: This structure for maintaining card data.
	[Structure Members]:
		1. string of 25 characters to store card holder name
		2. string of 20 numbers to store card pan
		3. string of 6 numbers to store card expiration date
-------------------------------------------------------------------------------------------------------------*/
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

/********************************************* ENUMERATIONS **************************************************/
/*-------------------------------------------------------------------------------------------------------------
	[Enumeration Name]: EN_cardError_t
	[Enumeration Description]: This enumeration for Card errors
	[Enumeration Members]:
		1. CARD_OK -> 0
		2. WRONG_NAME -> 1
		3. WRONG_EXP_DATE -> 2
		4. WRONG_PAN -> 3
-------------------------------------------------------------------------------------------------------------*/
typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/******************************************** Functions Prototypes *******************************************/
/*------------------------------------------------------------------------------------------------------------
	[Function Name]:getCardHolderName
	[Description]:	This function is responsible for getting card holder name from user and store it into
					cardHolderName string member of card data structure.
	[Arguments]
	[in]:			cardData Pointer to structure from ST_cardData structure type.
	[out]:			None
	[Return]:		Enumeration member of Card State
-------------------------------------------------------------------------------------------------------------*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

/*------------------------------------------------------------------------------------------------------------
	[Function Name] :	getCardExpiryDate
	[Description] :		This function is responsible for getting card expiry date from user and store it into
						cardExpirationDate string member of card data structure.
	[Arguments]
	[in] :				cardData Pointer to structure from ST_cardData structure type.
	[out] :				None
	[Return] :			Enumeration member of Card State(CARD_OK or WRONG_EXP_DATE)
------------------------------------------------------------------------------------------------------------ - */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	getCardPAN
	[Description]:	This function is responsible for getting card primary account number from user and store it
					into primaryAccountNumber string member of card data structure.
	[Arguments]
	[in]:			cardData Pointer to structure from ST_cardData structure type.
	[out]:			None
	[Return]:		Enumeration member of Card State (CARD_OK or WRONG_PAN)
-------------------------------------------------------------------------------------------------------------*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif
