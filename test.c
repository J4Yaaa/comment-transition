#include "convert.h"

int main()
{
	FILE *IP = fopen(INPUT, "r");
	FILE *OP = fopen(OUTPUT, "w");
	if (IP == NULL || OP == NULL)
	{
		perror("Error opening file");
		exit(1);

	}
	Test_Convert_Main(IP,OP);
	
	fclose(IP);
	fclose(OP);
	return 0;
}
