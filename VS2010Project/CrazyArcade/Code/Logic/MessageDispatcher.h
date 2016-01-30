#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H
//------------------------------------------------------------------------
//
//  Name:   MessageDispatcher.h
//
//  Desc:   A message dispatcher. Manages messages of the type Telegram.
//          Instantiated as a singleton.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#pragma warning (disable:4786)

#include <set>


#include "Telegram.h"
#include "LGHead.h"
#include "CrudeTimer.h"

class Object;


//to make code easier to read
const double SEND_MSG_IMMEDIATELY = 0.0f;
const int   NO_ADDITIONAL_INFO   = 0;

//to make life easier...
#define Dispatch MessageDispatcher::Instance()


class MessageDispatcher
{
	SINGLETON(MessageDispatcher);
private:  

	//this method is utilized by DispatchMessage or DispatchDelayedMessages.
	//This method calls the message handling member function of the receiving
	//entity, pReceiver, with the newly created telegram
	void Discharge(Object* pReceiver, const Telegram& msg);

public:

	//send a message to another agent. Receiving agent is referenced by ID.
	void DispatchMessage(double  delay,
		int    sender,
		int    receiver,
		int    msg,
		void*  ExtraInfo);

	//send out any delayed messages. This method is called each time through   
	//the main game loop.
	void DispatchDelayedMessages();

private:
	//a std::set is used as the container for the delayed messages
	//because of the benefit of automatic sorting and avoidance
	//of duplicates. Messages are sorted by their dispatch time.
	std::set<Telegram> PriorityQ;

	CrudeTimer* m_GameTimer;
};

#endif