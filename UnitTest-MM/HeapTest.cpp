#include "pch.h"
#include "CppUnitTest.h"

#include "../MemoryManager/Heap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HeapTest {
	TEST_CLASS(GivenAHeap)
	{
	public:
		//TEST_METHOD(TheReturnedHeapIsInitialisedWithExpectedValues)
		TEST_METHOD(TheReturnedHeap)
		{
			//Expected values
			const size_t expectedByteCount = 0;
			const std::string expectedTag = "Default";
			
			//Heap pHeap = Heap();
			//Assert::AreEqual(pHeap.getBytes(), expectedByteCount);
			//Assert::AreEqual(pHeap.getTag(), expectedTag);
			//Assert::IsNull(pHeap.getNext(), nullptr);
			//Assert::IsNull(pHeap.getPrev(), nullptr);
		}
	};
}