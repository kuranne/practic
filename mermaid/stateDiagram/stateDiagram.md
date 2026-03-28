# State Diagram

### Start and End

- use `[*] --> X` for start point
- use `X --> [*]` for end point

### Composite States

Sometimes a major status might have several sub-statuses within it; for example, a "Processing" status could be broken down into "Reading file" or "Writing file."

use `state X { ... }` for grouping states

### Other

|Symbol|Meaning|
|--|:--|
|`<<choice>>`|like if-else|
|`<<fork>>`|multiple line of working branch|
|`<<join>>`|combine two each line together|
