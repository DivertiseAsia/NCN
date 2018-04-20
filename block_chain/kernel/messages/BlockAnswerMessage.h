//
// Created by default on 19/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCKANSWERMESSAGE_H
#define BLOCK_CHAIN_BLOCKANSWERMESSAGE_H


#include "Message.h"

/**
 *  An answer containing the required block
 *  @see Message
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class BlockAnswerMessage: public Message
{
    friend class BlockAnswerParser;
public:
    BlockAnswerMessage();

    /**
     *  Creates an answer to a block request
     *  Calls the super constructor with the type value
     *  @see Message::ANSWER_BLOCK
     *
     *  @param p The serialized block
     */
    BlockAnswerMessage(std::string p);
    ~BlockAnswerMessage() override;
    Element* toElement() const override;
protected:
    void fromElement(ElementObject*, const Serializer* serializer, const char* encoding) override;

private:

    /**
     * The serialized required block
     */
    std::string block;
};



#endif //BLOCK_CHAIN_BLOCKANSWERMESSAGE_H
