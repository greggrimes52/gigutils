#define   VERSION  "04"
#include "us.h"
#include "usargs.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef DOS
#define   SLASH    '\\'
#define   NAMELEN  15
#define   FILENAME name
#include <dos.h>
#else
#define   SLASH    '/'
#define   NAMELEN  255
#define   FILENAME d_name
#include <sys/types.h>
#ifdef    NO_DIRENT
#include <sys/dir.h>
#else
#include <dirent.h>
#endif
#include <unistd.h>
#endif

 struct BLOCK
      {
        struct BLOCK *next;
        struct BLOCK  *kid;
        char         *extn;
        char          attr;
        char          name[NAMELEN];
      };

 static int       numfiles;
 static int           drtn;
 static char         *parm;
 static char      *catparm;
 static char          path[128];
 static struct BLOCK  *top;

int do_it(char *arg);
int vprint(char *tag);
int vblock(struct BLOCK *block);
int bldtree(char *catname);
int runtree(struct BLOCK *block);


#define BLOCK_SIZE           sizeof(struct BLOCK)
#define BLOCKS_TO_ALLOCATE   1024
#define BLOCKS_MALLOC_SIZE   (BLOCKS_TO_ALLOCATE * BLOCK_SIZE + sizeof(char *))

 static int   blocks = 0;
 static int   blockt = 0;
 static char *blockp = 0;
 static char *blocka = 0;

/***************
 * get a BLOCK *
 ***************/
static struct BLOCK *get_a_block()
{
   char *block;

   if(!blocks)
     {
      char *p;
      p = blocka;
      blocka = (char *)malloc(BLOCKS_MALLOC_SIZE);
      if(blocka == 0)
        {
         printf("Out of memory!\n");
         exit(1);
        }
      if(FLAG(v)>3) printf("\n   Allocated BLOCK pool (%p).\n",blocka);
      memset(blocka,0,BLOCKS_MALLOC_SIZE);
      *(char **)blocka = p;
      blockp = (blocka + sizeof(char *));
      blocks = BLOCKS_TO_ALLOCATE;
     }

   blocks --;
   block   = blockp;
   blockp += BLOCK_SIZE;
   blockt += BLOCK_SIZE;

   return((struct BLOCK *)block);
}

/******************
 * return a BLOCK *
 ******************/
static void return_a_block(p)
 struct BLOCK *p;
{
   /* Keep track of bytes allocated */
   blockt -= BLOCK_SIZE;
}

/*******************
 * free all BLOCKs *
 *******************/
static void free_all_blocks()
{
   char *next;

   if(blockt)
      printf("Oops!  Freeing all blocks with %d bytes still allocated.\n",
         blockt);
   while(blocka)
     {
      next = blocka;
      blocka = *(char **)blocka;
      free(next);
      if(FLAG(v)>3) printf("\n   Freed BLOCK pool (%p).\n",next);
     }
   blocks = blockt = 0;
   blockp = 0;
}

#define CHUNK_SIZE           128
#define CHUNKS_TO_ALLOCATE   16
#define CHUNKS_MALLOC_SIZE   (CHUNKS_TO_ALLOCATE * CHUNK_SIZE + sizeof(char *))

 static int   chunks = 0;
 static int   chunkt = 0;
 static char *chunkp = 0;
 static char *chunka = 0;

/***************
 * get a CHUNK *
 ***************/
static char *get_a_chunk()
{
   char *chunk;

   if(!chunks)
     {
      char *p;
      p = chunka;
      chunka = (char *)malloc(CHUNKS_MALLOC_SIZE);
      if(chunka == 0)
        {
         printf("Out of memory!\n");
         exit(1);
        }
      if(FLAG(v)>3) printf("\n   Allocated CHUNK pool (%p).\n",chunka);
      memset(chunka,0,CHUNKS_MALLOC_SIZE);
      *(char **)chunka = p;
      chunkp = (chunka + sizeof(char *));
      chunks = CHUNKS_TO_ALLOCATE;
     }

   chunks --;
   chunk   = chunkp;
   chunkp += CHUNK_SIZE;
   chunkt += CHUNK_SIZE;

   return(chunk);
}

