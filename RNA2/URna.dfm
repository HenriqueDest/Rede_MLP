object FmRna: TFmRna
  Left = 0
  Top = 0
  Caption = 'Redes Neurais Artificiais'
  ClientHeight = 524
  ClientWidth = 1139
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 13
  object Label11: TLabel
    Left = 892
    Top = 39
    Width = 92
    Height = 13
    Caption = 'Casos de valida'#231#227'o'
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 1128
    Height = 509
    ActivePage = TabSheet4
    MultiLine = True
    TabOrder = 0
    OnChange = PageControl1Change
    object TabSheet1: TTabSheet
      Caption = 'Treinamento'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      object Label12: TLabel
        Left = 867
        Top = 66
        Width = 143
        Height = 16
        Caption = 'Erro medio quadratico'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label13: TLabel
        Left = 867
        Top = 88
        Width = 5
        Height = 16
        Caption = '-'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label14: TLabel
        Left = 867
        Top = 117
        Width = 228
        Height = 16
        Caption = 'Erro medio quadratico de validacao'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label15: TLabel
        Left = 867
        Top = 139
        Width = 5
        Height = 16
        Caption = '-'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label16: TLabel
        Left = 911
        Top = 88
        Width = 12
        Height = 16
        Caption = '%'
      end
      object Label17: TLabel
        Left = 911
        Top = 139
        Width = 12
        Height = 16
        Caption = '%'
      end
      object Label18: TLabel
        Left = 867
        Top = 26
        Width = 38
        Height = 16
        Caption = #201'poca'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label19: TLabel
        Left = 923
        Top = 26
        Width = 4
        Height = 16
      end
      object TLabel
        Left = 867
        Top = 357
        Width = 101
        Height = 16
        Caption = 'Sele'#231#227'o da '#233'poca'
      end
      object Label20: TLabel
        Left = 867
        Top = 173
        Width = 184
        Height = 16
        Caption = #201'poca de parada antecipada'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label21: TLabel
        Left = 867
        Top = 203
        Width = 5
        Height = 16
        Caption = '-'
      end
      object Label22: TLabel
        Left = 867
        Top = 242
        Width = 113
        Height = 16
        Caption = 'Eficiencia da rede'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label23: TLabel
        Left = 867
        Top = 264
        Width = 5
        Height = 16
        Caption = '-'
      end
      object Label24: TLabel
        Left = 911
        Top = 264
        Width = 12
        Height = 16
        Caption = '%'
      end
      object Chart1: TChart
        Left = 3
        Top = 3
        Width = 835
        Height = 475
        Legend.Visible = False
        Title.Font.Color = clNavy
        Title.Text.Strings = (
          'Curvas de Treinamento da Rede Neural')
        BottomAxis.MinimumOffset = 3
        BottomAxis.Title.Caption = #201'pocas de Treinamento'
        LeftAxis.MinimumOffset = 5
        LeftAxis.Title.Caption = 'Erro M'#233'dio Quadr'#225'tico (EMQ)'
        View3D = False
        TabOrder = 0
        DefaultCanvas = 'TGDIPlusCanvas'
        ColorPaletteIndex = 13
        object Series1: TFastLineSeries
          HoverElement = []
          SeriesColor = clRed
          ValueFormat = '#.##0,00###'
          LinePen.Color = clRed
          LinePen.Width = 2
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series6: TFastLineSeries
          HoverElement = []
          SeriesColor = 16744448
          Title = 'Series2'
          ValueFormat = '#.##0,00###'
          LinePen.Color = 16744448
          LinePen.Width = 2
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series5: TFastLineSeries
          HoverElement = []
          SeriesColor = 8684676
          Title = 'verticalLine'
          ValueFormat = '#.##0,00###'
          LinePen.Color = 8684676
          LinePen.Style = psDash
          LinePen.Width = 3
          LinePen.EndStyle = esRound
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series4: TFastLineSeries
          HoverElement = []
          SeriesColor = 10523950
          Title = 'passarEpocas'
          ValueFormat = '#.##0,00###'
          LinePen.Color = 10523950
          LinePen.Style = psDash
          LinePen.Width = 2
          LinePen.EndStyle = esRound
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
      object Button1: TButton
        Left = 844
        Top = 433
        Width = 121
        Height = 45
        Caption = 'Treinamento'
        TabOrder = 1
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 995
        Top = 433
        Width = 122
        Height = 45
        Caption = 'Cancelar'
        TabOrder = 2
        OnClick = Button2Click
      end
      object UpDown1: TUpDown
        Left = 953
        Top = 376
        Width = 21
        Height = 24
        Associate = Edit
        TabOrder = 3
        Thousands = False
      end
      object Edit: TEdit
        Left = 867
        Top = 376
        Width = 86
        Height = 24
        NumbersOnly = True
        TabOrder = 4
        Text = '0'
        OnChange = EditChange
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Padr'#245'es de Treinamento'
      ImageIndex = 1
      object Shape16: TShape
        Left = 888
        Top = 396
        Width = 25
        Height = 33
        Shape = stCircle
      end
      object Shape17: TShape
        Left = 951
        Top = 396
        Width = 25
        Height = 33
        Shape = stCircle
      end
      object Label2: TLabel
        Left = 888
        Top = 371
        Width = 122
        Height = 19
        Caption = 'Camada de Sa'#237'da'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 3
        Top = 7
        Width = 105
        Height = 13
        Caption = 'Casos de treinamento'
      end
      object Label5: TLabel
        Left = 3
        Top = 233
        Width = 92
        Height = 13
        Caption = 'Casos de valida'#231#227'o'
      end
      object Label6: TLabel
        Left = 992
        Top = 290
        Width = 88
        Height = 19
        Caption = 'Neur'#244'nio 02'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel
        Left = 888
        Top = 290
        Width = 88
        Height = 19
        Caption = 'Neur'#244'nio 01'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel
        Left = 888
        Top = 322
        Width = 9
        Height = 19
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label9: TLabel
        Left = 992
        Top = 322
        Width = 9
        Height = 19
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label10: TLabel
        Left = 124
        Top = 452
        Width = 23
        Height = 24
        Caption = #55356#56727
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object ListBox1: TListBox
        Left = 3
        Top = 26
        Width = 121
        Height = 189
        ItemHeight = 13
        TabOrder = 0
        OnClick = ListBox1Click
      end
      object Chart2: TChart
        Left = 153
        Top = 3
        Width = 708
        Height = 475
        Legend.Visible = False
        Title.Text.Strings = (
          'Sinal selecionado')
        BottomAxis.Automatic = False
        BottomAxis.AutomaticMaximum = False
        BottomAxis.Maximum = 251.000000000000000000
        BottomAxis.Title.Caption = 'Amostras'
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMaximum = False
        LeftAxis.AutomaticMinimum = False
        LeftAxis.Maximum = 1.000000000000000000
        LeftAxis.MaximumOffset = 5
        LeftAxis.MinimumOffset = 5
        LeftAxis.Title.Caption = 'Amplitude'
        View3D = False
        TabOrder = 1
        DefaultCanvas = 'TGDIPlusCanvas'
        ColorPaletteIndex = 13
        object Series2: TFastLineSeries
          HoverElement = []
          SeriesColor = clRed
          LinePen.Color = clRed
          LinePen.Width = 2
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series3: TFastLineSeries
          HoverElement = []
          SeriesColor = clBlue
          LinePen.Color = clBlue
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
      object ListBox2: TListBox
        Left = 3
        Top = 252
        Width = 121
        Height = 194
        ItemHeight = 13
        TabOrder = 2
        OnClick = ListBox2Click
      end
      object Button3: TButton
        Left = 3
        Top = 452
        Width = 121
        Height = 25
        Caption = 'Classificar valida'#231#227'o'
        TabOrder = 3
        OnClick = Button3Click
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Tempo real'
      ImageIndex = 2
      object Label1: TLabel
        Left = 16
        Top = 2
        Width = 26
        Height = 13
        Caption = 'Porta'
      end
      object Label3: TLabel
        Left = 16
        Top = 50
        Width = 80
        Height = 13
        Caption = 'Bits por segundo'
      end
      object Label25: TLabel
        Left = 16
        Top = 306
        Width = 88
        Height = 19
        Caption = 'Neur'#244'nio 01'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label26: TLabel
        Left = 16
        Top = 338
        Width = 9
        Height = 19
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label27: TLabel
        Left = 120
        Top = 338
        Width = 9
        Height = 19
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label28: TLabel
        Left = 120
        Top = 306
        Width = 88
        Height = 19
        Caption = 'Neur'#244'nio 02'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label29: TLabel
        Left = 16
        Top = 402
        Width = 6
        Height = 19
        Caption = '-'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object CbSerialPort1: TComboBox
        Left = 16
        Top = 21
        Width = 169
        Height = 21
        Color = clMoneyGreen
        TabOrder = 0
      end
      object BtOpenPort: TButton
        Left = 15
        Top = 105
        Width = 145
        Height = 32
        Caption = 'Abrir Porta'
        TabOrder = 2
        OnClick = BtOpenPortClick
      end
      object CbBaudRate1: TComboBox
        Left = 16
        Top = 69
        Width = 169
        Height = 21
        Color = clMoneyGreen
        TabOrder = 3
        Text = '115200'
        Items.Strings = (
          '1200'
          '2400'
          '4800'
          '9600'
          '19200'
          '38400'
          '57600'
          '115200'
          '128000'
          '256000'
          '576000'
          '1152000')
      end
      object BtClosePort: TButton
        Left = 16
        Top = 143
        Width = 145
        Height = 34
        Caption = 'Fechar Porta'
        TabOrder = 1
        OnClick = BtClosePortClick
      end
      object Chart3: TChart
        Left = 346
        Top = 3
        Width = 708
        Height = 475
        Legend.Visible = False
        Title.Text.Strings = (
          'Dados Coletados Normalizados')
        BottomAxis.Automatic = False
        BottomAxis.AutomaticMaximum = False
        BottomAxis.Maximum = 500.000000000000000000
        BottomAxis.Title.Caption = 'Amostras'
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMaximum = False
        LeftAxis.AutomaticMinimum = False
        LeftAxis.Maximum = 1.000000000000000000
        LeftAxis.MaximumOffset = 5
        LeftAxis.MinimumOffset = 5
        LeftAxis.Title.Caption = 'Amplitude'
        View3D = False
        TabOrder = 4
        DefaultCanvas = 'TGDIPlusCanvas'
        ColorPaletteIndex = 13
        object FastLineSeries1: TFastLineSeries
          HoverElement = []
          SeriesColor = clRed
          LinePen.Color = clRed
          LinePen.Width = 2
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
      object Memo1: TMemo
        Left = 15
        Top = 200
        Width = 185
        Height = 89
        TabOrder = 5
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Gr'#225'fico de Pontos'
      ImageIndex = 3
      object Label30: TLabel
        Left = 875
        Top = 34
        Width = 38
        Height = 16
        Caption = #201'poca'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label31: TLabel
        Left = 875
        Top = 74
        Width = 143
        Height = 16
        Caption = 'Erro medio quadratico'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label32: TLabel
        Left = 875
        Top = 96
        Width = 5
        Height = 16
        Caption = '-'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label33: TLabel
        Left = 919
        Top = 96
        Width = 11
        Height = 13
        Caption = '%'
      end
      object Label34: TLabel
        Left = 875
        Top = 125
        Width = 228
        Height = 16
        Caption = 'Erro medio quadratico de validacao'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label35: TLabel
        Left = 875
        Top = 147
        Width = 5
        Height = 16
        Caption = '-'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label36: TLabel
        Left = 919
        Top = 147
        Width = 11
        Height = 13
        Caption = '%'
      end
      object Label37: TLabel
        Left = 875
        Top = 181
        Width = 184
        Height = 16
        Caption = #201'poca de parada antecipada'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label38: TLabel
        Left = 875
        Top = 211
        Width = 4
        Height = 13
        Caption = '-'
      end
      object Label39: TLabel
        Left = 875
        Top = 250
        Width = 113
        Height = 16
        Caption = 'Eficiencia da rede'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label40: TLabel
        Left = 919
        Top = 272
        Width = 11
        Height = 13
        Caption = '%'
      end
      object Label41: TLabel
        Left = 875
        Top = 272
        Width = 4
        Height = 13
        Caption = '-'
      end
      object TLabel
        Left = 875
        Top = 365
        Width = 84
        Height = 13
        Caption = 'Sele'#231#227'o da '#233'poca'
      end
      object Label42: TLabel
        Left = 934
        Top = 34
        Width = 3
        Height = 13
      end
      object Chart4: TChart
        Left = 32
        Top = 39
        Width = 785
        Height = 406
        Legend.Alignment = laTop
        Legend.HorizJustify = ljNo
        Legend.TopPos = 38
        Title.Text.Strings = (
          'Classificador de Sinais')
        BottomAxis.Automatic = False
        BottomAxis.AutomaticMaximum = False
        BottomAxis.Maximum = 1.000000000000000000
        BottomAxis.Title.Caption = 'Sa'#237'da Neur'#244'nio 1'
        Chart3DPercent = 3
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMaximum = False
        LeftAxis.AutomaticMinimum = False
        LeftAxis.Maximum = 1.000000000000000000
        LeftAxis.Title.Caption = 'Sa'#237'da Neur'#244'nio 2'
        TabOrder = 0
        DefaultCanvas = 'TGDIPlusCanvas'
        ColorPaletteIndex = 13
        object Series7: TPointSeries
          HoverElement = [heCurrent]
          Title = 'Beatriz'
          ClickableLine = False
          Pointer.HorizSize = 7
          Pointer.InflateMargins = True
          Pointer.Style = psCircle
          Pointer.VertSize = 7
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series8: TPointSeries
          HoverElement = [heCurrent]
          Title = 'Erick'
          ClickableLine = False
          Pointer.Brush.Color = 65408
          Pointer.HorizSize = 6
          Pointer.InflateMargins = True
          Pointer.Style = psDownTriangle
          Pointer.VertSize = 6
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series9: TPointSeries
          HoverElement = [heCurrent]
          Title = 'Henrique'
          ClickableLine = False
          Pointer.HorizSize = 6
          Pointer.InflateMargins = True
          Pointer.Style = psTriangle
          Pointer.VertSize = 6
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series10: TPointSeries
          HoverElement = [heCurrent]
          Title = 'Jo'#227'o'
          ClickableLine = False
          Pointer.Brush.Color = clYellow
          Pointer.HorizSize = 6
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.VertSize = 6
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series11: TFastLineSeries
          HoverElement = []
          Legend.Visible = False
          SeriesColor = 14886417
          ShowInLegend = False
          Title = 'EixoX'
          ValueFormat = '#.##0,###'
          LinePen.Color = 14886417
          LinePen.Style = psDash
          LinePen.Width = 2
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series12: TFastLineSeries
          HoverElement = []
          Legend.Visible = False
          SeriesColor = 14886417
          ShowInLegend = False
          Title = 'EixoY'
          LinePen.Color = 14886417
          LinePen.Style = psDash
          LinePen.Width = 2
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
      object UpDown2: TUpDown
        Left = 969
        Top = 392
        Width = 20
        Height = 21
        Associate = Edit2
        TabOrder = 1
        Thousands = False
      end
      object Edit2: TEdit
        Left = 883
        Top = 392
        Width = 86
        Height = 21
        NumbersOnly = True
        TabOrder = 2
        Text = '0'
        OnChange = Edit2Change
      end
    end
  end
end
