
void SendCommand(struct Output command)
{

    while((UCSR2A & 0b00100000)==0)	 //Vent på register er klar til at modtage byte
    {}
    UDR2 = command.start; //Send første byte til output


    while((UCSR2A & 0b00100000)==0)	 //Vent på register er klar til at modtage byte
    {}
    UDR2 = command.feedback; //Send andet byte til output

    while((UCSR2A & 0b00100000)==0)	
    {}
    UDR2 = command.para1;

    while((UCSR2A & 0b00100000)==0)	
    {}
    UDR2 = command.para2;

    while((UCSR2A & 0b00100000)==0)	
    {}
    UDR2 = command.checksum1;

    while((UCSR2A & 0b00100000)==0)	
    {}
    UDR2 = command.checksum2;

    while((UCSR2A & 0b00100000)==0)	
    {}
    UDR2 = command.end;


}