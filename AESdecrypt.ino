/**************************************************************************
* 
*    @title    AESdecrypt
*    @author   Dr Aaron McConville 
*    @email    a.mcconville@ulster.ac.uk
*    @date     2019/11/30
*    @license  GPL v3.0
*    
**************************************************************************/

#include <AESLib.h>
#include <Base64.h>
#include "base64.hpp"

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

int c = 0;
String uid = "0";

void setup() {
 
  Serial.begin(115200);
  while (!Serial);
  
  nfc.begin();

}

void loop() {

  if (c < 1) {
    Serial.println("\n=================================");
    Serial.println("Present card to decrypt password.");
    Serial.println("=================================\n");
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

          char pass[] = "O+2lNKO6JF98+L+3+ZBmhQ==";  //          <--------------- Base64 Encoded Password

          int passLen = sizeof(pass);
          int decodedLen = base64_dec_len(pass, passLen);
          char decoded[decodedLen];
    
          base64_decode(decoded, pass, passLen);
          Serial.print("\nBase64 Decoded: "); Serial.println(pass);

          aes128_dec_single(key, decoded);
          
          char * p = strchr(decoded, ' ');
          if (p){
            *p = 0;
          }
          
          Serial.print("Decrypted Password: "); Serial.println(decoded);

          c = 0;
          delay(2000);
        }
}
