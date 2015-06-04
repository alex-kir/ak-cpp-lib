//--------------------------------------------------------------------
//  Declare variables.

HCRYPTPROV hCryptProv;
HCRYPTHASH hHash;

//--------------------------------------------------------------------
// Get a handle to a cryptography provider context.


if(CryptAcquireContext(
   &hCryptProv, 
   NULL, 
   NULL, 
   PROV_RSA_FULL, 
   0)) 
{
    printf("CryptAcquireContext complete. \n");
}
else
{
     printf("Acquisition of context failed.\n");
     exit(1);
}
//--------------------------------------------------------------------
// Acquire a hash object handle.

if(CryptCreateHash(
   hCryptProv, 
   CALG_MD5, 
   0, 
   0, 
   &hHash)) 
{
    printf("An empty hash object has been created. \n");
}
else
{
    printf("Error during CryptBeginHash!\n");
    exit(1);
}

//--------------------------------------------------------------------


// Insert code that uses the hash object here.
if(CryptHashData(
   hHash, 
   pbBuffer, 
   dwBufferLen, 
   0)) 
{
     printf("The data buffer has been added to the hash.\n");
}
else
{
     printf("Error during CryptHashData.\n");
     exit(1);
}



//--------------------------------------------------------------------
// After processing, hCryptProv and hHash must be released.

BOOL WINAPI CryptGetHashParam(
  __in          HCRYPTHASH hHash,
  __in          DWORD dwParam,
  __out         BYTE* pbData,
  __in_out      DWORD* pdwDataLen,
  __in          DWORD dwFlags
);


if(hHash) 
   CryptDestroyHash(hHash);
if(hCryptProv) 
   CryptReleaseContext(hCryptProv,0);
