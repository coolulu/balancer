#include "SyncServiceReq.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"
#include "tool/Util.h"

const std::string& SyncServiceReq::s_task_name = "SyncServiceReq";

SyncServiceReq::SyncServiceReq(Proc& proc)
	:	TaskMsgBase(proc, s_task_name, _proc._config.proc.sync_gap)
{
	_ip_info.in_ip = _proc._config.proc.sync_ip;
	_ip_info.in_port = _proc._config.proc.sync_port;
	_ip_info.change();
}

SyncServiceReq::~SyncServiceReq()
{

}

void SyncServiceReq::sync()
{
	_request.reset(new Packet(service::CENTER, 0, 0, 0, 0, _seq_id));
	CenterStack::SyncServiceReq(_request->_body, 
								_proc._sc.get_config_derivative().update_time);
	bool b = _proc._tcp_client_pool.get_client(_ip_info)->send_msg(_request);
	if(b)
	{
		B_LOG_INFO << "send_msg=true, _seq_id=" << _seq_id;
	}
	else
	{
		B_LOG_WARN << "send_msg=false, _seq_id=" << _seq_id;
	}
}

int SyncServiceReq::timeout()
{
	print("SyncServiceReq is timeout");
	return 0;
}

int SyncServiceReq::run(void* p)
{
	if(_code != ::common::SUCCESS)
	{
		return 0;
	}

	const ::google::protobuf::Any& service_msg = _response->_body.service_msg();
	if(service_msg.Is<center::CenterMsg>())
	{
		center::CenterMsg msg;
		service_msg.UnpackTo(&msg);
		if(msg.choice_case() == center::CenterMsg::kSyncServiceRsp)
		{
			const center::SyncServiceRsp& rsp = msg.sync_service_rsp();
			B_LOG_INFO	<< "conf_update_time=" << rsp.conf_update_time()
						<< ", conf_json=" << rsp.conf_json();

			std::string conf_json = rsp.conf_json();
			if(conf_json.empty())
			{
				B_LOG_INFO << "not update conf_json ";
			}
			else
			{
				B_LOG_INFO << "update conf_json, start";
				ServiceConfig sc;
				std::string err = sc.json_to_map(conf_json);
				if(err.empty())
				{
					_proc._sc.assign(sc);
					_proc._sc.get_config_derivative().update_time = rsp.conf_update_time();

					Util::bin_2_file(_proc._config.proc.service_path, conf_json.c_str(), conf_json.size());

					B_LOG_ERROR << "update conf_json, success";
				}
				else
				{
					B_LOG_ERROR << "update conf_json, json_to_map=false, err=" << err;
				}
			}
		}
	}

	return 0;
}



