#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define NUMBER_OF_CONTACTS 42
#define LENGTH_OF_LINE 100
#define NUMBER_OF_LINES 2
#define PHONE_NUMBER 1
#define NAME 0

char *strcpy_until_newline(char destination[], char source[])
{
    int i = 0;
    while (source[i] != '\0' && source[i] != '\n') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
    return destination;
}

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

void convert_string_to_number(char string[])
{ //convert letters of the string to assigned numbers
    int length = strlen(string);
    for (int i = 0; i < length; i++) {
        string[i] = convert_symbol_to_number(string[i]);
    }
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

int find_matching_contacts_by_line(char all_contacts[NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE],
                                   char matched_contacts[NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE],
                                   char number[])
{
    int number_of_matched_contacts = 0;
    for (int contact = 0; contact < NUMBER_OF_CONTACTS; contact++) {

        char converted_name[LENGTH_OF_LINE];
        strcpy(converted_name, all_contacts[contact][NAME]);
        convert_string_to_number(converted_name);

        if (matches_number(number, all_contacts[contact][PHONE_NUMBER]) || matches_number(number, converted_name)) {
            strcpy(matched_contacts[number_of_matched_contacts][NAME], all_contacts[contact][NAME]);
            strcpy(matched_contacts[number_of_matched_contacts][PHONE_NUMBER], all_contacts[contact][PHONE_NUMBER]);
            ++number_of_matched_contacts;
        }
    }
    return number_of_matched_contacts;
}

void read_contacts_to_array(char contacts[NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE])
{
    char file_input[LENGTH_OF_LINE];
    int contact = 0;
    int line = 0;
    while (fgets(file_input, sizeof(file_input), stdin) != NULL) {
        strcpy_until_newline(contacts[contact][line], file_input);
        if (line == 0) {
            line++;
        } else {
            line = 0;
            contact++;
        }
    }
}

// void convert_names_to_numbers(char contacts[NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE]) {
//     for(int contact = 0; contact < NUMBER_OF_CONTACTS; contact++){
//         convert_string_to_number(contacts[contact][NAME]);
//     }
// }

void print_contact_array(char contacts[NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE], int length)
{
    for (int contact = 0; contact < length; contact++) {
        printf("%s, %s\n", contacts[contact][NAME], contacts[contact][PHONE_NUMBER]);
    }
}

int main(int argc, char *argv[])
{
    char contacts[NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE];
    read_contacts_to_array(contacts);

    if (argc < 2) { // if program runs with no input
        print_contact_array(contacts, NUMBER_OF_CONTACTS); // print every contact
        return 0;
    }
    char *entered_number = argv[1]; // read entered number

    char matched_contacts[NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE];
    int number_of_matched_contacts = find_matching_contacts_by_line(contacts, matched_contacts, entered_number);
    print_contact_array(matched_contacts, number_of_matched_contacts);

    if (number_of_matched_contacts == 0) { // if no matches found
        printf("Not Found\n");
    }

    return 0;
}
