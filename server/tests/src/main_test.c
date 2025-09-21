#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void Main_WhenExecuted_OutputsHelloWorld(void)
{
    // FILE *fp;
    // char output[100];
    
    // fp = popen("../build/MultiplayerChat_Server", "r");
    // TEST_ASSERT_NOT_NULL(fp);
    
    // fgets(output, sizeof(output), fp);
    // pclose(fp);
    
    // TEST_ASSERT_EQUAL_STRING("Hello world", output);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(Main_WhenExecuted_OutputsHelloWorld);
    return UNITY_END();
}