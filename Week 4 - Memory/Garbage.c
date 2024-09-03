#include <stdlib.h>
#include <stdio.h>

int main(void) {
   int scores[1024];

   for (int i = 0; i < 1024; i++) {
        printf("%i\n", scores[i]); // There are no values there. At least, not that we put them
   }
   // But there are values in there. Those are called 'garbage values'
}
