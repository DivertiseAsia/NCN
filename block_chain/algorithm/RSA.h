#ifndef BLOCK_CHAIN_RSA_H
#define BLOCK_CHAIN_RSA_H
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <fstream>
#include <cstring>

/**
 *  A class for RSA cryptography, based on OpenSLL
 *
 *  @author Mathieu Lochet
 *  @version 2
 */
class RSA_Cryptography {
    public:
        /**
         *  A default constructor initializing the size of the key
         */
        RSA_Cryptography();

        /**
         *  A constructor with a given public key. It creates an
         *  object that can decrypt or encrypt using public key
         *
         *  @param key The known public key
         */
        explicit RSA_Cryptography(std::string key);

        /**
         *  Encrypt a message using private key
         *
         *  @param message The message to encrypt
         *  @return The encrypted message
         */
        std::string encrypt(std::string message);

        /**
         *  Decrypt a message using private key
         *
         *  @param message The message to decrypt
         *  @param size The size of the message to decrypt
         *  @return The decrypted message
         */
        std::string decrypt(std::string message, int size);

        /**
         *  Write a key inside a file
         *
         *  @param fun The function that will choose which key to write
         *  @param file The file name
         */
        void write(void(* fun)(BIO*, RSA*), std::string file);

        /**
         *  Get the public key
         *
         *  @return The public key
         */
        std::string getPublicKey();

        /**
         *  Get the private key
         *
         *  @return The private key
         */
        std::string getPrivateKey();

        /**
         *  Generates new RSA key and writes it into a file
         *
         *  @param private_file The file in which to write the private key
         *  @param public_file The file in which to write the public key
         */
        void generate(const char* private_file, const char* public_file);

        /**
         *  Read the key from files
         *
         *  @param private_file The file in which to read the private key
         *  @param public_file The file in which to read the public key
         */
        bool backup(const char* private_file, const char* public_file);

        /**
         *  Frees RSA key ressources
         */
        virtual ~RSA_Cryptography();
    private:

        /**
         *  The real rsa object containing the keys
         */
        RSA* rsa;

        /**
         *  The size of the RSA key
         */
        int size;
};

#endif // BLOCK_CHAIN_RSA_H
