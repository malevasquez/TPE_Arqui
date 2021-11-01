#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

void startVideoDriver();

void clearScreen();

void drawPixel(int row, int col, int color);

void drawRectangle(int x, int y, int width, int height, int col);

void drawLine(int xStart, int yStart, int xEnd, int yEnd, int col);

int drawMatrix(int * matrix, int row, int col, int rows, int columns);

int getScreenHeight();

int getScreenWidth();

int drawChar(int character, int color);

int drawCharFrom(int character, int row, int col, int color);

#endif
