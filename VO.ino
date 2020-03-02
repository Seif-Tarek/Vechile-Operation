#define Start_btn 50
#define CAN_EN 41
#define RTD_btn 30
#define RFE_EN 32
#define FRG_EN 34
#define BAMO_ERR 36
#define Charge90 38
#define Charge60 40
#define Break_light 42 
#define RTD_Sound 44
#define Pump 46
#define FB_BSPD 48
#define FB_IMD 52
#define FB_AMS 54
#define SDC_Relay 56
#define AIR_Positive 58
#define PRE_CH_relay 27 
#define FB_IMD_OUT 29
#define FB_BSPD_OUT 31
#define FB_AIR_Positive 33
#define FB_AIR_negative 35
#define FB_PRE_CH_relay 37
#define FB_DIS_CH_relay 39
#define APPS_1 13
#define APPS_2 12
#define Brake_Pressure 11
#define Brake_angle 10
#define Temp_Sensor 9

typedef enum{
  iDLE,PRECHARGE,NEUTRAL,DRIVE,DISCHARGE
}States;

States state;

void setup() 
{

    pinMode( Start_btn,INPUT);
    pinMode( CAN_EN,OUTPUT);
    pinMode( RTD_btn,INPUT);
    pinMode( RFE_EN,OUTPUT);
    pinMode( FRG_EN,OUTPUT);
    pinMode( BAMO_ERR,INPUT);
    pinMode( Charge90,INPUT);
    pinMode( Charge60,INPUT);
    pinMode( Break_light,OUTPUT);
    pinMode( RTD_Sound,OUTPUT);
    pinMode( Pump,OUTPUT);
    pinMode( FB_BSPD,INPUT);
    pinMode( FB_IMD,INPUT);
    pinMode( FB_AMS,INPUT);
    pinMode( SDC_Relay,OUTPUT);
    pinMode( AIR_Positive,OUTPUT);
    pinMode( PRE_CH_relay,OUTPUT);
    pinMode( FB_IMD_OUT,INPUT);
    pinMode( FB_BSPD_OUT,INPUT);
    pinMode( FB_AIR_Positive,INPUT);
    pinMode( FB_AIR_negative,INPUT);
    pinMode( FB_PRE_CH_relay,INPUT);
    pinMode( FB_DIS_CH_relay,INPUT);
    pinMode( FB_AIR_negative,INPUT);
    pinMode( APPS_1,OUTPUT);
    pinMode( APPS_2,OUTPUT);
    pinMode( Brake_Pressure,OUTPUT);
    pinMode( Brake_angle,OUTPUT);
    pinMode( Temp_Sensor,OUTPUT);
    state=iDLE;
    
}

void idle()
{
      if(digitalRead(Start_btn))
            state = PRECHARGE;
      else
            state = iDLE;
}

void precharge()
{
      digitalWrite(PRE_CH_relay,HIGH);
      while(!digitalRead(Charge90));
      state=NEUTRAL;
}

void Neutral()
{
      digitalWrite(PRE_CH_relay,LOW);
      digitalWrite(AIR_Positive,HIGH);
      int time1=millis();
      int time2=millis();
      while(digitalRead(RTD_btn) && analogRead(Brake_angle)>800)
      {
        if(time2-time1>=3000)
        {
          state=DRIVE;
          return; 
        }
        time2=millis();
      }

      if(digitalRead(Start_btn))
            state = DISCHARGE;  

}

void Drive()
{
    digitalWrite(RTD_Sound,HIGH);
    digitalWrite(RFE_EN,HIGH);
    delay(500);
    digitalWrite(FRG_EN,HIGH);
    
}

void loop() {
  // put your main code here, to run repeatedly:
    switch(state){
      case iDLE:
        idle();
      break;

      case PRECHARGE:
         precharge();
      break;

      case NEUTRAL:
         Neutral();
      break;

      case DRIVE:
         Drive();
      break;
    }
}
