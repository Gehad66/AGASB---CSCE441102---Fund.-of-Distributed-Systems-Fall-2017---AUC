#include "message.h"

Message::Message (int _operation, void *_message, size_t _message_size, int _rpc_id, MessageType _message_type) {
  this->setMessage(_message, _message_size);
  this->setMessageType(_message_type);
  this->setOperation(_operation);
  this->setRPCId(_rpc_id);
}

Message::Message (char *_marshalled_base64) {}

Message::Message (){}

Message::~Message (){}

char* Message::marshal (){}

void* Message::getMessage () const{
  return message;
}

size_t Message::getMessageSize () const {
  return message_size;
}

int Message::getOperation () const{
  return operation;
}

int Message::getRPCId () const{
  return rpc_id;
}

MessageType Message::getMessageType () const{
  return message_type;
}

void Message::setMessage (void *_message, size_t _message_size) {
    this->message_size = _message_size;
    this->message = (void*) new char(_message_size + 1);
    strcpy((char*) this->message, (char*) _message);
}

void Message::setMessageType (MessageType _message_type) {
  this->message_type = _message_type;
}

void Message::setOperation (int _operation){
  this->operation = _operation;
}

void Message::setRPCId(int _rpc_id) {
  this->rpc_id = _rpc_id;
}
