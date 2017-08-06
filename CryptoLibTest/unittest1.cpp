#include "stdafx.h"
#include "CppUnitTest.h"
#include "MD5.h"
#include "SHA1.h"
#include "SHA256.h"
#include "Math.h"
#include "LongMultiplyReference.h"
#include "BigInt.h"

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
			return result;
		}
		TEST_METHOD(BigIntTest)
		{
			BigInt a("1");
			BigInt b("2");
			BigInt c = a + b;
			Assert::AreEqual(c.GetValue().c_str(), "3", "BigInt: add test failed", LINE_INFO());

			a = BigInt(0);
			c = a + 1 + 2 + 3;
			c += BigInt(4);
			((c += 5) += 6) += 7;
			Assert::AreEqual(c.GetValue().c_str(), "28", "BigInt: int add test failed", LINE_INFO());
		}

		TEST_METHOD(MultiplyTest)
		{
			BigInt a("1");
			for (size_t i = 1; i <= 100; i++)
			{
				a *= i;
			}
			Assert::AreEqual(a.GetValue().c_str(), "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000", "BigInt: zero multiply test failed", LINE_INFO());

			for (size_t i = 0; i < 40; i++)
			{
				int length1 = rand() % 300;
				int length2 = rand() % 300;
				char output[200] = { 0 };
				sprintf(output, "#%d Lengths: %d %d", i, length1, length2);
				Logger::WriteMessage(output);

				std::string t1 = GenerateRandomNumber(length1);
				std::string t2 = GenerateRandomNumber(length2);

				number r1(t1);
				number r2(t2);
				r1 *= r2;
				
				BigInt b1(t1);
				BigInt b2(t2);
				BigInt b3;
				try
				{
					b3 = b1 * b2;
				}
				catch (std::exception e)
				{
					char msg[100];
					sprintf(msg, "%d %d\n", b1.GetLength(), b2.GetLength());
					Logger::WriteMessage(msg);
				}
				
				std::string t3 = b3.GetValue();
				std::string r3 = r1.get();

				Assert::AreEqual(t3.c_str(), r3.c_str(), "Multiply of random numbers test fail", LINE_INFO());
			}
		}
	};
}