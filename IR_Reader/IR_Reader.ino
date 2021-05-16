/**************************************************************
 * You read IR Remote button value using this and!
 *
 *   Downloads, Guide:           https://github.com/KamranBabar16/KB-Smart-Home-Automation-Using-NodeMCU/blob/main/Guide.pdf
 *   My Website:                 https://bit.ly/3nNIqyj
 *   Social networks:            https://twitter.com/KamranBabar16
 *                               https://www.facebook.com/KamranBabarOfficial
 *                               https://www.linkedin.com/in/kamranbabar16/
 *
 *
 **************************************************************
 *
 * NOTE: Use this only for non-commercial projects!!!
 *
 **************************************************************/

#include <IRrecv.h>

// an IR detector/demodulator is connected to GPIO pin 2
uint16_t RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();  // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    unsigned int ircode = results.value;
    Serial.println(ircode);
    irrecv.resume();  // Receive the next value
  }
  delay(100);
}
