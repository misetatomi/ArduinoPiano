/*

*/

byte commandByte;
byte noteByte;
byte velocityByte;
double FrequencyDatabase[7];
volatile bool CurrentPeroid;
float FrequencyTable[126];
double Power = 1.059463094359;
double A4Tuning = 440;
int i;

//elemzi az üzeneteket
void Analyze_Message(){
    if (commandByte >=128){
        if (commandByte<160){
            for (i=0;i<8;i++){
                if (FrequencyDatabase[i]==0){                      //ha üres helyet talál akkor feljegyzi a frekvenciát
                    FrequencyDatabase[i]=FrequencyTable[noteByte]; //note on üzenet
                    break;
                }
            }
        }

    }
    if (commandByte <=128){
        if (commandByte<160){
            for (i=0;i<8;i++){
                if (FrequencyDatabase[i]==FrequencyTable[noteByte]){ //kiszedi a note on-hoz tartozó frekvenciát
                    FrequencyDatabase[i]=0;                             //note off üzenet
                    break;
                }
            }
        }

    }
}

// beolvassa a midit
//jeleneleg nem támogatja csak a note on-note off üzeneteket
void checkMIDI(){
  do{
    if (Serial.available()){
      commandByte = Serial.read();//read first byte
      noteByte = Serial.read();//read next byte
      velocityByte = Serial.read();//read final byte
      Analyze_Message();
    }
  }
  while (Serial.available() > 2);//when at least three bytes available
}
void SetOutputs(){
    for (i=0;i<8;i++){
        if(FrequencyDatabase[i]!=0){
            
        }
    }
}
void FillFrequencyTable(){
    for (i=0;i<127;i++){
        FrequencyTable[i] = (A4Tuning*pow(Power,(i-57)));
    }
}
void setup(){
  Serial.begin(31250);
  FillFrequencyTable();
}

void loop(){
  checkMIDI();
  SetOutputs();
}


