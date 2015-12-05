#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include "../include/define.h"

int getch(void)
{
             char   ch;
             int   error;
             static struct termios Otty, Ntty;

             fflush(stdout);
             tcgetattr(0, &Otty);
             Ntty = Otty;
             Ntty.c_iflag  =  0;
             Ntty.c_oflag  =  0;
             Ntty.c_lflag &= ~ICANON;
#if 1
            Ntty.c_lflag &= ~ECHO;
#else
            Ntty.c_lflag |=  ECHO;
#endif
            Ntty.c_cc[VMIN]  = CCHAR;
            Ntty.c_cc[VTIME] = CTIME;

#if 1
#define FLAG TCSAFLUSH
#else
#define FLAG TCSANOW
#endif

            if (0 == (error = tcsetattr(0, FLAG, &Ntty)))
            {
                       error  = read(0, &ch, 1 );
                       error += tcsetattr(0, FLAG, &Otty);
            }

            return (error == 1 ? (int) ch : -1 );
}
