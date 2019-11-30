/**************************************************************************
* 
*    @title    AESencrypt
*    @author   Dr Aaron McConville 
*    @email    a.mcconville@ulster.ac.uk
*    @date     2019/11/30
*    @license  GPL v3.0
*    
**************************************************************************/

#include <AESLib.h>
#include "base64.hpp"

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

int c = 0;
String uid = "0";
unsigned char base64[100];

void setup() {
   
  Serial.begin(115200);
  while (!Serial);
  
  nfc.begin();
  
}

void loop() {

  if (c < 1) {
    Serial.println("\n============================================");
    Serial.println("Present card to generate encrypted password.");
    Serial.println("============================================\n");
    c++;
  }

  if (nfc.tagPresent())
        {
          NfcTag tag = nfc.read();
          uid = tag.getUidString();

          Serial.print("UID: "); Serial.println(uid);
         
          uid.replace(" ", "");
          
          Serial.print("Whitespace Removed: "); Serial.println(uid);

          String uid2 = uid + uid;
            
          char key[uid2.length()];     
          uid2.toCharArray(key, uid2.length());

          Serial.print("Secret Key: "); Serial.println(key);

          String password = "password"; //          <--------------- Plain Text Password (max 16 char)

          int passLen = password.length();
          
          while (passLen < 16) {
            password = password + " ";
            passLen = password.length();
          }

          char pass[password.length()];
          password.toCharArray(pass, password.length());
          
          aes128_enc_single(key, pass);      
          
          passLen = sizeof(pass);
          encode_base64(pass, passLen, base64);
          Serial.print("\nBase64 Encoded: "); Serial.println((char*)base64);

          c = 0;
          delay(2000);
        }
}
