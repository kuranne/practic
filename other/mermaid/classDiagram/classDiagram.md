# Class Diagram

### Line

|Line|Relationship|Describe|Example|
|-|--|---|--|
|`--\|>`|Inheritance|Use for Extends|`Animal <\|-- Dog`|
|`..\|>`|Realization|Use for Interface|`iPayment <\|.. Credit Card `|
|`*--`|Composition|Each must being along with other like |`Home *-- Room`|
|`o--`|Aggregation|Temporary|`Student o-- Backpack`|
|`-->`|Directed Association|U know me but me n'know U| `Customer --> Order`|
|`--`|Link/Association|Know each other|`Me -- Friend`|
|`..>`|Dependency|Temporary Association|`Processor ..> Memory`|