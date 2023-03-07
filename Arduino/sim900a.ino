#include <SoftwareSerial.h>

//Programa para comunicação do Arduino com o SIM900A

#define RX2 10
#define TX2 9

SoftwareSerial mySerial(RX2,TX2);

String Mensagem_Serial = "", Numero = "", Mensagem = "";
int posicao_sifrao, L_String = 0;
char C, *ptr, teste[50];
String Comando_Numero = "AT+CMGS=\"+5500000000000\"";

void Resposta_Serial(void);
String Numero_Formatado(String);

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);

  delay(5000);
  Serial.println("Inicializando...");

  Serial.println("Digite o numero e a mensagem separado por $\n");
}

void loop() {

  if (Serial.available()) {
    Mensagem_Serial = Serial.readString();
    ptr = &Mensagem_Serial[0];
  }

  if (Mensagem_Serial != "") {

    L_String = Mensagem_Serial.length();

    for (int i = 0; i < L_String; i++) {

      C = *(ptr + i);

      if (C == '$')
        posicao_sifrao = i;

      if ((i >= 0) && (i < 11)) {
        Comando_Numero[i + 12] = C;
        Numero += C;
      }

      if ((i > 11) && (i < L_String))
        Mensagem += C;
    }

    Serial.println("Numero: " + Numero);
    Serial.println("Mensagem: " + Mensagem);

    mySerial.println("AT");
    Resposta_Serial();

    mySerial.println("AT+CMGF=1");
    Resposta_Serial();

    mySerial.println(Comando_Numero);
    Resposta_Serial();

    mySerial.print(Mensagem);
    Resposta_Serial();

    mySerial.write(26);

    Serial.println();
    Serial.println("\nDigite o numero e a mensagem separado por $\n");

    Numero = "";
    Mensagem = "";
    Mensagem_Serial = "";
    Comando_Numero = "AT+CMGS=\"+5500000000000\"";
  }
}

void Resposta_Serial(void) {

  delay(1000);

  while (Serial.available()) {
    mySerial.write(Serial.read());
  }

  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
