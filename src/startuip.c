/**
 * Start uIPTool utility for AUTO folder
 *
 * (c) 2018 by Matthias Arndt <marndt@asmsoftware.de>
 *
 * @file  startuip.c
 * @brief main
 */

#include <stdint.h>
#include <osbind.h>

#define _200HZ_TICK (*((volatile uint32_t *)0x4ba))
#define _5s (200U * 5U)

typedef enum
{
    WAIT_FOR_INITIAL_INPUT,
    RUN_UIP_ONCE,
    RUN_UIP_LOOP,
    REPEAT_UIP,
    TERMINATE
} RunState;

static uint32_t timer_200_hz;

/**
 * @brief Read200hz
 * @attention Must be called in Supervisor mode.
 */
static void Read200hz(void)
{
    timer_200_hz = _200HZ_TICK;
}

static uint32_t Timer(void)
{
    Supexec(Read200hz);

    return timer_200_hz;
}

static void Print(const char *str)
{
    (void)Cconws(str);
    return;
}

/** @brief flush keyboard buffer */
static void flush_kbd(void)
{
    while(Bconstat(2) != 0)
    {
        (void)Bconin(2);
    }
}

int main(void)
{
    uint32_t tmr = Timer();
    int32_t errcode;

    RunState st = WAIT_FOR_INITIAL_INPUT;

    Print("\r\n\033p   Start utility for uIPTool   \033q\r\n");
    Print("(c) 2018 by Matthias Arndt <marndt@asmsoftware.de>\r\n");
    Print("[u] activate uIP-tool\r\n[r] activate uIP-tool with repetition\r\n[q] immedietaly quit\r\n");

    flush_kbd();

    do
    {
        switch(st)
        {

            case RUN_UIP_ONCE:
            case RUN_UIP_LOOP:

                errcode = Pexec(0, "UIP.TOS", 0, 0);

                if(errcode == -33)
                {
                    Print("ERROR: could not find UIP.TOS\r\n");
                    st = TERMINATE;
                }

                if(st == RUN_UIP_LOOP)
                {
                   Print("uIPTool will restart, press [q] to terminate\r\n");
                   tmr = Timer();
                   flush_kbd();
                   st = REPEAT_UIP;
                }
                else
                {
                    st = TERMINATE;
                }

            break;

            case REPEAT_UIP:
                if(Timer() - tmr > _5s)
                {
                    st = RUN_UIP_LOOP;
                }
                else if(Bconstat(2) != 0)
                {
                    uint32_t keycode = Bconin(2);
                    uint8_t ascii = (keycode & 0x000000FFUL);

                    if((ascii == 'q')||(ascii == 'Q'))
                    {
                        st = TERMINATE;
                    }

                    flush_kbd();
                }
                else
                {
                    /* wait for timeout */
                }

            break;

            case WAIT_FOR_INITIAL_INPUT:
                st = WAIT_FOR_INITIAL_INPUT;

                if(Timer() - tmr > _5s)
                {
                    st = TERMINATE;
                }
                else if(Bconstat(2) != 0)
                {
                    uint32_t keycode = Bconin(2);
                    uint8_t ascii = (keycode & 0x000000FFUL);

                    if((ascii == 'q')||(ascii == 'Q'))
                    {
                        st = TERMINATE;
                    }
                    else if((ascii == 'u')||(ascii == 'U'))
                    {
                        st = RUN_UIP_ONCE;
                    }
                    else if((ascii == 'r')||(ascii == 'R'))
                    {
                        st = RUN_UIP_LOOP;
                    }
                    else
                    {
                        /* key not handled */
                    }

                    flush_kbd();
                }
                else
                {
                    /* wait for timeout */
                }


            break;

            default:
                tmr = Timer();
                st = WAIT_FOR_INITIAL_INPUT;
            break;
        }

    }
    while(st != TERMINATE);

    flush_kbd();
	return 0;
}
