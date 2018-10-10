#include "PutLoad.h"
#include "log/Log.h"
#include "Proc.h"
#include "protocol/Protocol.h"
#include "define.h"

PutLoad::PutLoad(Proc& proc)
	:	_proc(proc),
		_trigger_count(0),
		_sync_time(::time(nullptr))
{

}

PutLoad::~PutLoad()
{

}

void PutLoad::trigger_sync_count()
{
	if(_proc._owner.is_inservice() && _proc._is.is_ok())	// ��������״̬ �� ��������ok
	{
		if((++_trigger_count % _proc._config.proc.put_load_sync_count) == 0)
		{
			B_LOG_INFO << "PutLoad is broadcast, _trigger_count=" << _trigger_count;
			broadcast();
		}
	}
}

void PutLoad::check_sync_gap()
{
	if( _proc._owner.is_inservice() && _proc._is.is_ok())	// ��������״̬ �� ��������ok
	{
		unsigned int now = ::time(nullptr);
		if(now - _sync_time >= _proc._config.proc.put_load_sync_gap)
		{
			_sync_time = now;

			B_LOG_INFO << "PutLoad is broadcast, _sync_time=" << _sync_time;
			broadcast();
		}
	}
}

void PutLoad::broadcast()
{
	InserviceList* p = _proc._is.get_inservice_list(service::NAVIGATE);	// p�����ͷ�
	if(p == nullptr)
	{
		B_LOG_WARN << "InserviceList is null, _service_id=" << service::NAVIGATE;
		return;
	}

	// ����req�����᷵����Ӧ�����ü��붨ʱ��
	PacketPtr packet_ptr_req(new Packet(service::NAVIGATE, 0, 0, 0, 0, _proc._seq.make_seq()));
	NavigateStack::PutLoadReq(packet_ptr_req->_body, 
							  Define::service_id, 
							  _proc._owner._proc_id,
							  _proc._gate_server.conn_size());
	// �㲥
	for(auto& ip_info : p->inservice_list)
	{	
		_proc._tcp_client_pool.get_client(ip_info)->send_msg(packet_ptr_req);
	}
}
