//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKASKMESSAGE_H
#define BLOCK_CHAIN_BLOCKASKMESSAGE_H


#include "Message.h"

/**
 *  @class BlockAskMessage "block_chain/kernel/messages/BlockAskMessage.h"
 *  A message to ask a missing block
 *  @see Message
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class BlockAskMessage: public Message
{
    friend class BlockAskParser;
public:
    BlockAskMessage();

    /**
     *  Creates a request for a missing block
     *  Calls the super constructor with the type value
     *  @see Message::ASK_BLOCK
     *
     *  @param p The peer string representation
     *  @param f The fingerprint of the missing block
     */
    BlockAskMessage(std::string p, std::string f);
    ~BlockAskMessage() override;
    Element* toElement() const override;
protected:
    void fromElement(ElementObject* element, const Serializer* serializer, const char* encoding) override;

private:

    /**
     *  The peer to send the block to
     */
    std::string peer;

    /**
     *  The fingerprint of the needed block
     */
    std::string fingerprint;
};

#endif //BLOCK_CHAIN_BLOCKASKMESSAGE_H
