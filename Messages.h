#pragma  once
#include "arduino.h"
#include "Print.h"
#include "DEF_Message.h"

#define AND &&
#define OR  ||
#define NOT !

//using PEventFunc = void(*)(int, int);


struct TMessage;
using  PMessage = TMessage *;

struct TMessage
{
public:
	byte   Message;
	word   LoParam;
	word   HiParam;

	TMessage();
	TMessage(byte msg, word loparam, word hiparam = 0);
	TMessage(byte msg);

	bool operator ==(TMessage msg);
	bool operator ==(PMessage msg);
	bool operator ==(byte msg);

#ifdef DDEBUG
	void PrintTo(Print &Stream);
#endif // DDEBUG
};

class TMessageList
{
private:
	PMessage *Items;

	byte     flength;
	byte     fcount;
	void     DeleteFirst(void);
	bool	 FindMessage(PMessage msg);  //есть ли такое сообщение в очереди
public:

	TMessageList();
	TMessageList(byte length);
	~TMessageList();



	bool Availiable();                 // проверка, что очередь сообщений не пуста

	TMessage GetMessage();

	bool Add(PMessage msg);
	bool Add(byte msg, word lo, word high);
	bool Add(byte msg);
	bool AddEmpty(void);
	bool Paint(void);
	bool Paint(int objptr, int param) { return Add(msg_Paint, objptr, param); }
	bool Error(int errornum);
	bool Error() { return Add(msg_Error); }

	byte Count();

#ifdef DDEBUG
	void PrintOut(Print &stream);
#endif // DDEBUG

};

extern TMessageList      *MessageList;
