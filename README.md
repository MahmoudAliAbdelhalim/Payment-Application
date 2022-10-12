# Payment-Application
Payment Application

Project Requirements

Development environment preparation
Implement the card module
Implement the terminal module
Implement the server module
Implement the application
Testing the application

Application flowchart
https://video.udacity-data.com/topher/2022/June/62bc647c_payment-flowchart/payment-flowchart.jpeg

Development environment preparation:

1.Implement the card module
Fill in card.h file with functions' prototypes and typedefs
Implement getCardHolderName function
Implement getCardExpiryDate function
Implement getCardPAN function

2.Implement the terminal module
Fill in terminal.h file with functions' prototypes and typedefs
Implement getTransactionDate function
Implement isCardExpried function
Implement gatTransactionAmount function
Implement isBelowMaxAmount function
Implement setMaxAmount function

3.Implement the server module
Fill in server.h file with functions' prototypes and typedefs
Implement server-side accounts' database
Implement server-side transactions' database
Implement recieveTransactionData function
Implement isValidAccount function
Implement isAmountAvailable function
Implement saveTransaction function

4.Implement the application
Fill in application.h file with functions' prototypes
Implement appStart function

5.Testing the application:

a.Transaction approved user story:

As a bank customer have an account and has a valid and not expired card, I want to withdraw an amount of money less than the maximum allowed and less than or equal to the amount in my balance, so that I am expecting that the transaction is approved and my account balance is reduced by the withdrawn amount.


b.Exceed the maximum amount user story:

As a bank customer have an account, that has a valid and not expired card, I want to withdraw an amount of money that exceeds the maximum allowed amount so that I am expecting that the transaction declined.


c.Insufficient fund user story:

As a bank customer have an account and has a valid and not expired card, I want to withdraw an amount of money less than the maximum allowed and larger than the amount in my balance so that I am expecting that the transaction declined.


d.Expired card user story:

As a bank customer have an account, have a valid but expired card, I want to withdraw an amount of money so that I expect that the transaction declined.

e.Invalid card user story:

As a bank customer have an account and has a valid and not expired stolen card, I want to block anyone from using my card so that I am expecting that any transaction made by this card is declined.

