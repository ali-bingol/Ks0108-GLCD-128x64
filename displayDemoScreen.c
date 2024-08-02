/*****************************************************************************
 File Name	: displayDemoScreen.c
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

#include "displayDemoScreen.h"
#include "KS0108.h" 

extern const unsigned char connection_16x16[32];
extern const unsigned char Green_energy_16x16[32];
extern const unsigned char lamb_16x16[32];
extern const unsigned char plug_16x16[32];
extern const unsigned char power_on_off_16x16[32];
extern const unsigned char restart_16x16[32];
extern const unsigned char settings_16x16[32];
extern const unsigned char settings_electric_16x16[32];
extern const unsigned char settings_gear_2_16x16[32];
extern const unsigned char settings_gear_16x16[32];
extern const unsigned char warning_16x16[32];

extern const unsigned char sultanAhmetCamii[];

extern const unsigned char fontBigImg_h16[];
extern const unsigned char fontMiddleImg_h8[];
extern const unsigned char fontSmallImg_h8[];

extern const unsigned char font_s[][5];
extern const unsigned char font_b[][5];


//////////////////////////////////    resim Test    ////////////////////////////////////////////////
void testSultanAhmetCamiiImg(uint8_t color){
	GLCD_DrawImg(sultanAhmetCamii,1024, 0,0,128,64,color);	
}

////////////////////////////////    Ikonlar Test    ////////////////////////////////////////////////
void testIcons(uint8_t color){
	GLCD_DrawImg(connection_16x16,			32, 0,   0, 16, 16, color);
	GLCD_DrawImg(Green_energy_16x16,		32, 17,  0, 16, 16, color);
	GLCD_DrawImg(lamb_16x16,				32, 34,  0, 16, 16, color);
	GLCD_DrawImg(plug_16x16,				32, 51,  0, 16, 16, color);
	GLCD_DrawImg(power_on_off_16x16,		32, 68,  0, 16, 16, color);
	GLCD_DrawImg(restart_16x16,				32, 85,  0, 16, 16, color);
	GLCD_DrawImg(settings_16x16,			32, 102, 0, 16, 16, color);
	GLCD_DrawImg(settings_electric_16x16,	32, 0,  17, 16, 16, color);
	GLCD_DrawImg(settings_gear_2_16x16,		32, 17, 17, 16, 16, color);
	GLCD_DrawImg(settings_gear_16x16,		32, 34, 17, 16, 16, color);
	GLCD_DrawImg(warning_16x16,				32, 51, 17, 16, 16, color);
}
////////////////////////////////    fontlar Test    ////////////////////////////////////////////////
void testSmallFonts(uint8_t color,uint8_t ExSpace,uint8_t drawLine){
	GLCD_DrawStringImg(fontSmallImg_h8, 0, 0, "!\"$%&'()*+,-./012345678", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontSmallImg_h8, 0, 10, "9:;<=>?@ABCDEFGHIJKLMN", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontSmallImg_h8, 0, 20, "OPQRSTUVWXYZ[\\]^_`abc", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontSmallImg_h8, 0, 30, "defghijklmnopqrstuvwxyz", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontSmallImg_h8, 0, 40, "{|}~", color, ExSpace, drawLine);
}

void testMiddleFonts(uint8_t color,uint8_t ExSpace,uint8_t drawLine){
	GLCD_DrawStringImg(fontMiddleImg_h8, 0, 0, "!\"$%&'()*+,-./0123456", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontMiddleImg_h8, 0, 10, "789:;<=>?@ABCDEFGHIJK", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontMiddleImg_h8, 0, 20, "LMNOPQRSTUVWXYZ[\\]^_`", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontMiddleImg_h8, 0, 30, "abcdefghijklmnopqrstu", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontMiddleImg_h8, 0, 40, "vwxyz{|}~", color, ExSpace, drawLine);
}

void testMiddleFontsNoImg(uint8_t color){
	GLCD_DrawString(0, 0, "!\"$%&'()*+,-./0123456", color);
	GLCD_DrawString(0, 10, "789:;<=>?@ABCDEFGHIJK", color);
	GLCD_DrawString(0, 20, "LMNOPQRSTUVWXYZ[\\]^_`", color);
	GLCD_DrawString(0, 30, "abcdefghijklmnopqrstu", color);
	GLCD_DrawString(0, 40, "vwxyz{|}~", color);
}
void testBigFonts1(uint8_t color,uint8_t ExSpace,uint8_t drawLine){
	GLCD_DrawStringImg(fontBigImg_h16, 0, 0, "!\"$%&'()*+,-./", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontBigImg_h16, 0, 16, "0123456789:;", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontBigImg_h16, 0, 32, "<=>?@ABCDEF", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontBigImg_h16, 0, 48, "GHIJKLMNOP", color, ExSpace, drawLine);
}
void testBigFonts2(uint8_t color,uint8_t ExSpace,uint8_t drawLine){
	GLCD_DrawStringImg(fontBigImg_h16, 0, 0, "QRSTUVWXYZ", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontBigImg_h16, 0, 16, "[\\]^_`abcdefg", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontBigImg_h16, 0, 32, "ghijklmnopqrs", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontBigImg_h16, 0, 48, "tuvwxyz{|}~", color, ExSpace, drawLine);
}
////////////////////////////////    Demo Menu Test    //////////////////////////////////////////////
void demoScreenBigSmallFont(uint8_t color,uint8_t ExSpace,uint8_t drawLine){
	GLCD_DrawStringImg(fontSmallImg_h8, 1, 10, "L1:", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontSmallImg_h8, 1, 25, "L2:", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontSmallImg_h8, 1, 40, "L3:", color, ExSpace, drawLine);
	
	GLCD_DrawStringImg(fontBigImg_h16, 28, 6, "-1.000", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontBigImg_h16, 28, 21, "-1.000", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontBigImg_h16, 28, 36, "-1.000", color, ExSpace, drawLine);
	
	GLCD_DrawStringImg(fontSmallImg_h8, 1, 0, "Cos(%)", color, ExSpace, drawLine);
	
	GLCD_DrawLine(0, 53, 128, 53, 1);
	
	GLCD_DrawStringImg(fontSmallImg_h8, 1, 55, "TCR(%) R:23 S:23 T:23",color, ExSpace, drawLine);
}
void demoScreenBigMiddleFont(uint8_t color,uint8_t ExSpace,uint8_t drawLine){
	GLCD_DrawStringImg(fontMiddleImg_h8, 1, 10, "L1:", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontMiddleImg_h8, 1, 25, "L2:", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontMiddleImg_h8, 1, 40, "L3:", color, ExSpace, drawLine);
	
	GLCD_DrawStringImg(fontBigImg_h16, 28, 6, "-1.000", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontBigImg_h16, 28, 21, "-1.000", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontBigImg_h16, 28, 36, "-1.000", color, ExSpace, drawLine);
	
	GLCD_DrawStringImg(fontMiddleImg_h8, 1, 0, "Cos(%)", color, ExSpace, drawLine);
	
	GLCD_DrawLine(0, 53, 128, 53, 1);
	
	GLCD_DrawStringImg(fontMiddleImg_h8, 1, 55, "TCR(%) R:23 S:23 T:23",color, ExSpace, drawLine);
}
void demoScreenSmallFont(uint8_t color,uint8_t ExSpace,uint8_t drawLine){
	GLCD_DrawStringImg(fontSmallImg_h8, 1, 10, "L1:", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontSmallImg_h8, 1, 20, "L2:", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontSmallImg_h8, 1, 30, "L3:", color, ExSpace, drawLine);
	
	GLCD_DrawStringImg(fontSmallImg_h8, 20, 10, "-1.000", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontSmallImg_h8, 20, 20, "-1.000", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontSmallImg_h8, 20, 30, "-1.000", color, ExSpace, drawLine);
	
	GLCD_DrawStringImg(fontSmallImg_h8, 1, 0, "kosinus(Cos)", color, ExSpace, drawLine);
	
	GLCD_DrawLine(0, 53, 128, 53, 1);
	
	GLCD_DrawStringImg(fontSmallImg_h8, 1, 55, "TCR(%) R:23 S:23 T:23",color, ExSpace, drawLine);
}
void demoScreenMiddleFont(uint8_t color,uint8_t ExSpace,uint8_t drawLine){
	GLCD_DrawStringImg(fontMiddleImg_h8, 1, 10, "L1:", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontMiddleImg_h8, 1, 20, "L2:", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontMiddleImg_h8, 1, 30, "L3:", color, ExSpace, drawLine);
	
	GLCD_DrawStringImg(fontMiddleImg_h8, 20, 10, "-1.000", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontMiddleImg_h8, 20, 20, "-1.000", color, ExSpace, drawLine);
	GLCD_DrawStringImg(fontMiddleImg_h8, 20, 30, "-1.000", color, ExSpace, drawLine);
	
	GLCD_DrawStringImg(fontMiddleImg_h8, 1, 0, "kosinus(Cos)", color, ExSpace, drawLine);
	
	GLCD_DrawLine(0, 53, 128, 53, 1);
	
	GLCD_DrawStringImg(fontMiddleImg_h8, 1, 55, "TCR(%) R:23 S:23 T:23",color, ExSpace, drawLine);
}
void demoScreenMiddleFontNoImg(uint8_t color){
	GLCD_DrawString(1, 10, "L1:", color);
	GLCD_DrawString(1, 20, "L2:", color);
	GLCD_DrawString(1, 30, "L3:", color);
	
	GLCD_DrawString(20, 10, "-1.000", color);
	GLCD_DrawString(20, 20, "-1.000", color);
	GLCD_DrawString(20, 30, "-1.000", color);
	
	GLCD_DrawString(1, 0, "kosinus(Cos)", color);
	
	GLCD_DrawLine(0, 53, 128, 53, 1);
	
	GLCD_DrawString(1, 55, "TCR(%) R:23 S:23 T:23",color);
}
////////////////////////////////////////////////////////////////////////////////////////////////////







