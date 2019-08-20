#pragma once

#include <dll.h>
#include <aes.h>
#include <filters.h>
#include <modes.h>

class CryptographyHelper
{
public:
	CryptographyHelper(char key[16], char iv[16]);
	~CryptographyHelper();

	std::string encrypt(const char *plainText);
	std::string decrypt(const char *cipherTextHex);

private:
	CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
	CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
};

