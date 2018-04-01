#include "stdafx.h"
#include "CppUnitTest.h"
#include "MD5.h"
#include "SHA1.h"
#include "SHA256.h"
#include "Math.h"
#include "LongMultiplyReference.h"
#include "BigInt.h"
#include "Primitives.h"
#include "bignum.h"
#include "DES.h"
#include "RSA.h"
#include "Base64.h"
#include <sstream>
#include <bitset>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CryptoLib;
namespace CryptoLibtest
{
	TEST_CLASS(MD5test)
	{
	public:

		TEST_METHOD(MD5_EmptyString)
		{
			char* result = CryptoLib::MD5("", 0);
			Assert::AreEqual(result, "d41d8cd98f00b204e9800998ecf8427e", "MD5: Empty string not matched", LINE_INFO());
			// TODO: Your test code here
		}
		TEST_METHOD(MD5_Foxie)
		{
			char* result = CryptoLib::MD5("The quick brown fox jumps over the lazy dog", 43);
			Assert::AreEqual(result, "9e107d9d372bb6826bd81d3542a419d6", "MD5: Fox string not matched", LINE_INFO());
		}
		TEST_METHOD(MD5_FoxieDot)
		{
			char* result = CryptoLib::MD5("The quick brown fox jumps over the lazy dog.", 44);
			Assert::AreEqual(result, "e4d909c290d0fb1ca068ffaddf22cbd0", "MD5: Fox string not matched", LINE_INFO());
		}
		TEST_METHOD(MD5_Files)
		{

			static char* names[] = { "../CryptoLibTest/testfile/1.testfile", "../CryptoLibTest/testfile/2.testfile", "../CryptoLibTest/testfile/3.testfile" };
			static char* md5s[] = {
				"0cc175b9c0f1b6a831c399e269772661",
				"49aa794b8a34d3a11aa5b1cbb2fc4a38",
				"cc45353d6b0041430a9857e418459984"
			};

			for (int i = 0; i < sizeof(names) / sizeof(char*); i++)
			{
				char* result = CryptoLib::MD5FromFile(names[i]);
				Assert::AreEqual(result, md5s[i], "MD5: File string not matched", LINE_INFO());
			}

		}
	};

	TEST_CLASS(SHA1test)
	{
	public:

		TEST_METHOD(SHA1_EmptyString)
		{
			char* result = CryptoLib::SHA1("", 0);
			Assert::AreEqual(result, "da39a3ee5e6b4b0d3255bfef95601890afd80709", "SHA1: Empty string not matched", LINE_INFO());
			// TODO: Your test code here
		}
		TEST_METHOD(SHA1_Foxie)
		{
			char* result = CryptoLib::SHA1("The quick brown fox jumps over the lazy dog", 43);
			Assert::AreEqual(result, "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12", "SHA1: Fox string not matched", LINE_INFO());
		}
		TEST_METHOD(SHA1_FoxieDot)
		{
			char* result = CryptoLib::SHA1("The quick brown fox jumps over the lazy dog.", 44);
			Assert::AreEqual(result, "408d94384216f890ff7a0c3528e8bed1e0b01621", "SHA1: Fox string not matched", LINE_INFO());
		}
		TEST_METHOD(SHA1_Files)
		{
			static char* names[] = { "../CryptoLibTest/testfile/1.testfile", "../CryptoLibTest/testfile/2.testfile", "../CryptoLibTest/testfile/3.testfile" };
			static char* shas[] = {
				"86f7e437faa5a7fce15d1ddcb9eaeaea377667b8",
				"9af5cea30c1112ee1ded9c40677703e4b74894a5",
				"633ca8e4881b577ecece13e49904afe35627947d"
			};

			for (int i = 0; i < sizeof(names) / sizeof(char*); i++)
			{
				char* result = CryptoLib::SHA1FromFile(names[i]);
				Assert::AreEqual(result, shas[i], "SHA1: File string not matched", LINE_INFO());
			}

		}
	};

