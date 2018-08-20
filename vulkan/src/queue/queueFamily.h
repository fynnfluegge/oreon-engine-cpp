#pragma once

class QueueFamily {

public:
	int getIndex() const;
	int getCount() const;
	int getFlags() const;
	int getPresentFlag() const;

private:
	int index;
	int count;
	int flags;
	int presentFlag;
};
