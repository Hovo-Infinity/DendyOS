#include "handlers.h"


/* Global variables*/

/* handler 0 */
char divbyzero[] = "Division by zero\n\r";

/* handler 3 */
char breakpoint[] = "Breakpoint happened\n\r";

/* Handlers */

/* handler 0 */
void division_by_zero_handler()
{
  put_str(divbyzero);
}

/* handler 3 */
void breakpoint_interrupt_handler()
{
  put_str(breakpoint);
}
