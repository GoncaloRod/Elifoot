#include "Utils.h"

#include <stdlib.h>

int RandomInRange(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void ShiftIntArrRight(int* arr, int count)
{
	int temp = arr[count - 1];

	for (int i = count - 1; i > 0; i--)
	{
		arr[i] = arr[i - 1];
	}

	arr[0] = temp;
}
