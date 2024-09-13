# Types

All custom types will be camel case.<br>
e.g.
```c
    typedef struct {

    } Entity;
```

# Functions

All functions will be snake case.<br>
e.g.
```c
    void some_func() {

    }
```

Any function that operates on a certain type will have its name prefixed with that type name.<br>
e.g.
```c
    void entity_update(Entity *entity) {

    }
```
