/**
 * Start uIP-Tool utility for AUTO folder
 *
 * (c) 2018 by Matthias Arndt <marndt@asmsoftware.de>
 *
 * @file  startuip.c
 * @brief main
 */

#include <stdint.h>
#include <osbind.h>

#define _200HZ_TICK (*((volatile uint32_t *)0x4ba))

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

    Print("\r\n\033p   Start utility for uIP-Tool   \033q\r\n");
    Print("(c) 2018 by Matthias Arndt <marndt@asmsoftware.de>\r\n");

    while((Timer() - tmr) < 1000)
    {
        /* wait 5s */
    }

    flush_kbd();
	return 0;
}
