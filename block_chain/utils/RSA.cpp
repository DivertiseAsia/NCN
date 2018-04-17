#include "RSA.h"

void w_private(BIO *bio, RSA* rsa) {
    PEM_write_bio_RSAPrivateKey(bio, rsa, nullptr, nullptr, 0, nullptr, nullptr);
}

void w_public(BIO *bio, RSA* rsa) {
    PEM_write_bio_RSAPublicKey(bio, rsa);
}

RSA_Cryptography::RSA_Cryptography()
{
    size = 4096;
}
#include <iostream>
#include <openssl/engine.h>
RSA_Cryptography::RSA_Cryptography(std::string key)
{
    size = 4096;
    BIO* bo = BIO_new_mem_buf( (void*) key.c_str(), (int) key.size());
    BIO_set_flags( bo, BIO_FLAGS_BASE64_NO_NL ) ; // NO NL
    rsa = PEM_read_bio_RSAPublicKey(bo, nullptr, nullptr, nullptr);
    BIO_free(bo);
}

std::string read(const char* filename){
    std::ifstream peers_file;
    std::string key;
    peers_file.open(filename, std::ifstream::in);
    if(peers_file.is_open()){
        std::string line;
        while (std::getline (peers_file, line)) {
            key += line;
        }
        peers_file.close();
    }
    return key;
}

bool RSA_Cryptography::backup(const char* priv, const char* pub){
    std::ifstream peers_file;
    std::string public_key = read(pub);
    std::string private_key = read(priv);
    FILE* a = fopen(priv, "r");
    FILE* b = fopen(pub, "r");
    if(a && b)
    {
        rsa = PEM_read_RSAPrivateKey(a, nullptr, nullptr, nullptr);
        rsa = PEM_read_RSAPublicKey(b, &rsa,  nullptr, nullptr);
        fclose(a);
        fclose(b);
        return true;
    }
    if(a)
        fclose(a);
    if(b)
        fclose(b);
    return false;
}
void RSA_Cryptography::generate(const char* priv, const char* pub) {
    const int kExp = 3;
    rsa = RSA_generate_key(size, kExp, nullptr, nullptr);
    write(w_private, priv);
    write(w_public, pub);
}


void RSA_Cryptography::write(void(* fun)(BIO*, RSA*), std::string file){
    int keylen;
    char *pem_key;
    BIO *bio = BIO_new(BIO_s_mem());
    fun(bio, rsa);
    keylen = BIO_pending(bio);
    pem_key = (char*)calloc((size_t) keylen+1, 1);
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

std::string RSA_Cryptography::encrypt(std::string message) {
    auto encrypt = (unsigned char*)malloc((size_t) RSA_size(rsa));
    int encrypt_len;
    if((encrypt_len = RSA_private_encrypt((int)message.size()+1, (const unsigned char*)message.c_str(), encrypt, rsa, RSA_PKCS1_PADDING)) == -1) {
        std::cout << "\033[1;31m[ERR] ERROR ENCRYPT\033[0m" << std::endl;
    }
    std::string str;
    str.assign((const char*)encrypt, (unsigned long)encrypt_len);
    return str;
}
std::string RSA_Cryptography::decrypt(std::string message, int size) {
    auto decrypt = (unsigned char*)malloc((size_t) size);
    if(RSA_public_decrypt((int)message.size(), (const unsigned char*) message.c_str(), decrypt, rsa, RSA_PKCS1_PADDING) == -1) {
        std::cout << "\033[1;31m[ERR] ERROR DECRYPT\033[0m" << std::endl;
    }
    return std::string((const char*)decrypt);
}

std::string getKey(void (* fun)(BIO*, RSA*), RSA* rsa){
    int len;
    char   *key;
    BIO *p = BIO_new(BIO_s_mem());
    fun(p, rsa);
    len = BIO_pending(p);
    key = (char*)malloc((size_t) len + 1);
    BIO_read(p, key, len);
    key[len] = '\0';
    std::string final_key = key;
    free(key);
    return final_key;
}

void private_action(BIO* bio, RSA* rsa) {
    PEM_write_bio_RSAPrivateKey(bio, rsa, nullptr, nullptr, 0, nullptr, nullptr);
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
