#ifndef SHA1_H 
#define SHA1_H 
 
#define SHA1_MAC_LEN 20 
 
typedef unsigned int	u32; 

#ifndef uint8
#define uint8  unsigned char
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif
 
typedef struct { 
        u32 state[5]; 
        u32 count[2]; 
        unsigned char buffer[64]; 
} SHA1_CTX; 
 
void SHA1Init(SHA1_CTX *context); 
void SHA1Update(SHA1_CTX *context, unsigned char const *data, u32 len); 
void SHA1Final(unsigned char digest[20], SHA1_CTX* context); 
void SHA1Transform(u32 state[5], const unsigned char buffer[64]); 
void SHA1_val2str(char str[40], unsigned char value[20]);
int sprintf_s( char *buffer, size_t sizeOfBuffer, const char *format ,...);

#endif /* SHA1_H */ 
