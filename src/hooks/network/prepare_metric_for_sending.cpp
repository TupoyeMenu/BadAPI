#include "hooking/hooking.hpp"
#include "rage/rlMetric.hpp"


namespace big
{
	bool hooks::prepare_metric_for_sending(rage::json_serializer* serializer, int unk, int time, rage::rlMetric* metric)
	{
		return false;
	}
}
