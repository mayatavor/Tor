#pragma once

class IDataAccess
{
public:
	virtual ~IDataAccess() = default;

	virtual bool open() = 0;
	virtual void close() = 0;
	virtual void clear() = 0;

private:

};

