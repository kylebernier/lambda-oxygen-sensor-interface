# Programming Rules for C [WIP]

## Function Calls in Conditionals
Do not embed function calls within condition statments
```
if (max(a, b) > 10) {
    dosomething();
}
```
Instead do something like this
```
ret = max(a, b);
if (ret > 10) {
    dosomething();
}
```
This helps with debugging and stepping through code. It is also easier to read.

## Formatting

### Functions and Function Calls
```
int main(void)
{
    dostuff(a, b, c);

    return 0;
}
```

### If Statements and Similar
```
if (a == 1) {
    dostuff();
}
```
or
```
// Single line if if the contents is short
if (a == 1) dostuff();

// This is a bit too long
if (a == 1) dostuff(parameter1, parameter2, parameter3, parameter4);
```
Don't do this
```
if (a == 1)
    dostuff();
```

## Comments
Always have at least one space before comment text
```
/* Big Global comment
 * Extra info
 */

/* Global Comment */
int main(void)
{
    // Contained comment
    dostuff();

    return 0;
}
```

### Switches
```
switch (a) {
    case 1:
        dostuff();
        break;
    case 2;
        dosomething();
        break;
    default:
}
```

### Spacing
C File
```
/* Header Comments
 *
 */


#include <something.h>

#include "some.h"


#define stuff


/* Do stuff */
static void dostuff(void);
/ Do stuff 2*/
static void dostuff1(void);


static int global_var;
static int global_var1;
static int global_var2;

static char global_var;
static char global_var1;
static char global_var2;


/* Main function*/
int main(void)
{
    dostuff();

    return 0;
}

/* Do stuff */
static void dostuff(void)
{
    return 0;
}
```
H file
```
/* Header Comments
 *
 */


#include <something.h>

#include "some.h"


#define stuff


/* Do stuff */
void dostuff(void);
/ Do stuff 2*/
void dostuff1(void);


typedef struct this_struct {
    int a;
} ThisStruct_t;
```
Order of some stuff may change based on prereqs
