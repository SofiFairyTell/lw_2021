#pragma once
//

void AESEncrypt(unsigned char * message, unsigned char * expandedKey, unsigned char * encryptedMessage);
//
////declaration of decryption function
void AESDecrypt(unsigned char * encryptedMessage, unsigned char * expandedKey, unsigned char * decryptedMessage);

class  mode_aes
{
public:
	void encrypt_aes();
	void decrypt_aes();
};

	


