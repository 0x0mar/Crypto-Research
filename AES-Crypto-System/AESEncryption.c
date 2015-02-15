#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>

#define BUFFER_SIZE 16

uint8_t sbox[256]= {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67,
		    0x2b, 0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59,
		    0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7,
		    0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1,
		    0x71, 0xd8, 0x31, 0x15, 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05,
		    0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83,
		    0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29,
		    0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
		    0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, 0xd0, 0xef, 0xaa,
		    0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c,
		    0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc,
		    0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec,
		    0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19,
		    0x73, 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee,
		    0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49,
		    0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
		    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4,
		    0xea, 0x65, 0x7a, 0xae, 0x08, 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6,
		    0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, 0x70,
		    0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9,
		    0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e,
		    0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, 0x8c, 0xa1,
		    0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0,
		    0x54, 0xbb, 0x16};

uint8_t iSbox[256] ={0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
		     0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
		     0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
		     0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
		     0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
		     0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
		     0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
		     0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
		     0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
		     0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
		     0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
		     0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
		     0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
		     0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
		     0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
		     0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
		     0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
		     0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
		     0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
		     0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
		     0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
		     0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
		     0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
		     0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
		     0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
		     0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
		     0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
		     0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
		     0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
		     0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
		     0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
		     0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};

uint8_t Rcon[26] = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
		    0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
		    0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3};


void encryptPlaintext(FILE* inFile, FILE* outFile, const uint8_t key[],
		      const int Nb, const int Nk, const int Nr);
void readKey(FILE* keyFile, uint8_t key[], const int Nk);
void encryptState(uint8_t state[4][4], const uint8_t key[], const int Nb,
		  const int Nk, const int Nr);

void expandKey  (uint8_t roundKeys[][4][4], const uint8_t key[]);
void subBytes   (uint8_t state[], const int Nb, const int Nk, const int Nr);
void shiftRows  (uint8_t state[], const int Nb, const int Nk, const int Nr);
void mixColumns (uint8_t state[], const int Nb, const int Nk, const int Nr);
void addRoundKey(uint8_t state[], const uint8_t roundKeys[], const int round,
		 const int Nb, const int Nk, const int Nr);

void rotateWord(uint8_t word[], const int pos, const int Nb);
uint8_t gMult(uint8_t a, uint8_t b);


int main(int argc, char** argv) {
  // verify for correct input 
  if(argc < 4) {
    fprintf(stderr, "./AESEncryption 'inFileName' 'keyFile' 'outfileName' Nb" \
	    " Nk Nr --- where Nb Nk Nr are optional with default 4 4 10");
  }
  if(argc > 4 && argc < 7) {
    fprintf(stderr, " you must specify all values of Nb, Nk and Nr or none" \
	    "; cannot specify only 1 or 2 of them");
  }
  
  const char* inFileName  = argv[1];
  const char* keyFile     = argv[2];
  const char* outFileName = argv[3];
  
  int NbRead = 4, NkRead = 4, NrRead = 10;  
  if(argc == 7) {
    NbRead = atoi(argv[4]);
    NkRead = atoi(argv[5]);
    NrRead = atoi(argv[6]);
  }
  
  // make const so that you can declare array sizes of this size
  const int Nb = NbRead;
  const int Nk = NkRead;
  const int Nr = NrRead;
  
  // do some reading function
  FILE* inFile  = fopen(inFileName,  "r");
  FILE* outFile = fopen(outFileName, "w");
  
  uint8_t key[Nk];
  readKey(keyFile, key, Nk, Nb); 
  encryptPlaintext(inFile, outFile, key, Nb, Nk, Nr);
  
  return 0;
}
 
void readKey(FILE* keyFile, uint8_t key[], const int Nk, const int Nb) {
  int i;
  for(i = 0; i < Nb*Nk; ++i) {
    char ch;
    if(fscanf(keyFile, "%c", &ch) <= 1) {
      fprintf(stderr, "the key has more values than your declared Nk: %d", Nk);
    }
    key[i] = (uint8_t) ch; 
  }
}

void encryptPlaintext(FILE* inFile, FILE* outFile, const uint8_t key[],
		       const int Nb, const int Nk, const int Nr) {
  // first make reads based on the distance
  char buffer[BUFFER_SIZE];
  uint8_t state[Nb][Nb];

  while(fgets(buffer, sizeof(buffer), stream) != NULL) {
    // parse the string into bytes
    int strSize = strlen(buffer);
    int i;
    for(i = 0; i < strSize; ++i) {
      state[i % 4][i / 4] = (uint8_t) buffer[i];
    }
    // add 0s at the end in case the plaintext is too short
    for(i = strSize; i < bufferSize; ++i) {
      state[i % 4][i / 4] = 0;
    }
    encryptState(state, key, Nb, Nk, Nr);
    printState(state);    
  }
}

