#ifndef DF1_H
#define DF1_H


#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)

#define DLE 0x10
#define STX 0x02
#define ETX 0X03
#define ENQ 0x05
#define ACK 0x06
#define NAK 0x15

#define DEST 0x01
#define SOURCE 0x00

#define SLC 1
#define PLC 2

#define FALSE 0
#define TRUE 1

#define TIME_OUT 1 //in seconds

//Error
#define SUCCES 0
#define ERROR -1
#define ERROR_NAK -2
#define ERROR_SENDDF1 -3
#define ERROR_RCVDF1 -4
#define ERROR_TIMEOUT -5
#define ERROR_BAD_QUERY -6
#define ERROR_TNS_MISMATCH -9
#define ERROR_READ_A2 -10
#define ERROR_READ_INTEGER -20
#define ERROR_CALC_ADDRESS -30
#define ERROR_WRITE_AA -40
#define ERROR_WRITE -41
#define ERROR_WRITE_AB -42

//Flag
#define DATA_FLAG 1
#define CONTROL_FLAG 2

typedef unsigned char byte;
typedef unsigned short word;

/* TMsg structure */
typedef struct {
	byte dst;
	byte src;
	byte cmd;
	byte sts;
	word tns;
	byte data[255];
	byte size;
} TMsg;

/* TBuffer structure */
typedef struct {
	byte data[512];
	byte size;
} TBuffer;

/* TThree_Address_Fields structure*/
typedef struct {
	byte size;
	byte fileNumber;
	byte fileType;
	byte eleNumber;
	byte s_eleNumber;
} TThree_Address_Fields;

/* TCmd */
typedef struct {
	byte fnc;
	byte size;
	byte fileNumber;
	byte fileType;
	byte eleNumber;
	byte s_eleNumber;
} TCmd;

/* TCmd4 */
typedef struct {
	byte fnc;
	byte size;
	byte fileNumber;
	byte fileType;
	byte eleNumber;
	byte s_eleNumber;
	word maskbyte;
	word value;
} TCmd4;



void initialize(const char* str);

// common.c
word bytes2word(byte lowb, byte highb);
int add_word2buffer(TBuffer * buffer, word value);
int add_byte2buffer(TBuffer *buffer, byte value);
int add_data2buffer(TBuffer * buffer, void * data, byte size);
int add_data2bufferWithDLE(TBuffer * buffer, TMsg msg);
void print_symbol(byte c);
int is_timeout(int start_time);

// df1.c
word calc_crc(word crc, word buffer);
word compute_crc(TBuffer * buffer);
int send_DF1(TMsg Df1Data);
int rcv_DF1(TMsg * Df1Data);
int get_symbol(byte * b);
void sendResponse(byte response);
int read_byte(byte * b);


//read
int read_A2(TThree_Address_Fields address, void *value, byte size);
int read_integer(int plctype, char *straddress, word *value);
int read_float(int plctype, char *straddress, float *value);
int read_boolean(int plctype, char *straddress, int *value);
//write
int write_AA(TThree_Address_Fields address, void *value, byte size);
int write_integer(int plctype, char *straddress, word *value);
int write_float(int plctype, char *straddress, float *value);
int write_AB(TThree_Address_Fields address, word value, word mask);
int write_boolean(int plctype, char *straddress, int *value);

int calc_address(char *straddress, TThree_Address_Fields *address);
int select_fnct(char *strquery, char *address, char *value);
int read_socket(const char *rcvmsg, char *response);
int server(void);



#endif // !DF1_H
