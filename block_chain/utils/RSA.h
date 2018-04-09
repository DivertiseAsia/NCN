#ifndef RSA_H
#define RSA_H
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <fstream>
#include <cstring>

class RSA_Cryptography {
    public:
        RSA_Cryptography();
        RSA_Cryptography(std::string filename);
        std::string encrypt(std::string message);
        std::string decrypt(std::string message, int size);
        void write(void(* fun)(BIO*, RSA*), std::string file);
        std::string getPublicKey();
        std::string getPrivateKey();
        void generate();
        bool backup();
        virtual ~RSA_Cryptography();
        RSA* rsa;

    protected:

    private:
        char *pri_key;
        char *pub_key;
        int size;
};

#endif // RSA_H
