/*****************************************************************************
 File Name	: KS0108.c
 Author		: Ali Bingöl - Copyright (C) 2024
 Date		: 24/07/2024
 Revised	: 24/07/2024
 Version	: 1.000
 Target MCU	: STM32

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
   BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
   OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
   WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
   ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
   SOFTWARE.
   
 This code is distributed under the GNU Public License
		which can be found at http://www.gnu.org/licenses/gpl.txt

*****************************************************************************/


#include "KS0108.h"
#include "main.h"
#include <string.h>
#include <stdlib.h>

extern const unsigned char tense[];
extern const unsigned char sultanAhmetCamii[];
extern const unsigned char font_b[][5];

unsigned char screenBuffer[KS0108_SCREEN_WIDTH * (KS0108_SCREEN_HEIGHT / 8)];

uint32_t OUT_LCD_Dy_Pin[] = {OUT_LCD_DB0_Pin,OUT_LCD_DB1_Pin,OUT_LCD_DB2_Pin,OUT_LCD_DB3_Pin,OUT_LCD_DB4_Pin,OUT_LCD_DB5_Pin,OUT_LCD_DB6_Pin,OUT_LCD_DB7_Pin};  

#define delayCycle     50
#define LCD_PORTS      GPIOC
#define bitN(arg,n)    (((arg)>>(n))&1) 

unsigned char screen_x = 0, screen_y = 0;
unsigned char cVal,cValTmp[6][128];

void GLCD_EN(uint16_t x){
	if(x==1)	HAL_GPIO_WritePin(LCD_PORTS, OUT_LCD_EN_Pin, GPIO_PIN_SET);
	else 		HAL_GPIO_WritePin(LCD_PORTS, OUT_LCD_EN_Pin, GPIO_PIN_RESET); 
}
void GLCD_DI(uint16_t x){
	if(x==1)	HAL_GPIO_WritePin(LCD_PORTS, OUT_LCD_DI_Pin, GPIO_PIN_SET);
	else		HAL_GPIO_WritePin(LCD_PORTS, OUT_LCD_DI_Pin, GPIO_PIN_RESET);
}
void GLCD_DATA(uint16_t x,uint16_t y){
	if(x==1)	HAL_GPIO_WritePin(LCD_PORTS, OUT_LCD_Dy_Pin[y], GPIO_PIN_SET);
	else		HAL_GPIO_WritePin(LCD_PORTS, OUT_LCD_Dy_Pin[y], GPIO_PIN_RESET);
}
void GLCD_CS1(uint16_t x){
	if(x==1)	HAL_GPIO_WritePin(LCD_PORTS, OUT_LCD_CS1_Pin, GPIO_PIN_SET);
	else		HAL_GPIO_WritePin(LCD_PORTS, OUT_LCD_CS1_Pin, GPIO_PIN_RESET);
}
void GLCD_CS2(uint16_t x){
	if(x==1)	HAL_GPIO_WritePin(LCD_PORTS, OUT_LCD_CS2_Pin, GPIO_PIN_SET);
	else		HAL_GPIO_WritePin(LCD_PORTS, OUT_LCD_CS2_Pin, GPIO_PIN_RESET);
}

void delaySomeCycle(uint16_t delay){  
	while(delay--) {__nop();} 
}


void GLCD_EnableController(unsigned char controller){
	switch(controller){
		case 1 : GLCD_CS1(0); break;
		case 0 : GLCD_CS2(0); break;
	}
}

void GLCD_DisableController(unsigned char controller){
	switch(controller){
		case 1 : GLCD_CS1(1); break;
		case 0 : GLCD_CS2(1); break;
	}
}


void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller){
	GLCD_DI(0);
	GLCD_EnableController(controller);
	for(char i=0; i<8; i++){    
		GLCD_DATA(bitN(commandToWrite,i),i);  
	}
	GLCD_EN(1);
	delaySomeCycle(delayCycle);
	GLCD_EN(0);
	GLCD_DisableController(controller);
}


void GLCD_WriteData(unsigned char dataToWrite){
	GLCD_DI(1);
	for(char i=0; i<8; i++){    
		GLCD_DATA(bitN(dataToWrite,i),i);  
	}
	GLCD_EnableController(screen_x / 64);
	GLCD_EN(1);
	delaySomeCycle(delayCycle);
	GLCD_EN(0);
	GLCD_DisableController(screen_x / 64);
	screen_x++;
}


