#include <stdint.h>
#include <font.h>
#include <lib.h>
#include <videoDriver.h>

#define BACKGROUND_COLOR 0x000000


unsigned int SCREEN_WIDTH = 1024;
unsigned int SCREEN_HEIGHT = 768;
unsigned int FRAME_BUFFER;
unsigned int SCREEN_bPP = 3;

static unsigned int xPos = 0;
static unsigned int yPos = (HEIGHT - CHAR_HEIGHT);

struct vbe_mode_info_structure {
    uint16_t attributes;        // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;           // deprecated
    uint8_t window_b;           // deprecated
    uint16_t granularity;       // deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr;      // deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;             // number of bytes per horizontal line
    uint16_t width;             // width in pixels
    uint16_t height;            // height in pixels
    uint8_t w_char;             // unused...
    uint8_t y_char;             // ...
    uint8_t planes;
    uint8_t bpp;                // bits per pixel in this mode
    uint8_t banks;              // deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size;          // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;

    uint32_t framebuffer;           // physical address of the linear frame buffer; write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size;   // size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__((packed));

struct vbe_mode_info_structure * screenData = (void *) 0x5C00; //VBEModeInfoBlock      puntero a la estructura para iniciar el video driver despues
/*
    uint16_t pitch;           // number of bytes per horizontal line
    uint16_t width;          // width in pixels
    uint16_t height;        // height in pixels
*/


void startVideoDriver() {
  SCREEN_WIDTH = screenData->width;
  SCREEN_HEIGHT = screenData->height;
  FRAME_BUFFER = screenData->framebuffer;
}

void clearScreen() {
    for (int i = 0; i < screenData->height; i++) {
        for (int j = 0; j < screenData->width; j++) {
            drawPixel(i, j, BACKGROUND_COLOR);
        }
    }
}

int validCoord(int x, int y){
    if (x >= screenData->height || y >= screenData->width) {
        return 0;
    }
    return 1;
}

void drawPixel(int x, int y, int color) {
    char *currentPos = (char *) (uint64_t) screenData->framebuffer + 3 * (row * screenData->width + col);

    int b = color & 0xFF;           //blue
    int g = (color >> 8) & 0xFF;    //green
    int r = (color >> 16) & 0xFF;   //red

    *currentPos = b;
    currentPos++;
    *currentPos = g;
    currentPos++;
    *currentPos = r;
}

void drawRectangle(int x, int y, int width, int height, int color) {
  if (validCoord(x, y)) {
    int b = color & 0x0000FF;
    int g = (color >> 8) & 0x0000FF;
    int r = (color >> 16) & 0x0000FF;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (validCoord(x + j, y + i)) {
          int * pos = (int *)(FRAME_BUFFER + ((y + i) * WIDTH + (x + j)) * 3);
          *pos = b;
          pos++;
          *pos = g;
          pos++;
          *pos = r;
        }
      }
    }
  }
}

void drawLine(int xStart, int yStart, int xEnd, int yEnd, int color) {
  if (!validCoord(xStart, yStart) || !validCoord(xEnd, yEnd))
    return;

  if(xStart == xEnd){
    drawVerticalLine(xStart, yStart, yEnd, color);
  }
  else{
    int b = col & 0x0000FF;
    int g = (col >> 8) & 0x0000FF;
    int r = ( col >> 16) & 0x0000FF;
    float m = (yEnd-yStart)/(xEnd-xStart);
    float b0 = 1.0f * yStart - m*xStart;
    for(int i = xStart; i <= xEnd; i++){
          int y = (uint64_t) (m * i + b0);
          uint8_t * pos = (uint8_t *)(FRAME_BUFFER+ (y * WIDTH + i) * 3);
          *pos = b;
          pos++;
          *pos = g;
          pos++;
          *pos = r;
    }
  }
}

