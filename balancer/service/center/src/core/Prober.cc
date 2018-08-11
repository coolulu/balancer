#include "Prober.h"
#include "Proc.h"
#include <ctime>
#include "protocol/Protocol.h"
#include "TaskMsgPool.h"
#include "handle/client/Heartbeat.h"
#include "tool/Util.h"

Prober::Prober(Proc& proc) : _proc(proc)
{

}

Prober::~Prober()
{

}

void Prober::probe()
{
	unsigned long long now_us = Util::get_us();	
	unsigned int t_now = now_us / 1000 / 1000;

	auto& service_map = _proc._sc.get_service_map();
	for(auto it_service_map = service_map.begin(); it_service_map != service_map.end(); it_service_map++)	
	{
		ServiceConfig::Service& service = it_service_map->second;
		unsigned int gap = t_now - service._service_derivative.probe_time;
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
							<< ", probe_time=" << service._service_derivative.probe_time
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
								<< ", probe_time=" << service._service_derivative.probe_time
								<< ", gap=" << gap
								<< ", proc_id=" << ip_info.proc_id
								<< ", proc_des=" << ip_info.proc_des
								<< ", in_ip=" << ip_info.in_ip
								<< ", out_ip=" << ip_info.out_ip
								<< ", port=" << ip_info.port
								<< ", ip=" << ip_info.ip
								<< ", key_ip_port=" << ip_info.key_ip_port;

					Heartbeat* hb = new Heartbeat(_proc,
												  _proc._config.proc.prober_timeout_us,
												  service.service_id,
												  service._service_derivative.update_time,
												  ip_info);
					hb->run();
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
								<< ", probe_time=" << service._service_derivative.probe_time
								<< ", gap=" << gap
								<< ", proc_id=" << ip_info.proc_id
								<< ", proc_des=" << ip_info.proc_des
								<< ", in_ip=" << ip_info.in_ip
								<< ", out_ip=" << ip_info.out_ip
								<< ", port=" << ip_info.port
								<< ", ip=" << ip_info.ip
								<< ", key_ip_port=" << ip_info.key_ip_port;

					Heartbeat* hb = new Heartbeat(_proc,
												  _proc._config.proc.prober_timeout_us,
												  service.service_id,
												  service._service_derivative.update_time,
												  ip_info);
					hb->run();
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
							<< ", probe_time=" << service._service_derivative.probe_time
							<< ", gap=" << gap;
			}

			service._service_derivative.probe_time = t_now;	// 更新最新探测时间
		}
		
	}
}
