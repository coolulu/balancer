#pragma once

class Owner
{
public:
	Owner();
	~Owner();

public:
	enum EN_CHANGE
	{
		EN_CHANGE_HEARTBEAT = 10,	// ����״̬�л�������״̬
		EN_CHANGE_INSERVICE	= 20,	// ����״̬�л�������״̬
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
	unsigned short _level;					// �ӹ�center�ĵȼ�
	unsigned int _proc_id;
	unsigned int _state;					// ����״̬
	unsigned int _owner_hb_time;			// �ӹ�center������������ʱ��
	unsigned int _expire_second;			// �ӹ�center�ĵ�������������ǰʱ��ͽӹ�center������������ʱ�����������
	unsigned long long _conf_update_time;	// ���ø��µ�ʱ��
	unsigned long long _msg_seq_id;			// ���ø��µ�msg_seq_id
};