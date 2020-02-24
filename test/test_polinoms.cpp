#include "Polinom.h"
#include <gtest.h>


TEST(Polinoms, can_create_polinom)
{
	ASSERT_NO_THROW(Polinom a("2+x^2*y3z4"));
}

TEST(Polinoms, can_push)
{
	Polinom a("2+x");
	a.push(Monom("y"));
	ASSERT_EQ(a, Polinom("2+x+y"));
}

TEST(Polinoms, can_add)
{
	Polinom a("2+x");
	Polinom b("y");
	ASSERT_EQ(a + b, Polinom("2+x+y"));
}

TEST(Polinoms, can_muul)
{
	Polinom a("2+x");
	Polinom b("y");
	ASSERT_EQ(a * b, Polinom("2y+xy"));
}