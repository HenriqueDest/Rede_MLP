const byte LED = 13;
unsigned char ADC_Buffer[8];
unsigned int val_canal0 = 0;
unsigned int val_canal1 = 0;

ISR(TIMER1_COMPA_vect)
{
  static boolean state = false;
  state = !state;  // toggle
  digitalWrite (LED, state ? HIGH : LOW);

  // Dados são enviados em pacotes | #$:AABBC
  ADC_Buffer[0] = '#';
  ADC_Buffer[1] = '$';
  ADC_Buffer[2] = ':';

  // Leitura do canal analógico A0
  val_canal0 = analogRead(A0);     
  ADC_Buffer[3] = val_canal0 >> 8;
  ADC_Buffer[4] = val_canal0;

  // Leitura do canal analógico A1
  val_canal1 = analogRead(A1);     
  ADC_Buffer[5] = val_canal1 >> 8;
  ADC_Buffer[6] = val_canal1;

  // Cálculo do checksum para envio do pacote de dados
  unsigned char checksum = 0;
  for(unsigned char index = 0; index < 7; index++)
  {
    // Envia caracter a caracter do pacote
    Serial.write(ADC_Buffer[index]);
    checksum ^= ADC_Buffer[index];
  }

  Serial.write(checksum);
}

void setup() 
{
  // Inicialização da comunicação serial
  Serial.begin(115200);        

  // Definição dos pinos de I/O
  pinMode(LED, OUTPUT);
  pinMode(A0, INPUT);  
  pinMode(A1, INPUT);
  
  // Configuração do TIMER 1
  TCCR1A = 0;                         
  TCCR1B = bit(WGM12) | bit(CS10);  
  OCR1A  = 31976;                        // para: 500.01 Hz - 31976
                                         //       250.00 Hz - 15988
  TIMSK1 = bit (OCIE1A);             
}

void loop()
{ 
  
  
}
