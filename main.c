#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define NUMBER_OF_CONTACTS 3
#define LENGTH_OF_LINE 100
#define NUMBER_OF_LINES 2

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

void convert_string_to_number(char string[], char number[])
{ // arrays must be the same length
    int length = strlen(string);
    for (int i = 0; i < length; i++) {
        number[i] = convert_symbol_to_number(string[i]);
    }
    number[length] = '\0';
}

bool matches_number(char input[], char number[])
{
    int input_size = strlen(input);
    int number_size = strlen(number);
    if (input_size > number_size) { // number cannot match input larger that itself
        return false;
    }

    for (int i = 0; i < input_size; i++) {
        if (input[i] != number[i]) {
            return false;
        }
    }
    return true;
}

void read_contacts_from_file(char contacts[NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE]){
    char file_input[101];
    int contact = 0;
    int line = 0;
    while (fgets(file_input, sizeof(file_input), stdin) != NULL) {
        strcpy(contacts[contact][line], file_input);
        if (line == 0) {
            line++;
        } else {
            line = 0;
            contact++;
        }
    }
}

void print_contacts(char contacts[NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE]) // temp
{
    for (int i = 0; i < NUMBER_OF_CONTACTS; i++) {
        for (int j = 0; j < NUMBER_OF_LINES; j++) {
            printf("%s\n", contacts[i][j]);
        }
    }
}

int main(int argc, char *argv[])
{
    char contacts[NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE];
    read_contacts_from_file(contacts);
    print_contacts(contacts);

    if (argc < 2) {
        return 0; // TODO: vypíš všechny kontakty
    }
    char *input = argv[1];
    return 0;
}
