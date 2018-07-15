#pragma once

class Owner
{
public:
	Owner();
	~Owner();

public:
	void update_owner_hb_time(unsigned short level, int	state);
	void update_owner(unsigned short level, 
					  unsigned long long conf_update_time,
					  unsigned long long msg_seq_id);

public:
	unsigned short _level;					// 接管center的等级
	unsigned int _state;					// 服务状态
	unsigned int _owner_hb_time;			// 接管center最新心跳请求时间
	unsigned int _expire_second;			// 接管center的到期秒数（服务当前时间和接管center最新心跳请求时间相减秒数）
	unsigned long long _conf_update_time;	// 配置更新的时间
	unsigned long long _msg_seq_id;			// 配置更新的msg_seq_id
};