void GLCD_Start(void){
	unsigned char i;
//	HAL_GPIO_WritePin(OUT_LCD_RST_GPIO_Port, OUT_LCD_RST_Pin, GPIO_PIN_RESET);
	for(i = 0; i < 3; i++)
		GLCD_WriteCommand((DISPLAY_ON_CMD | ON), i);
}


void GLCD_GoTo(unsigned char x, unsigned char y){
	unsigned char i;
	screen_x = x;
	screen_y = y;

	for(i = 0; i < KS0108_SCREEN_WIDTH/64; i++) {
		GLCD_WriteCommand(DISPLAY_SET_Y | 0,i);
		GLCD_WriteCommand(DISPLAY_SET_X | y,i);
		GLCD_WriteCommand(DISPLAY_START_LINE | 0,i);
	}
	GLCD_WriteCommand(DISPLAY_SET_Y | (x % 64), (x / 64));
	GLCD_WriteCommand(DISPLAY_SET_X | y, (x / 64));
}

void GLCD_SetPixel(unsigned char x, unsigned char y, unsigned char color){
    if (x >= KS0108_SCREEN_WIDTH || y >= KS0108_SCREEN_HEIGHT) {
        return;
    }

    unsigned char bitPos = y % 8;
    unsigned char page = y / 8;

    if (color) {
        screenBuffer[x + page * KS0108_SCREEN_WIDTH] |= (1 << bitPos);
    } else {
        screenBuffer[x + page * KS0108_SCREEN_WIDTH] &= ~(1 << bitPos);
    }
}

void GLCD_FlushBuffer(void) {
	unsigned char i, j;
    for (j = 0; j < KS0108_SCREEN_HEIGHT / 8; j++) {
        GLCD_GoTo(0, j); 
		
        for (i = 0; i < KS0108_SCREEN_WIDTH; i++) {
            GLCD_WriteData(screenBuffer[i + j * KS0108_SCREEN_WIDTH]);
        }
    }
}

void GLCD_FillOrCleanAllScreen(uint8_t val){
	unsigned char i, j;
	for(j = 0; j < KS0108_SCREEN_HEIGHT/8; j++)	{
		for(i = 0; i < KS0108_SCREEN_WIDTH; i++)
			screenBuffer[i + j * KS0108_SCREEN_WIDTH]=val;
	}
}

void GLCDInit(void){
	OUT_LCD_BACKLIGHT_GPIO_Port->BSRR = OUT_LCD_BACKLIGHT_Pin; 
	GLCD_Start();  
	HAL_Delay(10);
}

void GLCD_DrawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        GLCD_SetPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void GLCD_DrawImg(const unsigned char *data, uint16_t length, uint8_t startX, uint8_t startY, uint8_t width, uint8_t height, uint8_t color){
    uint16_t index = 0;
    for (uint8_t y = 0; y < height / 8; y++) {
        for (uint8_t x = 0; x < width; x++) {
            if (index < width * height / 8) {
                uint8_t byte = data[y * width + x];
                for (uint8_t bit = 0; bit < 8; bit++) {
                    uint8_t pixelColor = (byte >> bit) & 0x01;
                    GLCD_SetPixel(startX + x, startY + y * 8 + bit, pixelColor ? color : !color);
                }
                index++;
            } else {
                break;
            }
        }
    }
}
void GLCD_DrawRectangle(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char color) {
    GLCD_DrawLine(x, y, x + width, y, color);            		// Top line
    GLCD_DrawLine(x, y, x, y + height, color);           		// left line
    GLCD_DrawLine(x + width, y, x + width, y + height, color);  // Right line
    GLCD_DrawLine(x, y + height, x + width, y + height, color); // bottom line
}

