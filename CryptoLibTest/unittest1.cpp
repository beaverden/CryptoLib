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
			static char* names[] = { "1.testfile", "2.testfile", "3.testfile" };
			static char* md5s[] = {
				"b6a8cab2780cb81b45864ffaf9157bec",
				"9a55ca8879302a5add9437559c45aa04",
				"9d9c90870bc46ad65baf0f3977e7590f"
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
			static char* names[] = { "1.testfile", "2.testfile", "3.testfile" };
			static char* shas[] = {
				"dab286035f38f3498e0c174bfb5a0d0ea7905666",
				"b6392ceaba9ec878f67a0207d85e4359c3ab0bfe",
				"dec5842d07bbd00edf564fe27c14118ec9ecc77f"
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
			static char* names[] = { "1.testfile", "2.testfile", "3.testfile" };
			static char* shas[] = {
				"c19325315346b44052892afce0bbd26ed507329fa1dae993e275a6b678c2fd77",
				"89dc7fd8d628ab7771a9704dda7d548ba42ef1382c5acec4a08f663fc5105f6f",
				"704138bec89cf9e7f00fbce100dbc09cf133d16dc0203806392f0e153c43c68c"
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
			DES::DesKeySchedule(&key, &key_set);
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
			DES::DesEncrypt(message, sz, result, key);
			DES::DesDecrypt(result, sz, decrypted, key);
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
			DES::DesEncrypt(message, sz, round1, key1);
			DES::DesEncrypt(round1, sz, round2, key2);
			uint64_t known_key1 = 0x3132333435363700;
			uint64_t known_key2 = 0x3837363534333200;
			uint64_t result_key1;
			uint64_t result_key2;
			bool res = DES::MITMAttack(
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
};