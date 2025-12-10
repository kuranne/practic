#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int an;
    scanf("%d", &an);

    int *prime = (int *)malloc(sizeof(int) * an);
    if (prime == NULL)
    {
        perror("Failed to allocate memory for prime array");
        return 1;
    }

    prime[0] = 2;
    int prime_count = 1, nn = 3;

    while (prime_count < an)
    {
        int is_prime = 1, limit = (int)sqrt(nn);
        for (int i = 0; i < prime_count && prime[i] <= limit; i++)
        {
            if (nn % prime[i] == 0)
            {
                is_prime = 0;
                break;
            }
        }

        if (is_prime)
        {
            prime[prime_count] = nn;
            prime_count++;
        }
        nn += 2;
    }

    printf("\n%d\n", prime[an - 1]);

    free(prime);

    return 0;
}