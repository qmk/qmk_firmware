#include "samd51j18a.h"
#include "stdarg.h"
#include "spfssf.h"
#include "usb_util.h"

int vspf(char *_Dest, const char *_Format, va_list va)
{
    //va_list va;                                                   //Variable argument list variable
    char *d = _Dest;                                               //Pointer to dest

    //va_start(va,_Format);                                         //Initialize the variable argument list
    while (*_Format)                                                //While not end of format string
    {
        if (*_Format == SPF_SPEC_START)                             //If current format string character is the specifier start character
        {
            _Format++;                                              //Skip over the character
            while (*_Format && *_Format <= 64) _Format++;           //Forward past any options
            if (*_Format == SPF_SPEC_START) *d++ = *_Format;        //If the character is the specifier start character, output the character and advance dest
            else if (*_Format == SPF_SPEC_LONG)                     //If the character is the long type
            {
                _Format++;                                          //Skip over the character
                if (*_Format == SPF_SPEC_DECIMAL)                   //If the character is the decimal type
                {
                    int64_t buf = va_arg(va,int64_t);               //Get the next value from the va list
                    //if (buf < 0) { *d++ = '-'; buf = -buf; }      //If the given number is negative, add a negative sign to the dest and invert number
                    //spf_uint2str_32_3t(&d,buf,32);                //Perform the conversion
                    d += UTIL_ltoa_radix(buf, d, 10);
                }
                else if (*_Format == SPF_SPEC_UNSIGNED)             //If the character is the unsigned type
                {
                    uint64_t num = va_arg(va,uint64_t);             //Get the next value from the va list
                    //spf_uint2str_32_3t(&d,num,32);                //Perform the conversion
                    d += UTIL_ltoa_radix(num, d, 10);
                }
                else if (*_Format == SPF_SPEC_UHINT || *_Format == SPF_SPEC_UHINT_UP)   //If the character is the unsigned type
                {
                    uint64_t buf = va_arg(va,uint64_t);             //Get the next value from the va list
                    //spf_uint2hex_32(&d,(unsigned long) buf);
                    d += UTIL_ltoa_radix(buf, d, 16);
                }
                else                                                //If the character was not a known type
                {
                    *d++ = SPF_SPEC_START;                          //Output the start specifier
                    *d++ = SPF_SPEC_LONG;                           //Output the long type
                    *d++ = *_Format;                                //Output the unknown type
                }
            }
            else if (*_Format == SPF_SPEC_DECIMAL)                  //If the character is the decimal type
            {
                int buf = va_arg(va,int);                           //Get the next value from the va list
                //if (buf < 0) { *d++ = '-'; buf = -buf; }          //If the given number is negative, add a negative sign to the dest and invert number
                //spf_uint2str_32_3t(&d,buf,16);                    //Perform the conversion
                d += UTIL_itoa(buf, d);
            }
            else if (*_Format == SPF_SPEC_INT)                      //If the character is the integer type
            {
                int buf = va_arg(va,int);                           //Get the next value from the va list
                //if (buf < 0) { *d++ = '-'; buf = -buf; }          //If the given number is negative, add a negative sign to the dest and inverted number
                //spf_uint2str_32_3t(&d,buf,16);                    //Perform the conversion
                d += UTIL_itoa(buf, d);
            }
            else if (*_Format == SPF_SPEC_UINT)                     //If the character is the unsigned integer type
            {
                int buf = va_arg(va,int);                           //Get the next value from the va list
                //spf_uint2str_32_3t(&d,buf,16);                    //Perform the conversion
                d += UTIL_utoa(buf, d);
            }
            else if (*_Format == SPF_SPEC_STRING)                   //If the character is the string type
            {
                char *buf = va_arg(va,char*);                       //Get the next value from the va list
                while (*buf) *d++ = *buf++;                         //Perform the conversion (simply output characters and adcance pointers)
            }
            else if (*_Format == SPF_SPEC_UHINT || *_Format == SPF_SPEC_UHINT_UP)   //If the character is the short type
            {
                int buf = va_arg(va,unsigned int);                  //Get the next value from the va list
                //spf_uint2hex_32(&d,(unsigned long) buf);          //Perform the conversion
                d += UTIL_utoa(buf, d);
            }
            else                                                    //If the character type is unknown
            {
                *d++ = SPF_SPEC_START;                              //Output the start specifier
                *d++ = *_Format;                                    //Output the unknown type
            }
        }
        else *d++ = *_Format;                                       //If the character is unknown, output it to dest and advance dest
        _Format++;                                                  //Advance the format buffer pointer to next character
    }
    //va_end(va);                                                   //End the variable argument list

    *d = '\0';                                                      //Cap off the destination string with a zero

    return d - _Dest;                                               //Return the length of the destintion buffer
}