void GLCD_DrawCircle(int x0, int y0, int radius, unsigned char color) {
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;

    GLCD_SetPixel(x0, y0 + radius, color);
    GLCD_SetPixel(x0, y0 - radius, color);
    GLCD_SetPixel(x0 + radius, y0, color);
    GLCD_SetPixel(x0 - radius, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        GLCD_SetPixel(x0 + x, y0 + y, color);
        GLCD_SetPixel(x0 - x, y0 + y, color);
        GLCD_SetPixel(x0 + x, y0 - y, color);
        GLCD_SetPixel(x0 - x, y0 - y, color);
        GLCD_SetPixel(x0 + y, y0 + x, color);
        GLCD_SetPixel(x0 - y, y0 + x, color);
        GLCD_SetPixel(x0 + y, y0 - x, color);
        GLCD_SetPixel(x0 - y, y0 - x, color);
    }
}
void GLCD_DrawTextInRectangle(unsigned char x, unsigned char y, unsigned char width, unsigned char height, char *str, unsigned char color) {
    
    unsigned char textX = x + 2; // Metin için x koordinatı (dikey boşluk)
    unsigned char textY = y + 2; // Metin için y koordinatı (yatay boşluk)
    
    GLCD_DrawString(textX, textY, str, color);
	GLCD_DrawRectangle(x, y, width, height, color);
}

void GLCD_DrawChar(unsigned char x, unsigned char y, char c, unsigned char color) {
//    if (c < 32 || c > 127) return; // Font dizisinin dışındaki karakterler için
    for (unsigned char i = 0; i < 5; i++) {
        unsigned char line = font_b[c - 19][i];
        for (unsigned char j = 0; j < 8; j++) {
            if (line & 0x1) {
                GLCD_SetPixel(x + i, y + j, color);
            } else {
                GLCD_SetPixel(x + i, y + j, !color);
            }
            line >>= 1;
        }
    }
}

void GLCD_DrawString(unsigned char x, unsigned char y, char *str, unsigned char color) {
	for(char i=0; i<strlen(str); i++)	{
		GLCD_DrawChar(x, y, str[i], color);
		x += 6;
	}
}


unsigned char GLCD_DrawCharImg(const unsigned char *font, unsigned char x, unsigned char y, char c, unsigned char color, unsigned char extraSpaceToRight){
	unsigned char charIndex =0,charHeight=8;
    unsigned char charWidth = 0,charWidthVal = 0;
	uint16_t bitmapStartIndex=0;
	unsigned char tmpString[2][40]={0};
	
    // Validate the character range
    if ((c > 0 && c < ' ') || c > '~') return 0;
	
    // get the height of font
    charHeight = font[3];
	
    // check if height is other than 8 or 16
    if(!(charHeight == 8 || charHeight == 16)) return 0;

    // Calculate the character index
    charIndex = c - ' ';
	if(c==0) charIndex = 0;
	
    // Retrieve the character width (in bytes)
    charWidth = font[6 + charIndex];

    // Calculate the bitmap start index
    bitmapStartIndex = 102; // Starting after the header and widths
    for (unsigned char i = 0; i < charIndex; i++) {
		if(charHeight==16)		charWidthVal = font[6 + i]<<1;
		else if(charHeight==8)	charWidthVal = font[6 + i];
        bitmapStartIndex += charWidthVal; 
    }

	for(char i=0; i<charWidth; i++){
		tmpString[0][i+extraSpaceToRight]=font[bitmapStartIndex+i];
		if(charHeight==16) tmpString[1][i+extraSpaceToRight]=font[bitmapStartIndex+charWidth+i];
	}
		
    GLCD_DrawImg(tmpString[0], charWidth+(extraSpaceToRight), x, y, charWidth+(extraSpaceToRight), 8, color);
    if(charHeight==16) GLCD_DrawImg(tmpString[1], charWidth+(extraSpaceToRight), x, y+8, charWidth+(extraSpaceToRight), 8, color);
	
	return charWidth;
}


//burada 
void GLCD_DrawStringImg(const unsigned char *font, unsigned char x, unsigned char y, const char *str, unsigned char color, unsigned char extraSpaceToRight, unsigned char drawLineToTop) {
	char len=strlen(str),width=0;
	for(char i=0; i<=len; i++)	{
		width=GLCD_DrawCharImg(font, x, (drawLineToTop)?(y+1):(y), str[i], color, (extraSpaceToRight)) + (extraSpaceToRight);
		if(drawLineToTop) GLCD_DrawLine(x,y,x+width-1,y,!color);
		x += width;
	}
	
}