	TEST_CLASS(SHA256Test)
	{
	public:

		TEST_METHOD(SHA256_EmptyString)
		{
			char* result = CryptoLib::SHA256("", 0);
			Assert::AreEqual(result, "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855", "SHA256: Empty string not matched", LINE_INFO());
			// TODO: Your test code here
		}
		TEST_METHOD(SHA256_Foxie)
		{
			char* result = CryptoLib::SHA256("The quick brown fox jumps over the lazy dog", 43);
			Assert::AreEqual(result, "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592", "SHA256: Fox string not matched", LINE_INFO());
		}
		TEST_METHOD(SHA256_FoxieDot)
		{
			char* result = CryptoLib::SHA256("The quick brown fox jumps over the lazy dog.", 44);
			Assert::AreEqual(result, "ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c", "SHA256: Fox string not matched", LINE_INFO());
		}
		TEST_METHOD(SHA256_Files)
		{
			static char* names[] = { "../CryptoLibTest/testfile/1.testfile", "../CryptoLibTest/testfile/2.testfile", "../CryptoLibTest/testfile/3.testfile" };
			static char* shas[] = {
				"ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb",
				"65f3d76d631d833714b4ac08b8543d31223d02cc274a2a127dd7ab6144f3e61d",
				"dc13dfb2b9d3d0f1ff27339a76b23a33084e2e671136289a4cb738a95f8059cf"
			};

			for (int i = 0; i < sizeof(names) / sizeof(char*); i++)
			{
				char* result = CryptoLib::SHA256FromFile(names[i]);
				Assert::AreEqual(result, shas[i], "SHA256: File string not matched", LINE_INFO());
			}

		}
	};
	
