// dragrove-cloud-test for edwin
// code here: https://github.com/reeedstudio/Cloud_Dragrove_Test

#include <SoftwareSerial.h>

#define START1      0x53
#define START2      0x15
#define END1        0x2f
#define END2        0x45

SoftwareSerial mySerial(6, 7); // RX, TX

unsigned char dtaUart[20];
unsigned char dtaLen = 0;
unsigned char getDta = 0;

/*********************************************************************************************************
** Function name:           addDevice
** Descriptions:            add a device to dragino, sensorid and actuatorid is setted
*********************************************************************************************************/
unsigned char addDevice(unsigned char deviceId, unsigned char sensorId, unsigned char actuatorId)
{
    // add code here 
    
    Serial.println("\r\n----------ADD CMD----------\r\n");
    Serial.print("deviceId =\t");
    Serial.println(deviceId);
    Serial.print("sensorId =\t");
    Serial.println(sensorId);
    Serial.print("actuatorId =\t");
    Serial.println(actuatorId);
    return 1;
}

/*********************************************************************************************************
** Function name:           delDevice
** Descriptions:            delete a device
*********************************************************************************************************/
unsigned char delDevice(unsigned char deviceId)
{
    // add code here
    Serial.println("\r\n----------DEL CMD----------\r\n");
    Serial.print("deviceId =\t");
    Serial.println(deviceId);
    return 1;
}

/*********************************************************************************************************
** Function name:           pushDta
** Descriptions:            push data to dragino, data is random(0, 1023)
*********************************************************************************************************/
unsigned char pushDta(unsigned char deviceId)
{
    // add code here 
    unsigned int dat= random(0, 1023);
    Serial.println("\r\n----------PUSH CMD----------\r\n");
    Serial.print("deviceId =\t");
    Serial.println(deviceId);
    Serial.print("data =\t\t");
    Serial.println(dat);
    return 1;
}

/*********************************************************************************************************
** Function name:           serialDtaProc
** Descriptions:            serialDtaProc
*********************************************************************************************************/
unsigned char serialDtaProc()
{
    if(getDta)
    {
        getDta = 0;                                                         // clear get data flag

        if(dtaUart[0] != 'A' || dtaUart[1] != 'T' || dtaLen<7)              // err atcmd
        {
            goto ERR;                       // I know goto is not good, but it's really useful here
        }
        
        if(dtaUart[2] == 'A' && dtaUart[3] == 'D' && dtaUart[4] == 'D')     // add command
        {
            if(dtaUart[5] != ' ')goto ERR;
            
            if(dtaUart[6]>='0' && dtaUart[6]<='9')
            {
                addDevice(dtaUart[6]-'0', 1, 200);
                goto OK;                
            }
            else
            {
                goto ERR;
            }
        }
        else if(dtaUart[2] == 'D' && dtaUart[3] == 'E' && dtaUart[4] == 'L')    // del command
        {
            if(dtaUart[5] != ' ')goto ERR;
            
            if(dtaUart[6]>='0' && dtaUart[6]<='9')
            {
                delDevice(dtaUart[6]-'0');
                goto OK;                
            }
            else
            {
                goto ERR;
            }
        }
        else if(dtaUart[2] == 'P' && dtaUart[3] == 'U' && dtaUart[4] == 'S' && dtaUart[5] == 'H')   // push data
        {
            if(dtaUart[6] != ' ')goto ERR;
            
            if(dtaUart[7]>='0' && dtaUart[7]<='9')
            {
                pushDta(dtaUart[7]-'0');
                goto OK;                
            }
            else
            {
                goto ERR;
            }
        }
        else
        {
            goto ERR;
        }
        
        
    }
    else
    {
        return 0;
    }
    
ERR:
    Serial.println("ERR ATCMD");
    dtaLen = 0;
    return 0;
OK:
    dtaLen = 0;
    return 1;
}


/*********************************************************************************************************
** Function name:           setup
** Descriptions:            setup
*********************************************************************************************************/
void setup()
{
    Serial.begin(115200);               // hard serial baudrate, you can change it to fit you
    mySerial.begin(115200);             // you can change baudrate to fit you
    
    Serial.println("hello world");      // just to show setup over
}

/*********************************************************************************************************
** Function name:           loop
** Descriptions:            loop
*********************************************************************************************************/
void loop()
{
    // if you don't want to use ATCMD, you can add addDevicd() or delDevice() or pushDta() here
    
    serialDtaProc();
    delay(1);
}

/*********************************************************************************************************
** Function name:           serialEvent
** Descriptions:            serialEvent will run after loop() by Arduino system
*********************************************************************************************************/
void serialEvent()
{
    while (Serial.available())
    {
        dtaUart[dtaLen++] = (unsigned char)Serial.read();
        if(dtaUart[dtaLen-1] == '\n')
        {
            getDta = 1;
        }
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/