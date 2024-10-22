//---------------------------------------------------------------------------

#ifndef URnaH
#define URnaH

//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <vcl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused
//---------------------------------------------------------------------------

class TFmRna : public TForm
{
	__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TChart *Chart1;
	TFastLineSeries *Series1;
	TButton *Button1;
	TButton *Button2;
	TTabSheet *TabSheet2;
	TShape *Shape16;
	TShape *Shape17;
	TLabel *Label2;
	TListBox *ListBox1;
	TChart *Chart2;
	TFastLineSeries *Series2;
	TFastLineSeries *Series3;
	TListBox *ListBox2;
	TButton *Button3;
	TTabSheet *TabSheet3;
	TComboBox *CbSerialPort1;
	TLabel *Label1;
	TButton *BtClosePort;
	TButton *BtOpenPort;
	TComboBox *CbBaudRate1;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TChart *Chart3;
	TFastLineSeries *FastLineSeries1;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TUpDown *UpDown1;
	TEdit *Edit;
	TLabel *Label20;
	TLabel *Label21;
	TFastLineSeries *Series5;
	TFastLineSeries *Series6;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TFastLineSeries *Series4;
	TTabSheet *TabSheet4;
	TChart *Chart4;
	TPointSeries *Series7;
	TPointSeries *Series8;
	TPointSeries *Series9;
	TPointSeries *Series10;
	TFastLineSeries *Series11;
	TFastLineSeries *Series12;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TMemo *Memo1;
	TLabel *Label30;
	TLabel *Label31;
	TLabel *Label32;
	TLabel *Label33;
	TLabel *Label34;
	TLabel *Label35;
	TLabel *Label36;
	TLabel *Label37;
	TLabel *Label38;
	TLabel *Label39;
	TLabel *Label40;
	TLabel *Label41;
	TUpDown *UpDown2;
	TEdit *Edit2;
	TLabel *Label42;
		void __fastcall Button1Click(TObject *Sender);
		void __fastcall Button2Click(TObject *Sender);
        void __fastcall AtualizaGrafico();
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall ListBox2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall AdicionarLinhaVertical(int xValue);
	void __fastcall EditChange(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall BtOpenPortClick(TObject *Sender);
	void __fastcall BtClosePortClick(TObject *Sender);
	void __fastcall Edit2Change(TObject *Sender);





	private:	// User declarations
		HANDLE hSerial;
		bool isReading;
		void __fastcall ListComPorts();
		void __fastcall ConfigureSerialPort();
		void __fastcall ReadSerialData();
		void __fastcall StopSerialReading();
		void __fastcall OnSerialPortChange(TObject *Sender);
		void __fastcall BtRefreshPortsClick(TObject *Sender);

	public:		// User declarations
		__fastcall TFmRna(TComponent* Owner);

};

//---------------------------------------------------------------------------

class Thread : public TThread
{
	private:
	protected:
		void __fastcall Execute();

	public:
		__fastcall Thread(bool CreateSuspended);
};

//---------------------------------------------------------------------------
extern PACKAGE TFmRna *FmRna;

//---------------------------------------------------------------------------
#endif

