#include "MultiStack.h"
#include "gtest/gtest.h"

TEST(TMultiStack, can_create_multistack_with_positive_length)
{
	ASSERT_NO_THROW(TMultiStack<int> m(10, 3));
}

TEST(TMultiStack, throws_when_create_multistack_with_negative_length)
{
	ASSERT_ANY_THROW(TMultiStack<int> m(-4, 3));
}

TEST(TMultiStack, throws_when_create_multistack_with_negative_stackCount)
{
	ASSERT_ANY_THROW(TMultiStack<int> m(10, -3));
}

TEST(TMultiStack, can_create_copied_multistack)
{
	TMultiStack<int> m(10, 3);
	ASSERT_NO_THROW(TMultiStack<int> m1(m));
}

TEST(TMultiStack, copied_multistack_is_equal_to_source_one)
{
	TMultiStack<int> m(10, 3);
	m.Push(1, 0);
	m.Push(2, 1);
	m.Push(3, 2);

	TMultiStack<int> m1(m);

	EXPECT_EQ(m.GetSize(), m1.GetSize());
	EXPECT_EQ(m.GetStackCount(), m1.GetStackCount());
}

TEST(TMultiStack, copied_multistack_has_its_own_memory)
{
	TMultiStack<int> m(10, 3);
	m.Push(1, 0);
	m.Push(2, 1);

	TMultiStack<int> m1(m);
	m1.Pop(0);

	EXPECT_FALSE(m[0].IsStackEmpty());
	EXPECT_TRUE(m1[0].IsStackEmpty());
}

TEST(TMultiStack, can_get_size_and_stackCount)
{
	TMultiStack<int> m(10, 3);
	EXPECT_EQ(10, m.GetSize());
	EXPECT_EQ(3, m.GetStackCount());
}

TEST(TMultiStack, can_push_and_pop_element_from_some_stack)
{
	TMultiStack<int> m(10, 3);
	m.Push(7, 0);
	m.Push(8, 1);
	m.Push(9, 2);

	EXPECT_EQ(7, m.Pop(0));
	EXPECT_EQ(8, m.Pop(1));
	EXPECT_EQ(9, m.Pop(2));
}


TEST(TMultiStack, throws_when_push_to_wrong_stack_index)
{
	TMultiStack<int> m(10, 3);
	ASSERT_ANY_THROW(m.Push(1, -1));
	ASSERT_ANY_THROW(m.Push(1, 3));
}

TEST(TMultiStack, throws_when_pop_from_wrong_stack_index)
{
	TMultiStack<int> m(10, 3);
	ASSERT_ANY_THROW(m.Pop(-1));
	ASSERT_ANY_THROW(m.Pop(3));
}

TEST(TMultiStack, throws_when_pop_from_empty_stack)
{
	TMultiStack<int> m(10, 3);
	ASSERT_ANY_THROW(m.Pop(0));
}

TEST(TMultiStack, can_detect_empty_stack)
{
	TMultiStack<int> m(10, 3);
	EXPECT_TRUE(m.IsStackEmpty(0));
	EXPECT_TRUE(m.IsStackEmpty(1));
	EXPECT_TRUE(m.IsStackEmpty(2));

	m.Push(1, 0);
	EXPECT_FALSE(m.IsStackEmpty(0));
}

TEST(TMultiStack, can_detect_full_stack)
{
	TMultiStack<int> m(5, 2);

	m.Push(1, 0);
	m.Push(2, 0);

	EXPECT_TRUE(m.IsFull(0));
}

TEST(TMultiStack, repack_when_stack_is_full)
{
	TMultiStack<int> m(6, 3);

	m.Push(1, 0);
	m.Push(2, 0);

	ASSERT_NO_THROW(m.Push(3, 0));

	EXPECT_EQ(3, m.Pop(0));
	EXPECT_EQ(2, m.Pop(0));
	EXPECT_EQ(1, m.Pop(0));
}

TEST(TMultiStack, can_assign_multistacks_of_equal_sizes_and_StackCount)
{
	TMultiStack<int> m(10, 3);
	TMultiStack<int> m1(10, 3);
	m.Push(1, 0);
	m.Push(2, 1);

	ASSERT_NO_THROW(m1 = m);
	EXPECT_EQ(m.GetStackCount(), m1.GetStackCount());
}

TEST(TMultiStack, can_assign_multistacks_of_different_sizes_and_StackCount)
{
	TMultiStack<int> m(10, 3);
	TMultiStack<int> m1(8, 2);
	m.Push(1, 0);
	m.Push(2, 1);

	ASSERT_NO_THROW(m1 = m);
	EXPECT_EQ(3, m1.GetStackCount());
	EXPECT_EQ(10, m1.GetSize());
}

TEST(TMultiStack, compare_equal_multistacks_return_true)
{
	TMultiStack<int> m(10, 3);
	TMultiStack<int> m1(10, 3);
	m.Push(1, 0);
	m.Push(2, 1);
	m1.Push(1, 0);
	m1.Push(2, 1);

	EXPECT_TRUE(m == m1);
}

TEST(TMultiStack, compare_multistack_with_itself_return_true)
{
	TMultiStack<int> m(10, 3);
	m.Push(1, 0);
	m.Push(2, 1);

	EXPECT_TRUE(m == m);
}

TEST(TMultiStack, multistacks_with_different_sizes_are_not_equal)
{
	TMultiStack<int> m(10, 3);
	TMultiStack<int> m1(8, 3);

	EXPECT_FALSE(m == m1);
}

TEST(TMultiStack, multistacks_with_different_stackCount_are_not_equal)
{
	TMultiStack<int> m(10, 3);
	TMultiStack<int> m1(10, 2);

	EXPECT_FALSE(m == m1);
}

//TEST(TMultiStack, can_resize_multistack_to_larger)
//{
//	TMultiStack<int> m(6, 2);
//	m.Push(1, 0);
//	m.Push(2, 0);
//	m.Push(3, 1);
//	m.Push(4, 1);
//
//	ASSERT_NO_THROW(m.ReSize(10));
//	EXPECT_EQ(10, m.GetSize());
//	EXPECT_EQ(2, m.GetStackCount());
//
//	EXPECT_EQ(2, m.Pop(0));
//	EXPECT_EQ(1, m.Pop(0));
//	EXPECT_EQ(4, m.Pop(1));
//	EXPECT_EQ(3, m.Pop(1));
//}
//
//TEST(TMultiStack, throws_when_resize_to_smaller)
//{
//	TMultiStack<int> m(6, 2);
//	m.Push(1, 0);
//	m.Push(2, 0);
//	m.Push(3, 0);
//	m.Push(4, 1);
//	m.Push(5, 1);
//	m.Push(6, 1);
//
//	ASSERT_ANY_THROW(m.ReSize(5));
//}

