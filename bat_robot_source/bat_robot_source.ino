#include <NewPing.h>
/* #include <NewTone.h> */

#define SONAR_NUM 2      // Number of sensors.
#define MAX_DISTANCE 400 // Maximum distance (in cm) to ping.
/* #define BUZ1 13          // Buzzer 1 pin.
#define BUZ2 12          // Buzzer 2 pin.
Coming soon */
#define VIB1 11          // VibroEngine 1 pin.
#define VIB2 10          // VibroEngine 2 pin.

int k = 0, s = 0, av = 0;

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(2, 3, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(4, 5, MAX_DISTANCE)
};

void setup() {
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
  pinMode(VIB1, OUTPUT);
  pinMode(VIB2, OUTPUT);
}

void loop() { 
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(29); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    k += sonar[i].ping_cm();
  }

  printDistance();
  
  if (av < 15) {
    digitalWrite(VIB1, HIGH);
    digitalWrite(VIB2, HIGH);
    /* NewTone(BUZ1, 1000);
    NewTone(BUZ2, 1000);
    Again. coming soon (or not, who knows) */
    delay(500);
    digitalWrite(VIB1, LOW);
    digitalWrite(VIB2, LOW);
    /* noNewTone(BUZ1);
    noNewTone(BUZ2); */ }
  
  av = k / SONAR_NUM;
    
  k = 0;
  s = 0;
}

void printDistance() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (sonar[i].ping_cm() > MAX_DISTANCE)
      s++;
    }
    if (s != 0)
      Serial.println("The majority of sensors are out of range");
    else {    
      Serial.print("Average = ");
      Serial.print(av);
      Serial.println("cm ");
  }
}

