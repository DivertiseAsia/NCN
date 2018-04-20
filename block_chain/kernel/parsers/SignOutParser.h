//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_SIGNOUTPARSER_H
#define BLOCK_CHAIN_SIGNOUTPARSER_H


#include "MessageParser.h"
#include <algorithm>

/**
 *  A message parser linked to a SignOutMessage.
 *  @see Message
 *  @see SignOutMessage
 *  @see MessageParser
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class SignOutParser: public MessageParser {
public:
    void operator()(Message* m, Node* node) const final;
    int get_type() const final;
};


#endif //BLOCK_CHAIN_SIGNOUTPARSER_H
