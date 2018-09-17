#include "TaskMsgSub.h"

#include "core/Proc.h"
#include "core/TaskMsgMaster.h"
#include "tool/Util.h"

TaskMsgSub::TaskMsgSub(Proc& proc, const std::string& task_name, unsigned int gap_us,
					   unsigned short depend_service_id, 
					   unsigned int proc_id,
					   TaskMsgMaster* p_task_msg_master)
	:	TaskMsgBase(proc, task_name, gap_us),
		_depend_service_id(depend_service_id),
		_proc_id(proc_id),
		_p_task_msg_master(p_task_msg_master)
{
	_state = EN_STATE_REQUEST;
}

TaskMsgSub::~TaskMsgSub()
{
	_p_task_msg_master = nullptr; // �����ͷ�
}

int TaskMsgSub::timeout()
{
	// timeout���غ�����㺯���ͷ�
	_p_task_msg_master->sub_remove(_seq_id);	//��������ɣ��Ͽ������������ϵ
	int ret = _p_task_msg_master->timeout_by_sub(*this);	//�����񴥷�������ʱ����	
	if(ret != 0)
	{
		print("on timeout, del master task");

		// ɾ��������,ͬʱ����ʣ���������ɾ��
		_proc._task_msg_pool.del(_p_task_msg_master->_seq_id);
		_p_task_msg_master = nullptr;
	}
	else
	{
		print("on timeout");
	}
}

int TaskMsgSub::run(void* p)
{
	switch (_state)
	{
	case EN_STATE_REQUEST:
		{
			_state = EN_STATE_RESPONSE;
			_begin_time_us = Util::get_us();

			bool b = false;
			if(_proc_id == 0)
			{
				b = _proc._is.get_ip_info(_depend_service_id, _ip_info);	// ��ѯ
			}
			else
			{
				b = _proc._is.get_ip_info(_depend_service_id, _proc_id, _ip_info);	// ָ��proc_id
			}
				
			if(b)
			{
				bool is_send = _proc._tcp_client_pool.get_client(_ip_info)->send_msg(_request);
				if(is_send)
				{
					B_LOG_INFO << "send_msg=true, _seq_id=" << _seq_id;
				}
				else
				{
					B_LOG_WARN << "send_msg=false, _seq_id=" << _seq_id;
				}
			}
			else
			{
				B_LOG_ERROR << "get_ip_info not find"
							<< ", _depend_service_id=" << _depend_service_id
							<< ", _proc_id=" << _proc_id;
			}

			if(_gap_us != 0)	// ��ʱʱ�䲻Ϊ0�����붨ʱ��
			{
				_proc._task_msg_pool.add(this);
			}
		}
		break;

	case EN_STATE_RESPONSE:
		{
			// rsp���غ�����㺯���ͷ�
			_end_time_us = Util::get_us();
			_delay_us = _end_time_us - _begin_time_us;

			_p_task_msg_master->sub_remove(_seq_id);	//��������ɣ��Ͽ������������ϵ
			int ret = _p_task_msg_master->run(this);
			if(ret != 0)
			{
				print("on response, del master task");

				// ɾ��������,ͬʱ����ʣ���������ɾ��
				_proc._task_msg_pool.del(_p_task_msg_master->_seq_id);
				_p_task_msg_master = nullptr;
			}
			else
			{
				print("on response");
			}
		}
		break;

	default:
		B_LOG_ERROR	<< "state is unknow, _state=" << _state;
		break;
	}

	return 0;
}

void TaskMsgSub::print(const std::string& prefix)
{
	_p_task_msg_master->print(prefix);
	::TaskMsgBase::print(prefix);	
	B_LOG_INFO	<< "_depend_service_id=" << _depend_service_id
				<< ", _proc_id=" << _proc_id
				<< ", _ip_info.proc_id=" << _ip_info.proc_id
				<< ", _ip_info.proc_des=" << _ip_info.proc_des
				<< ", _ip_info.in_ip=" << _ip_info.in_ip
				<< ", _ip_info.in_port=" << _ip_info.in_port
				<< ", _ip_info.out_ip=" << _ip_info.out_ip
				<< ", _ip_info.out_port=" << _ip_info.out_port;
}
