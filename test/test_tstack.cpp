#include "Stack.h"
#include "gtest/gtest.h"

TEST(TStack, can_create_stack_with_positive_size)
{
  ASSERT_NO_THROW(TStack<int> s(3));
}

TEST(TStack, throws_when_create_stack_with_zero_size)
{
    ASSERT_NO_THROW(TStack<int> s(0));
}

TEST(TStack, throws_when_create_stack_with_negative_size)
{
    ASSERT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, can_create_copied_stack)
{
    TStack<int> s(10);

    ASSERT_NO_THROW(TStack<int> s1(s));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
    TStack<int> s(3);
    
    s.Push(1);
    s.Push(2);
    s.Push(3);

    TStack<int> s1(s);
    
    EXPECT_EQ(s.GetSize(), s1.GetSize());
    EXPECT_EQ(s.GetCount(), s1.GetCount());
    
}

TEST(TStack, copied_stack_has_its_own_memory)
{
    TStack<int> s(3);
    s.Push(1);
    s.Push(2);

    TStack<int> s1(s);
    s1.Pop();

    EXPECT_EQ(s.GetCount(), 2);
    EXPECT_EQ(s1.GetCount(), 1);
}

TEST(TStack, can_get_size_and_count)
{
    TStack<int> s(4);
    EXPECT_EQ(4, s.GetSize());
    EXPECT_EQ(0, s.GetCount());
}

TEST(TStack, can_push_and_pop_element)
{
    TStack<int> s(3);
    s.Push(7);
    s.Push(8);

    EXPECT_EQ(8, s.Pop());
    EXPECT_EQ(7, s.Pop());
}

TEST(TStack, throws_when_pop_from_empty_stack)
{
    TStack<int> s(3);

    ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, throws_when_push_to_full_stack)
{
    TStack<int> s(2);
    s.Push(1);
    s.Push(2);

    ASSERT_ANY_THROW(s.Push(3));
}

TEST(TStack, can_detect_empty_stack)
{
    TStack<int> s(3);
    EXPECT_TRUE(s.IsStackEmpty());

    s.Push(1);
    EXPECT_FALSE(s.IsStackEmpty());
}

TEST(TStack, can_detect_full_stack)
{
    TStack<int> s(2);
    EXPECT_FALSE(s.IsFull());

    s.Push(1);
    EXPECT_FALSE(s.IsFull());

    s.Push(2);
    EXPECT_TRUE(s.IsFull());
}

TEST(TStack, can_assign_stack_to_itself)
{
    TStack<int> s(3);
    s.Push(1);
    s.Push(2);

    ASSERT_NO_THROW(s = s);
    EXPECT_EQ(2, s.GetCount());

}

TEST(TStack, can_assign_stacks_of_equal_size)
{
    TStack<int> s(3);
    TStack<int> s1(3);
    s.Push(1);
    s.Push(2);

    ASSERT_NO_THROW(s1 = s);
    EXPECT_EQ(s.GetCount(), s1.GetCount());
}

TEST(TStack, assign_operator_change_stack_size)
{
    TStack<int> s(3);
    TStack<int> s1(2);
    s1 = s;
    EXPECT_EQ(s1.GetSize(), s.GetSize());
}

TEST(TStack, can_assign_stacks_of_different_size)
{
    TStack<int> s(3);
    TStack<int> s1(2);
    s.Push(1);
    s.Push(2);

    ASSERT_NO_THROW(s1 = s);
    EXPECT_EQ(2, s1.GetCount());
}

TEST(TStack, compare_equal_stacks_return_true)
{
    TStack<int> s(3);
    TStack<int> s1(3);
    s.Push(1);
    s.Push(2);
    s1.Push(1);
    s1.Push(2);

    EXPECT_TRUE(s == s1);
}

TEST(TStack, compare_stack_with_itself_return_true)
{
    TStack<int> s(3);
    s.Push(1);
    s.Push(2);

    EXPECT_TRUE(s == s);
}

TEST(TStack, stacks_with_different_sizes_are_not_equal)
{
    TStack<int> s(3);
    TStack<int> s1(4);

    EXPECT_FALSE(s == s1);
}

TEST(TStack, stacks_with_different_elements_are_not_equal)
{
    TStack<int> s(3);
    TStack<int> s1(3);
    s.Push(1);
    s1.Push(2);

    EXPECT_FALSE(s == s1);
}

TEST(TStack, can_resize_stack_to_larger)
{
    TStack<int> s(2);
    s.Push(1);
    s.Push(2);

    ASSERT_NO_THROW(s.ReSize(4));
    EXPECT_EQ(4, s.GetSize());
    EXPECT_EQ(2, s.GetCount());

    EXPECT_EQ(2, s.Pop());
    EXPECT_EQ(1, s.Pop());
}

TEST(TStack, can_resize_stack_to_smaller)
{
    TStack<int> s(4);
    s.Push(1);
    s.Push(2);

    ASSERT_NO_THROW(s.ReSize(2));
    EXPECT_EQ(2, s.GetSize());
    EXPECT_EQ(2, s.GetCount());
}

TEST(TStack, throws_when_resize_to_negative_size)
{
    TStack<int> s(3);
    ASSERT_ANY_THROW(s.ReSize(-1));
}