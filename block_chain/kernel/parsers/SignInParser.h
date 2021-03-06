//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_SIGNINPARSER_H
#define BLOCK_CHAIN_SIGNINPARSER_H


#include "MessageParser.h"

/**
 *  @class SignInParser "block_chain/kernel/parsers/SignInParser.h"
 *  A message parser linked to a SignInMessage.
 *  @see Message
 *  @see SignInMessage
 *  @see MessageParser
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class SignInParser: public MessageParser {
public:
    void operator()(Message* m, Node* node) const final;
    int get_type() const final;
};

#endif //BLOCK_CHAIN_SIGNINPARSER_H
