#include <stdio.h>
#include "./graphic_defs.h"

int main()
{
	#ifdef _WIN32
	
	console_output = GetConsoleHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_info;
	GetConsoleScreenBufferInfo(console_output, &screen_info);

	viewport_width = screen_info.dwMaximumWindowSize.X;
	viewport_height = screen_info.dwMaximumWindowSize.Y;
	
	#else
	
	console_output = stdout;
	struct winsize screen_info;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen_info);

    viewport_width = screen_info.ws_col;
    viewport_height = screen_info.ws_row;
	
	#endif
	
	printf("%d     %d", viewport_width, viewport_height);

	getchar();
	
	int viewport_res = viewport_width*viewport_height;

	z_buffer = (double*) malloc(sizeof(double) * viewport_res);
	framebuffer = (char*) malloc(sizeof(char) * viewport_res);

	for(int idx = 0; idx < viewport_res; idx++)
		z_buffer[idx] = 1.0;

	for(int idx = 0; idx < viewport_res; idx++)
		framebuffer[idx] = ' ';
		
	#ifdef _WIN32
	
	DWORD written = 0;
	
	#endif

	while(1)
	{
		// Write the sequence for clearing the display.
    	
    	//system("cls");

		for(int tidx = 0; tidx < 6; tidx++)
		{
			//model_view(&tmp1);
			//model_view(&tmp2);

			//raster_triangle(&tmp1);
			//raster_triangle(&tmp2);
		}

		framebuffer[viewport_width*viewport_height - 1] = '\0';
		
		#ifdef _WIN32
		
		WriteConsoleOutputCharacter(console_output, framebuffer, viewport_height * viewport_width, (COORD) {0, 0}, &written);

		#else

		fprintf(console_output, framebuffer, viewport_res);

		#endif

		for(int idx = 0; idx < viewport_res; idx++)
			framebuffer[idx] = ' ';
		for(int idx = 0; idx < viewport_res; idx++)
			z_buffer[idx] = 1.0;

		#ifdef _WIN32

		Sleep(25);
		
		#else

		usleep(25000);
		printf("\033[0;0f");

		#endif
	}

	free(z_buffer);

	
	
}
