#ifndef MESSAGE_H
#define MESSAGE_H
#include <string.h>

enum MessageType { Request, Reply };

class Message
{
private:
  void *message;
  size_t message_size;
  MessageType message_type;
  int operation;
  int rpc_id;
public:
  Message();
  Message (int _operation, void *_message, size_t _message_size,
	   int _rpc_id, MessageType _message_type);
  Message (char *_marshalled_base64);
   ~Message ();
  char *marshal ();

  void *getMessage () const;
  size_t getMessageSize () const;
  MessageType getMessageType () const;
  int getOperation () const;
  int getRPCId () const;

  void setMessage (void *_message, size_t _message_size);
  void setMessageType (MessageType _message_type);
  void setOperation (int _operation);
  void setRPCId(int _rpc_id);
};
#endif // MESSAGE_H
