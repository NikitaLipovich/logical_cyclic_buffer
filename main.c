#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define TRUE    1
#define FALSE   0

#define DEBUG_TEST

#ifdef DEBUG_TEST
#define DEBUG_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

enum buffer_state { buffer_overflow = -1, OK = -3, container_empty = -2 };
const int size = 5;

char buffer[size];

struct Put {
    uint8_t i_start;
    uint8_t i_end;
    uint8_t fullness_counter;
};

Put put = {0, 0, 0};

int put_char(char c) {
    if ( (  put.i_start == put.i_end ) &&
            put.fullness_counter == size )
        return buffer_overflow;

    put.fullness_counter++;
    buffer[put.i_end] = c;

    if (++put.i_end >= size)
        put.i_end = 0;

    return OK;
}

int get_char() {
    if ((  put.i_start == put.i_end) &&
        (   !put.fullness_counter ) )
        return container_empty;

    if (put.i_start == size)
        put.i_start = 0;

    put.fullness_counter--;

    return buffer[put.i_start++];
}

void show_buff(uint8_t i);
uint8_t check_equal(const char *a, const char *b);
/*
 * Cyclic call put_char
 *     varables: times  - how much cycles
 *               val    - from which digit start iterate value
 *  return: return last state from last cycle or value if state not error
 */
int test_put(uint8_t times, char *val);
/*
 * Cyclic call get_char
 *     varables: times  - how much cycles
 *  return: return last state from last cycle or value if state not error
 */
int test_get(uint8_t times);

void run_tests(){

    // Test 1
    char c = '1';
    assert(test_put(size + 1, &c) == buffer_overflow);
    const char from1to5[] = "12345";
    assert(check_equal(buffer, from1to5));
    printf("Test 1 passed: Fill buffer and check overflow \n\n");

    // Test 2
    assert(test_get(1) != container_empty );
    c = '6';
    assert(test_put(2, &c) == buffer_overflow);
    const char after_get_one_and_put2[] = "62345";
    assert(check_equal(buffer, after_get_one_and_put2));
    printf("Test 2 passed: Get one element and add two more, overflow\n\n");

    // Test 3
    assert(test_get(2) != container_empty );
    c = '7';
    assert(test_put(2, &c) != buffer_overflow);
    const char after_get_two_and_put2[] = "67845";
    assert(check_equal(buffer, after_get_two_and_put2));
    printf("Test 3 passed: Get two elements and add two more\n\n");

    // Test 4
    assert(put.fullness_counter == size);
    assert(test_put(2, &c) == buffer_overflow);
    assert(put.fullness_counter == size);
    assert(test_get(6) == container_empty);
    assert(put.fullness_counter == 0);
    printf("Test 4 passed: Empty the buffer\n\n");

    // Test 5
    c = '1';
    test_put(2, &c);
    const char after_put_two_value[] = "67812";
    assert(check_equal(buffer, after_put_two_value));
    printf("Test 5 passed: Add two elements to empty buffer\n\n");
}

void show_buff(uint8_t i) {
    DEBUG_PRINT("i: %d st %d end %d counter: %d buffer: ", i, put.i_start, put.i_end, put.fullness_counter);
    for (uint8_t j = 0; j < size; j++) {
        DEBUG_PRINT("%c", buffer[j]);
    }
    DEBUG_PRINT("\n");
}

int test_put(uint8_t times, char *val) {
    DEBUG_PRINT("test_put times: %d val: %c\n", times, *val);
    (*val)--;
    for (uint8_t i = 0; i < times; i++) {
        if (put_char(++(*val)) == buffer_overflow) {
            DEBUG_PRINT("buffer_overflow\n");
            return buffer_overflow;
        }
        show_buff(i);
    }
    return OK;
}

int test_get(uint8_t times) {
    DEBUG_PRINT("test_get times: %d\n", times);
    int c;
    for (uint8_t i = 0; i < times; i++) {
        c = get_char();
        if (c == container_empty) {
            DEBUG_PRINT("container_empty\n");
        } else {
            DEBUG_PRINT("%c\n", (char)c);
        }
        show_buff(i);
    }

    DEBUG_PRINT("ret_get: %c %d\n", (char)c, c);
    return c;
}

uint8_t check_equal(const char *a, const char *b) {
    for (uint8_t i = 0; i < size; i++) {
        DEBUG_PRINT("%c %c\n", a[i], b[i]);
        if (a[i] != b[i])
            return FALSE;
    }
    return TRUE;
}

int main()
{
    run_tests();
    return 0;
}
