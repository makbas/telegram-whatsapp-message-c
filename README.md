# telegram-whatsapp-message-c
Simple C library to send messages over TLS to Telegram bot api or/and WhatsApp bot api

// DON'T FORGET TO ADD LINKER OPTIONS: -lssl -lcrypto

// How to get telegram bot api key, visit:
// https://core.telegram.org/bots/features#creating-a-new-bot

// How to get whatsapp bot api key? visit:
// https://www.callmebot.com/blog/free-api-whatsapp-messages/

You can use any character in your messages.
Text messages are encoded URL friendly format before being sent.

Tested on Raspberry Pi 3b+ running Linux Bullseye

Q&A:
Q: Can I send message to any telegram user with phone number?
A: No. You must have his/her (or a group's) chatid.

Q: How I get his/her chatid?
A: On an Android device;
 1. Tap to open the Telegram app.
 2. In the top-right corner, tap on the small magnifying glass icon.
 3. Type @RawDataBot in the search dialog box and then tap the search icon.
 4. Select 'Telegram Bot Raw' from the search results.
 5. You’ll get an auto-reply message. Tap the 'Start' button.
 6. You’ll get another message containing your First Name, Last Name, and Chat ID. Find chat from the list of information.
 7. Under chat, you’ll see a number. It’s marked with the word id on the right-hand side. That’s your Chat ID number.

Q: Can I send message to any whatsapp user?
A: The callmebot supports (free of charge) to send only to yourself.
