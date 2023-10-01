#ifdef DOS
#include <types.h>
#include <stat.h>
#include <time.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#endif

main(argc,argv)
 int argc;
 char **argv;
{
 struct stat sb;
 struct stat *sp = &sb;
 int rc;

 rc = stat(argv[1],sp);

 printf("stat for \"%s\" returned %d.\n",argv[1],rc);
 printf("   st_dev   = %9d (0x%X)\n",   sp->st_dev  ,sp->st_dev  );
 printf("   st_ino   = %9d (0x%X)\n",   sp->st_ino  ,sp->st_ino  );
 printf("   st_mode  = %9d (0x%X)\n",   sp->st_mode ,sp->st_mode );
 printf("   st_nlink = %9d (0x%X)\n",   sp->st_nlink,sp->st_nlink);
 printf("   st_uid   = %9d (0x%X)\n",   sp->st_uid  ,sp->st_uid  );
 printf("   st_gid   = %9d (0x%X)\n",   sp->st_gid  ,sp->st_gid  );
 printf("   st_rdev  = %9d (0x%X)\n",   sp->st_rdev ,sp->st_rdev );
 printf("   st_size  = %9ld (0x%lX)\n", sp->st_size ,sp->st_size );
 printf("   st_atime = %9ld (0x%lX) %s",sp->st_atime,sp->st_atime,ctime(&sp->st_atime));
 printf("   st_mtime = %9ld (0x%lX) %s",sp->st_mtime,sp->st_mtime,ctime(&sp->st_mtime));
 printf("   st_ctime = %9ld (0x%lX) %s",sp->st_ctime,sp->st_ctime,ctime(&sp->st_ctime));

 return 0;
}