/******************
 * return a CHUNK *
 ******************/
static void return_a_chunk(p)
 char *p;
{
   /* Keep track of bytes allocated */
   chunkt -= CHUNK_SIZE;
}

/*******************
 * free all CHUNKs *
 *******************/
static void free_all_chunks()
{
   char *next;

   if(chunkt)
      printf("Oops!  Freeing all chunks with %d bytes still allocated.\n",
         chunkt);
   while(chunka)
     {
      next = chunka;
      chunka = *(char **)chunka;
      free(next);
      if(FLAG(v)>3) printf("\n   Freed CHUNK pool (%p).\n",next);
     }
   chunks = chunkt = 0;
   chunkp = 0;
}



/**********************************************************************/
/* Main function                                                      */
/**********************************************************************/
int main(argc,argv)
 int argc;
 char *argv[];
{
   char *arg;

/**********************************************************************/
/* Parse the arguments                                                */
/**********************************************************************/
   arg = USARGS();

/**********************************************************************/
/* Show help, if requested                                            */
/**********************************************************************/
   if(FLAG(?))
     {
      US_NAME(arg)
      printf("Usage:\n");
      printf("   %s [flags] [template]...\n",arg);
      printf("\n");
      printf("   Show directory entry information.\n");
      printf("\n");
      printf("flags:\n");
#ifdef DOS
      printf("   -H   Include hidden files in the list.\n");
      printf("   -S   Include system files in the list.\n");
#endif
      printf("   -Vn  Verbose (debug) information.\n");
      printf("\n");
      printf(US_COPYRIGHT);
      exit(0);
     }

/**********************************************************************/
/* Display catalog/directory for each argument                        */
/**********************************************************************/
   do{
      do_it(arg);
     } while(arg=USARGS());

/**********************************************************************/
/* Return                                                             */
/**********************************************************************/
   return 0;

}



/******************
 * Let's go do it *
 ******************/
int do_it(arg)
 char *arg;
{
   int        notpat;
   char        *temp;
   struct BLOCK *nxt;

/**********************************************************************/
/* Parse the catalog pathname (if any)                                */
/**********************************************************************/
   if(FLAG(v)>1) printf("do_it entry\n");

   /* If nothing given, use the current directory */
   temp = 0;
   catparm = arg;
   if(catparm == 0)
     {
      catparm = temp = get_a_chunk();
      if(getcwd(parm,CHUNK_SIZE)==0)
         printf("getcwd returned zero.\n");
     }
   if(FLAG(v)>1)  printf("   parm:  \"%s\"\n",catparm);

   /* Start with a null string work area */
   parm = path;
   parm[0] = '\0';
   if(FLAG(v)>1)  printf("   path:  \"%s\"\n",path);

#ifdef DOS
   /* Put in the disk identifier */
   if(catparm[1] == ':')
     {
      *parm++ = *catparm++;
      *parm++ = *catparm++;
     }
   else
     {
      *parm++ = 'A' + getdsk();
      *parm++ = ':';
     }
   if(FLAG(v)>1)  printf("   path:  \"%s\"\n",path);
#endif

   /* Add current directory, if we got a relative path */
   if(*catparm != SLASH)
     {
#ifdef DOS
      *parm++ = SLASH;
      if((drtn=getcd(toupper(path[0])-'A'+1,parm))!=0)
         printf("getcd returned %d.\n",drtn);
#else
      if(getcwd(parm,sizeof(path))==0)
         printf("getcwd returned zero.\n");
#endif
      parm = path+strlen(path);
      if(strlen(catparm) && *(parm-1) != SLASH)
         *parm++ = SLASH;
     }
   if(FLAG(v)>1)  printf("   path:  \"%s\"\n",path);

   /* Add the given stuff */
   notpat = 1;
   while(*catparm)
     {
      if(*catparm == '*' || *catparm == '?') notpat = 0;
      *parm++ = *catparm++;
     }
   if(FLAG(v)>1)  printf("   path:  \"%s\"\n",path);

#ifdef DOS
   /* Root directories are a special case */
   if(notpat || (strlen(path) == 3 && path[2] == SLASH))
     {
      if(parm[-1] != SLASH) *parm++ = SLASH;
      parm[0] = '*';
      parm[1] = '.';
      parm[2] = '*';
      parm[3] = '\0';
     }
   if(FLAG(v)>1)  printf("   path:  \"%s\"\n",path);

   /* Upper case the sucker */
   strupr(path);
   if(FLAG(v)>1)  printf("   path:  \"%s\"\n",path);
#endif

   /* That's what we'll use for the pathname */
   catparm = path;

   if(temp!=0) return_a_chunk(temp);

/**********************************************************************/
/* Build the catalog tree                                             */
/**********************************************************************/
   bldtree(catparm);

/**********************************************************************/
/* Print the catalog tree                                             */
/**********************************************************************/
   printf("Display names by file type for \"%s\".\n",catparm);
   while(top)
     {
      nxt = top->next;
      runtree(top);
      top = nxt;
     }
   printf("%d names in all.\n",numfiles);
   numfiles = 0;

/**********************************************************************/
/* Clean up and leave                                                 */
/**********************************************************************/
   free_all_blocks();
   free_all_chunks();
   if(FLAG(v)>1)  vprint("do_it exit");
   return 0;
}



