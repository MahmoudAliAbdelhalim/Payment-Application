/* -----------------------------------------------------------------------------------------------------------

	[FILE NAME]:	<TERMINAL.H>

	[AUTHOR(S)]:	<MAHMOUD ALI ABDELHALIM ALI>

	[DATE CREATED]:	<18/8/2022>

	[DESCRIPTION]: <HEADER FILE FOR PAYMENT APPLICATION TERMINAL>

-------------------------------------------------------------------------------------------------------------*/
/********************************************* HEADER FILE GAURD *********************************************/
#ifndef TERMINAL_H
#define TERMINAL_H
/************************************************* INCLUDES **************************************************/
#include "std_types.h"
#include "common_macros.h"
#include "card.h"
/************************************************ STRUCTURES *************************************************/
/*-------------------------------------------------------------------------------------------------------------
	[Structure Name]: ST_terminalData_t
	[Structure Description]: This structure for maintaining terminal data.
	[Structure Members]:
		1. float variable to store transaction amount
		2. float variable to store maximum transaction amount
		3. string of 11 numbers to store terminal transaction date
-------------------------------------------------------------------------------------------------------------*/
typedef struct ST_terminalData_t
{
	float32_t transAmount;
	float32_t maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

/********************************************* ENUMERATIONS **************************************************/
/*-------------------------------------------------------------------------------------------------------------
	[Enumeration Name]: EN_termialError_t
	[Enumeration Description]: This enumeration for terminal errors
	[Enumeration Members]:
		1. TERMINAL_OK -> 0
		2. WRONG_DATE -> 1
		3. EXPIRED_CARD -> 2
		4. INVALID_CARD -> 3
		5. INVALID_AMOUNT -> 4
		6. EXCEED_MAX_AMOUNT -> 5
		7. INVALID_MAX_AMOUNT -> 6
-------------------------------------------------------------------------------------------------------------*/
typedef enum EN_termialError_t
{
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

/******************************************** Functions Prototypes *******************************************/
/*------------------------------------------------------------------------------------------------------------
	[Function Name]:getTransactionDate
	[Description]:	This function is responsible for getting transaction date from user and store it into
					transactionDate string member of terminal data structure.
	[Arguments]
	[in]:			Pointer to structure from ST_terminalData_t structure type.
	[out]:			None
	[Return]:		Enumeration member of terminal State (TERMINAL_OK,WRONG_DATE)
-------------------------------------------------------------------------------------------------------------*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);

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
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:	getTransactionAmount
	[Description]:	This function is responsible for getting transaction amount from user and store it into
					transAmount string member of terminal data structure.
	[Arguments]
	[in]:			termData Pointer to structure from ST_terminalData_t structure type.
	[out]:			None
	[Return]:		Enumeration member of terminal State (TERMINAL_OK,INVALID_AMOUNT)
-------------------------------------------------------------------------------------------------------------*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:isBelowMaxAmount
	[Description]:	This function is responsible for comparing the transaction amount with the terminal max amount.
	[Arguments]
	[in]:			termData Pointer to structure from ST_terminalData_t structure type.
	[out]:			None
	[Return]:		Enumeration member of terminal State (TERMINAL_OK,EXCEED_MAX_AMOUNT)
-------------------------------------------------------------------------------------------------------------*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);

/*------------------------------------------------------------------------------------------------------------
	[Function Name]:setMaxAmount
	[Description]:	This function is responsible for setting the maximum allowed amount into transAmount
					string member of terminal data structure.
	[Arguments]
	[in]:			termData Pointer to structure from ST_terminalData_t structure type.
	[out]:			None
	[Return]:		Enumeration member of terminal State (TERMINAL_OK,INVALID_MAX_AMOUNT )
-------------------------------------------------------------------------------------------------------------*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);

#endif
