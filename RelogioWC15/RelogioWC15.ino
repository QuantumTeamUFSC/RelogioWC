
// CONNECTIONS:
// DS1302 CLK/SCLK --> 4
// DS1302 DAT/IO --> 3
// DS1302 RST/CE --> 2
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND

#include <ThreeWire.h>
#include <RtcDS1302.h>

#define b1 A2
#define b2 A3
#define b3 A5
#define b4 A4
#define b5 13
#define b6 5
#define b7 6
#define a1 7
#define a2 8
#define a3 9
#define a4 10
#define a5 11
#define a6 12
#define a7 A0

#define day 86400000

int contagem = 0;

const int digitos[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 1, 1, 0},
  {1, 0, 1, 1, 0, 1, 1},
  {1, 0, 0, 1, 1, 1, 1},
  {0, 1, 0, 0, 1, 1, 1},
  {1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 1, 1, 0, 1},
  {1, 0, 0, 0, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 0, 1, 1, 1, 1},
};


ThreeWire myWire(3, 4, 2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);



void setup ()
{
  Serial.begin(115200);

  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  if (Rtc.GetIsWriteProtected())
  {
    Serial.println("RTC was write protected, enabling writing now");
    Rtc.SetIsWriteProtected(false);
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
    Serial.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled)
  {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }
}

int diasNoMes(int mes, int ano) {
  if (mes == 2) {
    // Verifica ano bissexto
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
      return 29;
    } else {
      return 28;
    }
  } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
    return 30;
  } else {
    return 31;
  }
}

void cont() {
  contagem = 0;

  RtcDateTime now = Rtc.GetDateTime();
  RtcDateTime destino = RtcDateTime(2025, 6, 19, 0, 0, 0);

  int ano = now.Year();
  int mes = now.Month();
  int dia = now.Day();

  while (ano < destino.Year() || (ano == destino.Year() && mes < destino.Month())) {
    if (ano == now.Year() && mes == now.Month()) {
      // mês atual: conta só os dias restantes
      contagem += diasNoMes(mes, ano) - dia;
    } else {
      contagem += diasNoMes(mes, ano);
    }

    mes++;
    if (mes > 12) {
      mes = 1;
      ano++;
    }
    if(contagem < 0) {
      contagem = 0;
    }
  }

  // Soma os dias do mês final até o destino
  contagem += destino.Day();

  Serial.print("Dias até ");
  Serial.print(destino.Year());
  Serial.print("-");
  Serial.print(destino.Month());
  Serial.print("-");
  Serial.print(destino.Day());
  Serial.print(": ");
  Serial.println(contagem);
  
  disp(contagem);
  delay(5000);
}

void loop ()
{ 
  cont();

  Serial.println();

  animacao();
  delay(10000);
  
  animacao2();

}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
  char datestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );
  Serial.print(datestring);
}
void disp(int a) {

  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(b3, LOW);
  digitalWrite(b4, LOW);
  digitalWrite(b5, LOW);
  digitalWrite(b6, LOW);
  digitalWrite(b7, LOW);
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(a3, LOW);
  digitalWrite(a4, LOW);
  digitalWrite(a5, LOW);
  digitalWrite(a6, LOW);
  digitalWrite(a7, LOW);

  digitalWrite(b1, digitos[a % 10][0]);
  digitalWrite(b2, digitos[a % 10][1]);
  digitalWrite(b3, digitos[a % 10][2]);
  digitalWrite(b4, digitos[a % 10][3]);
  digitalWrite(b5, digitos[a % 10][4]);
  digitalWrite(b6, digitos[a % 10][5]);
  digitalWrite(b7, digitos[a % 10][6]);

  digitalWrite(a1, digitos[a / 10][0]);
  digitalWrite(a2, digitos[a / 10][1]);
  digitalWrite(a3, digitos[a / 10][2]);
  digitalWrite(a4, digitos[a / 10][3]);
  digitalWrite(a5, digitos[a / 10][4]);
  digitalWrite(a6, digitos[a / 10][5]);
  digitalWrite(a7, digitos[a / 10][6]);
}
void animacao() {


  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(b3, LOW);
  digitalWrite(b4, LOW);
  digitalWrite(b5, LOW);
  digitalWrite(b6, LOW);
  digitalWrite(b7, LOW);
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(a3, LOW);
  digitalWrite(a4, LOW);
  digitalWrite(a5, LOW);
  digitalWrite(a6, LOW);
  digitalWrite(a7, LOW);
  int aux = 200;
  digitalWrite(a3, HIGH);
  delay(aux);
  digitalWrite(a3, LOW);

  digitalWrite(a2, HIGH);
  delay(aux);
  digitalWrite(a2, LOW);

  digitalWrite(a1, HIGH);
  delay(aux);
  digitalWrite(a1, LOW);

  digitalWrite(a6, HIGH);
  delay(aux);
  digitalWrite(a6, LOW);

  digitalWrite(a5, HIGH);
  delay(aux);
  digitalWrite(a5, LOW);



  digitalWrite(b3, HIGH);
  delay(aux);
  digitalWrite(b3, LOW);

  digitalWrite(b2, HIGH);
  delay(aux);
  digitalWrite(b2, LOW);

  digitalWrite(b1, HIGH);
  delay(aux);
  digitalWrite(b1, LOW);

  digitalWrite(b6, HIGH);
  delay(aux);
  digitalWrite(b6, LOW);

  digitalWrite(b5, HIGH);
  delay(aux);
  digitalWrite(b5, LOW);

}

void animacao2() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(b1, LOW);
    digitalWrite(b2, LOW);
    digitalWrite(b3, LOW);
    digitalWrite(b4, LOW);
    digitalWrite(b5, LOW);
    digitalWrite(b6, LOW);
    digitalWrite(b7, LOW);

    digitalWrite(a1, LOW);
    digitalWrite(a2, LOW);
    digitalWrite(a3, LOW);
    digitalWrite(a4, LOW);
    digitalWrite(a5, LOW);
    digitalWrite(a6, LOW);
    digitalWrite(a7, LOW);

    digitalWrite(a1, HIGH);
    digitalWrite(a2, HIGH);
    digitalWrite(a3, HIGH);
    digitalWrite(a4, HIGH);
    digitalWrite(a5, HIGH);
    digitalWrite(a6, HIGH);
    digitalWrite(a7, HIGH);

    digitalWrite(b1, HIGH);
    digitalWrite(b2, HIGH);
    digitalWrite(b3, HIGH);
    digitalWrite(b4, HIGH);
    digitalWrite(b5, HIGH);
    digitalWrite(b6, HIGH);
    digitalWrite(b7, HIGH);
    delay(200);
    digitalWrite(b1, LOW);
    digitalWrite(b2, LOW);
    digitalWrite(b3, LOW);
    digitalWrite(b4, LOW);
    digitalWrite(b5, LOW);
    digitalWrite(b6, LOW);
    digitalWrite(b7, LOW);

    digitalWrite(a1, LOW);
    digitalWrite(a2, LOW);
    digitalWrite(a3, LOW);
    digitalWrite(a4, LOW);
    digitalWrite(a5, LOW);
    digitalWrite(a6, LOW);
    digitalWrite(a7, LOW);
    delay(50);
  }

}
