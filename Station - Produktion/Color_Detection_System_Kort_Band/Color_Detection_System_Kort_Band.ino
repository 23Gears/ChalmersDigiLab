
/*
 *  Uppgift 1) Definiera utgångar för solenoider
 */

int solenoidRed = 5  ;
int solenoidGreen =6 ;
int solenoidBlue = 7 ;

/*
 *  Uppgift 2) Definiera utgångar för LEDs
 */

 int RedLED = 2  ;
 int GreenLED =3 ;
 int BlueLED = 4 ;


// Define colour sensor LED pins
int ledArray[] = {RedLED,GreenLED,BlueLED};

// boolean to know if the balance has been set
boolean balanceSet = false;

//place holders for colour detected
int red = 0;
int green = 0;
int blue = 0;

//floats to hold colour arrays
float colourArray[] = {0,0,0};
//float whiteArray[] = {0,0,0};
//float blackArray[] = {0,0,0};

// INSTÄLLNINGAR



float whiteArray[] = {123,102,103};
float blackArray[] = {48,44,44};
int blackLimit = 9;
int blinkTime= 100;

// -------------------------

int backgroundArray[2];
float previousR=blackArray[0];
float previousG=blackArray[1];
float previousB=blackArray[2];
int c1r=184;
int c1g=63;
int c1b=55;

int c2r=24;
int c2g=149;
int c2b=108;

int c3r=24;
int c3g=85;
int c3b=130;

boolean redSimilar;
boolean greenSimilar;
boolean blueSimilar;




//place holder for average
int avgRead;
int deltaR;
int deltaG;
int deltaB;

int delta1;
int delta2;
int delta3;
float avgdelta;


void setup(){
 
  //setup the outputs for the colour sensorpro
  pinMode(RedLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  pinMode(BlueLED,OUTPUT);
 
  //begin serial communication
  Serial.begin(9600);
  pinMode(solenoidRed, OUTPUT);
  pinMode(solenoidGreen, OUTPUT);
  pinMode(solenoidBlue, OUTPUT);

  
 // Serial.println("SETUP") ;
 // Serial.println("Black Limit: "+ blackLimit);
 // Serial.println("Difference Interval: " + diffInterval);
  //checkColour();
  for(int i = 0; i <= 2; i++){
    backgroundArray[i] = colourArray[i];
   // Serial.println("Setting Background");
   // Serial.println(backgroundArray[i]);
   // Serial.println(" ") ;
   }
   
  

}

void loop(){
  
    checkBalance();
    checkColour();
    printColour();

    for(int i = 0; i <= 2; i++){
       backgroundArray[i] = colourArray[i];
      }

    checkColour();

    if(colourArray[0] < blackLimit && colourArray[1] < blackLimit && colourArray[2] < blackLimit){
      Serial.println("BLACK DETECTED");  
    }
    else  {
    

    if(colourArray[0] > colourArray[1] && colourArray[0] > colourArray[2]){                            //RÖD
     Serial.print("RÖD HITTAD");

      digitalWrite(solenoidRed,HIGH);       //RÖD PÅ
      digitalWrite(solenoidGreen,LOW);      //GRÖN AV
      digitalWrite(solenoidBlue,LOW);       //BLÅ AV

     }

     
    if(colourArray[1] > colourArray[0] && colourArray[1] > colourArray[2] && colourArray[1] < 200){     //GRÖN
     Serial.print("GRÖN HITTAD"); 
     
     digitalWrite(solenoidRed,LOW);         //RÖD AV
     digitalWrite(solenoidGreen,HIGH);      //GRÖN PÅ
     digitalWrite(solenoidBlue,LOW);        //BLÅ AV

     }
     
     if(colourArray[2] > colourArray[0] && colourArray[2] > colourArray[1]){                            //BLÅ
     Serial.print("BLÅ HITTAD"); 
     
     digitalWrite(solenoidRed,LOW);         //RÖD AV
     digitalWrite(solenoidGreen,LOW);       //GRÖN AV
     digitalWrite(solenoidBlue,HIGH);       //BLÅ PÅ

     }
    } //else if
   
}

void checkBalance(){
  //check if the balance has been set, if not, set it
  if(balanceSet == false){
    setBalance();
  }

}

void setBalance(){
  //set white balance
   delay(5000);                              //delay for five seconds, this gives us time to get a white sample in front of our sensor
  //scan the white sample.
  //go through each light, get a reading, set the base reading for each colour red, green, and blue to the white array
  for(int i = 0;i<=2;i++){
     digitalWrite(ledArray[i],HIGH);
     delay(100);
     getReading(5);          //number is the number of scans to take for average, this whole function is redundant, one reading works just as well.
     whiteArray[i] = avgRead;
     Serial.println(whiteArray[i]);
     digitalWrite(ledArray[i],LOW);
     delay(100);
  }
  //done scanning white, now it will pulse blue to tell you that it is time for the black (or grey) sample.
   //set black balance
    delay(5000);              //wait for five seconds so we can position our black sample 
  //go ahead and scan, sets the colour values for red, green, and blue when exposed to black
  for(int i = 0;i<=2;i++){
     digitalWrite(ledArray[i],HIGH);
     delay(100);
     getReading(5);
     blackArray[i] = avgRead;
     //blackArray[i] = analogRead(2);
       Serial.println(blackArray[i]);
     digitalWrite(ledArray[i],LOW);
     delay(100);
  }
   //set boolean value so we know that balance is set
  balanceSet = true;
  //delay another 5 seconds to allow the human to catch up to what is going on
  delay(5000);
    previousR=blackArray[0];
    previousG=blackArray[1];
    previousB=blackArray[2];
  }


void getReading(int times){
  int reading;
  int tally=0;
  //take the reading however many times was requested and add them up
for(int i = 0;i < times;i++){
   reading = analogRead(0);
   tally = reading + tally;
   delay(8);
}
//calculate the average and set it
avgRead = (tally)/times;
}

//prints the colour in the colour array, in the next step, we will send this to processing to see how good the sensor works.
void printColour(){
Serial.print("R = ");
Serial.println(int(colourArray[0]));
Serial.print("G = ");
Serial.println(int(colourArray[1]));
Serial.print("B = ");
Serial.println(int(colourArray[2]));
//delay(2000);
}

void checkColour(){
    for(int i = 0;i<=2;i++){
     digitalWrite(ledArray[i],HIGH);  //turn or the LED, red, green or blue depending which iteration
     delay(100);                      //delay to allow CdS to stabalize, they are slow
     getReading(3);                  //take a reading however many times
     colourArray[i] = avgRead;        //set the current colour in the array to the average reading
     float greyDiff = whiteArray[i] - blackArray[i];                    //the highest possible return minus the lowest returns the area for values in between
     colourArray[i] = (colourArray[i] - blackArray[i])/(greyDiff)*255; //the reading returned minus the lowest value divided by the possible range multiplied by 255 will give us a value roughly between 0-255 representing the value for the current reflectivity(for the colour it is exposed to) of what is being scanned
     digitalWrite(ledArray[i],LOW);   //turn off the current LED
     delay(blinkTime);
  }
}







