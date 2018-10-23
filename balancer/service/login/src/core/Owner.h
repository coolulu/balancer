#pragma once

class Owner
{
public:
	Owner();
	~Owner();

public:
	enum EN_CHANGE
	{
		EN_CHANGE_HEARTBEAT = 10,	// 上线状态切换到下线状态
		EN_CHANGE_INSERVICE	= 20,	// 下线状态切换到上线状态
	};

public:
	int update_owner_hb_time(unsigned int now, 
							 unsigned short level, 
							 unsigned int state);
	void update_owner(unsigned short level,
					  unsigned int proc_id,
					  unsigned long long conf_update_time,
					  unsigned long long msg_seq_id);

	bool is_inservice();
	bool is_not_inservice();

public:
	unsigned short _level;					// 接管center的等级
	unsigned int _proc_id;
	unsigned int _state;					// 服务状态
	unsigned int _owner_hb_time;			// 接管center最新心跳请求时间
	unsigned int _expire_second;			// 接管center的到期秒数（服务当前时间和接管center最新心跳请求时间相减秒数）
	unsigned long long _conf_update_time;	// 配置更新的时间
	unsigned long long _msg_seq_id;			// 配置更新的msg_seq_id
};