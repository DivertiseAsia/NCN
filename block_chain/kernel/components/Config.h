//
// Created by default on 24/4/2561.
//

#ifndef BLOCK_CHAIN_CONFIG_H
#define BLOCK_CHAIN_CONFIG_H


#include "../../utils/serialization/Serializer.h"
#include "../../chain/block/proof/Proof.h"
#include "../../algorithm/cryptography/Cryptography.h"

/**
 *  @class Config "block_chain/kernel/components/Config.h"
 *  The config is the object that contains all of the important data to run the program.
 *  @see Serializer
 *  @see Reward
 *  @see Proof
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
class Config {
public:

    /**
     *  Read a file and list all the parameters
     *
     *  @param filename The config file. file must be a json file and at the root of the program
     *  @param s The serializer to use
     *  @param p The proof id
     *  @param h The hash id
     *  @param c Thge crypto id
     *  @param r The reward object
     */
    Config(const char* filename, const Serializer* s, Reward* r, int p = Proof::WORK, int h = Hash::HASH_MD5, int c = Cryptography::CRYPTOGRAPHY_RSA);

    /**
     *  Get the encoding value
     *
     *  @return The encoding for serialization
     */
    virtual const char* get_encoding() const;

    /**
     *  Get the serializer
     *
     *  @return The serializer
     */
    virtual const Serializer* get_serializer() const;

    /**
     *  Get the proof object
     *
     *  @return The proof object
     */
    virtual const Proof* get_proof() const;

    /**
     *  Get the reward object
     *
     *  @return The reward object for block validation
     */
    virtual const Reward* get_reward() const;

    /**
     *  Get the port value
     *
     *  @return The port the server needs to listen to
     */
    virtual const int get_port() const;

    /**
     *  Get the crypto value
     *
     *  @return The cryptography id to use
     */
    virtual const int get_crypto() const;

    /**
     *  Is the program in debug mode
     *
     *  @return True if the program runs in debug mode
     */
    virtual const bool is_debug() const;
protected:

    /**
     *  The port the server needs to listen to
     */
    int port;

    /**
     *  The crypto id
     */
    int crypto;

    /**
     *  The encoding for serialization
     */
    std::string encoding;

    /**
     *  The serializer
     */
    const Serializer* serializer;

    /**
     *  The reward object for validation
     */
    Reward* reward;

    /**
     *  The proof object for validation
     */
    Proof* proof;

    /**
     *  Is the program in debug mode
     */
    bool debug;
};


#endif //BLOCK_CHAIN_CONFIG_H
