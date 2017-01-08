#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SPEED 120    // length of dit in ms
#define FREQ 750    // tone frequency
#define P_DIT 2    // DIT
#define P_DAH 3    // DAH
#define P_MAN 4    // manual
#define P_AUDIO 5    // Audio output (must be pwm)
#define P_TXOUT 6    // Tranceiver output

LiquidCrystal_I2C lcd(0x27, 16, 2);
char buffer[17];

struct symbol{
    struct symbol *dit;
    struct symbol *dah;
    char character;
};

struct symbol *start;
struct symbol *cur;

// Source: https://commons.wikimedia.org/wiki/File:Morse_code_tree3.png
// FIXME: apply from http://www.itu.int/dms_pubrec/itu-r/rec/m/R-REC-M.1677-1-200910-I!!PDF-E.pdf
// Order: preorder
void createTree(){
    struct symbol //*start = (struct symbol*) 0,
        *last = (struct symbol*) 0,
        *temp = (struct symbol*) 0;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start = temp;

    cur = start;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'E';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'I';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'S';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'H';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '5';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dit->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '4';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'V';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // ŝ
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dit->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '3';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dit->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'U';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'F';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // é
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dah->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // ü
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // Đ
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dah->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '?';      // Question mark (note of interrogation or requestfor repetition of a transmission not understood)
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dah->dah->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '_';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dah->dah->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '2';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dah->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'A';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'R';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'l';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // è
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '"';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dit->dit->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // ä
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '+';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dit->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '.';      // Full stop (period)
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dit->dah->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'W';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'P';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // pb
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // à
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '@';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dit->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'J';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '\'';     // Apostrophe
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dah->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '1';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dah->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dah->dah->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'T';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'N';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'D';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'B';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '6';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '-';      // Hyphen or dash or subtraction sign
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '=';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'X';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '/';      // Fraction bar or division sign
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'K';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'C';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // ç
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dah->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'Y';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '(';      // Left-hand bracket (parenthesis)
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dah->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ')';      // Right-hand bracket (parenthesis)
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dah->dah->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'M';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'G';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'Z';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '7';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dit->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // unused node
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ',';      // Comma
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dit->dit->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'Q';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'O';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // ö
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '8';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dah->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ':';      // Colon or division sign
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dah->dit->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // ch
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '9';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dah->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '0';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dah->dah->dah->dah = temp;
}

void setup(){
    pinMode(P_DIT, INPUT_PULLUP);
    pinMode(P_DAH, INPUT_PULLUP);
    pinMode(P_MAN, INPUT_PULLUP);
    pinMode(P_AUDIO, OUTPUT);
    pinMode(P_TXOUT, OUTPUT);

    // initialize Serial
    Serial.begin(115200);

    // initialize the LCD
    lcd.begin();
    lcd.backlight();
    lcd.print("Behindertengleic");
    lcd.setCursor(0,1);
    lcd.print("hstellungsgesetz");

    createTree();
    buffer[0] = '\0';

    tone(P_AUDIO, 1000, 150);
    delay(150);
    tone(P_AUDIO, 2000, 150);
    delay(150);
    tone(P_AUDIO, 1500, 150);
    delay(150);
    tone(P_AUDIO, 1750, 150);
    delay(150);

    lcd.clear();
    Serial.println("Started automatic keyer");
    printParams();
    lcd.cursor();
    lcd.blink();
    lcd.setCursor(0,1);
}

void printParams(){
    // FIXME: real values
    lcd.setCursor(0,0);
    lcd.print("700Hz 50BpM");
}

void beep(int curTone){
    int nextTone = 0;
    unsigned int toneLength;

    switch(curTone){
        case 1:
            toneLength = 1*SPEED;
            cur = cur->dit;
            break;
        case 2:
            toneLength = 3*SPEED;
            cur = cur->dah;
            break;    // one Dah = 3*Dit
    }
//    Serial.print(cur->character);

    digitalWrite(P_TXOUT, HIGH);
    tone(P_AUDIO, FREQ, toneLength);

    // check if the other key is pressed while the current tone is played
    for(int i = 0; i <= toneLength; i = i+10){
        if(curTone == 1 && digitalRead(P_DAH) == LOW){
            nextTone = 2;
        }
        else if(curTone == 2 && digitalRead(P_DIT) == LOW){
            nextTone = 1;
        }
        delay(10);
    }
    digitalWrite(P_TXOUT, LOW);

    // silence
    //delay(SPEED);    // space between tones = one dit
    for(int i = 0; i <= SPEED; i = i+10){
        if(curTone == 1 && digitalRead(P_DAH) == LOW){
            nextTone = 2;
        }
        else if(curTone == 2 && digitalRead(P_DIT) == LOW){
            nextTone = 1;
        }
        delay(10);
    }

    if(nextTone){
        beep(nextTone);
    }
    else{
        if(digitalRead(P_DIT) == LOW){
            beep(1);
        }
        else if(digitalRead(P_DAH) == LOW){
            beep(2);
        }
        else{
            Serial.print(cur->character);
            printToLCD(cur->character);
            cur = start;
        }
    }
}

void printToLCD(char character){
    for(uint8_t i = 0; i<16; i++){
        if(buffer[i] == '\0'){
            buffer[i+1] = '\0';
            buffer[i] = cur->character;
            break;
        }

        // move
        else if(i==15){
            for(uint8_t j = 0; j<16; j++){
                buffer[j] = buffer[j+1];
            }
            buffer[i] = cur->character;
        }
    }
    lcd.setCursor(0,1);
    lcd.printstr(buffer);
}

void loop(){
    // automatic
    if(digitalRead(P_DIT) == LOW){
        beep(1);
    }
    else if(digitalRead(P_DAH) == LOW){
        beep(2);
    }

    // manual
    else if(digitalRead(P_MAN) == LOW){
        tone(P_AUDIO, FREQ);
        digitalWrite(P_TXOUT, HIGH);
        do{
            delay(10);
        } while(digitalRead(P_MAN) == LOW);
        digitalWrite(P_TXOUT, LOW);
        noTone(P_AUDIO);
    }
}

// vim: ai si expandtab tabstop=4 shiftwidth=4

