# pragma once

class State
{
public:
	State() = default;
	~State() = default;
	virtual void processManeger() = 0;
	virtual void update() = 0;
	virtual void Draw() = 0;
protected:
	virtual void initilaize() = 0;
private:


};