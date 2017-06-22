// 
// 
// 
#include "Print.h";
#include "Messages.h"

template <typename T> Print &operator << (Print &s, T n) { s.print(n); return s; }


extern word FreeMem(void);


TMessage::TMessage()
{
	Message = msg_Empty;
	LoParam = HiParam = 0;
}

TMessage::TMessage(byte msg, word loparam, word hiparam)
{
	Message = msg;
	LoParam = loparam;
	HiParam = hiparam;
}

TMessage::TMessage(byte msg): TMessage(msg,0,0){}

#ifdef DDEBUG

void TMessage::PrintTo(Print &Stream)
{
	Stream << Message << " " << LoParam << " " << HiParam << '\n';
}

#endif // DDEBUG


bool TMessage::operator==(TMessage msg)
{
	return ((Message == msg.Message) AND (LoParam == msg.LoParam) AND (HiParam == msg.HiParam));
}

bool TMessage::operator==(PMessage msg)
{
	return ((Message == msg->Message) AND (LoParam == msg->LoParam) AND (HiParam == msg->HiParam));
}

bool TMessage::operator==(byte msg)
{
	return Message == msg;
}

void TMessageList::DeleteFirst(void)
{
	byte _sreg = SREG;
	cli();
	for (byte i = 1; i < flength; i++) Items[i - 1] = Items[i];
	Items[flength - 1] = NULL;
	if (fcount>0) fcount--;
	SREG = _sreg;
}

bool TMessageList::FindMessage(PMessage msg)
{
	if (msg == NULL) return false;
	for (byte i = 0; i < fcount; i++)
	{
		if ((Items[i] != NULL) AND (*msg == *Items[i])) return true;
	}
	return false;
}

bool TMessageList::Availiable()
{
	return (fcount > 0);
}

TMessage TMessageList::GetMessage()
{
	TMessage msg;
	PMessage pmsg = Items[0];

	if (pmsg != NULL) 
	{
		msg = *pmsg; 
		free(pmsg);
		DeleteFirst();
	}
//	else Serial << "pmsg = NULL\n";
	return msg;
}

TMessageList::TMessageList() : TMessageList(16){}

TMessageList::TMessageList(byte len)
{
	flength = len;
	Items = new PMessage[flength];

	for (byte i = 0; i < len; i++) Items[i] = NULL;
	fcount = 0;
}

TMessageList::~TMessageList()
{
	while (fcount) GetMessage();
	delete[] Items;
}

#ifdef DDEBUG

void TMessageList::PrintOut(Print &stream)
{
	for (byte i = 0; i < length; i++)
	{
		stream << "Address: " << word(Items[i]);
		if (Items[i] == NULL) stream << '\n';
		else stream << ' ' << Items[i]->Message << '\t' << Items[i]->LoParam << '\t' << Items[i]->HiParam << '\n';
	}
}
#endif

bool TMessageList::Add(PMessage msg)
{

	if (msg == NULL) return false;

	if ((fcount<flength) AND (NOT FindMessage(msg)))
	{
		Items[fcount++] = msg;
		return true;
	}
	else
	{
		free(msg);
		return false;
	}

}

bool TMessageList::Add(byte msg, word lo, word hi)
{
	return Add(new TMessage(msg, lo, hi));
}

bool TMessageList::Add(byte msg)
{
	return Add(new TMessage(msg,0,0));
}

bool TMessageList::AddEmpty(void)
{
	return Add(new TMessage());
}

bool TMessageList::Paint(void)
{
	return Add(msg_Paint);
}

bool TMessageList::Error(int errornum)
{
	return Add(msg_Error, errornum, 0);
}


byte TMessageList::Count()
{
	return fcount;
}


TMessageList *MessageList;
