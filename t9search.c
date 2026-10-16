#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define MAX_NUMBER_OF_CONTACTS 42
#define LENGTH_OF_LINE 102
#define NUMBER_OF_LINES 2
#define PHONE_NUMBER 1
#define NAME 0

char *strcpy_until_newline(char destination[], char source[]) // same functionality as strcpy, but it stops at \n symbols
{
    int character = 0;
    while (source[character] != '\0' && source[character] != '\n') {
        destination[character] = source[character];
        character++;
    }
    destination[character] = '\0'; // set last character in string to null term.
    return destination;
}

bool string_only_contains_digits(char string[])
{
    for (size_t character = 0; character < strlen(string); character++) {
        if (string[character] < '0' || string[character] > '9') {
            return false;
        }
    }
    return true;
}

/*Replaces letters and "+" with assigned numbers. Digits remain unchanged.*/
int convert_symbol_to_number(int symbol)
{
    if (symbol >= '0' && symbol <= '9') { // digits do not change their value
        return symbol;
    }

    char symbol_values[256] = {0}; // array of assigned numbers for letters and "+"
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

/*Convert letters of the string to assigned numbers.*/
void convert_string_to_number(char string[])
{ 
    int length = strlen(string);
    for (int i = 0; i < length; i++) {
        string[i] = convert_symbol_to_number(string[i]);
    }
}

/*Check if string (of digits) contains input string.*/
bool matches_number(char input[], char number[])
{
    int input_size = strlen(input);
    int number_size = strlen(number);
    if (input_size > number_size) { // number cannot match input larger that itself
        return false;
    }

    for (int position = 0; position <= number_size - input_size; position++) {
        int character = 0;

        while (character < input_size && input[character] == number[position + character]) {
            character++;
        }

        if (character == input_size) {
            return true;
        }
    }

    return false;
}

/*Find all contacts that match the number and add them to empty matched_contacts array.*/
int find_matching_contacts_by_line(char all_contacts[MAX_NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE],
                                   char matched_contacts[MAX_NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE],
                                   char number[])
{
    int number_of_matched_contacts = 0;
    for (int contact = 0; contact < MAX_NUMBER_OF_CONTACTS; contact++) {

        char converted_name[LENGTH_OF_LINE];
        strcpy(converted_name, all_contacts[contact][NAME]);
        convert_string_to_number(converted_name);

        char converted_number[LENGTH_OF_LINE];
        strcpy(converted_number, all_contacts[contact][PHONE_NUMBER]);
        convert_string_to_number(converted_number);

        if (matches_number(number, converted_number) || matches_number(number, converted_name)) {
            strcpy(matched_contacts[number_of_matched_contacts][NAME], all_contacts[contact][NAME]);
            strcpy(matched_contacts[number_of_matched_contacts][PHONE_NUMBER], all_contacts[contact][PHONE_NUMBER]);
            ++number_of_matched_contacts;
        }
    }
    return number_of_matched_contacts;
}

/*Read contacts from file to empty array.*/
int read_contacts_to_array(char contacts[MAX_NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE])
{
    char file_input[LENGTH_OF_LINE];
    int contact = 0;
    int line = 0;
    while (fgets(file_input, sizeof(file_input), stdin) != NULL) {

        size_t length = strlen(file_input);
        if (length > 0 && file_input[length - 1] != '\n' &&
            !feof(stdin)) { // feof checks whether the end of the input stream has been reached
            return -1;
        }

        strcpy_until_newline(contacts[contact][line], file_input);
        if (line == 0) {
            line++;
        } else {
            line = 0;
            contact++;
        }
    }

    if (line != 0) { // function has read a name but has not read the corresponding phone number
        return -1;
    }

    return contact;
}

void print_contact_array(char contacts[MAX_NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE], int length)
{
    for (int contact = 0; contact < length; contact++) {
        printf("%s, %s\n", contacts[contact][NAME], contacts[contact][PHONE_NUMBER]);
    }
}

int main(int argc, char *argv[])
{
    char contacts[MAX_NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE];
    int number_of_contacts = read_contacts_to_array(contacts);

    if (number_of_contacts == -1) {
        fprintf(stderr, "Error - invalid contact list.\n");
        return 1;
    }

    if (argc < 2) {                                        // if program runs with no input
        print_contact_array(contacts, number_of_contacts); // print every contact
        return 0;
    }
    char *entered_number = argv[1]; // read entered number
    if (!string_only_contains_digits(entered_number)) {
        fprintf(stderr, "Error - invalid input.\n");
        return 1;
    }

    char matched_contacts[MAX_NUMBER_OF_CONTACTS][NUMBER_OF_LINES][LENGTH_OF_LINE];
    int number_of_matched_contacts = find_matching_contacts_by_line(contacts, matched_contacts, entered_number);
    print_contact_array(matched_contacts, number_of_matched_contacts);

    if (number_of_matched_contacts == 0) { // if no matches found
        printf("Not Found\n");
    }

    return 0;
}
