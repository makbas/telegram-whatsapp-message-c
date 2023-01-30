/******************************************************************************
 *  File Name:   message.h                                                    *
 *  Ver.: 1.00   Date: 15.01.2023                                             *
 *  Description: send messages over TLS to telegram bot or whatsapp bot api   *
 *  Copyright:   2023 mr.ma                                                   *
 *                                                                            *
 *  Permission to use, copy, modify, merge, publish, distribute, sublicense,  *
 *  is hereby granted, free of charge, to any person obtaining a copy of this *
 *  software subject to the following conditions:                             *
 *                                                                            *
 *  The above copyright notice and this permission notice shall be included.  *
 ******************************************************************************/

#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED


// Return values for functions (contrary to common convention)
#define FAIL  0
#define SUCCESS  1

#define WUP_HOST    "api.callmebot.com"
#define WUP_APIKEY  "4968426"
#define WUP_PHONE   "+905325170051"

/**
 * function: initTLS
 * initialize the SSL library and
 * creates a new object ctx as a framework to establish TLS
 *
 * returns: if ctx created reruns success
 */
int initTLS(void);


/**
 * function: connectTLS
 * tries to make a connection using parameters
 * note that port number also expected as char pointer
 *
 * host: host name or ip
 * port: port number
 *
 * returns: if connection made returns success
 */
int connectTLS(const char* host, const char* port);


/**
 * function: writeTLS
 * tries to make a connection using parameters
 * note that port number also expected as char pointer
 *
 * msg: message to be sent to telegram bot api
 *
 * returns: if written returns success
 */
int writeTLS(char* msg);


/**
 * function: readTLS
 * reads the response and prints it on the console
 */
void readTLS(void);


/**
 * function: freeTLS
 * clean and free resources
 */
void freeTLS(void);


/**
 * function: encodeUrl
 * encodes non alphanumeric characters in the source char *
 * and stores URL friendly chars to the destination
 *
 * src: source char pointer
 * dst: destination char pointer
 *
 * returns: length of the url encoded destination
 */
int encodeUrl(const char *src, char *dst);


/**
 * function: sendTelegramMessage
 * using telegram abot api sends a message to telegram user
 *
 * server: telegram bot api host name
 * key: telegram api key
 * cid: telegram chat ID
 * msg: message to be delivered
 *
 * returns: success if written peacefully
 */
 int sendTelegramMessage(const char* server, const char* key, const char* cid, const char* msg);


/**
 * function: sendWhatsAppMessage
 * using callmebot api sends a message to whatsapp user
 *
 * server: callmebot api host name
 * key: WhatsApp api key
 * cid: WhatsApp phone no
 * msg: message to be delivered
 *
 * returns: success if written peacefully
 */
 int sendWhatsAppMessage(const char* server, const char* key, const char* phone, const char* msg);

#endif // MESSAGE_H_INCLUDED
