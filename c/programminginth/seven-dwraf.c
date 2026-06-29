#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef uint8_t u8;
typedef uint16_t u16;

int main()
{
    u8 *dwrafs = (u8 *)calloc(9, sizeof(u8));
    u16 imposter = 0;
    if (!dwrafs)
        return 1;

    u8 i;
    for (i = 0; i < 9; i++)
    {
        scanf("%" SCNu8, &dwrafs[i]);
        imposter += dwrafs[i];
    }
    imposter -= 100;

    u8 j;
    for (i = 0; i < 8; i++)
        for (j = i + 1; j < 9; j++)
        {
            if (dwrafs[i] + dwrafs[j] == imposter)
            {
                dwrafs[i] = dwrafs[j] = 255;
                goto output;
            }
        }

output:
    for (i = 0; i < 9; i++)
        if (dwrafs[i] < 255)
            printf("%u\n", dwrafs[i]);

    free(dwrafs);
    return 0;
}
