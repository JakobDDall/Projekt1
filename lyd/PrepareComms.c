
void PrepareComms(int baud)
{
    UBRR2 = F_CPU/(16*baud) - 1; // Sæt baud rate af output
    UCSR2B = 0b00011000;
	UCSR2C = 0b00000110;
}