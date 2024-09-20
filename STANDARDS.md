# Types/Variales

Variables should always be snake case.<br>
```c
int some_num = 12;
```

All custom types should be camel case.<br>
```c
typedef struct {

} Entity;
```

# Functions

All functions should be snake case.<br>
```c
void some_func() {

}
```

Any function that operates on a certain type will have its name prefixed with that type name.<br>
```c
void entity_update(Entity *entity) {

}
```
