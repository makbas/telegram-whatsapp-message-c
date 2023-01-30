/******************************************************************************
 *  File Name:   message.c                                                    *
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

#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include "message.h"

static SSL_CTX* ctx;
static BIO* bio;


/**
 * function: initTLS
 * initialize the SSL library and
 * creates a new object ctx as a framework to establish TLS
 *
 * returns: if ctx created reruns success
 */
int initTLS()
{
    // starts the security layer
    SSL_library_init();

    // creates a new object as a framework to establish TLS
    // method will be mutually agreed on to highest version
    ctx = SSL_CTX_new(TLS_client_method());

    // checks the return value
    if (ctx == NULL)
    {
        printf("initTLS...Failed!\n");
        return FAIL;
    }
    else
    {
        return SUCCESS;
    }
}


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
int connectTLS(const char* host, const char* port)
{
    char server[255];

    // creates a new BIO chain
    bio = BIO_new_ssl_connect(ctx);

//    snprintf(server, sizeof(server), "%s:%s", tlgServer, tlgPort);
    snprintf(server, sizeof(server), "%s:%s", host, port);
    printf("hostname: %s\n", server);

    // sets the host name and the port
    BIO_set_conn_hostname(bio, server);

    // connects the supplied BIO
    while(1)
    {
        int res = BIO_do_connect(bio);

        if (res <= 0 && BIO_should_retry(bio))
        {
            sleep(1);
            continue;
        }

        if (res <= 0)
        {
            printf("connectTLS...Failed!\n");
            return FAIL;
        }
        return SUCCESS;
    }

}


/**
 * function: writeTLS
 * tries to make a connection using parameters
 * note that port number also expected as char pointer
 *
 * msg: message to be sent to telegram bot api
 *
 * returns: if written returns success
 */
int writeTLS(char* msg)
{
    int bytesWritten = 0;
    int lenPacket = strlen(msg);

    for (int n = 0; n < lenPacket; n += bytesWritten)
    {
        if ((bytesWritten = BIO_write(bio, msg + n, lenPacket - n)) <= 0)
        {
            if (BIO_should_retry(bio))
            {
                bytesWritten = 0;
                continue;
            }

            printf("writeTLS...Failed!\n");
            return FAIL;        }
    }

    return SUCCESS;
}


/**
 * function: readTLS
 * reads the response and prints it on the console
 */
void readTLS(void)
{

    // reads the response from the server

    int len = 0;

    do
    {
      char bf[1024] = {};
      len = BIO_read(bio, bf, sizeof(bf));

      // prints out the response
      printf("%s", bf);

    } while (len > 0 || BIO_should_retry(bio));

    printf("===end of response===");

}


/**
 * function: freeTLS
 * clean and free resources
 */
void freeTLS(void)
{

    // clean after ourselves

    BIO_free_all(bio);
    SSL_CTX_free(ctx);

}


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
 int encodeUrl(const char *src, char *dst)
{
    int i;
    char *c;

    for(i=0, c=dst; src[i]; i++)
    {
        if ( isdigit(src[i]) || isalnum(src[i]) )
        {
            *(c++) = src[i];
        } else
        {
            snprintf(c, 4, "%%%02X", src[i]);
            c += 3;
        }
    }
    *c = 0;
    return c - dst;
}


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
 int sendTelegramMessage(const char* server, const char* key, const char* cid, const char* msg)
{
    char codedMessage[1024];
    encodeUrl(msg, codedMessage);

    // printf("Pre-Encoded: %s\n", msg);
    printf("Encoded: %s\n", codedMessage);

    char buffer[4096];

    snprintf(buffer, sizeof(buffer), "GET /bot%s/sendMessage?chat_id=%s&text=%s HTTP/1.1\r\nHost:%s\r\nConnection: close\r\n\r\n", key, cid, codedMessage, server);

    int rt = writeTLS(buffer);

    printf("buffer: %s\n", buffer);

    return rt;
}



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
 int sendWhatsAppMessage(const char* server, const char* key, const char* phone, const char* msg)
{
    char codedMessage[1024];
    encodeUrl(msg, codedMessage);

    // printf("Pre-Encoded: %s\n", msg);
    printf("Encoded: %s\n", codedMessage);

    char buffer[4096];

    snprintf(buffer, sizeof(buffer), "GET /whatsapp.php?phone=%s&apikey=%s&text=%s HTTP/1.1\r\nHost:%s\r\nConnection: close\r\n\r\n", phone, key, codedMessage, server);
    int rt = writeTLS(buffer);

    printf("buffer: %s\n", buffer);

    return rt;
}


