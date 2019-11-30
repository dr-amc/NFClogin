# NFClogin
Quick and simple 128-bit AES encrypted NFC compatible login tool.

## To Do
- Increase maximum password size.
- Add full documentation and usage guide.

## Requirements
- Arduino Pro Micro (Leonardo)
- PN532 NFC RFID Module
- 4-byte UID ISO/IEC 14443 Type A 13.56 MHz Chip

## Setup
1. Connect SDA to Digital Pin 2
2. Connect SCL to Digital Pin 3
3. Set PN532 DIP switches to I2C

## Usage
1. Use [AESencrypt.ino](AESencrypt.ino) to generate Base64 encoded password.
2. Paste encoded password into [AESdecrypt.ino](AESdecrypt.ino) and run to verify.
3. Paste encoded password into [NFClogin.ino](NFClogin.ino) to use as a HID.

## Limitations
- Maximum password size currently limited to 16 characters.
