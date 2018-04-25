//
// Created by default on 25/4/2561.
//

#ifndef BLOCK_CHAIN_HASH_H
#define BLOCK_CHAIN_HASH_H

#include <string>
#include <functional>
#include "../../kernel/components/Component.h"

/**
 *  @class Hash "block_chain/algorithm/hash/Hash.h"
 *  An abstract class for hash, need to be implemented
 *
 *  @author Mathieu Lochet
 *  @version 3
 */
class Hash {
public:

    /**
     *  The ID for the md5 hash
     */
    static const int HASH_MD5;

    /**
     *  Get the hash object used by the block chain
     *
     *  @return The Hash object used to hash values
     */
    static Hash* get_hash();

    /**
     *  Set the used Hash for the block chain
     *
     *  @param h The hash to use
     */
    static void set_hash(Hash* h);

    /**
     *  A method that hash the two parameters together
     *
     *  @param hash1 First element to hash
     *  @param value Second element to hash
     *  @return The generated hash
     */
    virtual std::string generate_hash(std::string hash1, double value) = 0;

    /**
     *  A method that hash the two parameters together
     *
     *  @param hash1 First element to hash
     *  @param value Second element to hash
     *  @return The generated hash
     */
    virtual std::string generate_hash(std::string hash1, int value) = 0;

    /**
     *  A method that hash the two parameters together
     *
     *  @param hash1 First element to hash
     *  @param value Second element to hash
     *  @return The generated hash
     */
    virtual std::string generate_hash(std::string hash1, long long int value) = 0;

    /**
     *  A method that hash the two parameters together
     *
     *  @param hash1 First element to hash
     *  @param value Second element to hash
     *  @return The generated hash
     */
    virtual std::string generate_hash(std::string hash1, std::string value) = 0;

    /**
     *  A method that hash a string value
     *
     *  @param value Element to Hash
     *  @return The generated hash
     */
    virtual std::string generate_hash(std::string value) = 0;

    /**
     *  A method that Hash a component object
     *
     *  @param component The component to hash
     *  @param serializer The serializer to serialize the component
     *  @param encoding The encoding to serialize the component
     *  @return The generated hash
     */
    virtual std::string generate_hash(const Component* component, const Serializer* serializer, const char* encoding) = 0;
    /**
     *  A default constructor
     */
    Hash();

    /**
     *  Allows the user to add its own hash into the system
     *
     *  @param id The proof id
     *  @param hash The lambda expression that creates a proof
     */
    static void add_hash(int id, std::function<Hash*()> hash);

    /**
     *  Generates a hash for a given id
     *
     *  @param type The hash id
     *  @return The created hash object
     */
    static Hash* generate(int type);
private:
    static Hash* HASH;

    /**
     *  The list of all known hash methods
     */
    static std::map<int, std::function<Hash*()>> hash;
};


#endif //BLOCK_CHAIN_HASH_H
