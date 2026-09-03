#set text(font: "Arial Hebrew")
#show raw.where(block: true): block.with(
  fill: luma(240),
  inset: 10pt,
  radius: 4pt
)

= AplusB Programming

AplusB is from variable A and variable B with plus (+) operation.

#line(stroke: (cap: "round"))

Which can write in statement:

$$
A + B = C
$$

AplusB is most popular in compatitive programming, because AplusB is the simplest way to make people understand how to `input, operate, and output` the data.

This is an example of C++ code source to implement AplusB:

```cpp
// Tell compiler to link library (place function here.)
#include <iostream>

// Lazy to write std::<operation>
using namespace std;

int main()
{
  // Initial variables without value.
  int a; int b;
  // Recieve value from stdin then place in a, b in order
  cin >> a >> b;
  // Initial c with value from a + b operation
  int c = a + b;
  // Output via stdout
  cout << c << endl;
  // Return the value to tell supervisor that the program is exit with code 0 or meaning successful
  return 0;
}
```