	TEST_CLASS(MathTest)
	{
	public:
		std::string GenerateRandomNumber(unsigned int length)
		{
			std::string result = "";
			for (size_t i = 0; i < length; i++)
			{
				result += (char)((rand() % 10) + '0');
			}
			if (length == 0) return "0";
			if (rand() % 2) result = '-' + result;
			return result;
		}
		
		TEST_METHOD(_start)
		{
			srand(time(0));
		}

		long long GenerateRandomInt()
		{
			return rand() * rand();
		}

		TEST_METHOD(BigIntTest)
		{
			srand(time(0));

			for (size_t i = 0; i < 50; i++)
			{
				int alen = rand() % 50 + 1;
				int blen = rand() % 50 + 1;
				std::string sa = GenerateRandomNumber(alen);
				std::string sb = GenerateRandomNumber(blen);
				BigInt ba(sa);
				BigInt bb(sb);
				bigint ia(sa);
				bigint ib(sb);
				char msg[10000] = { 0 };
				sprintf(msg, "%s\n    %s\n    %s\n", ba.GetValue().c_str(), bb.GetValue().c_str(), (ba / bb).GetValue().c_str());
				Logger::WriteMessage(msg);
				
				Assert::IsTrue((ba + bb).GetValue() == (ia + ib).ToString(), L"Add test failed", LINE_INFO());
				Assert::IsTrue((ba - bb).GetValue() == (ia - ib).ToString(), L"Sub test failed", LINE_INFO());
				Assert::IsTrue((ba * bb).GetValue() == (ia * ib).ToString(), L"Mul test failed", LINE_INFO());
				if (bb !=0 ) Assert::IsTrue((ba / bb).GetValue() == (ia / ib).ToString(), L"Div test failed", LINE_INFO());
				if (bb != 0) Assert::IsTrue((ba % bb).GetValue() == (ia % ib).ToString(), L"Div test failed", LINE_INFO());
				//Assert::IsTrue(bigint((ba - bb).GetValue()) == (ia - ib), L"Sub test failed", LINE_INFO());
			}
			BigInt a, b, c;
			a = BigInt("145350");
			b = BigInt("255925395");
			c = CryptoLib::Primitives::GCD(a, b);
			Assert::AreEqual(c.GetValue().c_str(), "765", "Gcd test fail", LINE_INFO());

			a = BigInt("17");
			b = BigInt("32");
			c = CryptoLib::Primitives::GCD(a, b);
			Assert::AreEqual(c.GetValue().c_str(), "1", "Gcd test fail", LINE_INFO());

			a = BigInt("17");
			b = BigInt("32");
			CryptoLib::Primitives::Vector2D result;
			result = CryptoLib::Primitives::ExtendedGCD(a, b, &c);
			Assert::AreEqual(c.GetValue().c_str(), "1", "Ext Gcd test fail", LINE_INFO());
			
			for (size_t i = 0; i < 500; i++)
			{
				int alen = rand() % 50 + 1;
				int blen = rand() % 50 + 1;
				std::string sa = GenerateRandomNumber(alen);
				std::string sb = GenerateRandomNumber(blen);
				BigInt a(sa);
				BigInt b(sb);
				bigint ia(sa);
				bigint ib(sb);

				Assert::IsTrue((a == b) == (ia == ib), L"E test failed", LINE_INFO());
				Assert::IsTrue((a > b) == (ia > ib), L"G test failed", LINE_INFO());
				Assert::IsTrue((a >= b) == (ia >= ib), L"Ge test failed", LINE_INFO());
				Assert::IsTrue((a < b) == (ia < ib), L"L test failed", LINE_INFO());
				Assert::IsTrue((a <= b) == (ia <= ib), L"Le test failed", LINE_INFO());
				Assert::IsTrue((a != b) == (ia != ib), L"Ne test failed", LINE_INFO());
			}
		}

		TEST_METHOD(DivideTest)
		{
			BigInt a("54305439545093405934094350934095034509345093450934509345094350934509340593409534095345093459034059345043982348925453498");
			BigInt b("324283248754378534875438");
			BigInt c = ((a / b) / b) / b;
			Assert::AreEqual(c.GetValue().c_str(), "1592464602165876631668101864376880269997201205147", "Divide long failed", LINE_INFO());

			for (size_t i = 0; i < 40; i++)
			{
		
				long long t1 = GenerateRandomInt();
				long long t2 = GenerateRandomInt();

				BigInt b1(t1);
				BigInt b2(t2);
				BigInt b3 = b1 / b2;
				std::string res = std::to_string(t1 / t2);
				Assert::AreEqual(b3.GetValue().c_str(), res.c_str(), "Division of random numbers test fail", LINE_INFO());
			}
		}

		TEST_METHOD(GCDTest)
		{
			for (size_t i = 0; i < 50; i++)
			{

				int alen = rand() % 25 + 1;
				int blen = rand() % 25 + 1;
				std::string sa = GenerateRandomNumber(alen);
				std::string sb = GenerateRandomNumber(blen);
				BigInt ba(sa);
				BigInt bb(sb);
				char msg[10000] = { 0 };
				sprintf(msg, "%s\n    %s\n", ba.GetValue().c_str(), bb.GetValue().c_str());
				Logger::WriteMessage(msg);

				CryptoLib::Primitives::Vector2D res;
				BigInt gcd;
				res = Primitives::ExtendedGCD(ba, bb, &gcd);
				BigInt val = res.alpha * ba + res.beta * bb;
				Assert::AreEqual(gcd.GetValue().c_str(), val.GetValue().c_str(), "GCD fail", LINE_INFO());
			}

		}

		TEST_METHOD(InverseTest)
		{
			size_t i = 0;
			while (i < 50)
			{
				int alen = rand() % 25 + 1;
				int blen = rand() % 25 + 1;
				std::string sa = GenerateRandomNumber(alen);
				std::string sb = GenerateRandomNumber(blen);
				BigInt ba(sa);
				BigInt bb(sb);
				

				if (Primitives::GCD(ba, bb) == 1 && bb > 1)
				{
					i++;
				}
				else continue;
				char msg[10000] = { 0 };
				sprintf(msg, "%s\n    %s\n    %s\n", ba.GetValue().c_str(), bb.GetValue().c_str(), Primitives::InverseModM(ba, bb).GetValue().c_str());
				Logger::WriteMessage(msg);

				Assert::IsTrue(Primitives::MathematicalModulo(Primitives::InverseModM(ba, bb) * ba, bb) == 1);
			}
		}

		TEST_METHOD(POWTest)
		{
			for (size_t i = 0; i < 50; i++)
			{

				int alen = rand() % 13 + 1;
				int blen = rand() % 2 + 1;
				int mlen = rand() % 5 + 1;
				std::string sa = GenerateRandomNumber(alen);
				std::string sb = GenerateRandomNumber(blen);
				std::string sm = GenerateRandomNumber(mlen);
				BigInt ba(sa);
				BigInt bb(sb);
				BigInt bm(sm);
				char msg[10000] = { 0 };
				sprintf(msg, "%s\n    %s\n     %s\n", ba.GetValue().c_str(), bb.GetValue().c_str(), bm.GetValue().c_str());
				Logger::WriteMessage(msg);

				BigInt mul = 1;
				for (BigInt i = 0; i < bb; i += 1)
				{
					mul *= ba;
				}
				BigInt pow = Primitives::POW(ba, bb);
				Assert::AreEqual(pow.GetValue().c_str(), mul.GetValue().c_str(), L"POW fail", LINE_INFO());
				Assert::IsTrue(Primitives::POWModM(ba, bb, bm) == (mul%bm));
			}
		}
	};

