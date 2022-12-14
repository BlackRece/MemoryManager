#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

int testInt(int a, int b) { return a + b; }

namespace IntTest {
	TEST_CLASS(IntTest)
	{
	public:
		TEST_METHOD(IntTestMethod)
		{
			const int a = 1;
			const int b = 2;
			const int expectedResult = a + b;

			Assert::AreEqual(testInt(a, b), expectedResult);
		}
	};
}