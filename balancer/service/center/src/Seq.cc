#include "Seq.h"
#include <ctime>
#include <cstring>

#include "Util.h"

Seq::Seq() : count(0)
{

}

Seq::~Seq()
{

}

unsigned long long Seq::make_seq()
{
	if(0)
	{
		/*
		++count;
		unsigned int t = ::time(nullptr);

		unsigned long long seq = EN_SEQ_NULL;	
		memcpy((char*)&seq, (char*)&count, sizeof(count));
		memcpy((char*)&seq + sizeof(count), (char*)&t, sizeof(t));

		return seq;
		*/

		return Util::uiui2ull(::time(nullptr), ++count);
	}
	else
	{
		/*
		++count;

		unsigned long long seq = EN_SEQ_NULL;	
		memcpy((char*)&seq, (char*)&count, sizeof(count));

		return seq;
		*/

		return Util::uiui2ull(0, ++count);
	}
}