	TEST_CLASS(DESTest) 
	{
	public:
		void OutputBits(uint64_t num, uint8_t count = 64) {
			std::string res = "";
			for (int i = 0; i < count; i++)
			{
				if (GET(num, i)) res += "1";
				else res += "0";
			}
			Logger::WriteMessage(res.c_str());
		}

		TEST_METHOD(DES_SubkeysTest) {
			uint64_t key = 0x4b41534849534142;
			DES::KEY_SET key_set;
			CryptoLib::DES::DesKeySchedule(key, &key_set);
			uint64_t subkeys[] = { 
				0xa092c20ab140L, 0xa012524c00abL, 0x245a50065849L, 0x67150029170L, 
				0xe4551818d20L, 0x4f4109480e10L, 0xb818959401cL, 0x19088b015088L, 
				0x190a88182e90L, 0x10388c394011L, 0x102c44036002L, 0x406c24a42104L, 
				0xc0a524a002c6L, 0xc08623548283L, 0xe19222160449L, 0xa0922a601486L 
			};
			for (int i = 0; i < 16; i++) {
				Assert::IsTrue((key_set.keys[i] >> 16) == subkeys[i], L"Subkey invalid");
			}
		}

		TEST_METHOD(DES_MessageScheduleTest) {
			char c_message[] = { 0x4e, 0x45, 0x56, 0x52, 0x51, 0x55, 0x49, 0x54 };
			uint64_t* message = (uint64_t*)(c_message);
			uint64_t key = 0x4B41534849534142;
			size_t sz = sizeof(c_message);
			uint64_t* result = new uint64_t[sz / sizeof(uint64_t)]();
			uint64_t* decrypted = new uint64_t[sz / sizeof(uint64_t)]();
			CryptoLib::DES::DesEncrypt(message, sz, result, key);
			CryptoLib::DES::DesDecrypt(result, sz, decrypted, key);
			int res = memcmp(message, decrypted, sz);
			Assert::IsTrue(res == 0);
		}

		TEST_METHOD(Des_MITM) {
			char c_message[] = { 0x4e, 0x45, 0x56, 0x52, 0x51, 0x55, 0x49, 0x54 };
			uint64_t* message = (uint64_t*)(c_message);
			uint64_t key1 = 0x3132333435363738;
			uint64_t key2 = 0x3837363534333231;
			size_t sz = sizeof(c_message);
			uint64_t* round1 = new uint64_t[sz / sizeof(uint64_t)]();
			uint64_t* round2 = new uint64_t[sz / sizeof(uint64_t)]();
			CryptoLib::DES::DesEncrypt(message, sz, round1, key1);
			CryptoLib::DES::DesEncrypt(round1, sz, round2, key2);
			uint64_t known_key1 = 0x3132333435363700;
			uint64_t known_key2 = 0x3837363534333200;
			uint64_t result_key1;
			uint64_t result_key2;
			bool res = CryptoLib::DES::MITMAttack(
				known_key1, 
				known_key2, 
				message, 
				round2, 
				sz,
				&result_key1,
				&result_key2
			);
			Assert::IsTrue(res, L"Bool failed");
			char arr[512] = { 0 };
			sprintf(arr, "0x%I64X", result_key1);
			char arr2[512] = { 0 };
			sprintf(arr2, "0x%I64X", result_key2);
			Logger::WriteMessage(arr);
			Logger::WriteMessage(arr2);
		}
	};

