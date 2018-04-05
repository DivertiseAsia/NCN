#include "RSA.h"

void w_private(BIO *bio, RSA* rsa) {
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
}

void w_public(BIO *bio, RSA* rsa) {
    PEM_write_bio_RSAPublicKey(bio, rsa);
}

RSA_Cryptography::RSA_Cryptography()
{
    size = 2048;
}
#include <iostream>
RSA_Cryptography::RSA_Cryptography(std::string key)
{
    std::cout << key << std::endl;
    size = 2048;
    rsa = RSA_generate_key(size, 3, 0, 0);
    BIO* bo = BIO_new(BIO_s_mem());
    BIO_write(bo, key.c_str(), key.size());
    PEM_read_bio_RSA_PUBKEY(bo, &rsa, 0, 0 );
    BIO_free(bo);
}

bool RSA_Cryptography::backup(){
    //TODO: read file
    return false;
}
void RSA_Cryptography::generate() {
    const int kExp = 3;
    rsa = RSA_generate_key(size, kExp, 0, 0);
    write(w_private, "private.pem");
    write(w_public, "public.pem");
}


void RSA_Cryptography::write(void(* fun)(BIO*, RSA*), std::string file){
    int keylen;
    char *pem_key;
    BIO *bio = BIO_new(BIO_s_mem());
    fun(bio, rsa);
    keylen = BIO_pending(bio);
    pem_key = (char*)calloc(keylen+1, 1);
    BIO_read(bio, pem_key, keylen);
    std::ofstream block_file (file);
    std::string line;
    if(block_file.is_open()){
        block_file << pem_key;
        block_file.close();
    }
    BIO_free_all(bio);
    free(pem_key);
}

RSA_Cryptography::~RSA_Cryptography()
{
    RSA_free(rsa);
}

#include <iostream>
std::string RSA_Cryptography::encrypt(std::string message) {
    unsigned char* encrypt = (unsigned char*)malloc(RSA_size(rsa));
    int encrypt_len;
    if((encrypt_len = RSA_private_encrypt(message.size()+1, (const unsigned char*)message.c_str(), (unsigned char*)encrypt, rsa, RSA_PKCS1_OAEP_PADDING)) == -1) {
        std::cout << "ERROR ENCRYPT" << std::endl;
    }
    std::cout << "len: " << encrypt << std::endl;
    std::string str;
    str.assign((const char*)encrypt, encrypt_len);
    return str;
}
std::string RSA_Cryptography::decrypt(std::string message, int size) {
    unsigned char* decrypt = (unsigned char*)malloc(size);
    std::cout << "len: " << size << std::endl;
    if(RSA_public_decrypt(message.size(), (const unsigned char*) message.c_str(), (unsigned char*) decrypt, rsa, RSA_PKCS1_OAEP_PADDING) == -1) {
            std::cout << "ERROR DECRYPT" << std::endl;
    }
    return std::string((const char*)decrypt);
}

std::string getKey(void (* fun)(BIO*, RSA*), RSA* rsa){
    size_t len;
    char   *key;
    BIO *p = BIO_new(BIO_s_mem());
    fun(p, rsa);
    len = BIO_pending(p);
    key = (char*)malloc(len + 1);
    BIO_read(p, key, len);
    key[len] = '\0';
    std::string final_key = key;
    free(key);
    return final_key;
}

void private_action(BIO* bio, RSA* rsa) {
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
}

void public_action(BIO* bio, RSA* rsa) {
    PEM_write_bio_RSAPublicKey(bio, rsa);
}

std::string RSA_Cryptography::getPublicKey(){
    return getKey(public_action, rsa);
}

std::string RSA_Cryptography::getPrivateKey(){
    return getKey(private_action, rsa);
}
