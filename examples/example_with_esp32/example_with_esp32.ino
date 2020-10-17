#include "Melody.h"

#define SERIAL_BAUDRATE 115200
#define BROCHE_TONE 12
#define CHANNEL 5

//Wolfgang Amadeus Mozart, Eine kleine Nachtmusik (KV 525),
char mozartScore[] = "  g<r-d- |g< r-d-(g<dg<b)-d<*r | c*<r-a-c*<r-a- |(c*<af#<a)-d<r | (gr)- g. (bag | (gag)/3:1 f#)- f#. (ac*f# | ag)- g.  (bag | (gag)/3:1 f#)- f#. (ac*f#)- | (grgr)-- (gf#ef#)-- (grgr)-- (baga)-- | (brbr)-- (d*c*bc*)-- d* r | (de)+  | (d-c.)-c (c-b_.)-  b_ | (( b-a.)- a (gf#ef# | grarbr)- r )_ ";
Melody mozartMelody(mozartScore, 140);

//Frere Jacques
Melody frereJacques("(cdec)x2   (efgr)x2   ((gagf)-ec)x2     (c g_ c+)x2"); //Frère Jacques

//Scale with ascending loudness
Melody gammeLouder("c>>> d>> e>f g< a<< b<<< c*<<<<", 240);

//Au Clair de la Lune (Twinkle Twinkle little star)
Melody auClairDeLaLune(" (cccde+dr  ceddc+.r cccde+dr ceddc+.r dddd a_+ a_ r d c (b a g+.r)_ cccde+dr ceddc+.r )*");

// John Sebastian Bach, The Musical Offering Theme
Melody musicalOffering(" (((ce,ga,b_)+rg(f#fee,.)+  dd,c (ba-g-)_ c f e,+d+c+))+", 240);

void setup()
{
  Serial.begin(SERIAL_BAUDRATE);
  ledcSetup(CHANNEL, 5000, 8);
  ledcAttachPin(BROCHE_TONE, CHANNEL);
  ledcWrite(CHANNEL, 0); //duty Cycle de 0
}

void loop()
{
  play(mozartMelody);

  play(frereJacques);

  play(gammeLouder);

  play(auClairDeLaLune);

  play(musicalOffering);
}


void play(Melody melody)
{

  Serial.print("Melody length : ");
  Serial.println(melody.length());

  melody.restart();

  while (melody.hasNext())
  {
    melody.next();
    printInfo(melody);

    unsigned int frequency = melody.getFrequency();
    unsigned long duration = melody.getDuration();
    unsigned int loudness = melody.getLoudness();

    if (frequency > 0)
    {
      tone( frequency, loudness);
    }
    else
    {
      noTone();
    }
    delay(duration);
  }

  noTone();
  delay(1000);
}

void tone(int frequency, int loudness) {
  ledcWriteTone(CHANNEL, frequency);
  ledcWrite(CHANNEL, map(loudness, -4, 4, 0, 16 )) ;
}
void noTone() {
  ledcWrite(CHANNEL, 0) ;
}
void printInfo(Melody melody)
{
  Serial.print(melody.index() + 1);
  Serial.print("/");
  Serial.print(melody.length());
  Serial.print(" : ");
  Serial.print(melody.getFrequency());
  Serial.print("Hz, ");
  Serial.print(melody.getDuration());
  Serial.print(" ms, ");
  Serial.print(melody.getLoudness());
  Serial.print(" loud.\n");
}