static void drawVerticalLine(int x, int yStart, int yEnd, int color) {
  if (!validCoord(x, yStart) || !validCoord(x, yEnd))
    return;

  int b = col & 0x0000FF;
  int g = (col >> 8) & 0x0000FF;
  int r = ( col >> 16) & 0x0000FF;

  for (int i = yStart; i <= yEnd; i++) {
    int * pos = (uint8_t *)(FRAME_BUFFER+ (i * WIDTH + x) * 3);
    *pos = b;
    pos++;
    *pos = g;
    pos++;
    *pos = r;
  }
}


// void drawChar(uint64_t x, uint64_t y, uint8_t character, uint64_t fontSize, uint64_t fontColor, uint64_t backgroundColor, uint8_t alphaBackground){
//     uint64_t aux_x = x;
//     uint64_t aux_y = y;
//   uint8_t bitIsPresent;
//     unsigned char * toDraw = charBitmap(character);

//     for (uint8_t i = 0; i < CHAR_HEIGHT; i++){
//         for (uint8_t j = 0; j < CHAR_WIDTH; j++){
//             bitIsPresent = (1<< (CHAR_WIDTH-j)) & toDraw[i];
//             if (bitIsPresent){
//                 drawRectangle(aux_x, aux_y, fontSize, fontSize, fontColor);
//             } else if (alphaBackground == 0) {
//                 drawRectangle(aux_x, aux_y, fontSize, fontSize, backgroundColor);
//             }
//             aux_x+=fontSize;
//         }
//         aux_x = x;
//         aux_y += fontSize;
//     }
// }

// void drawMatrix(uint64_t x, uint64_t y, uint64_t *mat, uint64_t width, uint64_t height,uint64_t size){

//   for (int i = 0; i < height * size; i++){
//         for (int j = 0; j < width * size; j++){
//         if (!validCoord(x + j, y + i) ) continue;
//         if (mat[ (i/size) * width+(j/size) ] == 0x01000000) continue;
//         uint64_t col = mat[(i/size)*width+(j/size)];
//         uint8_t b = col & 0x0000FF;
//         uint8_t g = (col >> 8 )& 0x0000FF;
//         uint8_t r = ( col >> 16) & 0x0000FF;
//         uint8_t* pos = (uint8_t *)(FRAME_BUFFER + ((y+i) * WIDTH + (x+j)) * 3);
//         *pos = b;
//         pos++;
//         *pos = g;
//         pos++;
//         *pos = r;
//         }
//     }
// }

int drawMatrix(int * matrix, int row, int col, int rows, int columns) {
    if (row < 0 || col < 0 || row + rows > screenData->height || col + columns > screenData->width) {
        return 0;
    }
    int x = col;
    int y = row;
    int drawnPixels = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i * columns + j] >= 0 && matrix[i * columns + j] <= 0xFFFFFF) {
                drawPixel(y, x, matrix[i * columns + j]);
                drawnPixels++;
            }
            x++;
        }
        y++;
        x = col;
    }
    return drawnPixels;
}


int getScreenHeight() {
    return screenData->height;
}

int getScreenWidth() {
    return screenData->width;
}

int drawCharFrom(int character, int x, int y, int color) {
    if (x >= screenData->height || y >= screenData->width) {
        return 0;
    }
    switch (character) {
        case '\n':
            insertEnter();
            return 0;
        case '\b':
            backspace();
            return 0;
    }
    while (row % CHAR_HEIGHT != 0) {
        row++;
    }
    while (col % CHAR_WIDTH != 0) {
        col++;
    }
    unsigned char *bitMap = charBitmap(character);
    for (int i = 0; i < CHAR_HEIGHT; i++) {
        for (int j = 0; j < CHAR_WIDTH; j++) {
            unsigned int point = ((bitMap[i] >> j) & 0x01);
            if (point == 0) {
                drawPixel(row + i, col + CHAR_WIDTH - j, BACKGROUND_COLOR);
            } else {
                drawPixel(row + i, col + CHAR_WIDTH - j, color);
            }
        }
    }
    return 1;
}

int drawChar(int character, int color) {
    int ret = drawCharFrom(character, yPos, xPos, color);
    if (ret) {
        xPos += CHAR_WIDTH;
    }
    checkPosition();
    return ret;
}
