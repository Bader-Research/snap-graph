#if !defined(INTERNAL_TIMER_HEADER_)
#define INTERNAL_TIMER_HEADER_

extern double snap_runtime; /* Defined in utils.c */

#if defined(__MTA__) /* Platform options */

#include <sys/mta_task.h>
#include <machine/runtime.h>
static double timestamp0;
static void
tic (void)
{
  timestamp0 = ((double)mta_get_clock(0) / mta_clock_freq());
}
static double
toc (void)
{
  double t1 = ((double)mta_get_clock(0) / mta_clock_freq());
  return snap_runtime = t1 - timestamp0;
}

#else /* General platforms */

#include <time.h>
#if defined(CLOCK_PROCESS_CPUTIME_ID)
#define CLK CLOCK_PROCESS_CPUTIME_ID
#elif defined(CLOCK_REALTIME)
#define CLK CLOCK_REALTIME
#else
#error "Ugh. no clock."
#endif
static double t0;
double snap_runtime;
static double
ts2d (const struct timespec ts)
{
  return ts.tv_sec + 1.0e-9 * ts.tv_nsec;
}
static void
tic (void)
{
  struct timespec ts;
  clock_gettime (CLK, &ts);
  t0 = ts2d (ts);
}
static double
toc (void)
{
  struct timespec ts;
  clock_gettime (CLK, &ts);
  return snap_runtime = ts2d (ts) - t0;
}

#endif /* Platform options */

#endif /* INTERNAL_TIMER_HEADER_ */
