#include "brightness.h"
void _print(const uint8_t fs , const char *s)
{
  write(fs, s, strlen(s));
}

void err( const char *s)
{
  _print(2, s);
}
void errl( const char *s)
{
  err(s);
  _print(2, "\n\0");
}

void out( const char *s)
{
  _print(1, s);
}

void outl( const char *s)
{
  out(s);
  _print(1, "\n\0");
}

void _print_argv(const int argc, const char *argv[])
{
#ifdef DEBUG
  char *s;
  errl("argv:");
  for (uint8_t i=0; i < argc; ++i){
    s=calloc(sizeof(argv[i])+64,1);
    strcat( s, "\t " );
    sprintf( s, "%hhu", i );
    strcat( s, ": " );
    strcat( s, argv[i] );
    errl(s);
    free(s);
  }
#endif
  return;
}

void usage(const int argc, const char *argv[])
{
  errl("");
  err("Usage: ");
  err(argv[0]);
  errl(" [INCREMENT|up|down]");
  errl("\tINCREMENT can be any integer on [-100,100]\\{0}.");
  errl("\tFor negative increments, prepend a negative sign.");
}

int8_t fork_safely(){
  pid_t pid;
  pid=fork();
  if (pid == -1){
    perror("FATAL: Unable to fork process");
    exit(1);
  }
  if (pid == 0){
    return 0;
  }
  return 1;
}

int main(const int argc, const char *argv[], const char *envp[])
{
  int8_t  retval    = 0;
  int16_t time      = MAX_TIME;
  int64_t increment = INT64_MIN;

  char    increment_s[8];
  char    time_s[8];
  
  /* const char *display_envp[]= { "DISPLAY=:0", (char *)0 }; */

  if (argc < 2){
    usage(argc,argv);
    return 1;
  }

  if ( strncmp(argv[1], "-h", 2 ) == 0 || strncmp(argv[1],"--help",2) == 0 ){

    usage(argc, argv);
    return 0;
  }

  if ( strncmp(argv[1], "up", 2 ) == 0) {

    increment = (int64_t) 10;

  } else if ( strncmp(argv[1], "down", 2 ) == 0) {

    increment = (int64_t) -10;

  } else {
    
    increment = (int64_t) strtol(argv[1],NULL,10);

  }

  if ( increment == INT64_MIN || increment == 0 || !(increment >= -100 || increment <= 100 ) ){

    err("INCREMENT='");
    err( argv[1] );
    errl("' is invalid; not on the interval [-100,100]\\{0} or unable to parse to an integer.");
    return 1;

  }

  if ( increment < 5 && increment > -5 ){

    time=MIN_TIME;

  } else if ( increment < 10 && increment > -10 ){

    time=MED_TIME;

  }

  sprintf(increment_s,"%+li",increment);
  sprintf(time_s,"%hi",time);

  if ( fork_safely() == 0 ){
    retval = execl("/usr/bin/xbacklight","-inc",increment_s,"-time",time_s,"-display",":0",NULL);

    if (retval == -1){

      errl("xbacklight call failed");
      return 1;

    }

  }

/*
 *   if ( fork_safely() == 0 ) {
 *     pause(1);
 *     retval = execl("/usr/bin/sudo","-u","gxg","/usr/bin/notify-send","--urgency=low","--expire-time=300","\"Backlight: $(xbacklight -get | cut -d . -f 1)%\"",NULL);
 *     if (retval == -1){
 * 
 *       errl("sudo notify-send call failed");
 *       return 1;
 * 
 *     }
 * 
 *   }
 */
  
  return 0;

}
