#define SEGMENT_A 2
#define SEGMENT_B 3
#define SEGMENT_C 4
#define SEGMENT_D 5
#define SEGMENT_E 6
#define SEGMENT_F 7
#define SEGMENT_G 8

#define CAPTEUR_POINT_MORT 10
#define CAPTEUR_PLUS 11
#define CAPTEUR_MOINS 12

int Rapport_Engage;

void Chiffre_1() {
  Serial.println(1);
  digitalWrite(SEGMENT_A, LOW);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, LOW);
  digitalWrite(SEGMENT_E, LOW);
  digitalWrite(SEGMENT_F, LOW);
  digitalWrite(SEGMENT_G, LOW);
}

void Chiffre_2() {
  Serial.println(2);
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, LOW);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, HIGH);
  digitalWrite(SEGMENT_F, LOW);
  digitalWrite(SEGMENT_G, HIGH);
}

void Chiffre_3() {
  Serial.println(3);
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, LOW);
  digitalWrite(SEGMENT_F, LOW);
  digitalWrite(SEGMENT_G, HIGH);
}

void Chiffre_4() {
  Serial.println(4);
  digitalWrite(SEGMENT_A, LOW);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, LOW);
  digitalWrite(SEGMENT_E, LOW);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, HIGH);
}

void Chiffre_5() {
  Serial.println(5);
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, LOW);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, LOW);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, HIGH);
}

void Chiffre_6() {
  Serial.println(6);
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, LOW);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, HIGH);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, HIGH);
}

void Lettre_N() {
  Serial.println('N');
  digitalWrite(SEGMENT_A, LOW);
  digitalWrite(SEGMENT_B, LOW);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, LOW);
  digitalWrite(SEGMENT_E, HIGH);
  digitalWrite(SEGMENT_F, LOW);
  digitalWrite(SEGMENT_G, HIGH);
}

void Erreur() {
  Serial.println('E');
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, LOW);
  digitalWrite(SEGMENT_C, LOW);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, HIGH);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, HIGH);
}

void(*tabRapport[])() = {Chiffre_1, Lettre_N, Chiffre_2, Chiffre_3, Chiffre_4, Chiffre_5, Chiffre_6};
byte nbFontionRapports = sizeof(tabRapport) / sizeof(tabRapport[0]);

void setup() {
  Serial.begin(9600);

  pinMode(SEGMENT_A, OUTPUT);
  pinMode(SEGMENT_B, OUTPUT);
  pinMode(SEGMENT_C, OUTPUT);
  pinMode(SEGMENT_D, OUTPUT);
  pinMode(SEGMENT_E, OUTPUT);
  pinMode(SEGMENT_F, OUTPUT);
  pinMode(SEGMENT_G, OUTPUT);

  pinMode(CAPTEUR_PLUS, INPUT_PULLUP);
  pinMode(CAPTEUR_MOINS, INPUT_PULLUP);
  pinMode(CAPTEUR_POINT_MORT, INPUT_PULLUP);

  Rapport_Engage = 1; // POINT MORT --> A améliorer ultérieurement pour voir si un rapport est engagé

  (*tabRapport[Rapport_Engage])();
}

void loop()
{
  int Ancien_Rapport_Engage = Rapport_Engage;

  if (Rapport_Engage == 0 && digitalRead(CAPTEUR_PLUS) == LOW && digitalRead(CAPTEUR_POINT_MORT) != LOW ) {
      Rapport_Engage = 2;
  }

  if (Rapport_Engage == 2 && digitalRead(CAPTEUR_MOINS) == LOW && digitalRead(CAPTEUR_POINT_MORT) != LOW ) {
      Rapport_Engage = 0;
  }

  if (digitalRead(CAPTEUR_PLUS) == LOW) {
    Rapport_Engage++;
  }

  if (digitalRead(CAPTEUR_MOINS) == LOW) {
    Rapport_Engage--;
  }

  if (digitalRead(CAPTEUR_POINT_MORT) == LOW) {
    Rapport_Engage = 0;
  }

  if (Ancien_Rapport_Engage != Rapport_Engage) { // on a changé de rapport
    if (Rapport_Engage < 0)  {
      Erreur();
      Rapport_Engage = 0;
    }
    else if (Rapport_Engage >= nbFontionRapports)  {
      Erreur();
      Rapport_Engage = nbFontionRapports - 1;
    }
    else {
      Serial.print(F("Changement de rapport = "));
      (*tabRapport[Rapport_Engage])();
    }
    delay(15); // anti rebond du pauvre :-)
  }
}