/* This file contains the Simple File System API. */

/* Globals: */

int num_us;  /* Number of users */
int num_ds;  /* Number of directories per user */
int num_fs;  /* Number of files per directory */
int num_gs;  /* Number of groups including group 0. */
             /* When a user's group number is 0, */
             /* that user is in no group */

/* API Methods: */

/* Initialize global variables.  
   You may assume this gets called before any other SFS methods,
   and you may assume that this method gets called at most once.
   All parameters must be positive integers.
   This method returns -1 on error, 0 on success. */
int sfs_init(int us, int ds, int fs, int gs) {
  return -1;
}

/* Add the current user to the specified group.  
   The group_num parameter must be in the range 0..num_gs-1.
   When the group_num is 0, the user will belong to no group.
   If the user already belongs to a group, s/he gets removed from
   the old group and added to the new group.
   In the SFS, when a user's group changes, all of that user's files' 
   group permissions automatically get assigned to the user's new group. 
   This method returns -1 on error, 0 on success. */
int add2group(int group_num) {
  return -1;
}


/* Change the permissions associated with a file in the current directory.
   The file_num parameter must be in the range 0..num_fs-1, and 
   the other parameters must be in the range of 0..7.
   Important: Only the file's owner or a member of the file owner's current
   group (as long as the owner's group is nonzero) may change a file's 
   permissions.
   Return values:
   Returns -1 on paramter error (parameters not in proper range).
   Returns -2 on permissions error (access to change permissions is denied).
   Returns 0 on success (permissions successfully changed). */
int chmod(int file_num, int owner_permission, int group_permission, 
	  int universe_permission) {
  return -1;
}


/* Check permissions for opening a file in the current directory.
   The file_num parameter must be in the range 0..num_fs-1.
   The mode parameter must be 1, 2, or 4.
   When mode is 1, the file is being opened for executing.
   When mode is 2, the file is being opened for writing.
   When mode is 4, the file is being opened for reading.
   Note:
   Permission may be granted for this user based on the file's
   owner permission (i.e., the current user owns the file), or based on
   the file's group permission (i.e., the current user is in the same
   nonzero group as the file's owner), or based on the file's 
   universe permission.
   Return values:
   Returns -1 on paramter error (parameters not in proper range).
   Returns -2 on permissions error (access denied).
   Returns 0 on success (access granted). */
int fopen(int file_num, int mode) {
  return -1;
}


/* Switch the current user.  
   The user_num parameter must be in the range 0..num_us-1.
   For simplicity, any user can switch to any other (legal) user number.
   New user's initial current directory is that user's d0 directory.
   Returns -1 on error, 0 on success.
*/
int su(int user_num) {
  return -1;
}

/* Change the current user's current directory to the directory
   specified by the parameters.
   For simplicity assume that any user can change to any (legal)
   directory.
   The user_num parameter must be in the range 0..num_us-1.
   The dir_num parameter must be in the range 0..num_ds-1.
   This method returns -1 on error, 0 on success */
int cd(int user_num, int dir_num) {
  return -1;
}

/* Print the name of the current user's current directory */
void pwd() { 
}

/* Print the name of the current user. */
void whoami() { 
}

/* Example main method */
/* When the SFS API has been implemented, this main should 
   output the following:
   I am:   u0
   pwd is: /u0/d0/
   pwd is: /u2/d4/
   chmod access denied
   I am:   u2
   pwd is: /u0/d3/
   exe access denied
   I am:   u0
   pwd is: /u0/d3/
   exe access denied
   I am:   u1
   pwd is: /u0/d3/
   write access denied
   exe access denied
*/
int main() {
  sfs_init(5, 5, 5, 5);
  printf("I am:   "); whoami();
  printf("pwd is: "); pwd();
  cd(2, 4);
  printf("pwd is: "); pwd();
  if(chmod(0, 7, 7, 7)==-2) printf("chmod access denied\n");
  add2group(1);
  su(2);
  printf("I am:   "); whoami();
  add2group(1);
  cd(0, 3);
  printf("pwd is: "); pwd();
  if(chmod(3, 6, 2, 4)==-2) printf("chmod access denied\n");
  if(fopen(3, 4)==-2) printf("read access denied\n");
  if(fopen(3, 2)==-2) printf("write access denied\n");
  if(fopen(3, 1)==-2) printf("exe access denied\n");
  su(0);
  cd(0, 3);
  printf("I am:   "); whoami();
  printf("pwd is: "); pwd();
  if(fopen(3, 4)==-2) printf("read access denied\n");
  if(fopen(3, 2)==-2) printf("write access denied\n");
  if(fopen(3, 1)==-2) printf("exe access denied\n");
  su(1);
  cd(0, 3);
  printf("I am:   "); whoami();
  printf("pwd is: "); pwd();
  if(fopen(3, 4)==-2) printf("read access denied\n");
  if(fopen(3, 2)==-2) printf("write access denied\n");
  if(fopen(3, 1)==-2) printf("exe access denied\n");
}