int spf(char *_Dest, const char *_Format, ...)
{
    va_list va;                                                     //Variable argument list variable
    int result;

    va_start(va,_Format);                                           //Initialize the variable argument list
    result = vspf(_Dest, _Format, va);
    va_end(va);
    return result;
}

//sscanf string to number (integer types)
int64_t ssf_ston(const char **_Src, uint32_t count, uint32_t *conv_count)
{
    int64_t value = 0;                                  //Return value accumulator
    uint32_t counter=count;                             //Counter to keep track of numbers converted
    const char* p;                                      //Pointer to first non space character

    while (*(*_Src) == SSF_SKIP_SPACE) (*_Src)++;       //Forward through the whitespace to next non whitespace

    p = (*_Src);                                        //Set pointer to first non space character
    if (*p == '+' || *p == '-') (*_Src)++;              //Skip over sign if any
    while (*(*_Src) >= ASCII_NUM_START &&
        *(*_Src) <= ASCII_NUM_END &&
        counter)                                        //While the source character is a digit and counter is not zero
    {
        value *= 10;                                    //Multiply result by 10 to make room for next 1's place number
        value += *(*_Src)++ - ASCII_NUM_START;          //Add source number to value
        counter--;                                      //Decrement counter
    }
    if (counter - count == 0) return 0;                 //If no number conversion were performed, return 0
    if (*p == '-') value = -value;                      //If the number given was negative, make the result negative

    if (conv_count) (*conv_count)++;                    //Increment the converted count
    return value;                                       //Return the value
}

uint64_t ssf_hton(const char **_Src, uint32_t count,uint32_t *conv_count)
{
    int64_t value=0;                                            //Return value accumulator
    uint32_t counter=count;                                     //Counter to keep track of numbers converted
    //const char* p;                                            //Pointer to first non space character
    char c;

    while (*(*_Src) == SSF_SKIP_SPACE) (*_Src)++;               //Forward through the whitespace to next non whitespace

    //p = (*_Src);                                              //Set pointer to first non space character

    while (counter)
    {
        c = *(*_Src)++;
        if (c >= 'a' && c <= 'f') c -= ('a'-'A');               //toupper
        if (c < '0' || (c > '9' && c < 'A') || c > 'F') break;
        value *= 16;                                            //Multiply result by 10 to make room for next 1's place number
        c = c - '0';
        if (c > 9) c -= 7;
        value += c;                                             //Add source number to value
        counter--;                                              //Decrement counter
    }

    if (counter - count == 0) return 0;                         //If no number conversion were performed, return 0
    //if (*p == '-') value = -value;                            //If the number given was negative, make the result negative

    if (conv_count) (*conv_count)++;                            //Increment the converted count
    return value;
}