/***************************
 * display the debug print *
 ***************************/
int vprint(tag)
 char  *tag;
{
   int i;

   printf("\n%s:\n",tag);
   printf("   flags     =");
   for( i='a'; i<='z'; i++ )
     printf(" %c",i);
   printf("\n              ");
   for( i='a'; i<='z'; i++ )
     printf("%2d",args[i]);
   printf("\n");
   printf("   path      = (%p) \"%s\"\n", path,    path);
   printf("   catparm   = (%p) \"%s\"\n", catparm, catparm);
   printf("   top       = (%p)\n",        top);

   return 0;
}



/*********************
 * print out a block *
 *********************/
int vblock(block)
 struct BLOCK *block;
{

   printf("\nBlock (%p)\n",block);
   printf("   top       = (%p)",         top);
   printf("   name      = (%p) \"%s\"\n",block->name,block->name);
   printf("   extn      = (%p) \"%s\"\n",block->extn,block->extn);
   printf("   next      = (%p)\n",       block->next);
   printf("   kid       = (%p)\n",       block->kid);
   printf("   attr      = %x\n",         block->attr);

   return 0;
}



/************************
 * build a catalog tree *
 ************************/
int bldtree(catname)
 char *catname;
{
#ifdef DOS
   struct FILEINFO   data;
   struct FILEINFO  *file = &data;
#else
#ifdef NO_DIRENT
   struct direct    *file;
#else
   struct dirent    *file;
#endif
          DIR          *d;
#endif
   struct BLOCK     *prev;
   struct BLOCK     *this;
   struct BLOCK     *next;
   struct BLOCK     *uppr;
   struct BLOCK     *lowr;
   char                *p;
   char                *q;
   int                 rc;

   if(FLAG(v)>3)
     {
      vprint("bldtree entry");
      printf("   catname   = (%p) \"%s\"\n",catname,catname);
     }

#ifndef DOS
   d = opendir(catname);
   if(d == NULL)
     {
      printf("Unable to open directory \"%s\".\n",catname);
      return 1;
     }
   while(file=readdir(d))
#else
   drtn = dfind(file,catname,0x1e); 
   while(drtn == 0)
#endif
     {

      this = NULL;
      while(1)
        {

         if(strcmp(file->FILENAME, ".") == 0 ||
            strcmp(file->FILENAME,"..") == 0)
           {
            if(FLAG(v)) printf("Skipping directory entry \"%s\".\n",
               file->FILENAME);
            break;
           }
#ifdef DOS
         else if(file->attr & 0x08)
           {
            if(FLAG(v)) printf("Skipping volume label \"%s\".\n",
               file->FILENAME);
            break;
           }
         else if(file->attr & 0x04 && !FLAG(S))
           {
            if(FLAG(v)) printf("Skipping system file \"%s\".\n",
               file->FILENAME);
            break;
           }
         else if(file->attr & 0x02 && !FLAG(H))
           {
            if(FLAG(v)) printf("Skipping hidden file \"%s\".\n",
               file->FILENAME);
            break;
           }
#endif

         numfiles++;
         this = get_a_block();
#ifdef DOS
         this->attr = file->attr;
#endif
         this->extn = "";
         p = file->FILENAME + strlen(file->FILENAME);
         q = this->name     + strlen(file->FILENAME);
         while(p > file->FILENAME)
           {
            *q-- = *p--;
            if(q[1] == '.')
              {
               q[1] = '\0';
               this->extn = q+2;
               break;
              }
           }
         while(p >= file->FILENAME)
            *q-- = *p--;

         if(top==0)
           {
            top = this;
            break;
           }

         /* This first chain in the list is for directories */
         rc   = (top->attr & 0x10) == 0;
         prev = 0;
         next = top;
         if((this->attr & 0x10) == 0) /* This is NOT a directory */
           {
            if(rc == 0)
              {
               prev = top;
               next = top->next;
               if(!next)
                 {
                  top->next = this;
                  break;
                 }
              }  
            while((rc=strcmp(this->extn,next->extn)) > 0)
              {
               prev = next;
               next = next->next;
               if(!next) break; 
              }
           }
   
         if(rc != 0)
           {
            this->next = next;
            if(prev)
               prev->next = this;
            else
               top = this;
            break;
           }
   
         uppr = 0;
         lowr = next;
         next = lowr->next;
         while((rc=strcmp(this->name,lowr->name)) > 0)
           {
            uppr = lowr;
            lowr = lowr->kid;
            if(!lowr) break; 
           }

         if(top == lowr)
           {
            if(uppr || prev)
               printf("WHOOPS!  top==lowr but uppr=%p & prev=%p\n",uppr,prev);
            else
               if(FLAG(v))printf("Yes!  When top==lowr, uppr & prev are 0.\n");
           }

         this->kid = lowr;
         if(uppr)
            uppr->kid = this;
         else
           {
            this->next = next;
            if(prev)
               prev->next = this;
            else
               top = this;
           }

         break;
        }


      if(this!=NULL && FLAG(v)>2) vblock(this);

#ifdef DOS
      drtn = dnext(file);
#endif
     }

#ifdef DOS
   if(errno != EMFILE)
      printf("drtn=%d(%x), errno=%d(%x).\n",
              drtn,drtn,   errno,errno    );
#endif

   if(FLAG(v)>3)
     {
      vprint("bldtree exit");
      printf("   catname   = (%p) \"%s\"\n",catname,catname);
     }

   return 0;
}



/***************************
 * travel the catalog tree *
 ***************************/
int runtree(block)
 struct BLOCK *block;
{
   struct BLOCK *done;
   int          count;


   if(FLAG(v)>3)
     {
      vprint("runtree entry");
      printf("   extension = (%p) \"%s\"\n",block->extn,block->extn);
     }

#ifdef DOS
   if(block->attr & 0x10)
      printf(" dir:  ");
   else
      printf(" %-3.3s:  ",strupr(block->extn));
#else
   printf(   " %-3.3s:  ",       block->extn );
#endif
   count = 73;

   while(block)
     {
      if(FLAG(v)>4) vblock(block);

      if(count < 9)
        {
         count = 73;
         printf("\n       ");
        }
#ifdef DOS
      printf("%-8.8s ",strlwr(block->name));
#else
      printf("%-8.8s ",       block->name );
#endif
      count -= 9;

      done   = block;
      block  = block->kid;
      return_a_block(done);
     }
   printf("\n");

   if(FLAG(v)>3)
     {
      vprint("runtree exit");
      printf("   extension = (%p) \"%s\"\n",block->extn,block->extn);
     }

   return 0;
}
