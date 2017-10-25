#include "Message.h"

void* Message::getMessage () {
  return message;
}

size_t Message::getMessageSize () {
  return message_size;
}

char* Message::marshal (){}

int Message::getOperation (){
  return operation;
}

int Message::getRPCId (){
  return rpc_id;
}

MessageType Message::getMessageType () {
  return message_type;
}

void Message::setOperation (int _operation){
}

void Message::setMessage (void *message, size_t message_size) {
    this->message_size = message_size;
    this->message = (void*) new char(message_size + 1);
    strcpy((char*) this->message, (char*) message);
}

void Message::setMessageType (MessageType message_type) {
  this->message_type = message_type;
}

Message::Message (int operation, void *p_message, size_t p_message_size, int p_rpc_id) {
  if (message_size) {
    rpc_id = p_rpc_id;
    operation = operation;
    setMessage(p_message, p_message_size);
  }
}

Message::~Message (){}
