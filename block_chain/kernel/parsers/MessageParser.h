//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_PARSER_H
#define BLOCK_CHAIN_PARSER_H



class Node;
class Message;

/**
 *  @class MessageParser "block_chain/kernel/parsers/MessageParser.h"
 *  An abstract message parser.
 *  A message parser is linked to a particular type of message.
 *  Its goal is to receive the message, to parse it and to
 *  process it.
 *  @see Message
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class MessageParser
{
public:

    /**
     *  A default constructor: parsers don't need parameters
     */
    explicit MessageParser() = default;

    /**
     *  A default destructor
     */
    virtual ~MessageParser() = default;

    /**
     *  Process the message
     *  @see Message
     *  @see Node
     *
     *  @param m The received message
     *  @param node The peer receiving the message
     */
    virtual void operator()(Message* m, Node* node) const = 0;

    /**
     *  Get the type of message the parser is linked to
     *  @see Message
     */
    virtual int get_type() const = 0;
};


#endif //BLOCK_CHAIN_PARSER_H
