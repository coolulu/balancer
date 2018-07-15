#include "Prober.h"
#include "Proc.h"
#include <ctime>
#include "protocol/Protocol.h"

Prober::Prober(Proc& proc) : _proc(proc)
{

}

Prober::~Prober()
{

}

void Prober::probe()
{
	unsigned int t_now = ::time(nullptr);
	auto& service_map = _proc._sc.get_service_map();
	for(auto it_service_map = service_map.begin(); it_service_map != service_map.end(); it_service_map++)	
	{
		ServiceConfig::Service& service = it_service_map->second;
		auto p = get_service_probetime(service.service_id);
		unsigned int gap = t_now - p->probe_time;
		if(gap >= service.heartbeat.heartbeat_gap)
		{
			// 间隔时间到，需要发探测心跳
			B_LOG_INFO	<< "-------------------"
						<< "service_id=" << service.service_id 
						<< ", service_name=" << service.service_name
						<< "-------------------";

			if(service.heartbeat.heartbeat_enable)
			{
				std::vector<ServiceConfig::IPInfo>& heartbeat_list = service.heartbeat_list;
				std::vector<ServiceConfig::IPInfo>& inservice_list = service.inservice_list;

				B_LOG_INFO  << "need probe service" 
							<< ", service_id=" << service.service_id
							<< ", service_name=" << service.service_name
							<< ", heartbeat_enable=" << (service.heartbeat.heartbeat_enable ? "true" : "false")
							<< ", heartbeat_gap=" << service.heartbeat.heartbeat_gap
							<< ", t_now=" << t_now
							<< ", probe_time=" << p->probe_time
							<< ", gap=" << gap
							<< ", heartbeat_list.size=" << heartbeat_list.size()
							<< ", inservice_list.size=" << inservice_list.size();

				for(auto it = heartbeat_list.begin(); it != heartbeat_list.end(); it++)
				{
					const ServiceConfig::IPInfo& ip_info = *it;
					B_LOG_INFO  << "probe heartbeat_list" 
								<< ", service_id=" << service.service_id
								<< ", service_name=" << service.service_name
								<< ", heartbeat_enable=" << (service.heartbeat.heartbeat_enable ? "true" : "false")
								<< ", heartbeat_gap=" << service.heartbeat.heartbeat_gap
								<< ", t_now=" << t_now
								<< ", probe_time=" << p->probe_time
								<< ", gap=" << gap
								<< ", proc_id=" << ip_info.proc_id
								<< ", proc_des=" << ip_info.proc_des
								<< ", in_ip=" << ip_info.in_ip
								<< ", out_ip=" << ip_info.out_ip
								<< ", port=" << ip_info.port
								<< ", ip=" << ip_info.ip
								<< ", key_ip_port=" << ip_info.key_ip_port;

					PacketPtr packet_ptr(new Packet(service.service_id, 0, 0, 0, 0, _proc._seq.make_seq()));
					CenterStack::HeartbeatReq(packet_ptr->_body,
											  _proc._config.proc.level,
											  service.service_id,
											  ip_info.proc_id,
											  center::HEARTBEAT,
											  time(NULL), 
											  "");

					_proc._tcp_client_pool.get_client(ip_info)->send_msg(packet_ptr);
				}

				for(auto it = inservice_list.begin(); it != inservice_list.end(); it++)
				{
					const ServiceConfig::IPInfo& ip_info = *it;
					B_LOG_INFO  << "probe inservice_list" 
								<< ", service_id=" << service.service_id
								<< ", service_name=" << service.service_name
								<< ", heartbeat_enable=" << (service.heartbeat.heartbeat_enable ? "true" : "false")
								<< ", heartbeat_gap=" << service.heartbeat.heartbeat_gap
								<< ", t_now=" << t_now
								<< ", probe_time=" << p->probe_time
								<< ", gap=" << gap
								<< ", proc_id=" << ip_info.proc_id
								<< ", proc_des=" << ip_info.proc_des
								<< ", in_ip=" << ip_info.in_ip
								<< ", out_ip=" << ip_info.out_ip
								<< ", port=" << ip_info.port
								<< ", ip=" << ip_info.ip
								<< ", key_ip_port=" << ip_info.key_ip_port;

					PacketPtr packet_ptr(new Packet(service.service_id, 0, 0, 0, 0, _proc._seq.make_seq()));
					CenterStack::HeartbeatReq(packet_ptr->_body,
											  _proc._config.proc.level,
											  service.service_id,
											  ip_info.proc_id,
											  center::HEARTBEAT,
											  time(NULL), 
											  "");

					_proc._tcp_client_pool.get_client(ip_info)->send_msg(packet_ptr);
				}
			}
			else
			{
				B_LOG_INFO  << "not probe service" 
							<< ", service_id=" << service.service_id
							<< ", service_name=" << service.service_name
							<< ", heartbeat_enable=" << (service.heartbeat.heartbeat_enable ? "true" : "false")
							<< ", heartbeat_gap=" << service.heartbeat.heartbeat_gap
							<< ", t_now=" << t_now
							<< ", probe_time=" << p->probe_time
							<< ", gap=" << gap;
			}

			p->probe_time = t_now;	// 更新最新探测时间
		}
		
	}
}

Probetime* Prober::get_service_probetime(unsigned short service_id)
{
	auto it = _service_probetime_map.find(service_id);
	if(it == _service_probetime_map.end())
	{
		Probetime pt(service_id);
		_service_probetime_map.insert(std::make_pair(pt.service_id, pt));
		return get_service_probetime(service_id);
	}

	return &it->second;
}
