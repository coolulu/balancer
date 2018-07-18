#include "Owner.h"

#include "protocol/protobuf/proto_cpp/center.pb.h"

Owner::Owner()
	:	_level(center::INIT_LEVEL),
		_state(center::STATE_BEGIN),
		_owner_hb_time(::time(nullptr)), // 如果初始化为0，会导致程序启动时，配置下发两次
		_expire_second(0),
		_conf_update_time(0),
		_msg_seq_id(0)
{

}

Owner::~Owner()
{

}

void Owner::update_owner_hb_time(unsigned int now, 
								 unsigned short level, 
								 unsigned int state)
{
	_expire_second = now - _owner_hb_time;
	if(level == _level)
	{
		_owner_hb_time = now;
		_state = state;
	}
}

void Owner::update_owner(unsigned short level, 
						 unsigned long long conf_update_time,
						 unsigned long long msg_seq_id)
{
	_level = level;
	_conf_update_time = conf_update_time;
	_msg_seq_id = msg_seq_id;
}
