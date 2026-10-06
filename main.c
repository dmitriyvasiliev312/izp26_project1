#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int convert_symbol_to_number(int symbol)
{
    int symbol_values[256] = {0}; // array of numbers that represent letters and "+"
    symbol_values['A'] = 2;
    symbol_values['B'] = 2;
    symbol_values['C'] = 2;
    symbol_values['D'] = 3;
    symbol_values['E'] = 3;
    symbol_values['F'] = 3;
    symbol_values['G'] = 4;
    symbol_values['H'] = 4;
    symbol_values['I'] = 4;
    symbol_values['J'] = 5;
    symbol_values['K'] = 5;
    symbol_values['L'] = 5;
    symbol_values['M'] = 6;
    symbol_values['N'] = 6;
    symbol_values['O'] = 6;
    symbol_values['P'] = 7;
    symbol_values['Q'] = 7;
    symbol_values['R'] = 7;
    symbol_values['S'] = 7;
    symbol_values['T'] = 8;
    symbol_values['U'] = 8;
    symbol_values['V'] = 8;
    symbol_values['W'] = 9;
    symbol_values['X'] = 9;
    symbol_values['Y'] = 9;
    symbol_values['Z'] = 9;
    symbol_values['+'] = 0;
    return symbol_values[toupper(symbol)];
}

bool matches_number(char input[], char number[])
{
    int input_size = strlen(input);
    int number_size = strlen(number);
    if (input_size > number_size) {
        return false;
    }

    for (int i = 0; i < input_size; i++) {
        if (input[i] != number[i]) {
            return false;
        }
    }
    return true;
}

int main(void)
{

    // char a[2] = {'1', '2'};
    // char b[2] = {'1', '2'};
    // char c[3] = {'+', '1', '2'};
    // bool n = matches_number(a, b);
    // bool nn = matches_number(a, c);
    // printf("%d\n%d", n, nn);
    printf("%d", convert_symbol_to_number('L'));
    return 0;
}
