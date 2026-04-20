const int REST = 0;

int melody[] = {
  REST, REST, REST, NOTE_DS4, 
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,   
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, 
  NOTE_E4, REST, REST, NOTE_DS4,
  
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_E5,
  NOTE_DS5,   
  NOTE_D5, REST, REST, NOTE_DS4, 
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,   
  
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, 
  NOTE_E4, REST,
  REST, NOTE_E5, NOTE_D5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_E4,
  NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4,   
  NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4
};

int noteDurations[] = {
  2, 4, 8, 8, 
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,   
  2, 16, 16, 16, 16, 
  2, 4, 8, 4,
  
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,
  1,   
  2, 4, 8, 8, 
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,   
  
  2, 16, 16, 16, 16, 
  4, 4,
  4, 8, 8, 8, 8, 8, 8,
  16, 8, 16, 8, 16, 8, 16, 8,   
  16, 16, 16, 16, 16, 2
};

int winMelody[] = {
  // --- Bugler's Dream Fanfare ---
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5, NOTE_G4, 
  NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6, NOTE_G5, NOTE_E5, NOTE_G5, 
  NOTE_C5, NOTE_G4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, 
  
  // --- Main Olympic Theme (The Heroic Jump) ---
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G5, REST,
  NOTE_E5, NOTE_F5, NOTE_G5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_G5,
  NOTE_F5, NOTE_E5, NOTE_D5, REST,
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_C6
};

int winNoteDurations[] = {
  // Fanfare durations
  8, 8, 8, 2, 4, 4, 4, 4, 
  8, 8, 8, 2, 4, 4, 2,
  4, 4, 8, 8, 8, 1,
  
  // Theme durations
  8, 8, 8, 2, 4,
  8, 8, 2, 4, 4, 4, 2,
  8, 8, 1, 4,
  8, 8, 8, 1
};