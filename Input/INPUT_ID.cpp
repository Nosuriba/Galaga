#include <type_traits>
#include "INPUT_ID.h"

INPUT_ID begin(INPUT_ID)
{
	return INPUT_ID::LEFT;
}

INPUT_ID end(INPUT_ID)
{
	return INPUT_ID::MAX;
}

INPUT_ID operator*(INPUT_ID id)
{
	return id;
}

INPUT_ID operator++(INPUT_ID& id)
{
	return id = INPUT_ID(std::underlying_type<INPUT_ID>::type(id) + 1);
}

INPUT_ID operator--(INPUT_ID& id)
{
	return id = INPUT_ID(std::underlying_type<INPUT_ID>::type(id) - 1);
}
