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

    explicit RSA_Cryptography(std::string filename);
        std::string encrypt(std::string message);
        std::string decrypt(std::string message, int size);
        void write(void(* fun)(BIO*, RSA*), std::string file);
        std::string getPublicKey();
        std::string getPrivateKey();
        void generate(const char*, const char*);
        bool backup(const char*, const char*);
        virtual ~RSA_Cryptography();

    protected:

    private:
        RSA* rsa;
        int size;
};

#endif // RSA_H
