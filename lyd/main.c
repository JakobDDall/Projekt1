#include <header.h>



int baudRate = 9600;
int outputState = 0;

typedef struct Output       //Struct for output. 8 pladser i struct. Bestemt fra SOMO-II datasheet.
{
	unsigned char start;
	unsigned char command;
	unsigned char feedback;
	unsigned char para1;
    unsigned char para2;
    unsigned char checksum1;
    unsigned char checksum2;
    unsigned char end;

}Output;


int main(void)
{


    Output startSound;      //Startlyden ligger i mappe 01, er fil 001. Kommando "7E 0F 00 01 01 FF EF EF" sendes. "SPECIFY FOLDER & TRACK"
    startSound.start = 0x7E;
    startSound.command = 0x0F;
    startSound.feedback = 0x00;
    startSound.para1 = 0x01;
    startSound.para2 = 0x01;
    startSound.checksum1 = 0xFF;
    startSound.checksum2 = 0xEF;
    startSound.end = 0xEF;


    Output reflexSound;     //Reflexlyden ligger i mappe 01, er fil 002. Kommando "7E 0F 00 01 02 FF EF EF" sendes. "SPECIFY FOLDER & TRACK"
    reflexSound.start = 0x7E;
    reflexSound.command = 0x0F;
    reflexSound.feedback = 0x00;
    reflexSound.para1 = 0x01;
    reflexSound.para2 = 0x02;
    reflexSound.checksum1 = 0xFF;
    reflexSound.checksum2 = 0xEF;
    reflexSound.end = 0xEF;


    Output finishSound;     //Færdiglyden ligger i mappe 01, er fil 003. Kommando "7E 0F 00 01 03 FF EF EF" sendes. "SPECIFY FOLDER & TRACK"
    finishSound.start = 0x7E;
    finishSound.command = 0x0F;
    finishSound.feedback = 0x00;
    finishSound.para1 = 0x01;
    finishSound.para2 = 0x03;
    finishSound.checksum1 = 0xFF;
    finishSound.checksum2 = 0xEF;
    finishSound.end = 0xEF;


    Output stop;        //Stopkommando. Stopper afspilning af fil "7E 16 00 00 00 FF EA EF"
    stop.start = 0x7E;
    stop.command = 0x16;
    stop.feedback = 0x00;
    stop.para1 = 0x00;
    stop.para2 = 0x00;
    stop.checksum1 = 0xFF;
    stop.checksum2 = 0xEA;
    stop.end = 0xEF;
    

    Output volUp;       //Volume up kommando. Skruer op for lyden. "7E 04 00 00 00 FF FC EF"
    volUp.start = 0x7E;
    volUp.command = 0x04;
    volUp.feedback = 0x00;
    volUp.para1 = 0x00;
    volUp.para2 = 0x00;
    volUp.checksum1 = 0xFF;
    volUp.checksum2 = 0xFC;
    volUp.end = 0xEF;



    PrepareComms(baudRate);         //Klargør kommunikation med SOMO-II. Baudrate inputtes, OG ANDET ????
    


    
    for(int i = 0; i < 10; i++)     //Sender volUp kommando mange gange, så vi er sikker på at den er MAX
        SendCommand(volUp);





    while(1)
    {
        
        switch (outputState)     //Send kommando alt efter outPutState. Hvis det ikke matcher cases, bruges default.
        {
            case STARTOUT:
                SendCommand(startSound);
                break;
            case REFLEXOUT:
                SendCommand(reflexSound);
                break;
            case FINISHOUT:
                SendCommand(finishSound);
                break;
            case STOPOUT:
                SendCommand(stop);
                break;
            default:
                OUTPUTBEN = 0;      // SPAM output med nuller, hvis en kommando ikke skal sendes. Så kommer der ikke støj.
        }
    }









}