/**
   Test d'un capteur de couleur par conversion lumière / fréquence
   Taos TCS230
*/
// les quatre entrées TOR de programmation du capteur
#define S0  31
#define S1  5
#define S2  6
#define S3  33
// la sortie en fréquence
#define OUT  7


//Tableau pour moyenner la couleur en RVB
float sensorValue = 0;
int NB_SAMPLE = 10;
float tab[10]; //remplir tableau avec 10 valeurs du capteur qui se suivent


float moy;


void setup()
{
  Serial.begin(9600);

  // deux entrées pour réduire si besoin la fréquence en sortie
  // Echelle  | S0 | S1 |
  // 0=éteint | L  | L  |
  // 2%       | L  | H  |
  // 20%      | H  | L  |
  // 100%     | H  | H  |
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);

  // deux entrées pour choisir la couleur du filtre
  // Filtre | S2 | S3 |
  // rouge  | L  | L  |
  // bleu   | L  | H  |
  // aucun  | H  | L  |
  // vert   | H  | H  |

  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);


  // S0 bas et S1 haut = 2% de la fréquence
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);

  // S2 haut et S3 bas : sans filtre
  /*digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);*/

}
void loop() {
long somme = 0;

  Serial.println("Rouge : ");
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  //Serial.println(pulseIn(OUT,HIGH));

  for (int i = 0 ; i < NB_SAMPLE ; i++)
  {
    sensorValue = pulseIn(OUT, HIGH);
    tab[i] = sensorValue; //remplir tableau avec 10 valeurs du capteur qui se suivent
    //Serial.println(sensorValue);
    somme += tab[i] ; //somme des valeurs du tableau
    delay(30);
  }
  moy = somme / 10 ; //valeur moyenne
  Serial.print("Rmoy = "); //affichage moy
  Serial.println(moy);


  // pause de 500 ms
  delay(500);

  Serial.println("Vert  : ");
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  //Serial.println(pulseIn(OUT,HIGH));

  for (int j = 0 ; j < NB_SAMPLE ; j++)
  {
    sensorValue = pulseIn(OUT, HIGH);
    tab[j] = sensorValue; //remplir tableau avec 10 valeurs du capteur qui se suivent
    //Serial.println(sensorValue);
    somme += tab[j] ; //somme des valeurs du tableau
    delay(30);
  }
  moy = somme / 10 ; //valeur moyenne
  Serial.print("Vmoy = "); //affichage moy
  Serial.println(moy);


  // pause de 500 ms
  delay(500);

  Serial.println("Bleu  : ");
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  //Serial.println(pulseIn(OUT,HIGH));

  for (int k = 0 ; k < NB_SAMPLE ; k++)
  {
    sensorValue = pulseIn(OUT, HIGH);
    tab[k] = sensorValue; //remplir tableau avec 10 valeurs du capteur qui se suivent
    //Serial.println(sensorValue);
    somme += tab[k] ; //somme des valeurs du tableau
    delay(30);
  }
  moy = somme / 10 ; //valeur moyenne
  Serial.print("Bmoy = "); //affichage moy
  Serial.println(moy);

  // pause de 500 ms
  delay(500);  

  Serial.println("=================================================");
  delay(100);
}
