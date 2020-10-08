const int SPEAKER_PIN = 12;

void toneScale(int scale, int len) {
  int herz[14] = {
    262, 294, 330, 349, 392, 440, 494,
    523, 587, 659, 698, 784, 880, 988,
  };
  tone(SPEAKER_PIN, herz[scale-1]);
  delay(len);
  noTone(SPEAKER_PIN);
}

void setup()
{
    toneScale(5, 300);
    toneScale(5, 100);
    toneScale(6, 400);
    toneScale(5, 400);
    toneScale(8, 400);
    toneScale(7, 600);
    delay(200);
    
    toneScale(5, 300);
    toneScale(5, 100);
    toneScale(6, 400);
    toneScale(5, 400);
    toneScale(9, 400);
    toneScale(8, 600);
    delay(200);

    toneScale(5, 300);
    toneScale(5, 100);
    toneScale(12, 400);
    toneScale(10, 400);
    toneScale(8, 300);
    toneScale(8, 100);
    toneScale(7, 400);
    toneScale(6, 400);

    toneScale(11, 300);
    toneScale(11, 100);
    toneScale(10, 400);
    toneScale(8, 400);
    toneScale(9, 400);
    toneScale(8, 600);
    delay(200);
}
