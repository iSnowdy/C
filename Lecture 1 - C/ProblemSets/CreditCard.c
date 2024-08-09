#include <stdio.h>
#include <string.h> // To be able to use sprintf

// Functions

int verifyLong(long cardNumber);
int typeValidator(long cardNumber);
int luhnAlgorithm (long cardNumber);

int main(void)
{
    long cardNumber;
    printf("Number: ");
    scanf("%li", cardNumber);
    char *type;

    switch (typeValidator(cardNumber)) {
        case 0:
            type = "AMEX";
            break;
        case 1:
            type = "MASTERCARD";
            break;
        case 2:
            type = "VISA";
            break;
        case 3:
            type = "INVALID";
    }

    int luhn = luhnAlgorithm(cardNumber);

    // Only if the card is valid, meaning last digit is 0, and
    // if its type is not INVALID (!=3), then it will be a valid card
    if (luhn % 10 == 0 && typeValidator(cardNumber) != 3) {
        printf("Luhn number is %i\n", luhn);
        printf("%s\n", type);
    } else {
        printf("Luhn number is %i", luhn);
        printf("INVALID\n");
    }
}

// We verify the length
// 0: AMEX, 1: MasterCard, 2: VISA, 3: INVALID
int verifyLong(long cardNumber)
{
    char strNumber[16];
    sprintf(strNumber, "%li", cardNumber);

    int length = strlen(strNumber);

    printf("Length is: %i\n", length);

    if (length == 15) { // AMEX
        return 0;
    } else if (length == 16) { // MasterCard
        return 1;
    } else if (length == 13 || length == 16) { // VISA
        return 2;
    } else {
        return 3;
    }
}

// This function's objective is to tell us what kind of credit card
// we are dealing with. According to a code (0, 1, 2, 3), we will know
// what type is it.
// 0: AMEX, 1: MasterCard, 2: VISA, 3: INVALID
int typeValidator(long cardNumber)
{
    int result, firstDigit, secondDigit;
    // The return value will be stored here and the first
    // two digits of the card too (since only those are relevant)
    int lengthVerification = verifyLong(cardNumber);
    printf("Length verification is: %i\n", lengthVerification);

    if (lengthVerification == 3) {
        return 3;
    }

    // We reduce the number to two digits and store it
    while (cardNumber >= 100) {
        cardNumber /= 10;
    }
    firstDigit = cardNumber / 10;
    secondDigit = cardNumber % 10;

    // Now we check for coincidences

    if (firstDigit == 4 && (lengthVerification == 2 || lengthVerification == 1)) { // VISA
        return result = 2;
    } else if (firstDigit == 3 && (secondDigit == 4 || secondDigit == 7) && lengthVerification == 0) { // AMEX
        return result = 0;
    } else if (firstDigit == 5 && (secondDigit >= 1 && secondDigit <= 5) && (lengthVerification == 1 || lengthVerification == 2)) { // MasterCard
        return result = 1;
    } else {
        return result = 3;
    }
}

int luhnAlgorithm (long cardNumber)
{
    // Working with the number as a String will make it easier when dealing with digits
    char strNumber[16];
    sprintf(strNumber, "%li", cardNumber);

    int firstSum = 0, secondSum = 0, finalSum = 0;

    for (int i = strlen(strNumber) - 1; i >= 1; i -=2) {
        int temp1 = (strNumber[i - 1] - '0') * 2; // - '0' is a cast conversion from char to int that can be done in C
        int temp2 = strNumber[i] - '0';

        // Terniary operation. If the selected digits multiplication has
        // 2 digits (aka >=10), then we first sum the first digit (/10) followed by
        // the second digit (%10). If not, then just sum the temp number
        firstSum += (temp1 >= 10) ? (temp1 / 10) + (temp1 % 10) : temp1;
        secondSum += (temp2 >= 10) ? (temp2 / 10) + (temp2 % 10) : temp2;

        // printf("First sum: %i, Second Sum: %i, Temp 1: %i, Temp 2: %i\n", firstSum, secondSum, temp1, temp2);
    }

    // Because we are jumping 2 in 2, and these are odds numbers, the second sum does not get to reach index = 0
    // so we brute force through it adding that last digit needed
    if (strlen(strNumber) == 13 || strlen(strNumber) == 15) {
        secondSum += strNumber[0] - '0';
    }
    // We add both sums to get the final result
    return finalSum = firstSum + secondSum;
}