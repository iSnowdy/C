#include <stdio.h>

// Functions
int promptChange(void);
int changedOwed(int change);

int main(void)
{
    // Prompts the user for the change given to the shop and then
    // takes that same number and process it through the function
    // that will return the amount of coins he will be given
    int coins = changedOwed(promptChange());
    printf("Coins given back: %i\n", coins);
}

// Prompts the user for a change. However, it must be an int > 0
int promptChange(void)
{
    int a;
    do
    {
        printf("Coins? \n");
        scanf("%i", &a);
    }
    while (a < 0);
    return a;
}

// Counts the amount of coins given to the customer depending on the
// change. With while loops, it only leaves them once the amount of change
// is below what the coins values are
int changedOwed(int change)
{
    int counter = 0;
    int currentChange = change;

    while (currentChange >= 25)
    {
        counter++;
        currentChange = currentChange - 25;
    }
    while (currentChange >= 10)
    {
        counter++;
        currentChange = currentChange - 10;
    }
    while (currentChange >= 5)
    {
        counter++;
        currentChange = currentChange - 5;
    }
    while (currentChange >= 1)
    {
        counter++;
        currentChange = currentChange - 1;
    }
    return counter;
}