//sscanf
int ssf(const char *_Src, const char *_Format, ...)
{
    va_list va;                                                                         //Variable argument list variable
    unsigned char looking_for=0;                                                        //Static char specified in format to be found in source
    uint32_t conv_count=0;                                                              //Count of conversions made

    va_start(va,_Format);                                                               //Initialize the variable argument list
    while (*_Format)                                                                    //While the format string has not been fully read
    {
        if (looking_for != 0)                                                           //If we are looking for a matching character in the source string
        {
            while (*_Src != looking_for && *_Src) _Src++;                               //While the character is not found in the source string and not the end of the source
                                                                                        //  string, increment the pointer position
            if (*_Src == looking_for) _Src++;                                           //If the character was found, step over it
            else break;                                                                 //Else the end was reached and the scan is now invalid (Could not find static character)
            looking_for = 0;                                                            //Clear the looking for character
        }
        if (*_Format == SSF_SPEC_START)                                                 //If the current format character is the specifier start character
        {
            _Format++;                                                                  //Step over the specifier start character
            if (*_Format == SSF_SPEC_DECIMAL)                                           //If the decimal specifier type is found
            {
                int *value=va_arg(va,int*);                                             //User given destination address
                //*value = (int)ssf_ston(&_Src,5,&conv_count);                          //Run conversion
                *value = (int)ssf_ston(&_Src,10,&conv_count);                           //Run conversion
            }
            else if (*_Format == SSF_SPEC_LONG)                                         //If the long specifier type is found
            {
                _Format++;                                                              //Skip over the specifier type
                if (*_Format == SSF_SPEC_DECIMAL)                                       //If the decimal specifier type is found
                {
                    int64_t *value=va_arg(va,int64_t*);                                 //User given destination address
                    //*value = (int64_t)ssf_ston(&_Src,10,&conv_count);                 //Run conversion
                    *value = (int64_t)ssf_ston(&_Src,19,&conv_count);                   //Run conversion
                }
                else if (*_Format == SSF_SPEC_UHINT)                                    //If the decimal specifier type is found
                {
                    uint64_t *value=va_arg(va,uint64_t *);                              //User given destination address
                    //*value = (uint64_t int)ssf_hton(&_Src,12,&conv_count);            //Run conversion
                    *value = (uint64_t)ssf_hton(&_Src,16,&conv_count);                  //Run conversion
                }
            }
            else if (*_Format == SSF_SPEC_SHORTINT)                                     //If the short int specifier type is found
            {
                _Format++;                                                              //Skip over the specifier type
                if (*_Format == SSF_SPEC_SHORTINT)                                      //If the short int specifier type is found
                {
                    _Format++;                                                          //Skip over the specifier type
                    if (*_Format == SSF_SPEC_DECIMAL)                                   //If the decimal specifier type is found
                    {
                        unsigned char *value=va_arg(va,unsigned char*);                 //User given destination address
                        //*value = (unsigned char)ssf_ston(&_Src,3,&conv_count);        //Run conversion
                        *value = (unsigned char)ssf_ston(&_Src,5,&conv_count);          //Run conversion
                    }
                }
            }
            else if (*_Format == SSF_SPEC_STRING)                                       //If the specifier type is string
            {
                char *value=va_arg(va,char*);                                           //User given destination address, max chars read pointer
                while (*_Src == SSF_SKIP_SPACE) _Src++;                                 //Forward through the whitespace to next non whitespace
                while (*_Src != SSF_SKIP_SPACE && *_Src) *value++ = *_Src++;            //While any character but space and not end of string and not end location, copy char to dest
                *value = 0;                                                             //Cap off the string pointer with zero
                conv_count++;                                                           //Increment the converted count
            }
            else if (*_Format == SSF_SPEC_VERSION)                                      //If the specifier type is string
            {
                char *value=va_arg(va,char*);                                           //User given destination address, max chars read pointer
                while (*_Src == SSF_SKIP_SPACE) _Src++;                                 //Forward through the whitespace to next non whitespace
                while (*_Src != SSF_DELIM_COMMA && *_Src) *value++ = *_Src++;           //While any character but space and not end of string and not end location, copy char to dest
                *value = 0;                                                             //Cap off the string pointer with zero
                conv_count++;                                                           //Increment the converted count
            }
            else if (*_Format >= ASCII_NUM_START && *_Format <= ASCII_NUM_END)
            {
                uint32_t len = (uint32_t)ssf_ston(&_Format,3,NULL);                     //Convert the given length
                if (*_Format == SSF_SPEC_STRING)                                        //If the specifier type is string
                {
                    char *value=va_arg(va,char*),*e;                                    //User given destination address, max chars read pointer
                    while (*_Src == SSF_SKIP_SPACE) _Src++;                             //Forward through the whitespace to next non whitespace
                    e = (char*)_Src+len;                                                //Set a maximum length pointer location
                    while (*_Src != SSF_SKIP_SPACE && *_Src && _Src != e) *value++ = *_Src++;   //While any character but space and not end of string and not end location, copy char to dest
                    *value = 0;                                                         //Cap off the string pointer with zero
                    conv_count++;                                                       //Increment the converted count
                }
                else if (*_Format == SSF_SPEC_VERSION)                                  //If the specifier type is string
                {
                    char *value=va_arg(va,char*),*e;                                    //User given destination address, max chars read pointer
                    while (*_Src == SSF_SKIP_SPACE) _Src++;                             //Forward through the whitespace to next non whitespace
                    e = (char*)_Src+len;                                                //Set a maximum length pointer location
                    while (*_Src != SSF_DELIM_COMMA && *_Src && _Src != e) *value++ = *_Src++;  //While any character but space and not end of string and not end location, copy char to dest
                    *value = 0;                                                         //Cap off the string pointer with zero
                    conv_count++;                                                       //Increment the converted count
                }
            }
            else if (*_Format == SSF_SPEC_START) looking_for = *_Format;                //If another start specifier character is found, output a specifier character
            else break;                                                                 //Scan is now invalid (Uknown type specified)
        }
        else if (*_Format == SSF_SKIP_SPACE) { }                                        //If a space is found, ignore it
        else looking_for = *_Format;                                                    //If any other character is found, it is static and should be found in src as well
        _Format++;                                                                      //Skip over current format character
    }

    va_end(va);                                                                         //End the variable argument list
    return conv_count;                                                                  //Return the number of conversions made
}

