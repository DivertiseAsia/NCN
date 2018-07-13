//
// Created by default on 25/4/2561.
//

#ifndef BLOCK_CHAIN_CRYPTOGRAPHY_H
#define BLOCK_CHAIN_CRYPTOGRAPHY_H

#include <string>
#include <functional>
#include <map>

/**
 *  @class Cryptography "block_chain/algorithm/cryptography/Cryptography.h"
 *  An abstract class for cryptography.
 *  It is used to crypt transaction to be
 *  sure the transaction is correct
 *
 *  @author Mathieu Lochet
 *  @version 2
 */
class Cryptography {
public:

    /**
     *  The ID for the RSA cryptography
     */
    static const int CRYPTOGRAPHY_RSA;

    /**
     *  A default constructor
     */
    Cryptography() = default;

    /**
     *  A default destructor
     */
    virtual ~Cryptography() = default;

    /**
     *  Creates the cryptography object with a given public key.
     *
     *  @param key The known public key
     */
    virtual void set_public_key(std::string key) = 0;

    /**
     *  Encrypt a message using private key
     *
     *  @param message The message to encrypt
     *  @return The encrypted message
     */
    virtual std::string encrypt(std::string message) = 0;

    /**
     *  Decrypt a message using private key
     *
     *  @param message The message to decrypt
     *  @param size The size of the message to decrypt
     *  @return The decrypted message
     */
    virtual std::string decrypt(std::string message, unsigned long size) = 0;

    /**
     *  Get the public key
     *
     *  @return The public key
     */
    virtual std::string getPublicKey() = 0;

    /**
     *  Generates new RSA key and writes it into a file
     *
     *  @param private_file The file in which to write the private key
     *  @param public_file The file in which to write the public key
     */
    virtual void generate(const char* private_file, const char* public_file) = 0;

    /**
     *  Read the key from files
     *
     *  @param private_file The file in which to read the private key
     *  @param public_file The file in which to read the public key
     */
    virtual bool backup(const char* private_file, const char* public_file) = 0;

    /**
     *  Allows the user to add its own cryptography into the system
     *
     *  @param id The cryptography id
     *  @param crypto The lambda expression that creates a cryptography
     */
    static void add_cryptography(int id, std::function<Cryptography*()> crypto);

    /**
     *  Generates a Cryptography object for a given id
     *
     *  @param type The cryptography id
     *  @return The created cryptography object
     */
    static Cryptography* generate(int type);

    /**
     *  Generates a Cryptography object for a given id and a public key
     *
     *  @param type The cryptography id
     *  @param key The public key
     *  @return The created cryptography object
     */
    static Cryptography* generate(int type, std::string key);

private:
    /**
     *  The list of all known cryptography methods
     */
    static std::map<int, std::function<Cryptography*()>> cryptography;
};


#endif //BLOCK_CHAIN_CRYPTOGRAPHY_H
