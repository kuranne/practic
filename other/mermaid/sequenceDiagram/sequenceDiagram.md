# Sequence Diagram

### Syntax

`actor` use for main entity  
`participant` use for other entity  

Line `->>` is first action and `-->>` is second action  

`+` is Ok  
`-` is busy  

#### Box is use for grouping

```
box Name
...
end
```

#### Loop

```
loop Action
...
end
```

#### alt (if else)

```
alt Action
...
else Action
...
end
```
