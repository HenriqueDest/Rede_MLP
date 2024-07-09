//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>

#ifndef SerialComPortH
#define SerialComPortH

//---------------------------------------------------------------------------

class SerialCommPort
{
    // Links Úteis
    // https://control.com/forums/threads/serial-port-communication-c.11986/

    private:
        // Declaração da porta serial.
        HANDLE hComm;

        // Vetores Auxiliares
        unsigned char Buffer[4096];
        char Byte;

        // Variáveis de Controle da Porta Serial.
        DWORD dwToRead;
        DWORD dwRead;
        DWORD dwWritten;
        DWORD BaudRate;
        BYTE  Parity;
        BYTE  StopBits;
        BYTE  ByteSize;

    public:
        // Construtor da classe SerialPort.
        SerialCommPort();

        // Abertura e fechamento da porta serial.
        BOOL Open(AnsiString, AnsiString);
        void Close();

        // Escrita e leitura de dados da porta serial.
        BOOL WriteABuffer(char *, DWORD);
		std::vector <unsigned char> ReadBuffer();
        char * ReadABuffer();

        // Demais parâmetros de controle da porta serial.
		std::vector <AnsiString> List();
        unsigned int getBufferSize();
        unsigned char getBufferData();
};

//---------------------------------------------------------------------------

#endif
