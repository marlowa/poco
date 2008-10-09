//
// CryptoTest.cpp
//
// $Id: //poco/1.3/Crypto/testsuite/src/CryptoTest.cpp#1 $
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "CryptoTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Crypto/CipherFactory.h"
#include "Poco/Crypto/Cipher.h"
#include "Poco/Crypto/CipherKey.h"


using namespace Poco::Crypto;


CryptoTest::CryptoTest(const std::string& name): CppUnit::TestCase(name)
{
}


CryptoTest::~CryptoTest()
{
}


void CryptoTest::testEncoding()
{
	Cipher::Ptr pCipher = CipherFactory::defaultFactory().createCipher(CipherKey("aes256"));

	std::string in("1234567890");
	std::string out = pCipher->encryptString(in, Cipher::ENC_BASE64);
	std::string result = pCipher->decryptString(out, Cipher::ENC_BASE64);
	poco_assert (in == result);
}


void CryptoTest::testEncoding2()
{
	Cipher::Ptr pCipher = CipherFactory::defaultFactory().createCipher(CipherKey("aes256", "simplepwd", "Too much salt"));
	
	std::string in("1234567890");
	std::string out = pCipher->encryptString(in, Cipher::ENC_BASE64);

	Cipher::Ptr pCipher2 = CipherFactory::defaultFactory().createCipher(CipherKey("aes256", "simplepwd", "Too much salt"));
	
	std::string result = pCipher2->decryptString(out, Cipher::ENC_BASE64);
	poco_assert (in == result);
}


void CryptoTest::setUp()
{
}


void CryptoTest::tearDown()
{
}


CppUnit::Test* CryptoTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("CryptoTest");

	CppUnit_addTest(pSuite, CryptoTest, testEncoding);
	CppUnit_addTest(pSuite, CryptoTest, testEncoding2);

	return pSuite;
}