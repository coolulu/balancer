#include "Synchro.h"
#include "log/Log.h"
#include "Proc.h"
#include "handle/client/SyncServiceReq.h"

Synchro::Synchro(Proc& proc)
	:	_proc(proc),
		_sync_time(0)
{

}

Synchro::~Synchro()
{

}

void Synchro::check_sync()
{
	if(_proc._config.proc.sync)
	{
		unsigned int t_now = ::time(nullptr);
		if(t_now - _sync_time >= _proc._config.proc.sync_gap)
		{
			SyncServiceReq* req = new SyncServiceReq(_proc);
			req->sync();
			_proc._task_msg_pool.add(req);

			_sync_time = t_now;
		}
	}
}

