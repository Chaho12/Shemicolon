#include <Time.h>
unsigned long times;

// 2-dimensional array of row pin numbers:
const int row[3] = {
  2, 3, 4
};

// 2-dimensional array of column pin numbers:
const int col[5] = {
  8, 9, 10, 11, 12
};

// 2-dimensional array of pixels:
int pixels[3][5];

int count = 1000;

typedef bool charMapType[3][5];

const charMapType num0 = {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
};

const charMapType num1 = {
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0},
};

const charMapType num2 = {
  {1, 1, 1, 0, 1},
  {1, 0, 1, 0, 1},
  {1, 0, 1, 1, 1},
};

const charMapType num3 = {
  {1, 1, 1, 1, 1},
  {1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1},
};

const charMapType num4 = {
  {1, 1, 1, 1, 1},
  {0, 0, 1, 0, 0},
  {1, 1, 1, 0, 0},
};

const charMapType num5 = {
  {1, 0, 1, 1, 1},
  {1, 0, 1, 0, 1},
  {1, 1, 1, 0, 1},
};

const charMapType num6 = {
  {1, 0, 1, 1, 1},
  {1, 0, 1, 0, 1},
  {1, 1, 1, 1, 1},
};

const charMapType num7 = {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 1, 0, 0, 0},
};

const charMapType num8 = {
  {1, 1, 1, 1, 1},
  {1, 0, 1, 0, 1},
  {1, 1, 1, 1, 1},
};

const charMapType num9 = {
  {1, 1, 1, 1, 1},
  {1, 0, 1, 0, 1},
  {1, 1, 1, 0, 1},
};

const charMapType all = {
  {1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1},
};

const charMapType test = {
  {1, 0, 0, 0, 1},
  {0, 1, 0, 1, 0},                                
  {0, 0, 1, 0, 0},
};

const charMapType *charMap[10] = {&num0, &num1, &num2, &num3, &num4, &num5, &num6, &num7, &num8, &num9};
//const charMapType *charMap[1] = {&all};
// const charMapType *charMap[1] = {&num1};
// const charMapType *charMap[1] = {&test};

void setup() {
  Serial.begin(9600);
  // initialize the I/O pins as outputs
  // iterate over the pins:
  for (int thisPin = 0; thisPin < 5; thisPin++) {
      pinMode(col[thisPin], OUTPUT);
  }
  for (int thisPin = 0; thisPin < 3; thisPin++) {
    // initialize the output pins:
    pinMode(row[thisPin], OUTPUT);
    // take the row pins (i.e. the cathodes) high to ensure that
    // the LEDS are off:
    digitalWrite(row[thisPin], HIGH);
  }

  //setupScreen();
  setupChar();

}

void loop() {

  // draw the screen:
  refreshScreen();
  
  if(count-- == 0){
    count = 1000;
    setupChar();
  }

}

void setupChar(){
  //Number I want
  times = millis();
  //Serial.println(times);
  int second = 9 - (int) ((times / 60000) % 10);
  
  Serial.println(second);
  const charMapType *cMap = charMap[second];
  //charMapType *cMap = &charDummy;

  if(second < 0)
    second = 9;
  
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 5; y++) {
      bool v = (*cMap)[x][y];
      if(v){
        pixels[x][y] = LOW;
      }else{
        pixels[x][y] = HIGH;
      }
    }
  }

}

void refreshScreen() {
  // iterate over the cols (anodes):
  for (int thisCol = 0; thisCol < 5; thisCol++) {
    // take the col pin (anode) high:
    digitalWrite(col[thisCol], HIGH);
    // iterate over the rows (cathodes):
    for (int thisRow = 0; thisRow < 3; thisRow++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the col is HIGH and the row is LOW,
      // the LED where they meet turns on:
      digitalWrite(row[thisRow], thisPixel);
      // turn the pixel off:
      if (thisPixel == LOW) {
        digitalWrite(row[thisRow], HIGH);
      }
    }
    // take the col pin low to turn off the whole row:
    digitalWrite(col[thisCol], LOW);
  }
}
