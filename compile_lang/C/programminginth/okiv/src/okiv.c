#include <stdio.h>
#include <string.h>

// Fixed version with safer input handling
int main() {
    char quest[16];
    
    printf("Enter a string (max 15 chars): ");
    scanf("%15s", quest);  // Fixed: limit to 15 chars, no address operator
    
    int ope = strlen(quest);
    
    // Safety check for empty input
    if (ope == 0) {
        printf("Please enter at least one character.\n");
        return 1;
    }
    
    for (int i = 1; i <= 5; i++) {
        int count = 0;
        printf((i % 3 == 0) ? "\n#" : (i == 1) ? "." : "\n.");
        
        for (int j = 1; j <= (ope * 2); j++) {
            if (i == 1 || i == 5) {
                if (j % 2 == 1) {
                    printf(((j + 1) % 3 == 0) ? ".*." : ".#.");
                } else {
                    printf(".");
                }
            }
            
            if (i == 2 || i == 4) {
                if (j % 2 == 1) {
                    printf(((j + 1) % 6 == 0) ? "*.*" : "#.#");
                } else {
                    printf(".");
                }
            }
            
            if (i == 3) {
                if (count != 3) {
                    count++;
                    printf((j % 2 == 1) ? ".%c." : "#", quest[((j + 1) / 2) - 1]);
                } else if (j == ope * 2) {
                    printf("#");
                    break;
                } else {
                    count = 0;
                    printf("*.%c.*", quest[((j + 2) / 2) - 1]);
                    j += 2;
                }
            }
        }
    }
    printf("\n");
    return 0;
}
