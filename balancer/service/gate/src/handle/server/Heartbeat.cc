#include "Heartbeat.h"

#include <sstream> 
#include "log/Log.h"
#include "define.h"
#include "tool/Util.h"

Heartbeat::Heartbeat(Proc& proc,
					 const muduo::net::TcpConnectionPtr& conn, 
					 PacketPtr& packet_ptr, 
					 muduo::Timestamp time)
	:	_proc(proc),
		_conn(conn),
		_packet_ptr(packet_ptr),
		_time(time)
{

}

Heartbeat::~Heartbeat()
{

}

void Heartbeat::handle(const center::CenterMsg& msg)
{
	const center::HeartbeatReq& req = msg.heartbeat_req();
	B_LOG_INFO	<< "level=" << req.level()
				<< ", service_id=" << req.service_id()
				<< ", proc_id=" << req.proc_id()
				<< ", state=" << req.state()
				<< ", conf_update_time=" << req.conf_update_time()
				<< ", conf_json=" << req.conf_json();

	int code = common::SUCCESS;
	if(req.service_id() != Define::service_id)
	{
		code = center::ERR_PROBER_SERVICE_ID;
		B_LOG_ERROR << "unknow service_id=" << req.service_id();
	}
	else
	{
		unsigned int now = ::time(nullptr);
		int ret = _proc._owner.update_owner_hb_time(now, req.level(), req.state());
		if(ret == Owner::EN_CHANGE_INSERVICE)
		{
			// 下线状态切换到上线状态，需要的特殊动作
			B_LOG_ERROR << "state is HEARTBEAT -> INSERVICE";
		}
		else if(ret == Owner::EN_CHANGE_HEARTBEAT)
		{
			// 上线状态切换到下线状态，需要的特殊动作
			B_LOG_ERROR << "state is INSERVICE -> HEARTBEAT";

			// 断开所有client的连接
			_proc._gate_server.shutdown_all_conn();
		}

		if(req.conf_json().size() > 0)
		{
			// 更新配置
			B_LOG_ERROR << "update conf_json, start";

			ServiceConfig sc;
			std::string err = sc.json_to_map(req.conf_json());
			if(err.empty())
			{
				InserviceService is;
				bool b = is.load_ip_info(Define::service_id, sc);
				if(b)
				{
					_proc._sc.assign(sc);
					_proc._is.assign(is);

					_proc._owner.update_owner(req.level(), req.proc_id(), req.conf_update_time(), _packet_ptr->_msg_seq_id);
					_proc._owner.update_owner_hb_time(now, req.level(), req.state());

					save_conf(req);

					B_LOG_ERROR << "update conf_json, success";
				}
				else
				{
					code = center::ERR_PROBER_CONF_LOAD_IP_INFO;
					B_LOG_ERROR << "update conf_json, load_ip_info=false";
				}
			}
			else
			{
				code = center::ERR_PROBER_CONF_JSON_TO_MAP;
				B_LOG_ERROR << "update conf_json, json_to_map=false, err=" << err;
			}
		}
	}

	PacketPtr packet_ptr_rsp(new Packet(_packet_ptr->_from_service_id, 0, _packet_ptr->_app_id, _packet_ptr->_app_version, _packet_ptr->_conn_seq_id, _packet_ptr->_msg_seq_id));
	CenterStack::HeartbeatRsp(packet_ptr_rsp->_body,
							  code,
							  "",
							  _proc._owner._level,
							  req.service_id(),
							  req.proc_id(),
							  _proc._owner._conf_update_time,
							  _proc._owner._expire_second);

	_proc._tcp_server.send_msg(_conn, packet_ptr_rsp);
}

void Heartbeat::save_conf(const center::HeartbeatReq& req)
{
	std::ostringstream oss;
	oss << "req.level=" << req.level() << std::endl
		<< "req.service_id=" << req.service_id() << std::endl
		<< "req.proc_id=" << req.proc_id() << std::endl
		<< "req.state=" << req.state() << std::endl
		<< "req.conf_update_time=" << req.conf_update_time() << std::endl
		<< "req.conf_json=" << req.conf_json() << std::endl
		<< std::endl
		<< "_owner._level=" << _proc._owner._level << std::endl
		<< "_owner._proc_id=" << _proc._owner._proc_id << std::endl
		<< "_owner._state=" << _proc._owner._state << std::endl
		<< "_owner._owner_hb_time=" << _proc._owner._owner_hb_time << std::endl
		<< "_owner._expire_second=" << _proc._owner._expire_second << std::endl
		<< "_owner._conf_update_time=" << _proc._owner._conf_update_time << std::endl
		<< "_owner._msg_seq_id=" << _proc._owner._msg_seq_id << std::endl;

	std::string str = oss.str();
	std::string conf_file = Define::service_name + '_' + std::to_string(_proc._conf_id) + Define::conf_file_postfix;
	Util::bin_2_file(conf_file, str.c_str(), str.size());

	B_LOG_INFO << "conf_file=" << conf_file << ", str=" << str;
}


