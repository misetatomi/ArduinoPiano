/**/byte commandByte;byte noteByte;byte velocityByte;double FrequencyDatabase[7];bool CurrentPeroid;float FrequencyTable[126]double Power = 1.059463094359;double A4Tuning = 440;void setup(){  Serial.begin(31250);  FillFrequencTable()}void loop(){  checkMIDI();  EvaluatePeriod;}void FillFrequencyTable(){    for (i=0,i<127;i++){        FrequncyTable[i] = (A4Tuning*pow(Power,(i-57)));    }}void Analyze_Message(){    if (commandByte >=128){        if (commandByte<160){            for (i=0;i<8;i++){                if (FrequencyDatabase[i]==0){                    FrequencyDatabase[i]=FrequencyTable[noteByte];                    break;                }            }        }    }    if (commandByte <=128){        if (commandByte<160){            for (i=0;i<8;i++){                if (FrequencyDatabase[i]==FrequencyTable[noteByte]){                    FrequencyDatabase[i]=0;                    break;                }            }        }    }}void checkMIDI(){  do{    if (Serial.available()){      commandByte = Serial.read();//read first byte      noteByte = Serial.read();//read next byte      velocityByte = Serial.read();//read final byte      Analyze_Message();    }  }  while (Serial.available() > 2);//when at least three bytes available}void EvaluatePeroid(){    for (i=0;i<8;i++){        if(FrequencyDatabase[i]!=0){                    }    }}