	TEST_CLASS(RSA_TEST) {
	public:
		std::string toStr(NTL::ZZ val) {
			std::stringstream ss;
			ss << val;
			return std::string(ss.str());
		}

		void byte(unsigned char val) {
			char vv[10] = { 0 };
			sprintf(vv, "%02X", val);
			Logger::WriteMessage(vv);
		}

		TEST_METHOD(RsaTest) {
			RSA::RSA_CONTEXT ctx;
			RSA::RSAKeyGen(&ctx);
			Logger::WriteMessage(toStr(ctx.publicExponent).c_str());
			Logger::WriteMessage(toStr(ctx.privateExponent).c_str());
			Logger::WriteMessage(toStr(ctx.publicModulus).c_str());
			Logger::WriteMessage(toStr(ctx.privateP).c_str());
			Logger::WriteMessage(toStr(ctx.privateQ).c_str());
			ctx.decryptionType = RSA::RSA_DECRYPTION_TYPE::DECRYPTION_CRT;

			char* msg = "hello";
			char res[2000] = { 0 };
			size_t res_len = 0;
			RSA::RSAEncrypt(msg,5,res,&res_len,&ctx);

			size_t len = 0;
			char decr[2000] = { 0 };
			RSA::RSADecrypt(res, res_len, decr, &len, &ctx);
			Logger::WriteMessage(decr);

			RSA::ExportPublicKey(&ctx, "output.pub.rsa");
			RSA::ExportPrivateKey(&ctx, "output.prv.rsa");

			RSA::RSA_CONTEXT imp_ctx;
			RSA::ImportPublicKey(&imp_ctx, "output.pub.rsa");
			Assert::IsTrue(
				ctx.publicExponent == imp_ctx.publicExponent &&
				ctx.publicModulus == imp_ctx.publicModulus
			);
			RSA::ImportPrivateKey(&imp_ctx, "output.prv.rsa");
			Assert::IsTrue(
				ctx.privateExponent == imp_ctx.privateExponent &&
				ctx.publicModulus == imp_ctx.publicModulus
			);
			Assert::IsTrue(
				ctx.privateP == imp_ctx.privateP &&
				ctx.privateQ == imp_ctx.privateQ
			);
		}

		TEST_METHOD(Rsa_Continued) {
			NTL::ZZ a(73);
			NTL::ZZ b(95);
			std::stringstream ss;
			std::vector<NTL::ZZ> v1 = CryptoLib::RSA::ContinuedFraction(a, b);
			std::vector<NTL::ZZ> actual1{ 
				NTL::ZZ(0), 
				NTL::ZZ(1),
				NTL::ZZ(3),
				NTL::ZZ(3),
				NTL::ZZ(7),
			};
			Assert::IsTrue(v1 == actual1, L"Vectors 1 invalid", LINE_INFO());

			a = 17993;
			b = 90581;

			v1 = CryptoLib::RSA::ContinuedFraction(a, b);
			actual1 = {
				NTL::ZZ(0),
				NTL::ZZ(5),
				NTL::ZZ(29),
				NTL::ZZ(4),
				NTL::ZZ(1),
				NTL::ZZ(3),
				NTL::ZZ(2),
				NTL::ZZ(4),
				NTL::ZZ(3)
			};
			Assert::IsTrue(v1 == actual1, L"Vectors 1 invalid", LINE_INFO());
		}

		TEST_METHOD(Rsa_Covnergence) {
			std::vector<NTL::ZZ> nums{  // 17993/90581
				NTL::ZZ(0),
				NTL::ZZ(5),
				NTL::ZZ(29),
				NTL::ZZ(4),
				NTL::ZZ(1),
				NTL::ZZ(3),
				NTL::ZZ(2),
				NTL::ZZ(4),
				NTL::ZZ(3)
			};
			std::vector<std::pair<NTL::ZZ, NTL::ZZ>> actual{
				std::make_pair(NTL::ZZ(0), NTL::ZZ(1)),
				std::make_pair(NTL::ZZ(1), NTL::ZZ(5)),
				std::make_pair(NTL::ZZ(29), NTL::ZZ(146)),
				std::make_pair(NTL::ZZ(117), NTL::ZZ(589)),
				std::make_pair(NTL::ZZ(146), NTL::ZZ(735)),
				std::make_pair(NTL::ZZ(555), NTL::ZZ(2794)),
				std::make_pair(NTL::ZZ(1256), NTL::ZZ(6323)),
				std::make_pair(NTL::ZZ(5579), NTL::ZZ(28086)),
				std::make_pair(NTL::ZZ(17993), NTL::ZZ(90581))
			};
			auto result = CryptoLib::RSA::Convergents(nums);
			Assert::IsTrue(result == actual, L"Invalid conv values", LINE_INFO());
		}

		TEST_METHOD(Rsa_Wienner) {
			RSA::RSA_CONTEXT ctx;
			RSA::RSAKeyGenWeak(&ctx);
			std::stringstream ss;
			ss	<< "e = " << ctx.publicExponent << std::endl
				<< "d = " << ctx.privateExponent << std::endl
				<< "n = " << ctx.publicModulus << std::endl
				<< "p = " << ctx.privateP << std::endl
				<< "q = " << ctx.privateQ << std::endl;
			Logger::WriteMessage(ss.str().c_str());

			char* msg = "hello world";
			char encrypted[5000] = { 0 };
			size_t encrypted_len = 0;
			
			RSA::RSAEncrypt(msg, strlen(msg), encrypted, &encrypted_len, &ctx);

			// Generate new keys, perform the attack
			RSA::RSA_CONTEXT attack_ctx;
			attack_ctx.publicExponent = ctx.publicExponent;
			attack_ctx.publicModulus = ctx.publicModulus;
			Assert::IsTrue(RSA::WienerAttack(&attack_ctx), L"Could not find keys", LINE_INFO());
			ss.str(std::string());
			ss.clear();
			ss	<< "Found p = " << ctx.privateP << std::endl
				<< "Found q = " << ctx.privateQ << std::endl;
			Logger::WriteMessage("Found p and q");
			Logger::WriteMessage(ss.str().c_str());
			Assert::IsTrue(ctx.privateP == attack_ctx.privateP
				&& ctx.privateQ == attack_ctx.privateQ,
				L"Keys pq don't match",
				LINE_INFO()
			);
			char decrypted[5000] = { 0 };
			size_t decryped_len = 0;
			RSA::RSADecrypt(encrypted, encrypted_len, decrypted, &decryped_len, &attack_ctx);
			Assert::IsTrue(memcmp(msg, decrypted, decryped_len), L"Decrypted msg doesn't match", LINE_INFO());
		}
	};

