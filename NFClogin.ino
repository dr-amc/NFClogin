/**************************************************************************
* 
*    @title    NFClogin
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

#include <Keyboard.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

String uid = "0";

void setup() {
  
  nfc.begin();

}

void loop() {

  if (nfc.tagPresent())
        {
          NfcTag tag = nfc.read();
          uid = tag.getUidString();
          uid.replace(" ", "");
          String uid2 = uid + uid;
          char key[uid2.length()];
          uid2.toCharArray(key, uid2.length());

          char pass[] = "O+2lNKO6JF98+L+3+ZBmhQ==";  //          <--------------- Base64 Encoded Password

          int passLen = sizeof(pass);
          int decodedLen = base64_dec_len(pass, passLen);
          char decoded[decodedLen];
          base64_decode(decoded, pass, passLen);
          aes128_dec_single(key, decoded);
          
          char * p = strchr(decoded, ' ');
          if (p){
            *p = 0;
          }
          
          Keyboard.write(KEY_RETURN);
          delay(200);
          Keyboard.print(decoded);
          delay(2000);
        }
}
