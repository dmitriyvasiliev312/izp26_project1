#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void lowercase(char *str)
{
    int n = strlen(str);
    for (int i = 0; i < n; i++) {
        str[i] = tolower(str[i]);
    }
}

// int count_digits(int number)
// {
//     int count = 0;
//     while (number != 0) {
//         number /= 10;
//         count++;
//     }
//     return count;
// }

bool matches_number(char input[], char number[])
{
    int input_size = strlen(input);
    int number_size = strlen(number);
    if (input_size < number_size) {
        return false;
    }

    for (int i = 0; i < input_size; i++) {
        // if(number[i] == '+' && i == 0){ //number can contain + in the beginning, even if its not in the input
        //     continue;
        // }
        if (input[i] != number[i]) {
            return false;
        }
    }
    return true;
}

int main(void)
{

    char a[2] = {'1', '2'};
    char b[2] = {'1', '2'};
    bool n = matches_number(a, b);
    printf("%d", n);
    return 0;
}
