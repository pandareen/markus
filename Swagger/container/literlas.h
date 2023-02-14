#pragma once


constexpr ulong operator"" _B(unsigned long long n)
{
	return  n * 1;
}

constexpr ulong operator"" _KB(unsigned long long n)
{
	return  n * 1000;
}

constexpr ulong operator"" _MB(unsigned long long n)
{
	return  n * 1000_KB;
}

constexpr ulong operator"" _GB(unsigned long long n)
{
	return n * 1000_GB;
}

constexpr ulong operator"" _ms(unsigned long long n)
{
	return  n;
}

constexpr ulong operator"" _s(unsigned long long n)
{
	return  n * 1000;
}

constexpr ulong operator"" _min(unsigned long long n)
{
	return  n * 60_s;
}

constexpr ulong operator"" _h(unsigned long long n)
{
	return n * 60_min;
}
