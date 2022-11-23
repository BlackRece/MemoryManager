#include "pch.h"
#include "CppUnitTest.h"

#include "../MemoryManager/Heap.h"
#include "../MemoryManager/HeapManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HeapManagerTest {
	TEST_CLASS(GivenAHeapManager)
	{
	public:
		TEST_METHOD(WhenGettingAnInitialHeapADefaultHeapIsReturned)
		{
			//Expected values
			const size_t expectedByteCount = 0;
			const std::string expectedTag = "Default";

			Heap* pHeap = HeapManager::getHeap();

			Assert::AreEqual(pHeap->getBytes(), expectedByteCount);
			Assert::AreEqual(pHeap->getTag(), expectedTag);
			Assert::IsNull(pHeap->getNext(), nullptr);
			Assert::IsNull(pHeap->getPrev(), nullptr);
		}
	};
}