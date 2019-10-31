#include "ID.h"

ID::ID(const Bitset& id): _id(id)
{
}

bool ID::operator == (const ID& r_value) const
{
	return (_id == r_value._id);
}

bool ID::operator != (const ID& r_value) const
{
	return !(_id == r_value._id);
}

bool ID::operator<(const ID & r_value) const
{
	return (_id < r_value._id);
}

bool ID::operator>(const ID & r_value) const
{
	return (_id > r_value._id);
}

bool ID::operator<=(const ID & r_value) const
{
	return (_id <= r_value._id);
}

bool ID::operator>=(const ID & r_value) const
{
	return (_id >= r_value._id);
}

ID ID::operator~() const
{
	return ID(~_id);
}

ID ID::operator&(const ID& r_value) const
{
	return ID(_id & r_value._id);
}

ID ID::operator|(const ID& r_value) const
{
	return ID(_id | r_value._id);
}

ID ID::operator^(const ID& r_value) const
{
	return ID(_id ^ r_value._id);
}

ID ID::operator<<(const int& shift) const
{
	return ID(_id << shift);
}

ID ID::operator>>(const int& shift) const
{
	return ID(_id >> shift);
}

Bitset ID::GetValue() const
{
	return _id;
}