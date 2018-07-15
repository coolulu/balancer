#pragma once

class Seq
{
public:
	Seq();
	~Seq();

public:
	enum EN_SEQ
	{
		EN_SEQ_NULL	= 0,
	};

public:
	unsigned long long make_seq();

private:
	unsigned int count;
};