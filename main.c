#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int convert_symbol_to_number(int symbol)
{
    char symbol_values[256] = {0}; // array of numbers that represent letters and "+"
    symbol_values['A'] = '2';
    symbol_values['B'] = '2';
    symbol_values['C'] = '2';
    symbol_values['D'] = '3';
    symbol_values['E'] = '3';
    symbol_values['F'] = '3';
    symbol_values['G'] = '4';
    symbol_values['H'] = '4';
    symbol_values['I'] = '4';
    symbol_values['J'] = '5';
    symbol_values['K'] = '5';
    symbol_values['L'] = '5';
    symbol_values['M'] = '6';
    symbol_values['N'] = '6';
    symbol_values['O'] = '6';
    symbol_values['P'] = '7';
    symbol_values['Q'] = '7';
    symbol_values['R'] = '7';
    symbol_values['S'] = '7';
    symbol_values['T'] = '8';
    symbol_values['U'] = '8';
    symbol_values['V'] = '8';
    symbol_values['W'] = '9';
    symbol_values['X'] = '9';
    symbol_values['Y'] = '9';
    symbol_values['Z'] = '9';
    symbol_values['+'] = '0';
    return symbol_values[toupper(symbol)];
}

void convert_string_to_number(char string[], char number[]){ //arrays must be the same length
    int length = strlen(string);
    for(int i = 0; i < length; i++){
        number[i] = convert_symbol_to_number(string[i]);
    }
    number[length] = '\0';
}

bool matches_number(char input[], char number[])
{
    int input_size = strlen(input);
    int number_size = strlen(number);
    if (input_size > number_size) { //number cannot match input larger that itself
        return false;
    }

    for (int i = 0; i < input_size; i++) {
        if (input[i] != number[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    if(argc < 2){
        return 1; // TODO: vypíš všechny kontakty
    }
    char input[101];
    
    // char a[2] = {'1', '2'};
    // char b[2] = {'1', '2'};
    // char c[3] = {'+', '1', '2'};
    // bool n = matches_number(a, b);
    // bool nn = matches_number(a, c);
    // printf("%d\n%d", n, nn);
    // printf("%d", convert_symbol_to_number('L'));
    char s[] = "aaaddd";
    char number[strlen(s)+1];
    char n[] = "222333";
    convert_string_to_number(s, number);
    bool result = matches_number(number, n);
    printf("result:%d\ninput: %s\n number %s", result, number, n);
    return 0;
}
