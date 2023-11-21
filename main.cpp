#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

void getConsoleSize(int &columns, int &rows) 
{
	struct winsize ws;
	ioctl(fileno(stdout), TIOCGWINSZ, &ws);
	columns = ws.ws_col;
	rows = ws.ws_row;
}
//(x - cx)*(x - cx) + 5*(y - cy)*(y - cy) <= 25
void updt_screen(int cx, int cy, float fps)
{
	int columns, rows;
	getConsoleSize(columns, rows);
	printf("\033[H");
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
			if (((x - cx)*(x - cx) + 5*(y - cy)*(y - cy) <= 2500)) printf("0");
			else printf(" ");
		printf("\n");
	}
	usleep((1/fps) * 1000000);
}

int main()
{
	printf("\033[?25l");
	float fps = 75.0;
	int j, js; j = 1; js = 1;
	while(true)
	{
		printf("\033[?25l");
		int columns, rows;
		getConsoleSize(columns, rows);
		for (int i = 0; i < columns; i+=5)
		{
			if ((j >= rows) || ( j <= 0 )) js *= -1;
			getConsoleSize(columns, rows);
			updt_screen( i, j, fps);
			j += js;
		}
		getConsoleSize(columns, rows);
		for (int i = columns; i > 0; i-=5)
		{
			if ((j >= rows) || ( j <= 0 )) js *= -1;
			getConsoleSize(columns, rows);
			updt_screen( i, j, fps);
			j += js;
		}
	}

	return 0;
}
