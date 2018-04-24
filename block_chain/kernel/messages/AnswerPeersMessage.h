//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_ANSWERPEERSMESSAGE_H
#define BLOCK_CHAIN_ANSWERPEERSMESSAGE_H


#include "SignMessage.h"

/**
 *  @class AnswerPeersMessage "block_chain/kernel/messages/AnswerPeersMessage.h"
 *  An answer peers message for sending the peers list
 *  @see SignMessage
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class AnswerPeersMessage: public SignMessage {
public:
    AnswerPeersMessage();

    /**
     *  Creates a answer peers message with a text
     *  Calls the super constructor with the type value
     *  @see Message::ANSWER_PEERS
     *
     *  @param p The list of peers as a string value
     */
    AnswerPeersMessage(std::string p);
};


#endif //BLOCK_CHAIN_ANSWERPEERSMESSAGE_H
