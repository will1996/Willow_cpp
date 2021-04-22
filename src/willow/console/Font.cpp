//
// Created by W on 10/9/20.
//

#include "willow/console/Font.hpp"


#include"willow/console/consolas_font.hpp"


namespace wlo{
    Font::Font(std::string ttfFile) :m_BitMap(wlo::data::Type::of<wlo::Pixel1>(),STB_FONT_consolas_bold_12_usascii_BITMAP_WIDTH,STB_FONT_consolas_bold_12_usascii_BITMAP_WIDTH){
        WILO_CORE_INFO("IGNORING ttfFile, loading COnsolas");
        const static uint32_t fontWidth = STB_FONT_consolas_bold_12_usascii_BITMAP_WIDTH;
        const static uint32_t fontHeight = STB_FONT_consolas_bold_12_usascii_BITMAP_WIDTH;
        
        static unsigned char fontPixels[fontWidth][fontHeight];
        stb_fontchar stbFontData[STB_FONT_consolas_bold_12_usascii_NUM_CHARS];
        stb_font_consolas_bold_12_usascii(stbFontData, fontPixels, fontHeight);

        memcpy(m_BitMap.data(), &fontPixels[0][0], fontWidth * fontHeight);

    }
}