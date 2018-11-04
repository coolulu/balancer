#include "Seq.h"
#include <ctime>
#include <cstring>

#include "tool/Util.h"

Seq::Seq() : count(0)
{

}

Seq::~Seq()
{

}

unsigned long long Seq::make_seq()
{
	if(false)
	{
		return Util::uiui2ull(::time(nullptr), ++count);
	}
	else
	{
		return ++count;
	}
}