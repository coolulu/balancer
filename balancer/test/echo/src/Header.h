#pragma once

class Header
{
public:
	Header()
		:	head(0),
			len(0),
			version(0),
			service_id(0),
			from_id(0),
			app_id(0),
			session_id(0),
			data(nullptr),
			crc(0){}

	~Header(){}

public:
	unsigned int	head;      
	unsigned int	len;
	unsigned short	version;
	unsigned short	service_id; 
	unsigned short	from_id;    
	unsigned int	app_id;     
	unsigned int	session_id; 
	unsigned char*	data;   
	unsigned int	crc;       


};