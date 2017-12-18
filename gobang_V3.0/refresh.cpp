#include "stdafx.h"
#include "refresh.h"


void refresh(char* buff, int StartX, int StartY)
{
	HANDLE Handle;
	COORD XYPosition;

	XYPosition.X = StartX;
	XYPosition.Y = StartY;
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);  //获得标准输出的句柄
	SetConsoleCursorPosition(Handle, XYPosition);  //将光标移动到指定位置
	printf("%s", buff);
	XYPosition.X = 0;
	XYPosition.Y = 31;
	SetConsoleCursorPosition(Handle, XYPosition);
}
void RefreshNum(int buff, int StartX, int StartY)
{
	HANDLE Handle;
	COORD XYPosition;

	XYPosition.X = StartX;
	XYPosition.Y = StartY;
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);  //获得标准输出的句柄
	SetConsoleCursorPosition(Handle, XYPosition);  //将光标移动到指定位置
	printf("%.2d", buff);
	XYPosition.X = 0;
	XYPosition.Y = 31;
	SetConsoleCursorPosition(Handle, XYPosition);
}
//ghjgkjhjl
//jvhvhu uuh gyug uyig ug yu