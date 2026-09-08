#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int divide_by_2(char *s)
{
    int carry = 0;
    int len = 0;
    while (*(s + len) != '\0')
        len++;
    for (int i = 0; i < len; ++i)
    {
        int val = (*(s + i) - '0') + carry * 10;
        *(s + i) = (val / 2) + '0';
        carry = val % 2;
    }
    return carry;
}

bool is_zero(const char *s)
{
    int i = 0;
    while (*(s + i) != '\0')
    {
        if (*(s + i) != '0')
            return false;
        i++;
    }
    return true;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char *str_a = (char *)calloc(10000, sizeof(char));
    char *str_b = (char *)calloc(10000, sizeof(char));

    if (argc == 3)
    {
        int i = 0;
        while (*(argv[1] + i))
        {
            *(str_a + i) = *(argv[1] + i);
            i++;
        }
        int j = 0;
        while (*(argv[2] + j))
        {
            *(str_b + j) = *(argv[2] + j);
            j++;
        }
    }
    else
    {
        cin >> str_a >> str_b;
    }

    int cap_a = 64, cap_b = 64;
    double *a_bits = new double[cap_a]();
    double *b_bits = (double *)calloc(cap_b, sizeof(double));
    int sz_a = 0, sz_b = 0;

    while (!is_zero(str_a))
    {
        if (sz_a >= cap_a)
        {
            cap_a += 64;
            double *temp_a = new double[cap_a]();
            for (int i = 0; i < sz_a; ++i)
                *(temp_a + i) = *(a_bits + i);
            delete[] a_bits;
            a_bits = temp_a;
        }
        *(a_bits + sz_a) = (double)divide_by_2(str_a);
        sz_a++;
    }

    while (!is_zero(str_b))
    {
        if (sz_b >= cap_b)
        {
            cap_b += 64;
            double *temp_b = (double *)calloc(cap_b, sizeof(double));
            for (int i = 0; i < sz_b; ++i)
                *(temp_b + i) = *(b_bits + i);
            free(b_bits);
            b_bits = temp_b;
        }
        *(b_bits + sz_b) = (double)divide_by_2(str_b);
        sz_b++;
    }

    int cap_c = (cap_a > cap_b ? cap_a : cap_b) + 64;
    double *c_bits = (double *)calloc(cap_c, sizeof(double));
    double *carry_bits = (double *)calloc(cap_c, sizeof(double));

    for (int i = 0; i < cap_c - 1; ++i)
    {
        double bit_a = (i < sz_a) ? *(a_bits + i) : 0.0;
        double bit_b = (i < sz_b) ? *(b_bits + i) : 0.0;

        *(c_bits + i) = (bit_a != bit_b) ? 1.0 : 0.0;
        *(carry_bits + i) = (bit_a == 1.0 && bit_b == 1.0) ? 1.0 : 0.0;
    }

    double carry_in = 0.0;
    int final_bits_len = 0;
    for (int i = 0; i < cap_c; ++i)
    {
        double current_sum = *(c_bits + i) + carry_in;
        if (current_sum >= 2.0)
        {
            *(c_bits + i) = current_sum - 2.0;
            carry_in = 1.0 + *(carry_bits + i);
        }
        else
        {
            *(c_bits + i) = current_sum;
            carry_in = *(carry_bits + i);
        }
        if (*(c_bits + i) == 1.0)
            final_bits_len = i + 1;
    }

    int hex_cap = (final_bits_len / 4) + 2;
    char *hex_arr = (char *)calloc(hex_cap, sizeof(char));
    int hex_len = 0;

    for (int i = 0; i < final_bits_len; i += 4)
    {
        int hex_val = (int)*(c_bits + i) * 1 +
                      (int)*(c_bits + i + 1) * 2 +
                      (int)*(c_bits + i + 2) * 4 +
                      (int)*(c_bits + i + 3) * 8;
        *(hex_arr + hex_len) = (char)hex_val;
        hex_len++;
    }

    int dec_cap = 10000;
    char *dec_str = (char *)calloc(dec_cap, sizeof(char));
    *(dec_str + 0) = '0';
    int dec_len = 1;

    for (int i = hex_len - 1; i >= 0; --i)
    {
        int add_val = *(hex_arr + i);
        int current_carry = add_val;

        for (int j = 0; j < dec_len; ++j)
        {
            int val = (*(dec_str + j) - '0') * 16 + current_carry;
            *(dec_str + j) = (val % 10) + '0';
            current_carry = val / 10;
        }
        while (current_carry > 0)
        {
            *(dec_str + dec_len) = (current_carry % 10) + '0';
            dec_len++;
            current_carry /= 10;
        }
    }

    for (int i = dec_len - 1; i >= 0; --i)
    {
        cout << *(dec_str + i);
    }
    cout << "\n";

    delete[] a_bits;
    free(b_bits);
    free(c_bits);
    free(carry_bits);
    free(hex_arr);
    free(dec_str);
    free(str_a);
    free(str_b);

    return 0;
}