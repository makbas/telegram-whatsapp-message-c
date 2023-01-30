/******************************************************************************
 *  File Name:   main.c                                                       *
 *  Ver.: 1.00   Date: 30.01.2023                                             *
 *  Description: telegram bot and whatsapp bot api test over TLS              *
 *  Copyright:   2023 mr.ma                                                   *
 *                                                                            *
 *  Permission to use, copy, modify, merge, publish, distribute, sublicense,  *
 *  is hereby granted, free of charge, to any person obtaining a copy of this *
 *  software subject to the following conditions:                             *
 *                                                                            *
 *  The above copyright notice and this permission notice shall be included.  *
 ******************************************************************************/

// DON'T FORGET TO ADD LINKER OPTIONS: -lssl -lcrypto

// How to get telegram bot api key, visit:
// https://core.telegram.org/bots/features#creating-a-new-bot

// How to get whatsapp bot api key? visit:
// https://www.callmebot.com/blog/free-api-whatsapp-messages/

#include <stdio.h>
#include "message.h"

/**
 * for the purpose of providing examples this program
 * sends messages to both telegram and whatsapp bot apis
 */
 int main() {

    // fill in the spaces with your credidentals
    const char* tlgServer = "api.telegram.org";
    const char* tlgPort   = "443";
    const char* chatid    = "your_telegram_chat_id";
    const char* tlgKey    = "your_telegram_api_key";
    const char* tlgMsg    = "Every winter has its spring and every night has its morning.";

    initTLS();
    connectTLS(tlgServer, tlgPort);
    sendTelegramMessage(tlgServer, tlgKey, chatid, tlgMsg);
    readTLS();
    freeTLS();

    ////////////////////////////////////////////////////////////

    // fill in the spaces with your credidentals
    const char* wupServer = "api.callmebot.com";
    const char* wupPort   = "443";
    const char* phone     = "your_phone_number_starting_with_plus";
    const char* wupKey    = "your_whatsapp_api_key";
    const char* wupMsg    = "To persuade an ignorant is like describing colors to a blind person.";

    initTLS();
    connectTLS(wupServer, wupPort);
    sendWhatsAppMessage(wupServer, wupKey, phone, wupMsg);
    readTLS();
    freeTLS();

    return 0;
}



