#define SPEED 150
#define P_DIT 2	// DIT
#define P_DAH 3	// DAH
#define P_AUDIO 12	// Audio output
#define P_TXOUT 13	// Tranceiver output


void setup(){
	pinMode(P_DIT, INPUT_PULLUP);
	pinMode(P_DAH, INPUT_PULLUP);
	pinMode(P_AUDIO, OUTPUT);
	pinMode(P_TXOUT, OUTPUT);
}

void beep(int curTone){
	int nextTone = 0;
	unsigned int toneLength;

	switch(curTone){
		case 1: toneLength = 1*SPEED; break;
		case 2: toneLength = 3*SPEED; break;	// one Dah = 3*Dit
	}

	digitalWrite(P_TXOUT, HIGH);
	tone(P_AUDIO, 700, toneLength);

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
	delay(SPEED);	// space between tones = one dit

	if(nextTone){
		beep(nextTone);
	}
}

void loop(){
	if(digitalRead(P_DIT) == LOW){
		beep(1);
	}
	else if(digitalRead(P_DAH) == LOW){
		beep(2);
	}
}

