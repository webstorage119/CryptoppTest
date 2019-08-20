#include "CryptographyHelper.h"

#ifdef CRYPTOPP_IMPORTS

static CryptoPP::PNew s_pNew = NULLPTR;
static CryptoPP::PDelete s_pDelete = NULLPTR;

extern "C" __declspec(dllexport) void __cdecl SetNewAndDeleteFromCryptoPP(CryptoPP::PNew pNew, CryptoPP::PDelete pDelete, CryptoPP::PSetNewHandler pSetNewHandler)
{
	(void)(pSetNewHandler);
	s_pNew = pNew;
	s_pDelete = pDelete;
}

void * __cdecl operator new (size_t size)
{
	return s_pNew(size);
}

void __cdecl operator delete (void * p)
{
	s_pDelete(p);
}

#endif

CryptographyHelper::CryptographyHelper(char key[16], char iv[16])
{
	for (int j = 0; j < CryptoPP::AES::DEFAULT_KEYLENGTH; ++j)
	{
		this->key[j] = key[j];
	}

	for (int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
	{
		this->iv[i] = iv[i];
	}
}

CryptographyHelper::~CryptographyHelper()
{
}

std::string CryptographyHelper::encrypt(const char* plainText)
{
	std::string cipherText;

	//
	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::HexEncoder(new CryptoPP::StringSink(cipherText)));
	stfEncryptor.Put((CryptoPP::byte *)plainText, strlen(plainText));
	stfEncryptor.MessageEnd();

	return cipherText;
}

std::string CryptographyHelper::decrypt(const char *cipherText)
{
	std::string decryptedText;

	//
	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
	CryptoPP::HexDecoder stfDecryptor(new CryptoPP::StreamTransformationFilter(cbcDecryption, new CryptoPP::StringSink(decryptedText)));
	stfDecryptor.Put((CryptoPP::byte *)cipherText, strlen(cipherText));
	stfDecryptor.MessageEnd();

	return decryptedText;
}
