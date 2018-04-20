#ifndef MESSAGE_H
#define MESSAGE_H

#include"../components/Component.h"
#include <sstream>
#include <fstream>
#include "../../utils/Encoding.h"
#include "../../algorithm/MerkleTree.h"
#include <functional>

/**
 *  An abstract message and a message factory.
 *  A message is a way to ask requests to an other peer.
 *  All different messages have different action on the
 *  current peer.
 *
 *  @author Mathieu Lochet
 *  @version 2
 */
class Message: public Component
{
    public:
        static const int TRANSACTION;
        static const int BLOCK;
        static const int ASK_PEERS;
        static const int ANSWER_PEERS;
        static const int SIGN_IN;
        static const int SIGN_OUT;
        static const int ASK_BLOCK;
        static const int ANSWER_BLOCK;

        /**
         *  A default contructor
         */
        Message();

        /**
         *  A constructor to create a message of a given type
         *
         *  @param i the given type of the message
         */
        explicit Message(int i);

        /**
         *  A default destructor
         */
        ~Message() override;

        /**
         *  The message factory: creates the corresponding type
         *  of message with a given type.
         *  The generated message is empty and needs to be fill.
         *  @see Component::__init__
         *
         *  @param id the given type of the wanted message
         *  @return The type of the message
         */
        static Message* generate(int id);

        /**
         *  Get the type of the message
         *
         *  @return The type of the message
         */
        const int get_type() const;
protected:

        /**
         *  The type of the message
         */
        int type;
};

#endif // MESSAGE_H
