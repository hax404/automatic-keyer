#define SPEED 120    // length of dit in ms
#define FREQ 750    // tone frequency
#define P_DIT 2    // DIT
#define P_DAH 3    // DAH
#define P_MAN 4    // manual
#define P_AUDIO 5    // Audio output (must be pwm)
#define P_TXOUT 6    // Tranceiver output

struct symbol{
    struct symbol *dit;
    struct symbol *dah;
    char character;
};

struct symbol *start;
struct symbol *cur = start;

// Source: https://commons.wikimedia.org/wiki/File:Morse_code_tree3.png
// FIXME: apply from http://www.itu.int/dms_pubrec/itu-r/rec/m/R-REC-M.1677-1-200910-I!!PDF-E.pdf
void createTree(){
    struct symbol //*start = (struct symbol*) 0,
        *last = (struct symbol*) 0,
        *temp = (struct symbol*) 0;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'e';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'i';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 's';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'h';
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
    temp->character = 'v';
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
    temp->character = 'u';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'f';
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
    temp->character = '?';
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
    temp->character = 'a';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'r';
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
    temp->character = '.';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dit->dah->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'w';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'p';
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
    temp->character = 'j';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // ĵ
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dah->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '1';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dah->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '\'';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dit->dah->dah->dah->dah->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 't';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'n';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'd';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'b';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '6';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '-';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '=';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'x';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = '/';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dit->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'k';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'c';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dah->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // ç
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dah->dit->dit = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = 'y';
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dah->dah = temp;

    temp = (struct symbol*) malloc (sizeof(struct symbol));
    temp->character = ' ';      // ĥĤ
    temp->dit = (struct symbol*) 0;
    temp->dah = (struct symbol*) 0;
    start->dah->dit->dah->dah->dit = temp;


}

void setup(){
    pinMode(P_DIT, INPUT_PULLUP);
    pinMode(P_DAH, INPUT_PULLUP);
    pinMode(P_MAN, INPUT_PULLUP);
    pinMode(P_AUDIO, OUTPUT);
    pinMode(P_TXOUT, OUTPUT);

    Serial.begin(115200);
    createTree();

    tone(P_AUDIO, 1000, 150);
    delay(150);
    tone(P_AUDIO, 2000, 150);
    delay(150);
    tone(P_AUDIO, 1500, 150);
    delay(150);
    tone(P_AUDIO, 1750, 150);
    delay(150);

    Serial.println("Started automatic keyer");
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
            cur = start;
        }
    }
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

