/*
 * Test för solenoider
 */
int RED = 5;
int GREEN = 6; 
int BLUE = 7;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(13,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {


  digitalWrite(RED,HIGH);
  digitalWrite(GREEN,HIGH);
  digitalWrite(BLUE,HIGH);
  delay(500);
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
  digitalWrite(BLUE,LOW);
  delay(500);
  
  


}
