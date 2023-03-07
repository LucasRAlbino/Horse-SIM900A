program Horse_Sms;

{$APPTYPE CONSOLE}

{$R *.res}

uses Horse, System.SysUtils, Horse.Jhonson, System.JSON, CPort;

begin

  var
    dados: TJSONArray;

  THorse.Use(Jhonson);
  THorse.Get('/EnviaSms/:numero/:mensagem',
    procedure(Req: THorseRequest; Res: THorseResponse; Next: TProc)

    var
      NumeroTelefone: String;
      MensagemTexto: String;
      ComPort: TComPort;

    begin
      NumeroTelefone := Req.Params['numero'];
      MensagemTexto := Req.Params['mensagem'];

      ComPort := TComPort.Create(nil);

      try
        ComPort.Port := 'COM1'; // defina a porta serial do Arduino
        ComPort.BaudRate := br9600; // defina a taxa de transferência
        ComPort.Connected := True;

        if ComPort.Connected then
        begin
          Comport.WriteStr(NumeroTelefone + '$' + MensagemTexto);
          Res.Send('Número: ' + NumeroTelefone + '-- Mensagem: '+ MensagemTexto);
        end
        else
        begin
          Res.Send('Erro ao abrir a porta serial');
        end;
      finally
        ComPort.Free;
      end;
    end);

  THorse.Listen(9000, procedure(Horse: THorse)
  begin
    Writeln('Servidor ouvindo na porta: ' + Horse.Port.ToString);
  end);
end.

