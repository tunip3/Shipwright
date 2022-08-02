#pragma once
#include <string>
#include <unordered_map>
#include "z64item.h"

#undef MESSAGE_END

#define QM_WHITE 0x00
#define QM_RED 0x41
#define QM_GREEN 0x42
#define QM_BLUE 0x43
#define QM_LBLUE 0x44
#define QM_PINK 0x45
#define QM_YELLOW 0x46
#define QM_BLACK 0x47

#ifndef MESSAGE_DATA_STATIC_H

typedef enum {
    /*  0 */ TEXTBOX_TYPE_BLACK,
    /*  1 */ TEXTBOX_TYPE_WOODEN,
    /*  2 */ TEXTBOX_TYPE_BLUE,
    /*  3 */ TEXTBOX_TYPE_OCARINA,
    /*  4 */ TEXTBOX_TYPE_NONE_BOTTOM,
    /*  5 */ TEXTBOX_TYPE_NONE_NO_SHADOW,
    /* 11 */ TEXTBOX_TYPE_CREDITS = 11
} TextBoxType;

typedef enum {
    /* 0 */ TEXTBOX_BG_CROSS
} TextBoxBackground;

typedef enum {
    /* 0 */ TEXTBOX_POS_VARIABLE,
    /* 1 */ TEXTBOX_POS_TOP,
    /* 2 */ TEXTBOX_POS_MIDDLE,
    /* 3 */ TEXTBOX_POS_BOTTOM
} TextBoxPosition;

#endif

typedef struct {
    TextBoxType textBoxType;
    TextBoxPosition textBoxPos;
    std::string english;
    std::string german;
    std::string french;
} CustomMessageEntry;

// Message Entry without the text type and position, useful for when
// you need an array of these to loop over for registration
// that will all have the same textbox type and position.
typedef struct {
    std::string english;
    std::string german;
    std::string french;
} CustomMessageMinimal;

#define NULL_CUSTOM_MESSAGE \
    { (TextBoxType)(-1), (TextBoxPosition)(-1), "", "", "" }

typedef std::unordered_map<uint16_t, CustomMessageEntry> CustomMessageTable;

class CustomMessageManager {
  private: 
    std::unordered_map<std::string, char> textBoxSpecialCharacters;
    std::unordered_map<std::string, char> colors;
    std::unordered_map<std::string, CustomMessageTable> messageTables;

    void ReplaceSpecialCharacters(std::string &string);
    void ReplaceColors(std::string& string);
    bool InsertCustomMessage(std::string tableID, uint16_t textID, CustomMessageEntry messages);

    std::string MESSAGE_END();
    std::string ITEM_OBTAINED(uint8_t x);
    std::string NEWLINE();
    std::string COLOR(uint8_t x);
    std::string WAIT_FOR_INPUT();
    std::string PLAYER_NAME();

  public:
    static CustomMessageManager* Instance;

    CustomMessageManager();
    ~CustomMessageManager();

    bool CreateGetItemMessage(std::string tableID, GetItemID giid, ItemID iid, CustomMessageEntry messages);
    bool CreateMessage(std::string tableID, uint16_t textID, CustomMessageEntry messages);
    CustomMessageEntry RetrieveMessage(std::string tableID, uint16_t textID);
    bool ClearMessageTable(std::string tableID);
    bool AddCustomMessageTable(std::string tableID);
    void FormatCustomMessage(std::string& message, ItemID iid);
    void FormatCustomMessage(std::string& message);
};
