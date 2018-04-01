#include "stdafx.h"
#include "RSA.h"
#include <sstream>


std::string CryptoLib::RSA::ZZToB64(const NTL::ZZ& num) {
	size_t output_length = NTL::NumBytes(num);
	uint8_t* output = new uint8_t[output_length];
	NTL::BytesFromZZ(output, num, output_length);
	std::string result;
	CryptoLib::Base64::Base64Encode(
		output,
		output_length,
		result
	);
	return result;
}

NTL::ZZ CryptoLib::RSA::B64ToZZ(const std::string& input) {
	size_t decoded_len = 0;
	void* decoded = CryptoLib::Base64::Base64Decode(
		(void*)input.c_str(),
		input.length(),
		&decoded_len
	);
	NTL::ZZ res = NTL::ZZFromBytes((uint8_t*)decoded, decoded_len);
	return res;
}

void CryptoLib::RSA::RSAKeyGen(RSA_CONTEXT* ctx) 
{
	NTL::ZZ prime1;
	NTL::ZZ prime2;
	NTL::ZZ prime_product;
	NTL::ZZ euler_totient;

	GenPrime(prime1, 1024);
	GenPrime(prime2, 1024);
	prime_product = prime1 * prime2;
	euler_totient = (prime1 - 1) * (prime2 - 1);
	NTL::ZZ e(65537);
	NTL::ZZ d = NTL::InvMod(e, euler_totient);

	ctx->publicModulus = prime_product;
	ctx->publicExponent = e;
	ctx->privateExponent = d;
	ctx->privateP = prime1;
	ctx->privateQ = prime2;
}

void CryptoLib::RSA::RSAKeyGenWeak(RSA_CONTEXT* ctx)
{
	NTL::ZZ prime1;
	NTL::ZZ prime2;
	NTL::ZZ prime_product;
	NTL::ZZ euler_totient;

	while (true) 
	{
		NTL::GenPrime(prime1, 1024);
		NTL::GenPrime(prime2, 1024);
		if (prime1 > prime2 && prime1 < 2 * prime2) break;
	}
	prime_product = prime1 * prime2;
	euler_totient = (prime1 - 1) * (prime2 - 1);

	NTL::ZZ e, d;
	NTL::ZZ sq = NTL::SqrRoot(NTL::SqrRoot(prime_product)) / 3;
	size_t d_bits = NTL::NumBits(sq) - 1;
	while (true) 
	{
		NTL::GenPrime(d, d_bits);
		e = NTL::InvMod(d, euler_totient);
		if ((d * e) % euler_totient == 1) break;
	} 

	ctx->publicModulus = prime_product;
	ctx->publicExponent = e;
	ctx->privateExponent = d;
	ctx->privateP = prime1;
	ctx->privateQ = prime2;
}

void CryptoLib::RSA::RSAEncrypt(
	void* plaintext, 
	size_t plaintext_length,
	void* ciphertext,
	size_t* ciphertext_length,
	RSA_CONTEXT* ctx
) 
{
	NTL::ZZ message_integer = NTL::ZZFromBytes((uint8_t*)plaintext, plaintext_length);
	NTL::ZZ ciphertext_integer = NTL::PowerMod(
		message_integer,
		ctx->publicExponent,
		ctx->publicModulus
	);
	NTL::BytesFromZZ((unsigned char*)ciphertext, ciphertext_integer, NTL::NumBytes(ciphertext_integer));
	(*ciphertext_length) = NTL::NumBytes(ciphertext_integer);
}

void CryptoLib::RSA::RSADecrypt(
	void* ciphertext,
	size_t ciphertext_length,
	void* plaintext,
	size_t* plaintext_length,
	RSA_CONTEXT* ctx
)
{
	NTL::ZZ message_integer = NTL::ZZFromBytes((uint8_t*)ciphertext, ciphertext_length);
	NTL::ZZ plaintext_integer;
	if (ctx->decryptionType == RSA::RSA_DECRYPTION_TYPE::DECRYPTION_PRIVATE_KEY) 
	{
		plaintext_integer = NTL::PowerMod(
			message_integer,
			ctx->privateExponent,
			ctx->publicModulus
		);
	}
	else 
	{
		NTL::ZZ dP = ctx->privateExponent % (ctx->privateP - 1);
		NTL::ZZ dQ = ctx->privateExponent % (ctx->privateQ - 1);
		
		NTL::ZZ qInv = NTL::InvMod(ctx->privateQ % ctx->privateP, ctx->privateP);
		
		NTL::ZZ m1 = NTL::PowerMod(
			message_integer % ctx->privateP,
			dP,
			ctx->privateP
		);
		
		NTL::ZZ m2 = NTL::PowerMod(
			message_integer % ctx->privateQ,
			dQ,
			ctx->privateQ
		);
		
		NTL::ZZ h;
		if (m1 > m2) 
		{
			h = NTL::MulMod(qInv, m1 - m2, ctx->privateP);
		}
		else 
		{
			NTL::ZZ div = (ctx->privateQ % ctx->privateP == 0) ?
				(ctx->privateQ / ctx->privateP) : (1 + ctx->privateQ / ctx->privateP);
			h = NTL::MulMod(qInv, (m1 + div * ctx->privateP) - m2, ctx->privateP);
		}
		plaintext_integer = m2 + h * ctx->privateQ;
	}
	NTL::BytesFromZZ((unsigned char*)plaintext, plaintext_integer, NTL::NumBytes(plaintext_integer));
	(*plaintext_length) = NTL::NumBytes(plaintext_integer);
}



