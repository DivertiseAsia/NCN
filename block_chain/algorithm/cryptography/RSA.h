#ifndef BLOCK_CHAIN_RSA_H
#define BLOCK_CHAIN_RSA_H
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/engine.h>
#include <fstream>
#include <cstring>
#include "Cryptography.h"
#include <iostream>
/**
 *  @class RSA_Cryptography "block_chain/algorithm/cryptography/RSA.h"
 *  A class for RSA cryptography, based on OpenSLL
 *
 *  @author Mathieu Lochet
 *  @version 2
 */
class RSA_Cryptography:public Cryptography {
    public:
        /**
         *  A default constructor initializing the size of the key
         */
        RSA_Cryptography();

        void set_public_key(std::string key) override;

        std::string encrypt(std::string message) override;

        std::string decrypt(std::string message, int size) override;

        /**
         *  Write a key inside a file
         *
         *  @param fun The function that will choose which key to write
         *  @param file The file name
         */
        void write(void(* fun)(BIO*, RSA*), std::string file);

        std::string getPublicKey() override;

        void generate(const char* private_file, const char* public_file) override;

        bool backup(const char* private_file, const char* public_file) override;

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
