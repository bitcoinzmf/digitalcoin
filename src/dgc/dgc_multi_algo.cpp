#include "dgc_multi_algo.h"
#include "scrypt.h"
#include "hash.h"

int GetAlgo(int nVersion)
{
    int algo = ALGO_SCRYPT;
    int masked = nVersion & BLOCK_VERSION_ALGO;

    switch (masked)
    {
        case 1:
            algo = ALGO_SCRYPT; 
            break;
        case BLOCK_VERSION_SHA256D:
            algo = ALGO_SHA256D; 
            break;
        case BLOCK_VERSION_X11:
            algo = ALGO_X11; 
            break;
            default : 
            break;
    }
    return algo;
}

std::string GetAlgoName(int Algo)
{
    switch (Algo)
    {
        case ALGO_SHA256D:
            return std::string("sha256d");
        case ALGO_SCRYPT:
            return std::string("scrypt");
        case ALGO_X11:
            return std::string("x11");
    }
    return std::string("unknown");       
}

uint256 GetHash_Sha(int32_t nVersion, uint32_t nNonce)
{
    return Hash(BEGIN(nVersion), END(nNonce));
}

uint256 GetHash_X11(int32_t nVersion, uint32_t nNonce)
{
    return HashX11(BEGIN(nVersion), END(nNonce));
}

uint256 GetHash_Scrypt(int32_t nVersion)
{
    uint256 result;
    scrypt_1024_1_1_256(BEGIN(nVersion), BEGIN(result));
    return result;
}

uint256 GetPowHash(int32_t nVersion, uint32_t nNonce, int algo)
{
    uint256 result = GetHash_Sha(nVersion, nNonce);

    switch (algo)
    {
        case ALGO_SHA256D : result = GetHash_Sha(nVersion, nNonce); break;
        case ALGO_SCRYPT: result = GetHash_Scrypt(nVersion); break;
        case ALGO_X11: result = GetHash_X11(nVersion, nNonce); break;
    }

    return result;
}