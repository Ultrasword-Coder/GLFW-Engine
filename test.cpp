#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>

int main()
{
    int *array[8];
    memset(array, 0, sizeof(array));
    for (int i = 0; i < 8; i++)
    {
        std::cout << array[i] << std::endl;
    }

    return 0;
}