	TEST_CLASS(B64_TEST) {
	public:
		TEST_METHOD(B64Encode_Test) {
			char* strings[] = {
				"helloworld",
				"f",
				"fo",
				"foo",
				"foob",
				"fooba",
				"foobar",
				"base64",
				"foobarb",
				"foobarba",
				"foobarbar",
				"foobarbarf",
				"foobarbarfo",
				"foobarbarfoo",
				"\x01\x01\x02\x03\x04\x05",
				"\x99\xFF\x11\x22\x33\x44\x55\x66\x77\x88\xAA",
				"\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff",
				"\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe",
				"\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd",
				"\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb"
			};

			char* correct[] = { 
				"aGVsbG93b3JsZA==", 
				"Zg==", 
				"Zm8=", 
				"Zm9v", 
				"Zm9vYg==", 
				"Zm9vYmE=", 
				"Zm9vYmFy", 
				"YmFzZTY0",
				"Zm9vYmFyYg==", 
				"Zm9vYmFyYmE=", 
				"Zm9vYmFyYmFy", 
				"Zm9vYmFyYmFyZg==", 
				"Zm9vYmFyYmFyZm8=", 
				"Zm9vYmFyYmFyZm9v", 
				"AQECAwQF", 
				"mf8RIjNEVWZ3iKo=",
				"AQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/QEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaW1xdXl9gYWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXp7fH1+f4CBgoOEhYaHiImKi4yNjo+QkZKTlJWWl5iZmpucnZ6foKGio6SlpqeoqaqrrK2ur7CxsrO0tba3uLm6u7y9vr/AwcLDxMXGx8jJysvMzc7P0NHS09TV1tfY2drb3N3e3+Dh4uPk5ebn6Onq6+zt7u/w8fLz9PX29/j5+vv8/f7/",
				"AQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/QEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaW1xdXl9gYWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXp7fH1+f4CBgoOEhYaHiImKi4yNjo+QkZKTlJWWl5iZmpucnZ6foKGio6SlpqeoqaqrrK2ur7CxsrO0tba3uLm6u7y9vr/AwcLDxMXGx8jJysvMzc7P0NHS09TV1tfY2drb3N3e3+Dh4uPk5ebn6Onq6+zt7u/w8fLz9PX29/j5+vv8/f4=",
				"AQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/QEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaW1xdXl9gYWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXp7fH1+f4CBgoOEhYaHiImKi4yNjo+QkZKTlJWWl5iZmpucnZ6foKGio6SlpqeoqaqrrK2ur7CxsrO0tba3uLm6u7y9vr/AwcLDxMXGx8jJysvMzc7P0NHS09TV1tfY2drb3N3e3+Dh4uPk5ebn6Onq6+zt7u/w8fLz9PX29/j5+vv8/Q==",
				"AQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/QEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaW1xdXl9gYWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXp7fH1+f4CBgoOEhYaHiImKi4yNjo+QkZKTlJWWl5iZmpucnZ6foKGio6SlpqeoqaqrrK2ur7CxsrO0tba3uLm6u7y9vr/AwcLDxMXGx8jJysvMzc7P0NHS09TV1tfY2drb3N3e3+Dh4uPk5ebn6Onq6+zt7u/w8fLz9PX29/j5+vs="

			};
			for (int i = 0; i < sizeof(strings) / sizeof(char*); i++) {
				std::string out;
				Base64::Base64Encode(strings[i], strlen(strings[i]), out);
				Assert::AreEqual(correct[i], out.c_str(), "Invalid encode", LINE_INFO());
			}
		}

		TEST_METHOD(B64Decode_Test) {
			char* correct[] = {
				"helloworld",
				"f",
				"fo",
				"foo",
				"foob",
				"fooba",
				"foobar",
				"base64",
				"foobarb",
				"foobarba",
				"foobarbar",
				"foobarbarf",
				"foobarbarfo",
				"foobarbarfoo",
				"\x01\x01\x02\x03\x04\x05",
				"\x99\xFF\x11\x22\x33\x44\x55\x66\x77\x88\xAA",
				"\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff",
				"\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe",
				"\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd",
				"\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb"
			};

			char* strings[] = {
				"aGVsbG93b3JsZA==",
				"Zg==",
				"Zm8=",
				"Zm9v",
				"Zm9vYg==",
				"Zm9vYmE=",
				"Zm9vYmFy",
				"YmFzZTY0",
				"Zm9vYmFyYg==",
				"Zm9vYmFyYmE=",
				"Zm9vYmFyYmFy",
				"Zm9vYmFyYmFyZg==",
				"Zm9vYmFyYmFyZm8=",
				"Zm9vYmFyYmFyZm9v",
				"AQECAwQF",
				"mf8RIjNEVWZ3iKo=",
				"AQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/QEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaW1xdXl9gYWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXp7fH1+f4CBgoOEhYaHiImKi4yNjo+QkZKTlJWWl5iZmpucnZ6foKGio6SlpqeoqaqrrK2ur7CxsrO0tba3uLm6u7y9vr/AwcLDxMXGx8jJysvMzc7P0NHS09TV1tfY2drb3N3e3+Dh4uPk5ebn6Onq6+zt7u/w8fLz9PX29/j5+vv8/f7/",
				"AQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/QEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaW1xdXl9gYWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXp7fH1+f4CBgoOEhYaHiImKi4yNjo+QkZKTlJWWl5iZmpucnZ6foKGio6SlpqeoqaqrrK2ur7CxsrO0tba3uLm6u7y9vr/AwcLDxMXGx8jJysvMzc7P0NHS09TV1tfY2drb3N3e3+Dh4uPk5ebn6Onq6+zt7u/w8fLz9PX29/j5+vv8/f4=",
				"AQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/QEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaW1xdXl9gYWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXp7fH1+f4CBgoOEhYaHiImKi4yNjo+QkZKTlJWWl5iZmpucnZ6foKGio6SlpqeoqaqrrK2ur7CxsrO0tba3uLm6u7y9vr/AwcLDxMXGx8jJysvMzc7P0NHS09TV1tfY2drb3N3e3+Dh4uPk5ebn6Onq6+zt7u/w8fLz9PX29/j5+vv8/Q==",
				"AQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGRobHB0eHyAhIiMkJSYnKCkqKywtLi8wMTIzNDU2Nzg5Ojs8PT4/QEFCQ0RFRkdISUpLTE1OT1BRUlNUVVZXWFlaW1xdXl9gYWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4eXp7fH1+f4CBgoOEhYaHiImKi4yNjo+QkZKTlJWWl5iZmpucnZ6foKGio6SlpqeoqaqrrK2ur7CxsrO0tba3uLm6u7y9vr/AwcLDxMXGx8jJysvMzc7P0NHS09TV1tfY2drb3N3e3+Dh4uPk5ebn6Onq6+zt7u/w8fLz9PX29/j5+vs="

			};
			for (int i = 0; i < sizeof(strings) / sizeof(char*); i++) {
				//Logger::WriteMessage(Base64::Base64Enconde(strings[i], strlen(strings[i])).c_str());
				size_t len = 0;
				char* res = (char*)CryptoLib::Base64::Base64Decode(strings[i], strlen(strings[i]), &len);
				Assert::AreEqual(correct[i], res, "Invalid decode", LINE_INFO());
				delete[] res;
			}
		}
	};
};
