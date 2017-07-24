#define LOCAL static
#define IMPORT extern

#define FAST register

typedef short WORD;
typedef unsigned short UWORD;
typedef char TEXT;
typedef unsigned char UTINY;
typedef long LONG;
typedef unsigned long ULONG;
typedef int INT;

#define OUT_OF_MEMORY -10
#define BAD_CODE_SIZE -20
#define READ_ERROR -1
#define WRITE_ERROR -2
#define OPEN_ERROR -3
#define CREATE_ERROR -4

IMPORT TEXT *malloc();
IMPORT INT get_byte();
IMPORT INT out_line();
IMPORT INT bad_code_count;

#define NULL   0L
#define MAX_CODES   4095

/* Static variables */
LOCAL WORD curr_size;                     /* The current code size */
LOCAL WORD clear;                         /* Value for a clear code */
LOCAL WORD ending;                        /* Value for a ending code */
LOCAL WORD newcodes;                      /* First available code */
LOCAL WORD top_slot;                      /* Highest code for current size */
LOCAL WORD slot;                          /* Last read code */

/* The following static variables are used
 * for seperating out codes
 */
LOCAL WORD navail_bytes = 0;              /* # bytes left in block */
LOCAL WORD nbits_left = 0;                /* # bits left in current byte */
LOCAL UTINY b1;                           /* Current byte */
LOCAL UTINY byte_buff[257];               /* Current block */
LOCAL UTINY *pbytes;                      /* Pointer to next byte in block */

LOCAL LONG code_mask[13] = {
     0,
     0x0001, 0x0003,
     0x0007, 0x000F,
     0x001F, 0x003F,
     0x007F, 0x00FF,
     0x01FF, 0x03FF,
     0x07FF, 0x0FFF
     };

LOCAL WORD init_exp(size)
   WORD size;
   {
   curr_size = size + 1;
   top_slot = 1 << curr_size;
   clear = 1 << size;
   ending = clear + 1;
   slot = newcodes = ending + 1;
   navail_bytes = nbits_left = 0;
   return(0);
   }

LOCAL WORD get_next_code()
   {
   WORD i, x;
   ULONG ret;

   if (nbits_left == 0)
      {
      if (navail_bytes <= 0)
         {
         pbytes = byte_buff;
         if ((navail_bytes = get_byte()) < 0)
            return(navail_bytes);
         else if (navail_bytes)
            {
            for (i = 0; i < navail_bytes; ++i)
               {
               if ((x = get_byte()) < 0)
                  return(x);
               byte_buff[i] = x;
               }
            }
         }
      b1 = *pbytes++;
      nbits_left = 8;
      --navail_bytes;
      }

   ret = b1 >> (8 - nbits_left);
   while (curr_size > nbits_left)
      {
      if (navail_bytes <= 0)
         {
         pbytes = byte_buff;
         if ((navail_bytes = get_byte()) < 0)
            return(navail_bytes);
         else if (navail_bytes)
            {
            for (i = 0; i < navail_bytes; ++i)
               {
               if ((x = get_byte()) < 0)
                  return(x);
               byte_buff[i] = x;
               }
            }
         }
      b1 = *pbytes++;
      ret |= b1 << nbits_left;
      nbits_left += 8;
      --navail_bytes;
      }
   nbits_left -= curr_size;
   ret &= code_mask[curr_size];
   return((WORD)(ret));
   }
LOCAL UTINY stack[MAX_CODES + 1];            /* Stack for storing pixels */
LOCAL UTINY suffix[MAX_CODES + 1];           /* Suffix table */
LOCAL UWORD prefix[MAX_CODES + 1];           /* Prefix linked list */

WORD decoder(linewidth)
   WORD linewidth;
   {
   FAST UTINY *sp, *bufptr;
   UTINY *buf;
   FAST WORD code, fc, oc, bufcnt;
   WORD c, size, ret;

   if ((size = get_byte()) < 0)
      return(size);
   if (size < 2 || 9 < size)
      return(BAD_CODE_SIZE);
   init_exp(size);

   oc = fc = 0;

   if ((buf = (UTINY *)malloc(linewidth + 1)) == NULL)
      return(OUT_OF_MEMORY);

   sp = stack;
   bufptr = buf;
   bufcnt = linewidth;

   while ((c = get_next_code()) != ending)
      {

      if (c < 0)
         {
         free(buf);
         return(0);
         }

      if (c == clear)
         {
         curr_size = size + 1;
         slot = newcodes;
         top_slot = 1 << curr_size;

         while ((c = get_next_code()) == clear)
            ;

         if (c == ending)
            break;

         if (c >= slot)
            c = 0;

         oc = fc = c;

         *bufptr++ = c;
         if (--bufcnt == 0)
            {
            if ((ret = out_line(buf, linewidth)) < 0)
               {
               free(buf);
               return(ret);
               }
            bufptr = buf;
            bufcnt = linewidth;
            }
         }
      else
         {
         code = c;
         if (code >= slot)
            {
            if (code > slot)
               ++bad_code_count;
            code = oc;
            *sp++ = fc;
            }
         while (code >= newcodes)
            {
            *sp++ = suffix[code];
            code = prefix[code];
            }
         *sp++ = code;
         if (slot < top_slot)
            {
            suffix[slot] = fc = code;
            prefix[slot++] = oc;
            oc = c;
            }
         if (slot >= top_slot)
            if (curr_size < 12)
               {
               top_slot <<= 1;
               ++curr_size;
               }
         while (sp > stack)
            {
            *bufptr++ = *(--sp);
            if (--bufcnt == 0)
               {
               if ((ret = out_line(buf, linewidth)) < 0)
                  {
                  free(buf);
                  return(ret);
                  }
               bufptr = buf;
               bufcnt = linewidth;
               }
            }
         }
      }
   ret = 0;
   if (bufcnt != linewidth)
      ret = out_line(buf, (linewidth - bufcnt));
   free(buf);
   return(ret);
}

