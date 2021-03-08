#pragma once
//
////declaration of encryption function
//void AddRoundKey(unsigned char * state, unsigned char * roundKey);
//void SubBytes(unsigned char * state);
//void ShiftRows_left(unsigned char * state);
//void MixColumns(unsigned char * state);
//void Round_encr(unsigned char * state, unsigned char * key);
//void FinalRound(unsigned char * state, unsigned char * key);
void AESEncrypt(unsigned char * message, unsigned char * expandedKey, unsigned char * encryptedMessage);
//
////declaration of decryption function
//void SubRoundKey(unsigned char * state, unsigned char * roundKey);
//void InverseMixColumns(unsigned char * state);
//void ShiftRows_right(unsigned char * state);
//void SubBytes_inv(unsigned char * state);
//void Round_decr(unsigned char * state, unsigned char * key);
//void InitialRound(unsigned char * state, unsigned char * key);
void AESDecrypt(unsigned char * encryptedMessage, unsigned char * expandedKey, unsigned char * decryptedMessage);

class  mode_aes
{
public:
	void encrypt_aes();
	void decrypt_aes();
};

	


