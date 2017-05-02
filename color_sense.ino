/* color_sense.ino
 * Implementation of color sensing protocols.
 */

#include "color_sense.h"

extern Color read_color()
{
  analogWrite(
}
 analogWrite(8, 150);
  analogWrite(9, 0);
  delay(100);
  int blue = analogRead(A0);
  //Serial.println("blue");
  //Serial.println(blue);

  analogWrite(8, 0);
  analogWrite(9, 255);
  delay(50);
  int red = analogRead(A0);
 //Serial.println("red");
  //Serial.println(red);

  //analogWrite(8, 150);
  //analogWrite(9, 255);
  //delay(50);
  //int yellow = analogRead(A0);

  analogWrite(8, 0);
  analogWrite(9, 0);
  delay(100); 
  int black = analogRead(A0);
 // Serial.println("black");
  //
  Serial.println(black);

  if(red > 650 and black > 5){
      Serial.println("yellow");
      state = 0;
  } else if(red > 200){
      Serial.println("red");

        state = 4;

  } else if(red > 70 and blue > 650){
      Serial.println("blue");
      state = 1;
      onBlue = 1;
  } else{
      Serial.println("black");
      state = 1;
      //if(state == 1){
      //    state = 2;
       //   delay(100);
       //  state = 4;
      }