void encryptState(uint8_t state[4][4], const uint8_t key[], const int Nb,
		  const int Nk, const int Nr) {
  int round = 0;
  uint8_t roundKeys[Nr + 1][Nb][Nb];
  expandKey(roundKeys, key, Nb, Nk, Nr);
  addRoundKey(state, roundKeys, round);
  for(round = 1; round < Nr; ++round) {
    subBytes   (state, Nb, Nk, Nr);
    shiftRows  (state, Nb, Nk, Nr);
    mixColumns (state, Nb, Nk, Nr);
    addRoundKey(state, roundKeys, round, Nb, Nk, Nr);
  }
  r = Nr;
  subBytes   (state, Nb, Nk, Nr);
  shiftRows  (state, Nb, Nk, Nr);
  addRoundKey(state, roundKeys, round, Nb, Nk, Nr);
}

void subWord(uint8_t word[4], const int Nb) {
  int i;
  for(i = 0; i < Nb; ++i) {
    word[i] = sbox[word[i]]
  }
}

// this is a bit hacky. Create a 3d matrix by using only 2d
void expandKey(uint8_t roundKeys[][4][4], const uint8_t key[],
	       const int Nb, const int Nk, const int Nr) {
  int i,j;
  for(i = 0; i < Nk; ++i) {
    for(j = 0; j < Nb; ++j) {
      roundKeys[0][i][j] = key[i*4 + j];
    }
  }

  for(i = Nk; i < Nb * (Nr + 1); ++i) {
    uint8_t word[Nb];
    for(j = 0; j < Nb; ++j) {
      word[j] = roundKeys[0][i-1][j];
    }

    if((i % Nk) == 0) {
      rotateWord(word, 1, Nb);
      subWord(word, Nb);
      word[0] ^= Rcon[i/Nk];
    }
    else if ((Nk > 6) && (i % Nk == 4)) {
      subWord(word, Nb);
    }
    for(j = 0; j < Nb; ++j) {
      uint8_t val = roundKeys[0][i-Nk][j] ^ temp[j];
      roundKeys[0][i][j] = val;
    }
  }
}


void subBytes(uint8_t state[4][4], const int Nb, const int Nk, const int Nr){
  int line, col;
  for(line = 0; line < Nb; ++i){
    for(col = 0; col < Nb; ++i) {
      state[line][col] = sbox[state[line][col]];
    }
  }
}

// nothing fancy about this function. Rotates the word by 'pos' positions
void rotateWord(uint8_t word[], const int pos, const int Nb) {
  uint8_t auxWord[Nb];
  // create the rotation array
  int i;
  for(i = pos; i < Nb; ++i) {
    auxWord[i - pos] = word[i];
  }
  for(i = 0; i < pos; ++i) {
    auxWord[i + pos] = word[i];
  }

  // put the copy array back into word
  for(i = 0; i < Nb; ++i) {
    word[i] = auxWord[i];
  }
}

void shiftRows(uint8_t state[4][4], const int Nb, const int Nk, const int Nr){
  int line
  for(line = 0; line < Nb; ++line) {
    rotateWord(state[line], line, Nb);
  }
}

uint8_t gMult(uint8_t a, uint8_t b) {
  uint8_t p = 0;
  int i;
  uint8_t hiBitSet;
  for(i = 0; i < 8; ++i) {
    if((b & 1) != 0) {
      p ^= a;
    }
    hiBitSet = a & 0x80;
    a <<= 1;
    if(hiBitSet == 0x80) {
      a ^= 0x1b;
    }
    b >>= 1;
  }
  return p;
}


void mixColumns(uint8_t state[4][4], const int Nb, const int Nk, const int Nr){

  int col;
  for(col = 0; col < Nb; ++col) {
    uint8_t s0c, s1c, s2c, s3c;
    s0c = state[0][col];
    s1c = state[1][col];
    s2c = state[2][col];
    s3c = state[3][col];
      
    state[0][col] = gMult(0x02, s0c) ^ gMult(0x03, s1c) ^ s2c ^ s3c;
    state[1][col] = s0c ^ gMult(0x02, s1c) ^ gMult(0x03, s2c) ^ s3c;
    state[2][col] = s0c ^ s1c ^ gMult(0x02, s2c) ^ gMult(0x03, s3c);
    state[3][col] = gMult(0x03, s0c) ^ s1c ^ s2c ^ gMult(0x02, s3c);
  }  
}

void addRoundKey(uint8_t state[4][4], const uint8_t roundKeys[][4][4],
		 const int round, const int Nb, const int Nk, const int Nr){

  int i,j;
  for(i = 0; i < Nb; ++i) {
    for(j = 0; j < Nb; ++j) {
      // TODO: do such that i and j are not reverted here
      state[j][i] ^= roundKeys[round][i][j];
    }
  }
}