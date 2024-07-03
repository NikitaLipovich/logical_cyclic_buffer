# logical_cyclic_buffer

This project implements a cyclic buffer with capabilities for adding and extracting elements, as well as checking for overflow.
## Tutorial
Read in main.c from top to down function implementations:
1. put_char
2. get_char
3. description in prototype test_put
4. description in prototype test_get
5. all implementation run_tests
After this u must understand realization and tests which check realization logical_cyclic buffer

## Compilation

To compile the project, you can use any standard C compiler. Simply include all files and compile:

```bash
gcc main.c -o cyclic_buffer
```

## Tests

Automated tests are implemented in the project to verify the correct operation of the cyclic buffer.

### Running Tests

To run the tests, compile the project and execute the executable file. The tests will automatically verify the functionality of the buffer.

#### Without Enabled `DEBUG_TEST`:
```
Test 1 passed: Fill buffer and check overflow 

Test 2 passed: Get one element and add two more, overflow

Test 3 passed: Get two elements and add two more

Test 4 passed: Empty the buffer

Test 5 passed: Add two elements to empty buffer
```

#### With enabled `DEBUG_TEST`:
```
i: 0 st 0 end 1 counter: 1 1
i: 1 st 0 end 2 counter: 2 12
i: 2 st 0 end 3 counter: 3 123
i: 3 st 0 end 4 counter: 4 1234
i: 4 st 0 end 0 counter: 5 12345
buffer_overflow
1 1
2 2
3 3
4 4
5 5
Test 1 passed: Fill buffer and check overflow 

1
i: 0 st 1 end 0 counter: 4 12345
ret_get: 1 49
i: 0 st 1 end 1 counter: 5 62345
buffer_overflow
6 6
2 2
3 3
4 4
5 5
Test 2 passed: Get one element and add two more, overflow

2
i: 0 st 2 end 1 counter: 4 62345
3
i: 1 st 3 end 1 counter: 3 62345
ret_get: 3 51
i: 0 st 3 end 2 counter: 4 67345
i: 1 st 3 end 3 counter: 5 67845
6 6
7 7
8 8
4 4
5 5
Test 3 passed: Get two elements and add two more

buffer_overflow
4
i: 0 st 4 end 3 counter: 4 67845
5
i: 1 st 5 end 3 counter: 3 67845
6
i: 2 st 1 end 3 counter: 2 67845
7
i: 3 st 2 end 3 counter: 1 67845
8
i: 4 st 3 end 3 counter: 0 67845
container_empty
i: 5 st 3 end 3 counter: 0 67845
ret_get: � -2
Test 4 passed: Empty the buffer

i: 0 st 3 end 4 counter: 1 67815
i: 1 st 3 end 0 counter: 2 67812
6 6
7 7
8 8
1 1
2 2
Test 5 passed: Add two elements to empty buffer
```
