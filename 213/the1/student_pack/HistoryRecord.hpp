#ifndef _HISTORY_RECORD_H_
#define _HISTORY_RECORD_H_
#include "Entry.hpp"

enum Operation
{
	INSERT,
	DELETE,
	REVERSE,
};

class HistoryRecord 
{
private:
	Entry entry;
	Operation operation;
public:
	/*default constructor*/
	HistoryRecord();
	/*constructor*/
	HistoryRecord(Operation oper, Entry e=Entry());
	/*returns one of the Operations: INSERT, DELETE or DELETE*/
	Operation getOperation() const;
	/*returns the playlist entry for the corresponding history record*/
	Entry getEntry() const;
	/*It was already implemented and you should not edit this method*/
	friend std::ostream &operator<<(std::ostream &out, const HistoryRecord& t);
};

#endif