void CryptoLib::RSA::ExportPublicKey(RSA_CONTEXT* ctx, char* file_path) 
{
	std::string exp_enc = ZZToB64(ctx->publicExponent);
	std::string mod_enc = ZZToB64(ctx->publicModulus);

	std::ofstream f(file_path, std::ios::binary);
	f << "-----BEGIN RSA PUBLIC KEY-----\n"
		<< exp_enc << std::endl << mod_enc << std::endl
		<< "-----END RSA PUBLIC KEY-----";
	f.close();

	
}

void CryptoLib::RSA::ExportPrivateKey(RSA_CONTEXT* ctx, char* file_path) 
{
	std::string prv_enc = ZZToB64(ctx->privateExponent);
	std::string mod_enc = ZZToB64(ctx->publicModulus);

	std::string p_enc = ZZToB64(ctx->privateP);
	std::string q_enc = ZZToB64(ctx->privateQ);

	std::ofstream f(file_path, std::ios::binary);
	f << "-----BEGIN RSA PRIVATE KEY-----" << std::endl;
	if (ctx->decryptionType = RSA_DECRYPTION_TYPE::DECRYPTION_PRIVATE_KEY)
	{
		f << "PKEY" << std::endl;
		f << prv_enc << std::endl << mod_enc << std::endl;
	}
	else {
		f << "CRT" << std::endl;
		f << prv_enc << std::endl << mod_enc << std::endl;
		f << p_enc << std::endl;
		f << q_enc << std::endl;
	}
	f << "-----END RSA PRIVATE KEY-----";
	f.close();
}


void CryptoLib::RSA::ImportPublicKey(RSA_CONTEXT* ctx, char* file_path) 
{
	std::ifstream f(file_path, std::ios::binary);
	std::string exp_enc;
	std::string mod_enc;
	std::string temp;
	std::getline(f, temp);
	std::getline(f, exp_enc);
	std::getline(f, mod_enc);
	f.close();
	ctx->publicExponent = B64ToZZ(exp_enc);
	ctx->publicModulus = B64ToZZ(mod_enc);
}

void CryptoLib::RSA::ImportPrivateKey(RSA_CONTEXT* ctx, char* file_path) 
{
	std::ifstream f(file_path, std::ios::binary);
	ctx->decryptionType = RSA::RSA_DECRYPTION_TYPE::DECRYPTION_PRIVATE_KEY;
	std::string prv_enc;
	std::string mod_enc;
	std::string p_enc;
	std::string q_enc;
	std::string temp;
	std::getline(f, temp);
	std::getline(f, temp);
	std::getline(f, prv_enc);
	std::getline(f, mod_enc);
	
	if (temp == "CRT") {
		ctx->decryptionType = RSA::RSA_DECRYPTION_TYPE::DECRYPTION_CRT;
		std::getline(f, p_enc);
		std::getline(f, q_enc);
		ctx->privateP = B64ToZZ(p_enc);
		ctx->privateQ = B64ToZZ(q_enc);
	}
	f.close();
	ctx->privateExponent = B64ToZZ(prv_enc);
	ctx->publicModulus = B64ToZZ(mod_enc);
	
}

std::vector<NTL::ZZ> CryptoLib::RSA::ContinuedFraction(const NTL::ZZ& a, const NTL::ZZ& b)
{
	std::vector<NTL::ZZ> continued;
	NTL::ZZ q = a / b;
	NTL::ZZ r = a % b;
	continued.push_back(q);
	NTL::ZZ _a = a;
	NTL::ZZ _b = b;
	while (r != 0) {
		_a = _b;
		_b = r;
		q = _a / _b;
		r = _a % _b;
		continued.push_back(q);
	}
	return continued;
}

std::vector<std::pair<NTL::ZZ, NTL::ZZ>> CryptoLib::RSA::Convergents(const std::vector<NTL::ZZ>& continued) {
	NTL::ZZ alpha;
	NTL::ZZ beta;
	std::vector<std::pair<NTL::ZZ, NTL::ZZ>> convergents;
	for (size_t i = 0; i < continued.size(); i++)
	{
		if (i == 0) 
		{
			alpha = continued[0];
			beta = 1;
		}
		else if (i == 1)
		{
			alpha = continued[0] * continued[1] + 1;
			beta = continued[1];
		}
		else
		{
			alpha = continued[i] * convergents[i - 1].first + convergents[i - 2].first;
			beta = continued[i] * convergents[i - 1].second + convergents[i - 2].second;
		}
		convergents.push_back(std::make_pair(alpha, beta));
	}
	return convergents;
}

bool CryptoLib::RSA::WienerAttack(RSA_CONTEXT* ctx) {
	auto cont = ContinuedFraction(ctx->publicExponent, ctx->publicModulus);
	auto conv = Convergents(cont);
	NTL::ZZ phi;
	for (size_t i = 0; i < conv.size(); i++) {
		if (conv[i].first == 0) continue;
		phi = (ctx->publicExponent * conv[i].second - 1 ) / conv[i].first;
		NTL::ZZ a(1);
		NTL::ZZ b = -(ctx->publicModulus - phi + 1);
		NTL::ZZ c = ctx->publicModulus;
		NTL::ZZ delta = b*b - 4*a*c;
		NTL::ZZ sqrt = NTL::SqrRoot(delta);
		if (sqrt * sqrt != delta) 
		{
			continue;
		}
		NTL::ZZ x1 = -b + sqrt;
		NTL::ZZ x2 = -b - sqrt;
		if (x1 < 0 || x1 % (2 * a) != 0) continue;
		if (x2 < 0 || x2 % (2 * a) != 0) continue;
		x1 /= 2 * a;
		x2 /= 2 * a;
		if (x1 * x2 == ctx->publicModulus)
		{
			ctx->privateP = x1;
			ctx->privateQ = x2;
			return true;
		}
	}
	return false;
}