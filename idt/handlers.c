#include "handlers.h"

/* Handlers */

/* handler 0 */
void division_by_zero_handler()
{
  log_str("Division by zero!\n\r", information);
}

/* handler 3 */
void breakpoint_interrupt_handler()
{
  log_str("Breakpoint happened!\n\r", information);
}
