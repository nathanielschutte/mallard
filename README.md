# Mallard
My dynamic memory allocator in C

## Author
Nathaniel Schutte

## Testing Use
### Install
```
make
```
### Run
- Run tests noramally
```
./bin/mallard
```
- Run and select allocation algorithm
```
./bin/mallard -a [index]
```
### Implemented algorithms
- First Fit (index = 0)

## Use
mal_setmemory(char* mem_set, size_t max_bytes) must be called, giving a pointer to a byte array (mem_set) of size max_bytes for use by all other functions
