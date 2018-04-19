//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_PARSER_H
#define BLOCK_CHAIN_PARSER_H



class Node;
class Message;
class MessageParser
{
public:
    explicit MessageParser() = default;
    virtual void operator()(Message* m, Node* node) const = 0;
    virtual int get_type() const = 0;
};


#endif //BLOCK_CHAIN_PARSER_H