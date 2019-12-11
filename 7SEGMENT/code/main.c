#include "7segment.h"
#include "delay.h"

int main(void)
{
	SevenSegment_Init();
	
    while(1)
	{
		Segment_WriteData(1398);
	}
}



