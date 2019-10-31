
#ifndef ID_H
#define ID_H

typedef unsigned int Bitset;

class ID
{
public:
	explicit ID(const Bitset& id = 0);
	~ID() {};

	bool operator == (const ID& r_value) const;
	bool operator != (const ID& r_value) const;

	bool operator < (const ID& r_value) const;
	bool operator > (const ID& r_value) const;
	bool operator <= (const ID& r_value) const;
	bool operator >= (const ID& r_value) const;

	ID operator ~() const;
	ID operator &(const ID& r_value) const;
	ID operator |(const ID& r_value) const;
	ID operator ^(const ID& r_value) const;

	ID operator<<(const int& shift) const;
	ID operator>>(const int& shift) const;

	Bitset GetValue() const;
	
private:
	Bitset _id;
};

#endif // ID_H